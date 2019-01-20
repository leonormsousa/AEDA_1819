#pragma once
#include<iostream>
#include<string>
#include "Date.h"

class ZonaInexistente : public exception {
	/*!
	 * Invalid zone
	 * */
	string zona;
public:
	/*!
	 * Constructor for class ZonaInexistente. Initializes the invalid zone.
	 * @param z invalid zone
	 * */
	ZonaInexistente(string z) { zona = z; };
	/*!
	 * @return the invalid zone
	 * */
	string getZona() const { return zona; };
	friend ostream & operator<<(ostream &out, const ZonaInexistente &z);
};

class UtenteInexistente : public exception {
private:
	/*!
	 * Non existing client's name
	 * */
	string nome;
public:
	/*!
	 * Constructor for class UtenteInexistente.
	 * @param n non existing client's name
	 * */
	UtenteInexistente(string n) { nome = n; };
	/*!
	 * @return non existing client's name
	 * */
	string getUtente() const { return nome; };
	friend ostream & operator<<(ostream &out, const UtenteInexistente &u);
};

class UtenteRepetido : public exception {
private:
	/*!
	 *repeated  client's name
	 * */
	string nome;
public:
	/*!
	 * Constructor for class UtenteRepetido.
	 * @param n repeated client's name
	 * */
	UtenteRepetido(string n) { nome = n; };
	/*!
	 * @return repeated client's name
	 * */
	string getUtente() const { return nome; };
	friend ostream & operator<<(ostream &out, const UtenteRepetido &u);
};

class VeiculoInexistente : public exception {
	/*!
	 *Id of the non existing vehicle
	 * */
	string id;
public:
	/*!
	 * Constructor for class VeiculoInexistente
	 * @param i id of the non existing vehicle
	 * */
	VeiculoInexistente(string id) { this->id = id; };
	/*!
	 * @return id of the non existing vehicle
	 * */
	string getId() const { return id; };
	friend ostream & operator<<(ostream &out, const VeiculoInexistente &v);
};

class VeiculoRepetido : public exception {
	/*!
	 *Id of the repeated vehicle
	 * */
	string id;
public:
	/*!
	 * Constructor for class VeiculoInexistente
	 * @param i id of the repeated vehicle
	 * */
	VeiculoRepetido(string id) { this->id = id; };
	/*!
	 * @return id of the repeated vehicle
	 * */
	string getID() const { return id; };
	friend ostream & operator<<(ostream &out, const VeiculoRepetido &v);
};

class VeiculoIndisponivel : public exception {
	/*!
	 *Date on wich is not posible to do a service
	 * */
	Date data;
	/*!
	 *Number of people that the service required
	 * */
	unsigned int n_pessoas;
public:
	/*!
	 * Constructor for class VeiculoIndisponivel
	 * @param dat date on wich is not posible to do a service
	 * @param n_pes number of people that the service required
	 * */
	VeiculoIndisponivel(const Date& dat, int n_pes) : data(dat), n_pessoas(n_pes) {};
	/*!
	 * @return date on wich is not posible to do a service
	 * */
	Date getDate() const { return data; };
	/*!
	 * @return number of people that the service required
	 * */
	unsigned int getNumPessoas() const { return n_pessoas; };
	friend ostream & operator<<(ostream &out, const VeiculoIndisponivel &v);
};

class RemocaoVeiculoImpossivel : public exception {
	/*!
	 *Id of the vehicle that is impossible to remove
	 * */
	string id;
public:
	/*!
	 * Constructor for class RemocaoVeiculoImpossivel
	 * @param i id of the vehicle that is impossible to remove
	 * */
	RemocaoVeiculoImpossivel(string i) { id = i;  };
	/*!
	 * @return id of the vehicle that is impossible to remove
	 * */
	string getId() const { return id; };
	friend ostream & operator<<(ostream &out, const RemocaoVeiculoImpossivel &r);
};

