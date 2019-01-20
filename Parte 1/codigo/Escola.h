#pragma once

#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Escola {
	/*!
	 * Name of the school
	 * */
	string nome;
	/*!
	 * Zone of the school
	 * */
	string zona;
public:
	Escola(string n, string z);
	/*!Constructor of class Escola with no initializations.*/
	Escola() {};
	string getNome() const;
	string getZona() const;
	bool operator==(const Escola &esc2);
	friend ostream & operator<<(ostream &out, const Escola& e);
};

class Utente {
protected:
	/*!
	 * Name of the client
	 * */
	string nome;
	/*!
	 * Zone where the client lives
	 * */
	string zona;
	/*!
	 * Price the client pays, per month
	 * */
	double mensalidade;
	/*!
	 * School on wich the client studies/works
	 * */
	Escola escola;
public:
	Utente(string n, string z, Escola e);
	/*!
	 * Destructor of class Utente.
	 * */
	virtual ~Utente() {};
	string getNome() const;
	string getZona() const;
	Escola getEscola() const;
	double getMensalidade() const;
	virtual void setMensalidade(double preco_utente)=0;
	bool operator<(Utente& u2);
};

class Crianca: public Utente {
private:
	/*!
	 * Name of the child's tutor
	 * */
	string eE;
	/*!
	 * Boolean indicating if the child has or not social aid
	 * */
	bool subsidio;
public:
	Crianca(string n, string z, Escola e, string ee, bool sub);
	/*!
	 * Destructor of class Child.
	 * */
	~Crianca() {};
	void setMensalidade(double preco_utente);
	string getEnc_Educacao() const;
	bool getSubsidio() const;
	friend ostream & operator<<(ostream &out, const Crianca& c);
};

class Funcionario : public Utente {
public:
	Funcionario(string n, string z, Escola e);
	/*!
	 * Destructor of class Employee.
	 * */
	~Funcionario() {};
	void setMensalidade(double preco_utente);
	friend ostream & operator<<(ostream &out, const Funcionario& f);
};
