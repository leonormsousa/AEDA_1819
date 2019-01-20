#include "Empresa.h"
#include <map>
#include <utility>
#include <string>
#include <fstream>

/*!
 * Constructor of class Empresa. Initializes the company's name, zone, price per seat on the bus, the vector that contains the prices per zone and the map that has the number of zones that the bus has to go through to get from a certain zone to another(the elements of the pair).
 * @param nome string with the name of the company
 * @param zona string with the zone of the company
 * @param preco_pl price per set in occasional services
 * @param preco_nz vector of doubles containing the prices per number of zones
 * @param matriz map containing the number of zones the bus has to go through
 * */
Empresa::Empresa(string nome, string zona, double preco_pl, vector<double> preco_nz, map<pair<string, string>, int> matriz) : escolas(EscolaPtr(NULL))
{
	this->nome = nome;
	this->zona = zona;
	preco_por_lugar = preco_pl;
	preco_num_zonas = preco_nz;
	matriz_zonas = matriz;
}

/*!
 * Constructor of class Empresa. Gets the data by reading it from a text file. Initializes the company's name, zone, price per seat on the bus, the vector that contains the prices per zone and the map that has the number of zones that the bus has to go through to get from a certain zone to another(the elements of the pair).
 * @param nome_ficheiro string with the name of the file to load
 * */ 
