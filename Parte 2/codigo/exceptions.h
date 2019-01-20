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

class AlocacaoUtenteImpossivel : public exception {
	/*!
	*Name of the client that is impossible to alocate
	* */
	string nome;
public:
	/*!
	* Constructor for class RemocaoVeiculoImpossivel
	* @param n name of the client that is impossible to alocate
	* */
	AlocacaoUtenteImpossivel(string n) { nome = n; };
	/*!
	* @return name of the client that is impossible to alocate
	* */
	string getNome() const { return nome; };
	friend ostream & operator<<(ostream &out, const AlocacaoUtenteImpossivel &a);
};

class MotoristaIndisponivel : public exception {
	/*!
	 *Date on wich is not posible to do a service
	 * */
	Date data;
	/*!
	 * bool that indicates if the unavailability is for a regular or special service
	* */
	bool regular;
public:
	/*!
	 * Constructor for class MotoristaIndisponivel
	 * @param dat date on wich is not posible to do a service
	 * */
	MotoristaIndisponivel(const Date& dat, bool regular) : data(dat), regular(regular) {};
	/*!
	 * @return date on wich is not posible to do a service
	 * */
	Date getDate() const { return data; };
	/*!
	* @return true if the driver is unavailable for a regular service
	* */
	bool getRegular() const { return regular; };
	friend ostream & operator<<(ostream &out, const MotoristaIndisponivel &m);
};

class MotoristaRepetido : public exception{
	/*!
	 *Name of the repeated driver
	 * */
	string name;
public:
	/*!
	 * Constructor for class MotoristaRepetido
	 * @param name name of the repeated driver
	 * */
	MotoristaRepetido(string name) : name(name) {};
	/*!
	 * @return name of the repeated driver
	 * */
	string getName() const { return name; };
	friend ostream & operator<<(ostream &out, const MotoristaRepetido &m);
};


class MotoristaInexistente : public exception {
	/*!
	 *Name of the nonexistent driver
	 * */
	string name;
public:
	/*!
	 * Constructor for class MotoristaInexistente
	 * @param name name of the nonexistent driver
	 * */
	MotoristaInexistente(string name) : name(name) {};
	/*!
	 * @return name of the nonexistent driver
	 * */
	string getName() const { return name; };
	friend ostream & operator<<(ostream &out, const MotoristaInexistente &m);
};

class OficinaRepetida : public exception {
	/*!
	 * Name of the repeated garage
	 * */
	string name;
public:
	/*!
	 * Constructor for class OficinaRepetida
	 * @param name string with the name of the repeated garage
	 * */
	OficinaRepetida(string name) { this->name = name; };
	/*!
	 * @return name of the repeated vehicle
	 * */
	string getName() const { return name; };
	friend ostream & operator<<(ostream &out, const OficinaRepetida &o);
};

class OficinaInexistente : public exception {
	/*!
	 * Name of the non existing garage
	 * */
	string name;
public:
	/*!
	 * Constructor for class OficinaInexistente
	 * @param name string with the name of the non existing garage
	 * */
	OficinaInexistente(string name) { this->name = name; };
	/*!
	 * @return name of the non existing garage
	 * */
	string getName() const { return name; };
	friend ostream & operator<<(ostream &out, const OficinaInexistente &o);
};

class VeiculoEmReparacao : public exception {
	/*!
	 * Id of the vehicle that is under repair
	 * */
	string id;
public:
	/*!
	 * Constructor for class VeiculoEmReparacao
	 * @param id string with the name of the vehicle under repair
	 * */
	VeiculoEmReparacao(string id) { this->id = id; };
	/*!
	 * @return id of the vehicle under repair
	 * */
	string getId() const { return id; };
	friend ostream & operator<<(ostream &out, const VeiculoEmReparacao &o);
};

class VeiculoJaEmReparacao : public exception {
	/*!
	 * Id of the vehicle that is already under repair
	 * */
	string id;
public:
	/*!
	 * Constructor for class VeiculoJaEmReparacao
	 * @param id string with the name of the vehicle already under repair
	 * */
	VeiculoJaEmReparacao(string id) { this->id = id; };
	/*!
	 * @return id of the vehicle already under repair
	 * */
	string getId() const { return id; };
	friend ostream & operator <<(ostream &out, const VeiculoJaEmReparacao &v);
};

class OficinaComVeiculos : public exception {
	/*!
	 * Name of the non garage with vehicles
	 * */
	string nome;
public:
	/*!
	 * Constructor for class OficinaComVeiculos
	 * @param nome string with the name of the non garage with vehicles
	 * */
	OficinaComVeiculos(string nome) { this->nome = nome; };
	/*!
	 * @return name of the garage with vehicles
	 * */
	string getName() const { return nome; };
	friend ostream & operator<<(ostream &out, const OficinaComVeiculos &o);
};

class OficinaMuitoLonge : public exception {
	/*!
	 * Maximum distance from the company's garage
	 * */
	unsigned int distance;
public:
	/*!
	 * Constructor for class OficinaMuitoLonge
	 * @param distance maximum distance from the company's garage
	 * */
	OficinaMuitoLonge(unsigned int distance) { this->distance = distance; };
	/*!
	 * @return maximum distance from the company's garage
	 * */
	unsigned int getDistance() const { return distance; };
	friend ostream & operator<<(ostream &out, const OficinaMuitoLonge &o);
};
