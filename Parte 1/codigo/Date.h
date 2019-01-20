#pragma once

#include <iostream>
#include <string>
using namespace std;

class Date {
	/*!
	* Day
	* */
	unsigned int dia;
	/*!
	* Month
	* */
	unsigned int mes;
	/*!
	* Year
	* */
	unsigned int ano;
public:
	Date(unsigned int d, unsigned int m, unsigned int a);
	unsigned int getDia() const;
	unsigned int getMes() const;
	unsigned int getAno() const;
	bool operator<(const Date &d2) const;
	bool operator==(const Date &d2) const;
	void operator=(const Date &d2);
	friend ostream & operator<<(ostream &out, const Date &d);
};

class DataInvalida : public exception {
	/*!
	* Day
	* */
	unsigned int dia;
	/*!
	* Month
	* */
	unsigned int mes;
	/*!
	* Year
	* */
	unsigned int ano;
public:
	DataInvalida(unsigned int d, unsigned int m, unsigned int a): dia(d), mes(m), ano(a) {};
	/*!
	 * @return the invalid date's day
	 * */
	unsigned int getDia() const { return dia; };
	/*!
	 * @return the invalid date's month
	 * */
	unsigned int getMes() const { return mes; };
	/*!
	 * @return the invalid date's year
	 * */
	unsigned int getAno() const { return ano; };
	friend ostream & operator<<(ostream &out, const DataInvalida &d);
};