Empresa::Empresa(string nome_ficheiro) : escolas(EscolaPtr(NULL))
{
	ifstream ficheiro;
	ficheiro.open(nome_ficheiro);
	if (ficheiro.fail())
	{
		cerr << "Input file opening failed." << endl;
		exit(1);
	}
	string nome, zona_emp, ppl;
	getline(ficheiro, nome);
	getline(ficheiro, zona_emp);
	getline(ficheiro, ppl);
	double preco_por_lugar = stod(ppl);;
	string aux;
	getline(ficheiro, aux);
	//vetor preco por zonas
	vector<double> preco_por_zonas;
	while (getline(ficheiro, aux))
	{
		if (aux == "")
			break;
		preco_por_zonas.push_back(stod(aux));
	}
	getline(ficheiro, aux);
	//map zonas->num_zonas
	map<pair<string, string>, int> matriz;
	while (getline(ficheiro, aux))
	{
		if (aux == "")
			break;
		string z1, z2, num_zonas;
		z1 = aux.substr(0, aux.find_first_of(" "));
		aux = aux.substr(aux.find_first_of(" ") + 1);
		z2 = aux.substr(0, aux.find_first_of(" "));
		num_zonas = aux.substr(aux.find_first_of(" ") + 1);
		pair<string, string> zonas = make_pair(z1, z2);
		matriz[zonas] = stoi(num_zonas);
	}
	this->nome = nome;
	this->zona = zona_emp;
	this->preco_por_lugar = preco_por_lugar;
	this->preco_num_zonas = preco_por_zonas;
	this->matriz_zonas = matriz;
	//adicionar veiculos regulares
	bool driver = false;
	bool garage = false;
	while (!driver && !garage && getline(ficheiro, aux))
	{
		if (aux == "." || aux=="")
			break;
		if (aux == "--")
		{
			driver = true;
			break;
		}
		if (aux == "++")
		{
			garage = true;
			break;
		}
		string id, capacidade, nome_escola, morada, diretor, motorista, repair;
		id = aux;
		getline(ficheiro, capacidade);
		getline(ficheiro, motorista);
		getline(ficheiro, repair);
		getline(ficheiro, nome_escola);
		adicionaVeiculo(id, stoi(capacidade), true);
		cout << repair << endl;
		if(repair == "Y")
			veiculos[verificaVeiculo(id)]->setUnderRepair(true);
		else
			veiculos[verificaVeiculo(id)]->setUnderRepair(false);
		getline(ficheiro, aux);
		if (aux == "")
			continue;
		getline(ficheiro, morada);
		getline(ficheiro, diretor);
		Escola esc(nome_escola, aux, morada, diretor);
		insereEscola(esc);
		EscolaPtr ptr = escolas.find_new(&esc);
		ServicoRegular* sr = dynamic_cast<ServicoRegular*>(veiculos[verificaVeiculo(id)]);
		sr->setEscola(ptr.getPtr());
		sr->setMotorista(motorista);
		getline(ficheiro, aux);
		//Utentes
		while (getline(ficheiro, aux))
		{
			if (aux == "")
				break;
			if (aux == "--")
			{
				driver = true;
				break;
			}
			if (aux == "++")
			{
				garage = true;
				break;
			}
			string nome=aux, zona, ee, subsidio;
			double mensalidade;
			getline(ficheiro, zona);
			getline(ficheiro, aux);
			mensalidade=stod(aux);
			getline(ficheiro, ee);
			//funcionario
			if (ee == "")
			{
				sr->addUtente(nome, zona, ptr.getPtr(), mensalidade);
				continue;
			}
			getline(ficheiro, subsidio);
			if (subsidio == "S")
				sr->addUtente(nome, zona, ptr.getPtr(), ee, true, mensalidade);
			else
				sr->addUtente(nome, zona, ptr.getPtr(), ee, false, mensalidade);
			getline(ficheiro, aux);
		}
	}
	//ServicosEspeciais
	getline(ficheiro, aux);
	while (!garage && !driver && getline(ficheiro, aux))
	{
		if (aux == "" || aux == "--" || aux == "++")
			break;
		string id=aux, capacidade, motorista, repair;
		getline(ficheiro, capacidade);
		adicionaVeiculo(id, stoi(capacidade), false);
		getline(ficheiro, motorista);
		getline(ficheiro, repair);
		if(repair == "Y")
			veiculos[verificaVeiculo(id)]->setUnderRepair(true);
		else
			veiculos[verificaVeiculo(id)]->setUnderRepair(false);
		ServicoEspecial* se = dynamic_cast<ServicoEspecial*>(veiculos[verificaVeiculo(id)]);
		se->setMotorista(motorista);
		while (getline(ficheiro, aux))
		{
			if (aux == "")
				break;
			if (aux == "--")
			{
				driver = true;
				break;
			}
			if (aux == "++")
			{
				garage = true;
				break;
			}
			string dia, mes, ano, ganho;
			dia = aux.substr(0, aux.find_first_of("."));
			aux= aux.substr(aux.find_first_of(".")+1);
			mes = aux.substr(0, aux.find_first_of("."));
			aux = aux.substr(aux.find_first_of(".")+1);
			ano = aux.substr(0, aux.find_first_of(" "));
			ganho= aux.substr(aux.find_first_of(" ") + 1);
			double distancia = (stod(ganho)) / (preco_por_lugar*stoi(capacidade));
			se->addServico(Date(stoi(dia), stoi(mes), stoi(ano)), distancia);
		}
	}
	//motoristas
	cout << "motoristas" << endl;
	while (!garage && getline(ficheiro, aux))
	{
		if (aux == "")
			break;
		if (aux == "++")
		{
			garage = true;
			break;
		}
		string nome;
		bool active=false, disponivel=false;
		nome = aux;
		getline(ficheiro, aux);
		if(aux == "1")
			active = true;
		getline(ficheiro, aux);
		if (aux == "1")
			disponivel = true;
		Motorista m(nome, active, disponivel);
		addMotorista(nome, active, disponivel);
		while (getline(ficheiro, aux))
		{
			cout  << aux << endl;
			if (aux == "")
				break;
			string dia, mes, ano, ganho;
			dia = aux.substr(0, aux.find_first_of("."));
			aux = aux.substr(aux.find_first_of(".") + 1);
			mes = aux.substr(0, aux.find_first_of("."));
			ano = aux.substr(aux.find_first_of(".") + 1);
			Date data(stoi(dia), stoi(mes), stoi(ano));
			m.addServico(data);
		}
	}
	bool stop = false;
	while(!stop && getline(ficheiro, aux))
	{	
		if (aux == "")
			break;
		string nome = aux;
		getline(ficheiro, aux);
		unsigned int distancia, disponibilidade;
		disponibilidade = stoi(aux);
		getline(ficheiro, aux);
		distancia = stoi(aux);
		Oficina o(nome, disponibilidade, distancia);
		adicionaOficina(o);
		while(getline(ficheiro, aux))
		{
			if (aux == "")
			{
				stop = true;
				break;
			}
			adicionaVeiculoOficina(nome, aux);
		}
	}
	ficheiro.close();
}

/*!Destructor of class Empresa. Eliminates the company's vehicles and attributes.*/
Empresa::~Empresa()
{
	for (size_t i = 0; i < veiculos.size(); i++)
		delete veiculos[i];
	veiculos.clear();
	while (!escolas.isEmpty())
	{
		EscolaPtr ptr = escolas.findMax();
		delete ptr.getPtr();
		escolas.remove(ptr);
	}
}

/*!
 * @return the zone where the company is located.
 * */
string Empresa::getZona() const
{
	return zona;
}

/*!
 * @return the company's name.
 * */
string Empresa::getNome() const 
{
	return nome; 
}

/*!
 * @return a vector with all the company's vehicles.
 * */
vector<Veiculo* > Empresa::getVeiculos() const 
{
	return veiculos;
}

/*!
 * @return the vector with all the clients' schools.
 * */
BST<EscolaPtr> Empresa::getEscolas() const
{
	return escolas;
}

/*!
* Inserts a school to the BST, if the school still isn't there
* @param e object of class Escola
* */
void Empresa::insereEscola(Escola e)
{
	Escola* ptr = new Escola();
	*ptr = e;
	EscolaPtr p = ptr;
	escolas.insert(p);
}

