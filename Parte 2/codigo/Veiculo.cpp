#include "Veiculo.h"

/*!
 * Constructor for class Veiculo. Initializes the vehicle's id and capacity.
 * @param i string with the vehicle's id
 * @param cap number of seats of the vehicle
 * */
Veiculo::Veiculo(string i, int cap)
{
	id = i;
	capacidade = cap;
	underRepair = false;
}

/*!
 * @return the vehicle's ID
 * */
string Veiculo::getId() const
{
	return id;
}

/*!
 * @return the vehicle's capacity
 * */
unsigned int Veiculo::getCapacidade() const
{
	return capacidade;
}

/*!
 * @return the name of the vehicle's driver
 * */
string Veiculo::getMotorista()
{
	return motorista;
}

/*!
 * @return true if the vehicle is under repair
 */
bool Veiculo::getUnderRepair() const { return underRepair; }

/*!
 * sets underRepair true if the vehicle is in a garage being repaired
 */
void Veiculo::setUnderRepair(bool repair)
{
	underRepair = repair;
}

/*!
 * Sets the vehicle's driver name
 * @param name driver's name
 * */
void Veiculo::setMotorista(string name)
{
	motorista = name;
}

/*!
 * Constructor for derived class ServicoRegular. Creates a vehicle with id i and capacity cap.
 * @param i string with the vehicle's id
 * @param cap number of seats of the vehicle
 * */
ServicoRegular::ServicoRegular(string i, int cap) :Veiculo(i, cap) 
{}

/*!Destructor for class ServicoRegular. Deletes the vector of clients allocated to the vehicle.*/
ServicoRegular::~ServicoRegular()
{
	for (size_t i = 0; i < utentes.size(); i++)
	{
		delete utentes[i];
	}
}

/*!
 * Adds a student to the vehicle's vector of clients.
 * @param n string with the name of the student
 * @param z string with the zone of the student
 * @param e object of class Escola that is the school the student attends
 * @param ee string with the name of the student's tutor name
 * @param sub boolean that is true if the student has social aid
 * @param preco_utente price per number of zones without discounts
 * */
void ServicoRegular::addUtente(string n, string z, Escola *e, string ee, bool sub, double preco_utente)
{
//Verifies if the student is already allocated to this vehicle.
	if (verificaUtente(n) != -1)
		throw UtenteRepetido(n);
//If he isn't, creates the student and adds him to the vehicle's clients.
	Utente* novo = new Crianca(n,z,e,ee,sub);
	novo->setMensalidade(preco_utente);
	utentes.push_back(novo);
	e->increaseNumUtentes();
}

/*!
 * Adds a school employee to the vehicle's vector of clients.
 * @param n string with the name of the employee
 * @param z string with the zone of the employee
 * @param e object of class Escola that is the school the employee works at
 * @param preco_utente price per number of zones without discounts
 * */
void ServicoRegular::addUtente(string n, string z, Escola *e, double preco_utente)
{
/*!Verifies if the employee is already allocated to this vehicle. If the student is repeated, it throws the exception UtenteRepetido*/
	if (verificaUtente(n) != -1)
		throw UtenteRepetido(n);
/*!If he isn't, creates the employee and adds him to the vehicle's clients.*/
	Utente* novo = new Funcionario(n, z, e);
	novo->setMensalidade(preco_utente);
	utentes.push_back(novo);
	e->increaseNumUtentes();
}

/*!
 * Sets the vehicle's destination school.
 * @param esc object of class Escola
 * */
void ServicoRegular::setEscola(Escola *esc)
{
	escola = esc;
}

/*!
 * @return the school to which the vehicle is allocated
 * */
Escola* ServicoRegular::getEscola() const
{
	return escola;
}

/*!
 * Verifies if the client of name name already exists allocated to this vehicle.
 * @param name string with the name of the client
 * @return the index of the client in the vector of clients in a regular service's vehicle; -1 if the client was not found
 * */
int ServicoRegular::verificaUtente(string name)
{
	int resp = -1;
	for (size_t i = 0; i < utentes.size(); i++)
		if (utentes[i]->getNome() == name)
			resp = i;
	return resp;
}

/*!
 * Calculates the monthly earnings of the vehicle.
 * @return the earnings of a regular service's vehicle
 * */
double ServicoRegular::calculaGanhos()
{
	double soma = 0;
/*!Sums up all the monthly fees paid by the clients allocated to the vehicle.*/
	for (size_t i = 0; i < utentes.size(); i++)
		soma += utentes[i]->getMensalidade();
	return soma;
}

/*!
 * Eliminates a client allocated to the vehicle.
 * @param index index of the client in the vector
 * */
void ServicoRegular::eliminaUtente(unsigned int index)
{
	delete utentes[index];
	vector<Utente *>::const_iterator it=utentes.begin();
	utentes.erase(it + index);
}

/*!
 * @eturn the vector that contains all the clients allocated to the vehicle
 * */
vector<Utente *> ServicoRegular::getUtentes()  
{ 
	return utentes;
}

/*!
 * Auxiliary function that returns true if the client pointed by u1 is smaller then the client pointed by u2.
 * @param u1 pointer to object of class Utente
 * @param u2 pointer to object of class Utente
 * @return true if u1 is minor than u2
 * */
bool utente_ptr_menor(Utente *u1, Utente *u2)
{
	return (*u1 < *u2);
}

/*!Sorts the vehicle's clients using function utente_ptr_menor.*/
void ServicoRegular::ordenaUtentes()
{
	sort(utentes.begin(), utentes.end(), utente_ptr_menor);
}

