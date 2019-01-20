#include "Oficina.h"

/*!
 * Constructor for class Oficina. Initializes the garage's name, availability as zero and distance to the company's garage
 * @param n garage's name
 * @param dist distance to the company's garage
 * */
Oficina::Oficina(string n, unsigned int disponibilidade, unsigned int dist) : nome(n), disponibilidade(disponibilidade), distancia(dist)
{}

/*!
 * @return the garage's name
 * */
string Oficina::getNome() const { return nome; }

/*!
 * @return the garage's availability
 * */
unsigned int Oficina::getDisponibilidade() const { return disponibilidade; }

/*!
 * @return the garage's distance to the company's garage
 * */
unsigned int Oficina::getDistancia() const { return distancia; }

/*!
 * @return a queue with all the vehicles being repaired in the garage
 * */
queue<Veiculo*> Oficina::getVeiculos() const { return veiculos_oficina; }

/*!
 * Adds a vehicle to the garage
 * @param *v pointer to object of class Veiculo
 * */
void Oficina::adicionaVeiculo(Veiculo *v)
{
	veiculos_oficina.push(v);
	disponibilidade++;
}

/*!
 * Repairs the first vehicle of the queue of the garage
 * */
void Oficina::reparaVeiculo()
{
	if(!veiculos_oficina.empty())
	{
		veiculos_oficina.pop();
		disponibilidade--;
	}
}

/*!
 * Verifies of the vehicle with a certain id is in the garage
 * @param id id of the vehicle to search for
 * */
bool Oficina::verificaVeiculoOficina(string id) const
{
	queue<Veiculo*> temp = veiculos_oficina;

	while(!temp.empty())
	{
		if(temp.front()->getId() == id)
		{
			return true;
		}
	}

	return false;
}

/*!
 * Defines the operator < for class Oficina as a comparison between the availability, distance and name of the garages
 * @param o1 object reference of class Oficina
 * @return true if the garage o1 has less cars to be repaired; if they are the same, then returns true if its the distance is greater; and if they are the same, then returns true if its name is "smaller".
 * */
bool Oficina::operator<(const Oficina& o1) const
{
	if(disponibilidade == o1.getDisponibilidade())
	{
		if(distancia == o1.getDistancia())
		{
			return nome > o1.getNome();
		}

		return distancia < o1.getDistancia();
	}

	return disponibilidade > o1.getDisponibilidade();
}

/*!
 * Defines the operator << for the class Oficina and outputs the information of a garage (name, availability, distance and id's of the vehicles being repaired)
 * @param out ostream reference
 * @param s object reference of class Oficina
 * */
ostream & operator<<(ostream &out, const Oficina & o)
{
	out << o.getNome() << endl << o.getDisponibilidade() << endl << o.getDistancia() << endl;

	queue<Veiculo*> temp = o.getVeiculos();

	if(temp.empty())
		out << endl;

	while(!temp.empty())
	{
		out << temp.front()->getId() << endl;
		temp.pop();
	}

	return out;
}