/*!
 * Calculates the monthly fee that corresponds to the number of zones between the client's school zone and the client's home zone.
 * @param e object of class Escola
 * @param z string with zone of client's home
 * @return price to pay per number of zones without discounts
 * */
double Empresa::calculaPrecoUtente(Escola e, string z)
{
	bool encontrouZonaInicial = false, encontrouZonaEscola = false;
	pair<string, string> zonas = make_pair(z, e.getZona());
	map<pair<string, string>, int>::const_iterator it;
//Verifies if the client's home zone exists.
	for (it = matriz_zonas.begin(); it != matriz_zonas.end(); it++)
	{
		if (it->first.first == z)
		{
			encontrouZonaInicial = true;
		}

	}
//Verifies if the school exists and has a valid location.
	for (it = matriz_zonas.begin(); it != matriz_zonas.end(); it++)
	{
		if (it->first.first == e.getZona())
		{
			encontrouZonaEscola = true;
		}

	}
//throws exception in case one of the zones doesn't exist.	
	if (!encontrouZonaInicial)
	{
		throw ZonaInexistente(z);
	}
	if (!encontrouZonaEscola)
	{
		throw ZonaInexistente(e.getZona());
	}

	int num_zonas = 0;
//Finds out how many zones does the bus go through between the initial zone (z) and the final zone (school e zone)
	for (auto it = matriz_zonas.begin(); it != matriz_zonas.end(); it++)
	{
		if (it->first == zonas)
			num_zonas = it->second;
	}
//Calculates the price the client has to pay	
	double preco_utente = preco_num_zonas[num_zonas];
	return preco_utente;
}

/*!
 * Allocates a new student in the company.
 * @param n string with the name of the student
 * @param z string with the zone of the student
 * @param e object of class Escola that is the school the student attends
 * @param ee string with the name of the student's tutor
 * @param sub boolean that is true if the student has social aid
 * */
void Empresa::alocaUtente(string n, string z, Escola e, string ee, bool sub)
{
	//Calls calculaPrecoUtente to calculate the price the student has to pay monthly.
	double preco_utente = calculaPrecoUtente(e, z);
	bool alocado = false, motorista_indisponivel=true;
	bool escola_inexistente = false;
	EscolaPtr found = escolas.find_new(EscolaPtr(&e));
	if (found.getPtr() == NULL)
	{

		escola_inexistente = true;
		insereEscola(e);
		found = escolas.find(&e);
	}
//Verifies if there is vacancies in the vehicle allocated to the school e.
	for(size_t i = 0; i < veiculos.size(); i++)
	{
		ServicoRegular* veiculoRegular = dynamic_cast<ServicoRegular*>(veiculos[i]);
		if (!veiculoRegular)
			continue;
		if (veiculoRegular->getEscola()!=NULL && *(veiculoRegular->getEscola()) == e)
			if (veiculoRegular->getUtentes().size() < veiculoRegular->getCapacidade())
			{	//If there is vacancies, calls addUtente to allocate the student to the right vehicle.
				veiculoRegular->addUtente(n, z, found.getPtr(), ee, sub, preco_utente);
				alocado=true;
				break;
			}
	}
//If the vehicle was full or there wasn't a vehicle assigned to that school yet, verifies if there is a vehicle with no school attributed in order to place the student in that vehicle.
	if(!alocado)
	{
		for (size_t i = 0; i < veiculos.size(); i++)
		{
			ServicoRegular* veiculoRegular = dynamic_cast<ServicoRegular*>(veiculos[i]);
			if (!veiculoRegular)
				continue;
			if (veiculoRegular->getUtentes().size() == 0)
			{
				if(veiculoRegular->getUnderRepair())
					continue;
				HashTabMotorista::iterator it = motoristas.begin();
				for (; it != motoristas.end(); it++)
				{
					if ((*it).getDisponivel() && (*it).getActive())
					{
						veiculoRegular->setEscola(found.getPtr());
						veiculoRegular->addUtente(n, z, found.getPtr(), ee, sub, preco_utente);
						veiculoRegular->setMotorista((*it).getName());
						Motorista m = (*it);
						motoristas.erase(it);
						m.setDisponivel(false);
						motoristas.insert(m);
						motorista_indisponivel = false;
						alocado = true;
						break;
					}
				}
				break;
			}
		}
	}
	if (!alocado)
	{
		if (escola_inexistente)
			escolas.remove(found);
		if (motorista_indisponivel)
		{
			Date data(1,1,1);
			throw MotoristaIndisponivel(data, true);
		}
		throw AlocacaoUtenteImpossivel(n);
	}
}

/*!
 * Allocates a new school employee in the company.
 * @param n string with the name of the employee
 * @param z string with the zone of the employee
 * @param e object of class Escola that is the school the employee works at
 * */
