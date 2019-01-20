#pragma once

#include <utility>
#include <map>
#include <algorithm>
#include "exceptions.h"
#include "Escola.h"
#include "Date.h"

using namespace std;

class Veiculo {
protected:
	/*!
	 * Id of the vehicle
	 * */
	string id;
	/*!
	 * Capacity of the vehicle
	 * */
	unsigned int capacidade;
	/*!
	 * Driver of the vehicle
	 * */
	string motorista;
	/*!
	* Availability of the vehicle (true if it's under repair)
	* */
	bool underRepair;
public:
	Veiculo(string i, int cap);
	string getId() const;
	unsigned int getCapacidade() const;
	bool getUnderRepair() const;
	void setUnderRepair(bool repair);
	void setMotorista(string name);
	string getMotorista();
	virtual double calculaGanhos()=0;
	virtual bool operator<(Veiculo &v2)=0;
	virtual bool getRegular()=0;
	/*!
	 * Destructor of class Vehicle
	 * */
	virtual ~Veiculo() {};

};

class ServicoRegular: public Veiculo {
	/*!
	 * Vector containing pointer to all of the vehicle's clients
	 * */
	vector<Utente*> utentes;
	/*!
	 * School of the regular vehicle
	 * */
	Escola *escola;
public:
	ServicoRegular(string i, int cap);
	virtual ~ServicoRegular();
	void addUtente(string n, string z, Escola *e, string ee, bool sub, double preco_utente);
	void addUtente(string n, string z, Escola *e, double preco_utente);
	void setEscola(Escola *esc);
	Escola* getEscola() const;
	bool getRegular() { return true; };
	int verificaUtente(string name);
	double calculaGanhos();
	void eliminaUtente(unsigned int index);
	vector<Utente *> getUtentes();
	void ordenaUtentes();
	friend ostream & operator<<(ostream &out, ServicoRegular& s);
	bool operator<(Veiculo &v2);
};


class ServicoEspecial : public Veiculo {
	/*!
	 * Price per Kilometer, that the company charges, for this vehicle
	 * */
	double preco_total_porKm;
	/*!
	 * Map containing all of the services done by the special vehicle. To each date corresponds the Km made in that service
	 * */
	map < Date, double> servicos; 
public:
	ServicoEspecial(string i, int cap, double preco_por_lugar);
	/*!
	 * Destructor of class Special Vehicle
	 * */
	virtual ~ServicoEspecial() {};
	/*!
	 * R
	 * @return a vector containing all of the vehicle's services
	 * */
	map < Date, double> getServicos() {	return servicos;}
	bool getRegular() { return false; };
	void addServico(const Date &data, double distancia_km);
	double calculaGanhos(unsigned int mes,unsigned int ano);
	double calculaGanhos(unsigned int ano);
	double calculaGanhos();
	friend ostream & operator<<(ostream &out, ServicoEspecial& s);
	bool operator<(Veiculo &v2);
};
