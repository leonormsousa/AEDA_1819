#pragma once

#include <vector>
#include <string>
#include "Date.h"

class Motorista {
	/*!
	 * driver's name
	 * */
	string name;
	/*!
	 * If true, the driver is a current company employee 
	 * */
	bool isActive;
	/*!
	 * If true, the driver does not have any regular service assigned
	 * */
	bool available;
	/*!
	 * Vector of the dates of every special service assigned to the driver
	 * */
	vector<Date> servicos;
public:
	Motorista(string name, bool isActive, bool disponivel);
	string getName() const;
	bool getActive() const;
	void setActive(bool active);
	bool getDisponivel() const;
	void setDisponivel(bool disponivel);
	vector<Date> getServicos();
	bool addServico(Date data);
};
