#include <iostream>
#include "Empresa.h"
#include "Data.h"
using namespace std;

void funcionalidades(Empresa &p)
{
	while (true)
	{
	  try
	  {
		int option;
		cout << endl << "Opcoes:" << endl;
		cout << "1 - Adicionar Veiculo " << endl;
		cout << "2 - Adicionar Utente " << endl;
		cout << "3 - Adicionar servico ocasional " << endl;
		cout << "4 - Adicionar motorista " << endl;
		cout << "5 - Adicionar Oficina " << endl;
		cout << "6 - Reparar Veiculo" << endl;
		cout << "7 - Remover Veiculo " << endl;
		cout << "8 - Remover Utente " << endl;
		cout << "9 - Remover Motorista " << endl;
		cout << "10 - Remover Oficina " << endl;
		cout << "11 - Avancar dias e reparar veiculos" << endl;
		cout << "12 - Listar ganhos num determinado periodo" << endl;
		cout << "13 - Listar os utentes da empresa" << endl;
		cout << "14 - Listar as escolas asssociadas a empresa" << endl;
		cout << "15 - Listar os motoristas da empresa" << endl;
		cout << "16 - Listar os motoristas ativos da empresa" << endl;
		cout << "17 - Listar os motoristas inativos da empresa" << endl;
		cout << "18 - Listar as oficinas associadas a empresa" << endl;
		cout << "19 - Listar todos os dados relevantes da empresa" << endl;
		cout << "20 - Guardar dados da empresa num ficheiro" << endl;
		cout << "0 - Exit" << endl << endl;
		cout << "Opcao? ";
		cin >> option;
		option = toupper(option);
		while (!cin || ((option != 0) && (option != 1) && (option != 2) && (option != 3) && (option != 4) && (option != 5) && (option != 6) && (option != 7) && (option != 8) && (option !=9) && (option != 10) && (option != 11) && (option != 12) && (option != 13) && (option != 14) && (option != 15) && (option != 16) && (option != 17) && (option != 18) && (option != 19) && (option != 20)))
		{
			cin.clear();
			cin.ignore(100000, '\n');
			cout << endl << "Invalid Input" << endl;
			cout << "Option? ";
			cin >> option;
		}
		switch (option)
		{
		case 1: {
			string id;
			int capacidade;
			char regular;
			bool reg = false;
			cout << "Introduza o ID representativo do veiculo: ";
			cin >> id;
			cout << endl;
			cout << "Introduza o capacidade do veiculo: ";
			cin >> capacidade;
			cout << endl;
			cout << "E um veiculo de servico regular? (Y/N): ";
			cin >> regular;
			cout << endl;
			regular = toupper(regular);
			while (!cin || ((regular != 'Y') && (regular != 'N')))
			{
				cin.clear();
				cin.ignore(100000, '\n');
				cout << endl << "Invalid Input" << endl;
				cout << "E um veiculo de servico regular? (Y/N): ";
				cin >> regular;
				cout << endl;
			}
			if (regular == 'Y')
				reg = true;
			p.adicionaVeiculo(id, capacidade, reg);
			cout << "Veiculo adicionado com sucesso" << endl;
			break;
		}
		case 2: {
			char tipo, sub;
			cout << "O utente a ser adicionado e um aluno ou funcionario? (A/F): ";
			cin >> tipo;
			tipo = toupper(tipo);
			string nome, zona, zona_esc, nome_esc, nome_ee;
			bool subsidio = false;
			cout << endl << "Introduza o nome do utente: ";
			if (cin.peek() != NULL)
				cin.ignore(100000, '\n');
			getline(cin, nome);
			cout << endl;
			cout << "Introduza a zona de residencia do utente: ";
			cin >> zona;
			cout << endl;
			cout << "Nome da escola que o utente frequenta: ";
			if (cin.peek() != NULL)
				cin.ignore(100000, '\n');
			getline(cin, nome_esc);
			Escola e(nome_esc, "", "", "");
			EscolaPtr found = p.getEscolas().find_new(EscolaPtr(&e));
			if (found.getPtr() == NULL)
			{
				cout << endl << "Zona da escola que o utente frequenta: ";
				cin >> zona_esc;
				string morada, diretor;
				cout << endl << "Morada da escola que o utente frequenta: ";
				if (cin.peek() != NULL)
					cin.ignore(100000, '\n');
				getline(cin, morada);
				cout << endl << "Nome do diretor da escola que o utente frequenta: ";
				//if (cin.peek() != NULL)
					//	cin.ignore(100000, '\n');
				getline(cin, diretor);
				e = Escola(nome_esc, zona_esc, morada, diretor);
			}
			else
				e = *(found.getPtr());
			if (tipo == 'A')
			{
				cout << endl << "Nome do Encarregado de Educacao: ";
				getline(cin, nome_ee);
				cout << endl << "O aluno tem direito a apoios sociais? (Y/N): ";
				cin >> sub;
				cout << endl;
				while (!cin || ((sub != 'Y') && (sub != 'N')))
				{
					cin.clear();
					cin.ignore(100000, '\n');
					cout << endl << "Invalid Input" << endl;
					cout << "O aluno tem direito a apoios sociais? (Y/N): ";
					cin >> sub;
					sub = toupper(sub);
					cout << endl;
				}
				if (sub == 'Y')
					subsidio = true;
				else
					subsidio = false;
				p.alocaUtente(nome, zona, e, nome_ee, subsidio);
			}
			else
				p.alocaUtente(nome, zona, e);
			cout << "Utente alocado com sucesso" << endl;
			break;
		}
		case 3: {
			unsigned int dia, mes, ano, n_pessoas;
			double distancia_Km;
			cout << "Dia em que o servico se ira realizar: ";
			cin >> dia;
			cout << "Mes em que o servico se ira realizar: ";
			cin >> mes;
			cout << endl;
			cout << "Ano em que o servico se ira realizar: ";
			cin >> ano;
			cout << endl;
			cout << "Distancia a percorrer no servico(em km): ";
			cin >> distancia_Km;
			cout << endl;
			cout << "Numero de pessoas a ser transportadas: ";
			cin >> n_pessoas;
			cout << endl;
			p.alocaServico(dia, mes, ano, distancia_Km, n_pessoas);
			cout << "Servico ocasional criado com sucesso." << endl;
			break;
		}
		case 4:{
			string name;
			cout << "Nome do motorista a adicionar: ";
			if (cin.peek() != NULL)
				cin.ignore(100000, '\n');
			getline(cin, name);
			cout << endl;
			char ativo;
			cout << "Este motorista encontra-se atualmente na empresa (Y/N): ";
			cin >> ativo;
			ativo = toupper(ativo);
			while (!cin || ((ativo != 'Y') && (ativo != 'N') && (ativo != 'y') && (ativo != 'n')))
			{
				cin.clear();
				cin.ignore(100000, '\n');
				cout << endl << "Invalid Input" << endl;
				cout << "Este motorista encontra-se atualmente na empresa (Y/N): ";
				cin >> ativo;
				cout << endl;
			}
			if (ativo == 'Y')
				p.addMotorista(name, true, true);
			else
				p.addMotorista(name, false, true);
			break;
		}
		case 5:{
			string name;
			cout << "Nome da oficina a adicionar: ";
			if (cin.peek() != NULL)
				cin.ignore(100000, '\n');
			getline(cin, name);
			cout << endl;
			unsigned int distance;
			cout << "Distancia entre a oficina e a garagem da empresa: ";
			cin >> distance;
			while (!cin || distance <= 0)
			{
				cin.clear();
				cin.ignore(100000, '\n');
				cout << endl << "Invalid Input" << endl;
				cout << "Distancia entre a oficina e a garagem da empresa: ";
				cin >> distance;
				cout << endl;
			}
			p.adicionaOficina(name, distance);
			cout << "Oficina criada com sucesso" << endl;
			break;
		}
		case 6:{
			string id;
			cout << "ID do veiculo a reparar: ";
			if (cin.peek() != NULL)
				cin.ignore(100000, '\n');
			getline(cin, id);
			cout << endl;
			unsigned int distance;
			cout << "Distancia maxima entre a oficina e a garagem da empresa: ";
			cin >> distance;
			while (!cin || distance <= 0)
			{
				cin.clear();
				cin.ignore(100000, '\n');
				cout << endl << "Invalid Input" << endl;
				cout << "Distancia maxima entre a oficina e a garagem da empresa: ";
				cin >> distance;
				cout << endl;
			}
			string nome = p.adicionaVeiculoOficina(id, distance);
			cout << "Veiculo sera reparado na oficina " << nome << endl;
			break;
		}
		case 7: {
			string id;
			cout << "ID do veiculo a remover: ";
			cin >> id;
			cout << endl;
			p.removeVeiculo(id);
			cout << "Veiculo " << id << " removido com sucesso." << endl;
			break;
		}
		case 8: {
			string nome;
			cout << "Nome do utente a remover: ";
			if (cin.peek() != NULL)
				cin.ignore(100000, '\n');
			getline(cin, nome);
			cout << endl;
			p.removeUtente(nome);
			cout << "Utente " << nome << " removido com sucesso." << endl;
			break;
		}
		case 9: {
			string name;
			cout << "Nome do motorista que deseja remover: ";
			if (cin.peek() != NULL)
				cin.ignore(100000, '\n');
			getline(cin, name);
			cout << endl;
			p.removeMotorista(name);
			cout << "Motorista Removido com sucesso" << endl;
			break;
		}
		case 10: {
			string nome;
			cout << "Nome da oficina a remover: ";
			if (cin.peek() != NULL)
				cin.ignore(100000, '\n');
			getline(cin, nome);
			cout << endl;
			p.removeOficina(nome);
			cout << "Oficina " << nome << " removida com sucesso." << endl;
			break;
		}
		case 11:{
			unsigned int days;
			cout << "Numero de dias a avancar (e veiculos por oficina para reparar): ";
			cin >> days;
			while (!cin || (days <= 0))
			{
				cin.clear();
				cin.ignore(100000, '\n');
				cout << endl << "Invalid Input" << endl;
				cout << "Numero de dias a avancar (e veiculos por oficina para reparar): ";
				cin >> days;
				cout << endl;
			}
			p.avancarDias(days);
			break;
		}
		case 12: {
			char periodo;
			cout << "Pretende listar os ganhos de um mes ou de um ano? (M/A): ";
			cin >> periodo;
			periodo = toupper(periodo);
			while (!cin || ((periodo != 'M') && (periodo != 'A')))
			{
				cin.clear();
				cin.ignore(100000, '\n');
				cout << endl << "Invalid Input" << endl;
				cout << "Pretende listar os ganhos de um mes ou de um ano? (M/A): ";
				cin >> periodo;
				cout << endl;
			}
			if (periodo == 'M')
			{
				int mes, ano;
				cout << "Ano a consultar(aaaa): ";
				cin >> ano;
				cout << endl;
				cout << "Mes a consultar(mm): ";
				cin >> mes;
				cout << endl;
				p.listaGanhos(mes, ano);
			}

			else
			{
				int ano;
				cout << "Ano a consultar(aaaa): ";
				cin >> ano;
				cout << endl;
				p.listaGanhos(ano);
			}
			break;
		}
		case 13: {
			cout << "Utentes da empresa " << p.getNome() << endl;
			p.listaUtentes();
			break;
		}
		case 14: {
			cout << "Escolas associadas a empresa " << p.getNome() << endl << endl;
			p.listaEscolas();
			break;
		}
		case 15: {
			cout << "Motoristas associados a empresa " << p.getNome() << endl << endl;
			p.listaMotoristas();
			break;
		}
		case 16: {
			cout << "Motoristas que trabalham atualmente na empresa " << p.getNome() << endl << endl;
			p.listaMotoristasAtivos();
			break;
		}
		case 17: {
			cout << "Antigos motoristas da empresa " << p.getNome() << endl << endl;
			p.listaMotoristasInativos();
			break;
		}
		case 18: {
			cout << "Oficinas associadas a empresa " << p.getNome() << endl << endl;
			p.listaOficinas();
			break;
		}
		case 19: {
			cout << p << endl;
			break;
		}
		case 20: {
			p.imprimeEmpresa();
			cout << "O ficheiro da sua empresa foi criado com sucesso!" << endl;
			break;
		}
		case 0:exit(0);
		}
	  }

	  catch (ZonaInexistente &z)
	  	{
	  		cout << z << endl;
	  	}

	  	catch (UtenteInexistente &u)
	  	{
	  		cout << u << endl;
	  	}

		catch (AlocacaoUtenteImpossivel &u)
		{
			cout << u << endl;
		}

	  	catch (UtenteRepetido &u)
	  	{
	  		cout << u << endl;
	  	}

	  	catch (VeiculoInexistente &v)
	  	{
	  		cout << v << endl;
	  	}

	  	catch (VeiculoRepetido &v)
	  	{
	  		cout << v << endl;
	  	}

	  	catch (VeiculoIndisponivel &v)
	  	{
	  		cout << v << endl;
	  	}

	  	catch (DataInvalida &d)
	  	{
	  		cout << d << endl;
	  	}

	  	catch(RemocaoVeiculoImpossivel &v)
	  	{
	  		cout<< v << endl;
	  	}

	  	catch(MotoristaIndisponivel &m)
	  	{
	  		cout<< m << endl;
	  	}

	  	catch(MotoristaRepetido &m)
	  	{
	  		cout<< m << endl;
	  	}

		catch (MotoristaInexistente &m)
		{
			cout << m << endl;
		}

	  	catch(OficinaRepetida &o)
	  	{
	  		cout<< o << endl;
	  	}

	  	catch(OficinaInexistente &o)
	  	{
	  		cout<< o << endl;
	  	}

	  	catch(VeiculoEmReparacao &v)
	  	{
	  		cout<< v << endl;
	  	}

	  	catch(VeiculoJaEmReparacao &v)
	  	{
	  		cout<< v << endl;
	  	}

	  	catch(OficinaComVeiculos &o)
	  	{
	  		cout<< o << endl;
	  	}

	  	catch(OficinaMuitoLonge &o)
	  	{
	  		cout<< o << endl;
	  	}

	  	catch (exception &e)
	  	{
	  		e.what();
	  	}
	}
}