void Empresa::alocaUtente(string n, string z, Escola e)
{
	//Calls calculaPrecoUtente to calculate the price the employee has to pay monthly.
	bool motorista_indisponivel = true;
	double preco_utente = calculaPrecoUtente(e, z);
	bool alocado = false;
	bool escola_inexistente = false;
	EscolaPtr found;
	found = escolas.find_new(EscolaPtr(&e));
	if (found.getPtr()==NULL)
	{
		escola_inexistente = true;
		insereEscola(e);
		found = escolas.find(&e);
	}
//Verifies if there is vacancies in the vehicle allocated to the school e.
	for (size_t i = 0; i < veiculos.size(); i++)
	{
		ServicoRegular* veiculoRegular = dynamic_cast<ServicoRegular*>(veiculos[i]);
		if (!veiculoRegular)
			continue;
		if (veiculoRegular->getEscola() != NULL && (*veiculoRegular->getEscola()) == e)
			if (veiculoRegular->getUtentes().size() < veiculoRegular->getCapacidade())
			{	//If there is vacancies, calls addUtente to allocate the student to the right vehicle.
				veiculoRegular->addUtente(n, z, found.getPtr(), preco_utente);
				alocado = true;
				break;
			}
	}
//If the vehicle was full or there wasn't a vehicle assigned to that school yet, verifies if there is a vehicle with no school attributed in order to place the employee in that vehicle
	if(!alocado)
	for (size_t i = 0; i < veiculos.size(); i++)
	{
		ServicoRegular* veiculoRegular = dynamic_cast<ServicoRegular*>(veiculos[i]);
		if (!veiculoRegular)
			continue;
		if (veiculoRegular->getUtentes().size() == 0)
		{
			HashTabMotorista::iterator it = motoristas.begin();
			for (; it!=motoristas.end();it++)
			{
				if ((*it).getDisponivel() && (*it).getActive())
				{
					veiculoRegular->setEscola(found.getPtr());
					veiculoRegular->addUtente(n, z, found.getPtr(), preco_utente);
					veiculoRegular->setMotorista((*it).getName());
					Motorista m = (*it);
					motoristas.erase(*it);
					m.setDisponivel(false);
					motoristas.insert(m);
					motorista_indisponivel = false;
					alocado = true;
					break;
				}
			}
			break;
		}
	}
	if (!alocado)
	{
		if (escola_inexistente)
			escolas.remove(found);
		if(motorista_indisponivel)
		{
			Date data(1, 1, 1);
			throw MotoristaIndisponivel(data, true);
		}
		throw AlocacaoUtenteImpossivel(n);
	}
}

/*!
 * Removes a client from the company.
 * @param nome string with the name of the client to remove
 * */
void Empresa::removeUtente(string nome)
{
	bool encontrouUtente = false;
	vector<Utente *>::const_iterator it;
//Verifies if the client exists
	for (unsigned int i = 0; i < veiculos.size(); i++)
	{
		ServicoRegular* veiculoRegular = dynamic_cast<ServicoRegular*>(veiculos[i]);
		if (!veiculoRegular)
			continue;
		vector<Utente *> utentes = veiculoRegular->getUtentes();
		for (unsigned int j = 0; j < utentes.size(); j++)
		{
			if (utentes[j]->getNome() == nome)
			{
//If the client exists, calls eliminaUtente to remove the client from the records.
				encontrouUtente = true;
				EscolaPtr found = escolas.find_new(EscolaPtr(utentes[j]->getEscola()));
				veiculoRegular->eliminaUtente(j);
				(found.getPtr())->decreaseNumUtentes();
				if ((found.getPtr())->getNumUtentes() == 0)
				{
					delete found.getPtr();
					escolas.remove(found);
					veiculoRegular->setEscola(NULL);
				}
			}
		}
	}
//If the client doesn't exist, throws the exception UtenteInexistente.	
	if (!encontrouUtente)
		throw UtenteInexistente(nome);
}

/*!
 * Creates a new occasional service.
 * @param dia day of the service
 * @param mes month of the service
 * @param ano year of the service
 * @param distancia_Km distance in km of the service
 * @param n_pessoas number of students of the service
 * */
void Empresa::alocaServico(unsigned int dia, unsigned int mes, unsigned int ano, double distancia_Km, unsigned int n_pessoas)
{
	ordenaVeiculos();
	Date data(dia, mes, ano);
	for (size_t i = 0; i < veiculos.size(); i++)
	{
		ServicoEspecial* veiculoEspecial = dynamic_cast<ServicoEspecial*>(veiculos[i]);
		if (!veiculoEspecial)
			continue;

		map<Date, double> servicos = veiculoEspecial->getServicos();
		map<Date, double>::const_iterator it;
		it = servicos.find(data);
		if (it== servicos.end())
			if(veiculoEspecial->getCapacidade() >= n_pessoas)
			{
				cout << "1" << endl;
				HashTabMotorista::iterator ite = motoristas.begin();
				for (; ite != motoristas.end(); ite++)
				{
					Motorista mot = (*ite);
					cout << "2" << mot.getActive() << endl;
					if (mot.getActive() && mot.getDisponivel() && mot.addServico(data))
					{
						cout << "3"  << endl;
						motoristas.erase(ite);
						cout << "4" << endl;
						motoristas.insert(mot);
						cout << "5" << endl;
						veiculoEspecial->addServico(data, distancia_Km);
						cout << "6" << endl;
						veiculoEspecial->setMotorista(mot.getName());
						return;
					}
				}
				throw MotoristaIndisponivel(data, false);
			}
	}
	throw VeiculoIndisponivel(data, n_pessoas);
}

