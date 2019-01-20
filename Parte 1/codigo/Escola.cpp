#include "Escola.h"
#include<iostream>
#include<utility>
#include<string>
#include<vector>

/*!
 * Constructor of class Escola. Initializes the school name and zone.
 * @param n string with the school's name
 * @param z string with the school's zone
 * */
Escola::Escola(string n, string z) : nome(n), zona(z) 
{}

/*!
 * R
 * @return the school name
 * */
string Escola::getNome() const
{
	return nome;
}

/*!
 * @return the school zone
 * */
string Escola::getZona() const
{
	return zona;
}

/*!
 * Defines the operator == for class Escola as a comparison between the names of two schools.
 * @param esc2 object reference of class Escola
 * @return true if the schools' names are equal
 * */
bool Escola::operator==(const Escola &esc2)
{
	return (nome == esc2.getNome());
}

/*!
 * Defines the operator << for class Escola and outputs the name and zone of the school.
 * @param out ostream reference
 * @param e object reference of class Escola
 * */
ostream & operator<<(ostream &out, const Escola& e)
{
	out << e.getNome() << endl << e.getZona() << endl;
	return out;
}

/*!
 * Constructor for class Utente. Initializes the client's name, zone and school.
 * @param n string with the client's name
 * @param z string with the client's zone
 * @param e object of class Escola
 * */
Utente::Utente(string n, string z, Escola e) : nome(n), zona(z), escola(e) 
{}

/*!
 * @return the client's name
 * */
string Utente::getNome()  const
{ 
	return nome;
}

/*!
 * @return the client's home zone
 * */
string Utente::getZona() const
{
	return zona; 
}

/*!
 * @return the client's school
 * */
Escola Utente::getEscola() const
{
	return escola; 
}

/*!
 * @return the client's monthly fee
 * */
double Utente::getMensalidade() const
{
	return mensalidade; 
}
/*!
 * Defines the operator < for class Utente as a comparison between the names of the two clients (if they belong to the same derived class) or between derived classes.
 * @param u2 object reference of class Utente
 * @return true if u1 is minor than u2 (same classes) or if u1 is a student and u2 is an employee
 * */
bool Utente::operator<(Utente& u2)
{
	bool u1_crianca = true, u2_crianca = true;
	Crianca* u1_ptr = dynamic_cast<Crianca*>(this);
	if (!u1_ptr)
		u1_crianca = false;
	Crianca* u2_ptr = dynamic_cast<Crianca*>(&u2);
	if (!u2_ptr)
		u2_crianca = false;
	if (u1_crianca == u2_crianca)
		return (nome < u2.getNome());
	if (u1_crianca == true && u2_crianca == false)
		return true;
	return false;
}

/*!
 * Constructor for derived class Crianca. Initializes the student's name, zone, school, tutor and whether or not he has the right to social aid.
 * @param n string with the student's name
 * @param z string with the student's zone
 * @param e object of class Escola that is the school the student attends
 * @param ee string with the student's tutor name
 * @param sub boolean that is true if the student has social aid
 * */
Crianca::Crianca(string n, string z, Escola e, string ee, bool sub) :Utente(n, z, e), eE(ee), subsidio(sub) 
{}

/*!
 * @return the student's tutor
 * */
string Crianca::getEnc_Educacao() const
{
	return eE; 
}

/*!
 * @return true if the student has the right to social aid
 * */
bool Crianca::getSubsidio() const
{
	return subsidio;
}

/*!
 * Sets the student's monthly fee.
 * @param preco_utente price to pay per number of zones without discounts
 * */
void Crianca::setMensalidade(double preco_utente)
{
//If the student has the right to social aid, he also gets the right to a 60% discount.
	if(subsidio)
		mensalidade = double(0.4)*preco_utente;
//For being a student, even without the right to social aid, the client has the right to a 25% discount.
	else
		mensalidade= double(0.75)*preco_utente;
}

/*!
 * Defines the operator << for class Crianca and outputs the student's name, zone, monthly fee, tutor and whether or not has right to social aid.
 * @param out ostream reference
 * @param c object reference of class Crianca
 * */
ostream & operator<<(ostream &out, const Crianca& c)
{
	out << c.getNome() << endl << c.getZona() << endl << c.getMensalidade() << endl <<c.getEnc_Educacao() << endl;
	if (c.getSubsidio())
		out << "S" << endl;
	else
		out << "N" << endl;
	return out;
}

/*!
 * Constructor for derived class Funcionario. Initializes the employee's name, zone and the school where he works.
 * @param n string with the name of the employee
 * @param z string with the zone of the employee
 * @param e object of class Escola that is the school the employee works at
 * */
Funcionario::Funcionario(string n, string z, Escola e) :Utente(n, z, e)
{}

/*!
 * Sets the school's employee monthly fee. An employee pays the full price of the monthly fee.
 * @param preco_utente price to pay per number of zones without discounts
 * */
void Funcionario::setMensalidade(double preco_utente)
{
	mensalidade = preco_utente;
}

/*!
 * Defines the operator << for class Funcionario and outputs the employee's name, zone and monthly fee.
 * @param out ostream reference
 * @param c object reference of class Funcionario
 * */
ostream & operator<<(ostream &out, const Funcionario& c)
{
	out << c.getNome() << endl << c.getZona() << endl << c.getMensalidade() << endl;
	return out;
}
