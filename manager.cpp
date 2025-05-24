#include "manager.h"
#include <iostream>

//Mosteneste salariu si ani_experienta din Angajat
//Implementare Constructor,Constructor cu parametrii si Constructor de copiere
Manager::Manager() : Angajat(), m_departament_condus("Nespecificat") {}

Manager::Manager(const std::string& nume, const std::string& prenume, const std::string& cnp, int varsta,
                 double salariu, int ani_experienta, const std::string& departament)
    : Angajat(nume, prenume, cnp, varsta, salariu, ani_experienta), m_departament_condus(departament) {}

Manager::Manager(const Manager& other)
    : Angajat(other), m_departament_condus(other.m_departament_condus)  {}

//Destructor
Manager::~Manager() {}


//Getteri si Setteri
std::string Manager::GetFunctie() const {
    return "Manager"+m_departament_condus;
}

void Manager::SetDepartament(const std::string& departament) {
    m_departament_condus = departament;
}

std::string Manager::GetDepartament() const {
    return m_departament_condus;
}
//Implementeaza functia pur virtuala Afisare din interfata
void Manager::Afisare(std::ostream& os) const {
    Angajat::Afisare(os);

    os << ", Departament: " << m_departament_condus;

}