/*!
 * Adds a new vehicle to the company.
 * @param id string with the vehicle's id
 * @param capacidade number of seats of the vehicle
 * @param regular boolean that is true if it's a regular service vehicle
 * */
void Empresa::adicionaVeiculo(string id, unsigned int capacidade, bool regular)
{
	Veiculo *v;
//Verifies if the vehicle already exists and throws the exception VeiculoRepetido if it does
	if (verificaVeiculo(id) != -1)
		throw VeiculoRepetido(id);
//Creates a ServicoRegular vehicle or a ServicoEspecial vehicle depending on the boolean value of regular
	if(regular)
		v = new ServicoRegular(id, capacidade);
	else
		v = new ServicoEspecial(id, capacidade, preco_por_lugar);
//Adds the vehicle to the vector of vehicles the company owns.		
	veiculos.push_back(v);
}



/*!
 * @brief Removes an existing vehicle from the company. If the clients allocated to the vehicle can't be reallocated to another vehicle trows exception RemocaoVeiculoImpossivel.
 * @param id string with the vehicle's id to remove
 * */
void Empresa::removeVeiculo(string id)
{
	//Throws the exception VeiculoInexistente in case the vehicle received isn't a valid one.
	int pos_veiculo = verificaVeiculo(id);
	if (pos_veiculo==-1)
		throw VeiculoInexistente(id);
	if(veiculos[pos_veiculo]->getUnderRepair())
		throw VeiculoEmReparacao(id);
	ServicoRegular* veiculo = dynamic_cast<ServicoRegular*>(veiculos[pos_veiculo]);
	if (!veiculo)
	{
		delete veiculos[pos_veiculo];
		veiculos.erase(veiculos.begin() + pos_veiculo);
	}
	else
	{
		unsigned int lugares_disponiveis=0;
		for (size_t i=0; i < veiculos.size(); i++)
		{
			ServicoRegular* veiculoRegular = dynamic_cast<ServicoRegular*>(veiculos[i]);
			if (!veiculoRegular || i==(unsigned int)pos_veiculo)
				continue;
			if (veiculoRegular->getEscola() == veiculo->getEscola())
				lugares_disponiveis+=(veiculoRegular->getCapacidade() - veiculoRegular->getUtentes().size());
			else if (veiculoRegular->getUtentes().size()==0)
				lugares_disponiveis+= veiculoRegular->getCapacidade();
		}
		if (lugares_disponiveis<veiculo->getUtentes().size())
			throw RemocaoVeiculoImpossivel(veiculo->getId());
		cout << "ola" << endl;
		vector<Utente*> utentes;
		for (size_t i=0; i<veiculo->getUtentes().size(); i++)
		{
			Crianca* crianca = dynamic_cast<Crianca*>(veiculo->getUtentes()[i]);
			if (!crianca)
			{
				Funcionario* funcionario = dynamic_cast<Funcionario*>(veiculo->getUtentes()[i]);
				Utente* f= new Funcionario(funcionario->getNome(), funcionario->getZona(), funcionario->getEscola());
				utentes.push_back(f);
			}
			else
			{
				Utente* c= new Crianca(crianca->getNome(), crianca->getZona(), crianca->getEscola(), crianca->getEnc_Educacao(), crianca->getSubsidio());
				utentes.push_back(c);
			}

		}
		delete veiculos[pos_veiculo];
		veiculos.erase(veiculos.begin() + pos_veiculo);
		for (size_t i=0; i<utentes.size(); i++)
		{

			Crianca* crianca = dynamic_cast<Crianca*>(utentes[i]);
			if (!crianca)
			{
				Funcionario* funcionario = dynamic_cast<Funcionario*>(utentes[i]);
				alocaUtente(funcionario->getNome(), funcionario->getZona(), *(funcionario->getEscola()));
				delete(utentes[i]);
			}
			else
			{
				alocaUtente(crianca->getNome(), crianca->getZona(), *(crianca->getEscola()), crianca->getEnc_Educacao(), crianca->getSubsidio());
				delete(utentes[i]);
			}
		}
	}
}

/*!
 * Verifies if the vehicle with the id given exists.
 * @param id string with the vehicle's id
 * */
int Empresa::verificaVeiculo(string id)
{
	for(size_t i = 0; i < veiculos.size(); i++)
		if(veiculos[i]->getId() == id)
			return i;
	return -1;
}

