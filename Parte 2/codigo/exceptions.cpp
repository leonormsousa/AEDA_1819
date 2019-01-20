#include "exceptions.h"

/*!
* Defines the operator << of class ZonaInexistente and outputs a nonexistent zone.
* @param out ostream reference
* @param z object reference of class ZonaInexistente
* */
ostream & operator <<(ostream &out, const ZonaInexistente &z)
{
	out << "Zona Inexistente: " << z.getZona() << endl;
	return out;
}

/*!
 * Defines the operator << for class UtenteInexistente and outputs the nonexistent client.
 * @param out ostream reference
 * @param u object reference of class UtenteInexistente
 * */
ostream & operator <<(ostream &out, const UtenteInexistente &u)
{
	out << "Utente Inexistente: " << u.getUtente() << endl;
	return out;
}

/*!
 * Defines the operator << for class UtenteRepetido and outputs the repeated client.
 * @param out ostream reference
 * @param u object reference of class UtenteRepetido
 * */
ostream & operator <<(ostream &out, const UtenteRepetido &u)
{
	out << "Utente Repetido: " << u.getUtente() << endl;
	return out;
}

/*!
* Defines the operator << of class VeiculoInexistente and outputs a nonexistent vehicles's id.
* @param out ostream reference
* @param v object reference of class VeiculoInexistente
* */
ostream & operator <<(ostream &out, const VeiculoInexistente &v)
{
	out << "Veiculo Inexistente: " << v.getId() << endl;
	return out;
}

/*!
* Defines the operator << of class VeiculoRepetido and outputs a repeated vehicles's id.
* @param out ostream reference
* @param v object reference of class VeiculoRepetido
* */
ostream & operator <<(ostream &out, const VeiculoRepetido &v)
{
	out << "Veiculo Repetido: " << v.getID() << endl;
	return out;
}

/*!
* Defines the operator << of class VeiculoIndisponivel and outputs a vehicle's unavailability on a specific date for a certain number of passengers.
* @param out ostream reference
* @param v object reference of class VeiculoIndisponivel
* */
ostream & operator<<(ostream &out, const VeiculoIndisponivel &v)
{
	out << "Veiculo Indisponivel para o dia: " << v.getDate() << " para " << v.getNumPessoas() << " pessoas." << endl;
	return out;
}

/*!
* Defines the operator << of class AlocacaoUtenteImpossivel and outputs that there are clients that would have to be removed.
* @param out ostream reference
* @param a object reference of class AlocacaoUtenteImpossivel
* */
ostream & operator<<(ostream &out, const AlocacaoUtenteImpossivel &a)
{
	cout << "E impossivel alocar o utente com o nome " << a.getNome() << "." << endl;
	return out;
}

/*!
* Defines the operator << of class RemocaoVeiculoImpossivel and outputs that there are clients that would have to be removed.
* @param out ostream reference
* @param r object reference of class RemocaoVeiculoImpossivel
* */
ostream & operator<<(ostream &out, const RemocaoVeiculoImpossivel &r)
{
	cout << "É impossível alterar o veículo com o id " << r.getId() << ", visto que o mesmo implica a remoção de utentes." << endl;
	return out;
}

/*!
* Defines the operator << of class MotoristaIndisponivel and outputs a driver's unavailability on a specific date.
* @param out ostream reference
* @param m object reference of class MotoristaIndisponivel
* */
ostream & operator<<(ostream &out, const MotoristaIndisponivel &m)
{
	if(m.getRegular())
		out << "Nao existe motorista disponivel" << endl;
	else
		out << "Motorista indisponivel para o dia: " << m.getDate() << endl;
	return out;
}

/*!
* Defines the operator << of class MotoristaRepetido and outputs a repeated driver's name.
* @param out ostream reference
* @param m object reference of class MotoristaRepetido
* */
ostream & operator <<(ostream &out, const MotoristaRepetido &m)
{
	out << "Motorista Repetido: " << m.getName() << endl;
	return out;
}

/*!
* Defines the operator << of class MotoristaInexistente and outputs a repeated driver's name.
* @param out ostream reference
* @param v object reference of class MotoristaInexistente
* */
ostream & operator <<(ostream &out, const MotoristaInexistente &m)
{
	out << "Motorista Inexistente: " << m.getName() << endl;
	return out;
}

/*!
* Defines the operator << of class OficinaRepetida and outputs a repeated garage's name.
* @param out ostream reference
* @param o object reference of class OficinaRepetida
* */
ostream & operator <<(ostream &out, const OficinaRepetida &o)
{
	out << "Oficina Repetida: " << o.getName() << endl;
	return out;
}

/*!
* Defines the operator << of class OficinaInexistente and outputs a nonexistent garage's name.
* @param out ostream reference
* @param o object reference of class OficinaInexistente
* */
ostream & operator <<(ostream &out, const OficinaInexistente &o)
{
	out << "Oficina Inexistente: " << o.getName() << endl;
	return out;
}

/*!
* Defines the operator << of class VeiculoEmReparacao and outputs the name of the vehicle under repair.
* @param out ostream reference
* @param o object reference of class VeiculoEmReparacao
* */
ostream & operator <<(ostream &out, const VeiculoEmReparacao &v)
{
	out << "Veiculo " << v.getId() << " em reparacao." << endl;
	return out;
}

/*!
* Defines the operator << of class VeiculoJaEmReparacao and outputs the name of the vehicle already under repair.
* @param out ostream reference
* @param o object reference of class VeiculoJaEmReparacao
* */
ostream & operator<<(ostream & out, const VeiculoJaEmReparacao & v)
{
	out << "Veiculo " << v.getId() << " ja se encontra em reparacao." << endl;
	return out;
}

/*!
* Defines the operator << of class OficinaComVeiculos and outputs the name of the garage with vehicles.
* @param out ostream reference
* @param o object reference of class OficinaComVeiculos
* */
ostream & operator <<(ostream &out, const OficinaComVeiculos &o)
{
	out << "Oficina " << o.getName() << " ainda tem veiculos da empresa." << endl;
	return out;
}

/*!
* Defines the operator << of class OficinaMuitoLonge and outputs the maximum distance from the company's garage
* @param out ostream reference
* @param o object reference of class OficinaMuitoLonge
* */
ostream & operator <<(ostream &out, const OficinaMuitoLonge &o)
{
	out << "Nenhuma oficina disponivel a menos de " << o.getDistance() << "km de distancia." << endl;
	return out;
}
