#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include "Veiculo.h"

using namespace std;

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
public:
	Empresa(string nome, string zona, double preco_pl, vector<double> preco_nz, map<pair<string, string>, int> matriz);
	Empresa(string nome_ficheiro);
	~Empresa();
	string getZona() const;
	string getNome() const;
	vector<Veiculo* > getVeiculos() const;
	vector<Escola> getEscolas() const;
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
};