/*!
 * Auxiliary function that returns true if the vehicle pointed by v1 is smaller then the vehicle pointed by v2.
 * @param v1 pointer to object of class Veiculo
 * @param v2 pointer to object of class Veiculo
 * @return true if v1 is minor than v2
 * */
bool veiculo_ptr_menor(Veiculo* v1, Veiculo *v2)
{
	return (*v1 < *v2);
}

/*!Sorts the company's vehicles using function veiculo_ptr_menor.*/
void Empresa::ordenaVeiculos()
{
	sort(veiculos.begin(), veiculos.end(), veiculo_ptr_menor);
}

/*!
 * Prints on the screen the company's earnings of a specific month and year.
 * @param mes month of special services' earnings to display
 * @param ano year of the month of special services' earnings to display
 * */
void Empresa::listaGanhos(unsigned int mes, unsigned int ano)
{
	double soma = 0;
	for (size_t i = 0; i < veiculos.size(); i++)
	{
		ServicoEspecial* veiculoEspecial = dynamic_cast<ServicoEspecial*>(veiculos[i]);
		if (!veiculoEspecial)
		{
			cout << veiculos[i]->getId() << ": " << veiculos[i]->calculaGanhos()<<endl;
			soma += veiculos[i]->calculaGanhos();
		}
		else
		{
			cout << veiculoEspecial->getId() << ": " << veiculoEspecial->calculaGanhos(mes, ano)<<endl;
			soma += veiculoEspecial->calculaGanhos(mes, ano);
		}
	}
	cout << "Total no mes " <<mes<< " do ano " << ano <<": " << soma << endl<<endl;
}

/*!
 * Prints on the screen the company's profit of a specific year.
 * @param ano year of special services' earnings to display
 * */
void Empresa::listaGanhos(unsigned int ano)
{
	double soma = 0;
	for (size_t i = 0; i < veiculos.size(); i++)
	{
		ServicoEspecial* veiculoEspecial = dynamic_cast<ServicoEspecial*>(veiculos[i]);
		if (!veiculoEspecial)
		{
			soma += 12 * veiculos[i]->calculaGanhos();
			cout << veiculos[i]->getId() << ": " << soma << "(" << veiculos[i]->calculaGanhos()  << " mensais) " <<endl;
			
		}
		else
		{
			cout << veiculoEspecial->getId() << ": " << veiculoEspecial->calculaGanhos(ano)<<endl;
			soma += veiculoEspecial->calculaGanhos(ano);
		}
	}
	cout << "Total no ano " << ano << ": " << soma << endl<<endl;
}

/*!Prints on the screen a list of all the company's clients.*/
void Empresa::listaUtentes()
{
	for (size_t i= 0; i < veiculos.size(); i++)
	{
		ServicoRegular* veiculoRegular = dynamic_cast<ServicoRegular*>(veiculos[i]);
		if (!veiculoRegular)
			continue;
		for (size_t j = 0; j < veiculoRegular->getUtentes().size(); j++)
			cout << veiculoRegular->getUtentes()[j]->getNome() << endl;
	}
}

/*!Prints on the screen a list of all the school associated with the company.*/
void Empresa::listaEscolas()
{
	escolas.printTree();
}

/*!
 * Defines operator << for class Empresa and outputs the company's name, zone, price per seat on the bus, prices per zone and how many zones the bus has to go through from one zone to another.
 * @param out ostream reference
 * @param e object reference of class Empresa
 * */
ostream & operator<<(ostream &out, Empresa & e)
{
	e.ordenaVeiculos();
	out << e.getNome() << endl << e.getZona() << endl << e.getPrecoPorLugar() << endl << endl;
	for (size_t i = 0; i < e.getPrecoNumZonas().size(); i++)
		out << e.getPrecoNumZonas()[i] << endl;
	out << endl;
	map<pair<string, string>, int>::const_iterator it;
	map<pair<string, string>, int> matriz = e.getMatrizZonas();
	for (it = matriz.begin(); it != matriz.end(); it++)
		out << it->first.first << " " << it->first.second << " " << it->second << endl;
	out << endl;
	int ctrl=1;
	for (size_t i = 0; i <e.getVeiculos().size(); i++)
	{

		ServicoEspecial* veiculoEspecial = dynamic_cast<ServicoEspecial*>(e.getVeiculos()[i]);
		if (veiculoEspecial)
		{
			if(ctrl==1)
				out<<"."<<endl;
			out << *veiculoEspecial << endl;
			ctrl=0;
		}

		else
		{
			ServicoRegular* veiculoRegular = dynamic_cast<ServicoRegular*>(e.getVeiculos()[i]);
			if (veiculoRegular)
				out << *veiculoRegular << endl;
		}
	}
	ctrl = 1;
	vector<Motorista> motorista = e.getMotoristas();
	for (size_t i = 0; i < motorista.size(); i++)
	{
		if (ctrl == 1)
			out << "--" << endl;
		out << motorista[i].getName() << endl << motorista[i].getActive() << endl << motorista[i].getDisponivel() << endl;
		for (size_t j = 0; j < motorista[i].getServicos().size(); j++)
			out << motorista[i].getServicos()[j] << endl;
		ctrl = 0;
		out << endl;
	}
	ctrl = 1;
	priority_queue<Oficina> temp = e.getOficinas();
	while(!temp.empty())
	{
		if(ctrl == 1)
			out << "++" << endl;
		ctrl = 0;
		out << temp.top() << endl;
		temp.pop();
	}
	return out;
}

