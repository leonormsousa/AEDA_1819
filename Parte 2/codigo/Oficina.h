#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <queue>
#include "Veiculo.h"

using namespace std;

class Oficina {
	/*!
	 * Name of the garage
	 * */
	string nome;
	/*!
	 * Availability of the garage
	 * */
	unsigned int disponibilidade;
	/*!
	 * Distance of the garage to the company's garage
	 * */
	unsigned int distancia;
	/*!
	 * Vector containing pointers to the vehicles in the garage
	 */
	queue<Veiculo*> veiculos_oficina;
public:
	Oficina(string n, unsigned int disponibilidade, unsigned int dist);
	/*!
	 * Constructor for class Oficina. Initializes the garage's name, availability as zero and distance to the company's garage
	 * */
	Oficina() {};
	/*!
	 * Destructor of class Oficina
	 * */
	~Oficina() {};
	string getNome() const;
	unsigned int getDisponibilidade() const;
	unsigned int getDistancia() const;
	queue<Veiculo*> getVeiculos() const;
	void adicionaVeiculo(Veiculo *v);
	void reparaVeiculo();
	bool verificaVeiculoOficina(string id) const;
	bool operator<(const Oficina& o1) const;
	friend ostream & operator<<(ostream &out, const Oficina & o);
};

