#pragma once

#include <iostream>
#include <unordered_set>
#include <queue>
#include <iomanip>
#include "BST.h"
#include "Veiculo.h"
#include "Motorista.h"
#include "Oficina.h"

using namespace std;

struct MotoristaHash
{
	int operator() (const Motorista& motorista) const
	{
		int hash = 1469598537;
		hash *= 1099511628;
		hash = hash ^ motorista.getName().size();
		return hash%53;
	}

	bool operator() (const Motorista& motorista1, const Motorista& motorista2) const
	{
		if (motorista1.getName() == motorista2.getName())
			if ((motorista1.getActive() && motorista2.getActive()) || (!motorista1.getActive() && !motorista2.getActive()))
				return true;
			else
				return false;
		else
			return false;
	}
};

typedef unordered_set<Motorista, MotoristaHash, MotoristaHash> HashTabMotorista;

class Empresa {
	/*!
	 * Name of company
	 * */
	string nome;
	/*!
	 * Zone of company
	 * */
	string zona;
	/*!
	 * Vector containing pointers to each of the company's vehicles
	 * */
	vector<Veiculo* > veiculos;
	/*!
	 * price per place; used in Special Services
	 * */
	double preco_por_lugar;
	/*!
	 * Vector containing the prices per zones; in position n is the price for n zones
	 * */
	vector<double> preco_num_zonas;
	/*!
	 * Map containing the number of zones you have to pass to go from one zone to another. To a pair of zones corresponds the number of zones.
	 * */
	map<pair<string, string>, int> matriz_zonas;
	/*!
	* Binary Search Tree containing the Schools on which the company has clients
	* */
	BST<EscolaPtr> escolas;
	/*!
	* Hash Table containing every current or former driver of the company
	* */
	HashTabMotorista motoristas;
	/*!
	 * Priority queue containing the garages the company works with, ordered by availability, distance from the company's garage and name
	 */
	priority_queue<Oficina> oficinas;
public:
	Empresa(string nome, string zona, double preco_pl, vector<double> preco_nz, map<pair<string, string>, int> matriz);
	Empresa(string nome_ficheiro);
	~Empresa();
	string getZona() const;
	string getNome() const;
	vector<Veiculo* > getVeiculos() const;
	BST<EscolaPtr> getEscolas() const;
	void insereEscola(Escola e);
	/*!
	 * R
	 * @return the price per place
	 * */
	double getPrecoPorLugar() const {return preco_por_lugar;};
	/*!
	 * R
	 * @return the vector that contains the price per zones
	 * */
	vector<double> getPrecoNumZonas() const {return preco_num_zonas;};
	/*!
	 * R
	 * @return the zone matrix
	 * */
	map<pair<string, string>, int> getMatrizZonas() const {	return matriz_zonas;};
	double calculaPrecoUtente(Escola e, string zona);
	void alocaUtente(string nome, string zona, Escola e, string ee, bool subsidio);
	void alocaUtente(string nome, string zona, Escola e);
	void removeUtente(string nome);
	void alocaServico(unsigned int dia, unsigned int mes, unsigned int ano, double distancia_Km, unsigned int n_pessoas);
	void adicionaVeiculo(string id, unsigned int capacidade, bool regular);
	void removeVeiculo(string id);
	int verificaVeiculo(string id);
	void ordenaVeiculos();
	friend ostream & operator<<(ostream &out, Empresa & e);
	void imprimeEmpresa();
	void listaGanhos(unsigned int mes, unsigned int ano);
	void listaGanhos(unsigned int ano);
	void listaUtentes();
	void listaEscolas();
	void listaMotoristas();
	void listaMotoristasAtivos();
	void listaMotoristasInativos();
	bool verificaMotorista(const Motorista& motorista) const;
	vector<Motorista> getMotoristas() const;
	vector<Motorista> getInactiveMotoristas() const;
	vector<Motorista> getActiveMotoristas() const;
	bool addMotorista(string nome, bool active, bool disponivel);
	bool removeMotorista(string name);
	priority_queue<Oficina> getOficinas() const { return oficinas; };
	void adicionaOficina(string nome, unsigned int distancia);
	void adicionaOficina(Oficina o);
	void removeOficina(string nome);
	bool verificaOficina(string nome);
	string adicionaVeiculoOficina(string id, unsigned int distancia_max);
	void adicionaVeiculoOficina(string nome, string id);
	void avancarDias(unsigned int dias);
	void listaOficinas();
};