/*!Prints to a text file the information about a company.*/
void Empresa::imprimeEmpresa()
{
	string nome_ficheiro = nome;
	nome_ficheiro.append(".txt");
	ofstream ficheiro;
	ficheiro.open(nome_ficheiro);
	if (ficheiro.fail())
	{
		cerr << "Output file opening failed." << endl;
		exit(1);
	}
	ficheiro << *this;
	ficheiro.close();
}

/*!
 * Verifies if the driver already exists
 * @param Motorista driver we want to verify
 * @return true if the driver exists
 * */
bool Empresa::verificaMotorista(const Motorista& motorista) const
{
	HashTabMotorista::const_iterator it = motoristas.find(motorista);
	if (it == motoristas.end())
		return false;
	else
		return true;
}

/*!
 * Auxiliary function that returns true if the vehicle pointed by v1 is smaller then the vehicle pointed by v2.
 * @param name string that represents the driver's name
 * @param active bool that indicates if its a current or former driver
 * @return true if the driver was successfully added
 * */
bool Empresa::addMotorista(string name, bool active, bool available)
{
	Motorista motorista(name, active, available);
	if (!verificaMotorista(motorista))
	{
		motoristas.insert(motorista);
		return true;
	}
	throw MotoristaRepetido(name);
}

bool Empresa::removeMotorista(string name)
{
	HashTabMotorista::const_iterator it = motoristas.begin();
	for (; it!= motoristas.end(); it++)
	{
		if ((*it).getName() == name)
		{
			motoristas.erase(it);
			return true;
		}
	}
	throw MotoristaInexistente(name);
	//return false;
}

/*!
 * @return a vector with all the company's drivers.
 * */
vector<Motorista> Empresa::getMotoristas() const
{
	vector<Motorista> motorista;
	HashTabMotorista::const_iterator it = this->motoristas.begin();
	HashTabMotorista::const_iterator ite = this->motoristas.end();
	for (; it != ite; it++)
		motorista.push_back(*it);
	return motorista;
}

/*!
 * @return a vector with all the company's active drivers.
 * */
vector<Motorista> Empresa::getActiveMotoristas() const
{
	vector<Motorista> mot, motorista = getMotoristas();
	for (size_t i = 0; i < motorista.size(); i++)
	{
		if (motorista[i].getActive())
			mot.push_back(motorista[i]);
	}
	return mot;
}

/*!
 * @return a vector with all the company's inactive drivers.
 * */
vector<Motorista> Empresa::getInactiveMotoristas() const
{
	vector<Motorista> mot, motorista = getMotoristas();
	for (size_t i = 0; i < motorista.size(); i++)
	{
		if (!motorista[i].getActive())
			mot.push_back(motorista[i]);
	}
	return mot;
}

/*!Prints on the screen a list of all the current and former drivers of the company.*/
void Empresa::listaMotoristas()
{
	vector<Motorista> motorista = getMotoristas();
	for (size_t i = 0; i < motorista.size(); i++)
	{
		if (motorista[i].getActive())
			cout << "Name: " << setw(15) << motorista[i].getName() << "\t Ativo" << endl;
		else
			cout << "Name: " << setw(15) << motorista[i].getName() << "\t Inativo" << endl;
	}
}

/*!Prints on the screen a list of all the current drivers of the company.*/
void Empresa::listaMotoristasAtivos()
{
	vector<Motorista> motorista = getMotoristas();
	for (size_t i = 0; i < motorista.size(); i++)
	{
		if (motorista[i].getActive())
			cout << motorista[i].getName() << endl;
	}
}

/*!Prints on the screen a list of all the former drivers of the company.*/
void Empresa::listaMotoristasInativos()
{
	vector<Motorista> motorista = getMotoristas();
	for (size_t i = 0; i < motorista.size(); i++)
	{
		if (!motorista[i].getActive())
			cout << motorista[i].getName() << endl;
	}
}

/*!
 * Associates a garage to the company
 * @param nome garage's name
 * @param distancia distance between the garage and the company's garage
 */
void Empresa::adicionaOficina(string nome, unsigned int distancia)
{
	if(!verificaOficina(nome))
	{
		Oficina o(nome, 0, distancia);
		oficinas.push(o);
	}
	else
		throw OficinaRepetida(nome);
}