/*!
 * Defines the operator << for the class ServicoRegular and outputs the information of a regular service vehicle (id, capacity, the school to which it is allocated, the vehicle's monthly earnings and the client's allocated to it).
 * @param out ostream reference
 * @param s object reference of regular service's vehicle
 * */
ostream & operator<<(ostream &out, ServicoRegular& s)
{
	s.ordenaUtentes();
	out << s.getId() << endl << s.getCapacidade() << endl << s.getMotorista() << endl;
	if(s.getUnderRepair())
		out << 'Y' << endl;
	else
		out << 'N' << endl;
	if (s.getEscola() == NULL)
		{
			out << endl;
		}
	else
		{
			out << *(s.getEscola()) << endl;
		}
	for (size_t i = 0; i < s.getUtentes().size(); i++)
	{
		Crianca* crianca = dynamic_cast<Crianca*>(s.getUtentes()[i]);
		if (crianca)
			out << *crianca << endl;
		else
		{
			Funcionario* funcionario = dynamic_cast<Funcionario*>(s.getUtentes()[i]);
			if (funcionario)
				out << *funcionario << endl;
		}
	}
	if(s.getUtentes().size() == 0)
		out << endl;
	return out;
}

/*!
 * Defines the operator < for class ServicoRegular as a comparison between the earnings and ids of the vehicles
 * @param v2 object reference of class Veiculo
 * @return true if the vehicle v2 is a Special Service vehicle (we want to sort the vector of vehicles by type first) or if the profit from v2 is less than the profit from the vehicle. If the profit is the same, returns true if the vehicle's id is "smaller" than the v2's id.
 * */
bool ServicoRegular::operator<(Veiculo &v2)
{
	ServicoRegular* v2_ptr = dynamic_cast<ServicoRegular*>(&v2);
	if (!v2_ptr)
		return true;
	if (calculaGanhos() == v2.calculaGanhos())
		return (id < v2.getId());
	return (calculaGanhos() > v2.calculaGanhos());
}

/*!
 * Constructor for derived class ServicoEspecial. Creates a vehicle and calculates and initializes the total price.
 * @param i string with the id of the vehicle
 * @param cap number of seats of the vehicle
 * @param preco_por_lugar price per seat of the vehicle
 * */
ServicoEspecial::ServicoEspecial(string i, int cap, double preco_por_lugar):Veiculo(i,cap)
{
	preco_total_porKm = cap * preco_por_lugar;
}

/*!
 * Adds a new service made by the vehicle to the number of services made in that month.
 * @param data object reference of class Date that is the date of the service
 * @param distancia_km distance of the service
 * */
void ServicoEspecial::addServico(const Date &data, double distancia_km)
{
	servicos[data] = preco_total_porKm*distancia_km;
}

/*!
 * Calculates the total earnings of the vehicle for the month and year in the arguments.
 * @param mes month of the earnings to calculate
 * @param year of the month of the earnings to calculate
 * @return the earnings of a specific month and year
 * */
double ServicoEspecial::calculaGanhos(unsigned int mes,unsigned int ano)
{
	double soma = 0;
	map< Date, double>::iterator it;
	for (it = servicos.begin(); it != servicos.end(); it++)
	{
		if (it->first.getMes() == mes && it->first.getAno() == ano)
			soma = it->second;
	}
	return soma;
}

/*!
 * Calculates the total earnings of the vehicle for the year in the argument.
 * @param year of the earnings to calculate
 * @return the earnings of a specific year
 * */
double ServicoEspecial::calculaGanhos(unsigned int ano)
{
	double soma = 0;
	map< Date, double>::iterator it;
	for (it = servicos.begin(); it != servicos.end(); it++)
	{
		if (it->first.getAno() == ano)
			soma = it->second;
	}
	return soma;
}

/*!
 * Calculates the total earnings of the vehicle since it entered the company.
 * @return the earnings of the special service's vehicle
 * */
double ServicoEspecial::calculaGanhos()
{
	double soma = 0;
	map< Date, double>::iterator it;
	for (it = servicos.begin(); it != servicos.end(); it++)
		soma = it->second;
	return soma;
}

/*!
 * Defines the operator << for the class ServicoEspecial and outputs the information of a special service vehicle (id, capacity and all the services that the vehicle has made(sorted by date)).
 * @param out ostream reference
 * @param s object reference of class ServicoEspecial
 * */
ostream & operator<<(ostream &out, ServicoEspecial& s)
{
	out << s.getId() << endl << s.getCapacidade() << endl << s.getMotorista() << endl;
	if(s.getUnderRepair())
		out << 'Y' << endl;
	else
		out << 'N' << endl;
	map<Date, double> servicos = s.getServicos();
	while (!servicos.empty())
	{
			out << servicos.begin()->first << " " << servicos.begin()->second << endl;
			servicos.erase(servicos.begin());
	}
	return out;
}

/*!
 * Defines the operator < for class ServicoEspecial as a comparison between the earnings and ids of the vehicles
 * @return true if the vehicle's capacity is inferior to the v2's capacity. If the capacity is equal, compares the vehicles iD's.
 * */
bool ServicoEspecial::operator<(Veiculo &v2)
{
	ServicoEspecial* v2_ptr = dynamic_cast<ServicoEspecial*>(&v2);
	if (!v2_ptr)
		return false;
	if (capacidade == v2.getCapacidade())
	{
		if (calculaGanhos() == v2.calculaGanhos())
			return (id < v2.getId());
		return (calculaGanhos() > v2.calculaGanhos());
	}
	return (capacidade < v2.getCapacidade());
}
