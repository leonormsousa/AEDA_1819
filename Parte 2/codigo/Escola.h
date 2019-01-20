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
	/*!
	* Address of the school
	* */
	string morada;
	/*!
	* Name of the school principal
	* */
	string diretor;
	/*!
	* Number of company clients that study/work in this school
	* */
	int num_utentes;
public:
	Escola(string n, string z, string m, string d);
	/*!Constructor of class Escola with no initializations.*/
	Escola() {};
	string getNome() const;
	string getZona() const;
	string getMorada() const;
	string getDiretor() const;
	int getNumUtentes() const;
	void increaseNumUtentes();
	void decreaseNumUtentes();
	bool operator==(const Escola &esc2) const;
	bool operator<(const Escola &esc2) const;
	friend ostream & operator<<(ostream &out, const Escola& e);
};

class EscolaPtr {
	/*!
	* Pointer to an object of class Escola
	* */
	Escola* ptr;
public:
	/*!Constructor of class EscolaPtr with no initializations.*/
	EscolaPtr() { ptr = NULL; }
	/*!
	* Constructor of class EscolaPtr. Initializes the school pointer
	* @param p pointer to an object of class Escola
	* */
	EscolaPtr(Escola *p) { ptr = p; }
	/*!
	* R
	* @return the school pointer
	* */
	Escola* getPtr() const { return ptr; }
	/*!
	* Defines the operator < for class EscolaPtr as a comparison between the schools they point to
	* @param p2 object reference of class EscolaPtr
	* */
	bool operator<(const EscolaPtr p2) const
	{
		return ((*ptr) < *(p2.getPtr()));
	}
	/*!
	* Defines the operator == for class EscolaPtr as a comparison between the schools they point to
	* @param p2 object reference of class EscolaPtr
	* */
	bool operator==(const EscolaPtr p2)  const 
	{ 
		if (ptr == NULL || p2.getPtr() == NULL)
			return false;
		return (*ptr == *(p2.getPtr())); 
	}
	/*!
	* Defines the operator << for class EscolaPtr and outputs the atributes of the school it points to.
	* @param out ostream reference
	* @param e object reference of class EscolaPtr
	* */
	friend ostream & operator<<(ostream &out, const EscolaPtr& e)
	{
		out << *(e.getPtr());
		return out;
	}
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
	Escola *escola;
public:
	Utente(string n, string z, Escola *e);
	/*!
	 * Destructor of class Utente.
	 * */
	virtual ~Utente() {};
	string getNome() const;
	string getZona() const;
	Escola* getEscola() const;
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
	Crianca(string n, string z, Escola *e, string ee, bool sub);
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
	Funcionario(string n, string z, Escola *e);
	/*!
	 * Destructor of class Employee.
	 * */
	~Funcionario() {};
	void setMensalidade(double preco_utente);
	friend ostream & operator<<(ostream &out, const Funcionario& f);
};