/*!
 * Associates a garage to the company
 * @param o object of class Oficina
 */
void Empresa::adicionaOficina(Oficina o)
{
	if(!verificaOficina(o.getNome()))
	{
		oficinas.push(o);
	}
	else
		throw OficinaRepetida(nome);
}

/*!
 * Removes a garage from the company
 * @param nome garage's name
 */
void Empresa::removeOficina(string nome)
{

	vector<Oficina> temp;

	while(!oficinas.empty())
	{
		if(oficinas.top().getNome() == nome)
		{
			if(oficinas.top().getDisponibilidade() == 0)
			{
				oficinas.pop();
				for(size_t i = 0; i < temp.size(); i++)
				{
					oficinas.push(temp[i]);
				}
				return;
			}
			else
			{
				for(size_t i = 0; i < temp.size(); i++)
				{
					oficinas.push(temp[i]);
				}
				throw OficinaComVeiculos(nome);
			}
		}
		temp.push_back(oficinas.top());
		oficinas.pop();
	}

	throw OficinaInexistente(nome);
}

/*!
 * Verifies if a garage is associated wit the company
 * @param nome garage's name
 */
bool Empresa::verificaOficina(string nome)
{
	priority_queue<Oficina> temp = oficinas;

	while(!temp.empty())
	{
		if(temp.top().getNome() == nome)
		{
			return true;
		}
		temp.pop();
	}

	return false;
}

/*!
 * Adds vehicle to the most suitable garage
 * @param id id of the vehicle
 * @param distancia_max maximum distance of the garage to add the vehicle to
 * @return string with the name of the garage where the vehicle is going to be repaired
 */
string Empresa::adicionaVeiculoOficina(string id, unsigned int distancia_max)
{
	vector<Oficina> temp;
	string nome = "";

	if(verificaVeiculo(id) == -1)
		throw VeiculoInexistente(id);
	
	if(veiculos[verificaVeiculo(id)]->getUnderRepair())
		throw VeiculoJaEmReparacao(id);
	else
		veiculos[verificaVeiculo(id)]->setUnderRepair(true);

	Veiculo* v = veiculos[verificaVeiculo(id)];

	while(!oficinas.empty())
	{
		if(oficinas.top().getDistancia() < distancia_max)
		{
			Oficina o = oficinas.top();
			nome = o.getNome();
			oficinas.pop();
			o.adicionaVeiculo(v);
			adicionaOficina(o);
			break;
		}
		temp.push_back(oficinas.top());
		oficinas.pop();
	}

	if(temp.size() == oficinas.size())
		throw OficinaMuitoLonge(distancia_max);

	for(size_t i = 0; i < temp.size(); i++)
	{
		oficinas.push(temp[i]);
	}
	return nome;
}

/*!
 * Adds vehicle to the a specific garage
 * @param id id of the vehicle
 * @param nome garage's name
 */
void Empresa::adicionaVeiculoOficina(string nome, string id)
{
	vector<Oficina> temp;

	if(verificaVeiculo(id) == -1)
		throw VeiculoInexistente(id);

	if(veiculos[verificaVeiculo(id)]->getUnderRepair())
		throw VeiculoJaEmReparacao(id);
	else
		veiculos[verificaVeiculo(id)]->setUnderRepair(true);

	Veiculo* v = veiculos[verificaVeiculo(id)];

	while(!oficinas.empty())
	{
		if(oficinas.top().getNome() == nome)
		{
			Oficina o = oficinas.top();
			oficinas.pop();
			o.adicionaVeiculo(v);
			adicionaOficina(o);
			break;
		}
		temp.push_back(oficinas.top());
		oficinas.pop();
	}

	for(size_t i = 0; i < temp.size(); i++)
	{
		oficinas.push(temp[i]);
	}
}

/*
 * Forwards the time by a specific number of days, considering that each garage repairs one vehicle per day, which means each garage repairing as much vehicles as the number of days
 * @param dias number of  days to fast forward, meaning number of cars getting repaired in each garage
 */
void Empresa::avancarDias(unsigned int dias)
{
	Oficina o;
	priority_queue<Oficina> temp;
	while(!oficinas.empty())
	{
		o = oficinas.top();
		for(size_t i = 0; i < dias && i < o.getVeiculos().size(); i++)
		{
			veiculos[verificaVeiculo(o.getVeiculos().front()->getId())]->setUnderRepair(false);
			o.reparaVeiculo();
		}

		temp.push(o);
		oficinas.pop();
	}
	oficinas = temp;
}

/*!
 * Prints on the screen the name of the garage's associated with the company
 */
void Empresa::listaOficinas()
{
	priority_queue<Oficina> temp = oficinas;
	while(!temp.empty())
	{
		cout << "Oficina: " << setw(15) << temp.top().getNome() << " \t Veiculos para reparar: " << setw(10) <<temp.top().getDisponibilidade() << endl;
		temp.pop();
	}
}
