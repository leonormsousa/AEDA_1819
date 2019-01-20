#include "Motorista.h"

/*!
 * Constructor for class Motorista. Initializes the driver's name and availability
 * @param name the driver's name
 * @param isActive if true, the driver is a current employee
 * @param disponivel if true, the driver has no regular service assigned
 * */
Motorista::Motorista(string name, bool isActive, bool disponivel) 
{
	this->name = name; 
	this->isActive = isActive; 
	available = disponivel;
}

/*!
 * R
 * @return the driver's name
 * */
string Motorista::getName() const 
{ 
	return name; 
}

/*!
 * R
 * @return if true, the driver is a current employee
 * */
bool Motorista::getActive() const 
{ 
	return isActive; 
}

/*!
 * Defines if a driver is active or not .
 * @param active if true the driver is a current employee
 * */
void Motorista::setActive(bool active) 
{ 
	isActive = active; 
}

/*!
 * R
 * @return if true, the driver does not have any regular service assigned
 * */
bool Motorista::getDisponivel() const
{ 
	return available; 
}

/*!
 * Defines if a driver is available or not.
 * @param active if true the driver does not have any regular service assigned
 * */
void Motorista::setDisponivel(bool disponivel) 
{ 
	available = disponivel; 
}

/*!
 * R
 * @return a vector of dates of all the special services assigned to the driver
 * */
vector<Date> Motorista::getServicos()
{ 
	return servicos; 
}

/*!
 * If the driver does not have already have a service assigned on that date, a new service on the date specified is assigned
 * @param data object of class Date with the date of the new service to be added
 * */
bool Motorista::addServico(Date data) 
{
	for (size_t i = 0; i < servicos.size(); i++)
	{
		if (servicos[i].getDia() == data.getDia())
		{
			if (servicos[i].getMes() == data.getMes())
				if (servicos[i].getAno() == data.getAno())
					return false;
		}
	}
	servicos.push_back(data);
	return true;
}



