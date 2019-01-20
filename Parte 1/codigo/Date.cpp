#include "Date.h"

/*!
 * Constructor for class Date. Initializes the date's day, month and year.
 * @param d day of the date
 * @param m month of the date
 * @param a year of the date
 * */
Date::Date(unsigned int d, unsigned int m, unsigned int a)
{
	if (m < 1 || m>12)
		throw DataInvalida(d, m, a);
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
		if (d < 1 || d>31)
			throw DataInvalida(d, m, a);
	if (m == 4 || m == 6 || m == 9 || m == 11)
		if (d < 1 || d>30)
			throw DataInvalida(d, m, a);
	if (m == 2)
	{
		if (a % 4 == 0 && (d < 1 || d>29))
			throw DataInvalida(d, m, a);
		if (a % 4 != 0 && (d < 1 || d>28))
			throw DataInvalida(d, m, a);
	}
	ano = a;
	mes = m;
	dia = d;
}

/*!
 * @return the date's day
 * */
unsigned int Date::getDia() const
{
	return dia;
}

/*!
 * @return the date's month
 * */
unsigned int Date::getMes() const
{
	return mes;
}

/*!
 * @return the date's year
 * */
unsigned int Date::getAno() const
{
	return ano;
}

/*!
 * Defines the operator < for class Date and compares the day, month and year of the two dates.
 * @param d2 object reference of class Date
 * @return true if the date is older than d2
 * */
bool Date::operator<(const Date &d2) const
{
	if (ano == d2.getAno())
	{
		if (mes == d2.getMes())
			return (dia < d2.getDia());
		return (mes < d2.getMes());
	}
	return (ano < d2.getAno());
}

/*!
 * Defines the operator < for class Date as a comparison between the two dates.
 * @param d2 object reference of class Date
 * @return true if the dates are equal
 * */
bool Date::operator==(const Date &d2) const
{
	return (dia == d2.getDia() && mes == d2.getMes() && ano == d2.getAno());
}

/*!
 * Defines the operator << for class Date and outputs the day, month and year of the date.
 * @param out ostream reference
 * @param d object reference of class Date
 * */
ostream & operator<<(ostream &out, const Date &d)
{
	out << d.getDia() << "." << d.getMes() << "." << d.getAno();
	return out;
}

/*!
 * Defines the operator = for class Date, defining the date as d2.
 * @param d2 object reference of class Date
 * */
void Date::operator=(const Date &d2) 
{
	this->dia = d2.getDia();
	this->mes = d2.getMes();
	this->ano = d2.getAno();
}

/*!
 * Defines the operator << for class DataInvalida and outputs a string of the day, month and year of the invalid date.
 * @param out ostream reference
 * @param d object reference of class DataInvalida
 * */
ostream & operator<<(ostream &out, const DataInvalida &d)
{
	out << "A data " << d.getDia() << "." << d.getMes() << "." << d.getAno() << " é inválida." << endl;
	return out;
}