int main()
{
		cout << "============================" << endl;
		cout << "===  TRANSPORTE ESCOLAR  ===" << endl;
		cout << "============================" << endl;

		while (true)
		{
			char option;
			cout << endl << "Opcoes:" << endl;
			cout << "1 - Criar Empresa. Escolha esta opcao para criar uma empresa de raiz." << endl;
			cout << "2 - Carregar Empresa. Escolha esta opcao para carregar os dados da empresa a partir de um ficheiro previamente criado no formato adequado." << endl;
			cout << "0 - Exit" << endl << endl;
			cout << "Opcao? ";
			cin >> option;
			while (!cin || ((option != '1') && (option != '2') && (option != '0')))
			{
				cin.clear();
				cin.ignore(100000, '\n');
				cout << endl << "Invalid Input" << endl;
				cout << "Opcao? ";
				cin >> option;
			}
			cout << endl;
			if (option == '1')
			{
				string nome, zona_emp;
				double ppl;
				char predef, predefinido;
				cout << "Nome da empresa: ";
				if (cin.peek() != NULL)
					cin.ignore(100000, '\n');
				getline(cin, nome);
				cout << endl;
				cout << "Zona da empresa: ";
				cin >> zona_emp;
				cout << endl;
				cout << "Preco por lugar: ";
				cin >> ppl;
				cout << endl;
				cout << "Deseja inserir o seu proprio vetor de valores a cobrar por numero de zonas ou usar os valores predefinidos? (Inserir D para predefinido ou N para criar o proprio): ";
				cin >> predef;
				cout << endl;
				predef=toupper(predef);
				while (!cin || ((predef != 'D') && (predef != 'N')))
				{
					cin.clear();
					cin.ignore(100000, '\n');
					cout << endl << "Invalid Input" << endl;
					cout << "Deseja inserir o seu proprio vetor de valores a cobrar por numero de zonas ou usar os valores predefinidos? (Inserir D para predefinido ou N para criar o proprio): ";
					cin >> predef;
					cout << endl;
				}
				vector<double> prec_num_zonas;
				if (predef == 'N')
				{
					char aux;
					double valor, n = 0;
					while (true)
					{
						cout << "Valor a cobrar para " << n << " zonas: ";
						cin >> valor;
						prec_num_zonas.push_back(valor);
						n++;
						cout << "Prima Q para terminar, outra tecla para continuar";
						cin >> aux;
						if (aux == 'Q')
							break;
					}
				}
				cout << endl; 
				cout << "Deseja inserir a sua propria matriz que relaciona a zona inicial e final com o numero de zonas que atravessa ou usar os valores predefinidos? (Inserir D para predefinido ou N para criar o proprio): ";
				cin >> predefinido;
				predefinido=toupper(predefinido);
				cout << endl;
				while (!cin || ((predefinido != 'D') && (predefinido != 'N')))
				{
					cin.clear();
					cin.ignore(100000, '\n');
					cout << endl << "Invalid Input" << endl;
					cout << "Deseja inserir a sua propria matriz que relaciona a zona inicial e final com o numero de zonas que atravessa ou usar os valores predefinidos? (Inserir D para predefinido ou N para criar o proprio): ";
					cin >> predefinido;
					cout << endl;
				}
				map<pair<string, string>, int> matriz;
				if (predefinido == 'N')
				{
					string z_inicial, z_final;
					char aux;
					int num_zonas;
					while (true)
					{
						cout << "Zona inicial:  ";
						cin >> z_inicial;
						cout << "Zona final:  ";
						cin >> z_final;
						cout << "Numero de zonas no percurso entre a zona inicial e final: ";
						cin >> num_zonas;
						pair<string, string> zonas = make_pair(z_inicial, z_final);
						matriz[zonas] = num_zonas;
						cout << "Prima Q para terminar, outra tecla para continuar";
						cin >> aux;
						if (aux == 'Q')
							break;
					}
				}
				if (predef == 'D')
					if (predefinido == 'D')
					{
						Empresa p(nome, zona_emp, ppl, preco_num_zonas, matriz_zonas);
						funcionalidades(p);
					}
					else
					{
						Empresa p(nome, zona_emp, ppl, preco_num_zonas, matriz);
						funcionalidades(p);
					}
				else
					if (predefinido == 'D')
					{
						Empresa p(nome, zona_emp, ppl, prec_num_zonas, matriz_zonas);
						funcionalidades(p);
					}
					else
					{
						Empresa p(nome, zona_emp, ppl, prec_num_zonas, matriz);
						funcionalidades(p);
					}
			
			}

			if (option == '2')
			{
				string nome_ficheiro;
				cout << "Ficheiro onde se encontram os dados da empresa: ";
				if (cin.peek() != NULL)
					cin.ignore(100000, '\n');
				getline(cin, nome_ficheiro);
				cout << endl;
				Empresa p(nome_ficheiro);
				funcionalidades(p);
			}
			else
				{
				cout << "=======================================================================================================" << endl << endl;
					cout << "Program developed by: " << endl;
					cout << "Joao Praca" << endl <<  "Leonor M. Sousa" << endl << "Silvia Rocha" << endl <<
						"Informatics and Computing Engineering Students in the Faculty of Engineering of the University of Porto"<< endl << endl;
				exit(0);
				}
		}
	return 0;
}
