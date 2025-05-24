#include "client.h"
#include <iostream>


//Implementare Constructor,Constructor cu parametrii si Constructor de copiere
Client::Client() : Persoana(), m_numar_rezervari(0), m_client_fidel(false) {}

Client::Client(const std::string& nume, const std::string& prenume, const std::string& cnp,
               int varsta, int numar_rezervari)
    : Persoana(nume, prenume, cnp, varsta), m_numar_rezervari(numar_rezervari), m_client_fidel((numar_rezervari>=5)) {}

Client::Client(const Client& other)
    : Persoana(other), m_numar_rezervari(other.m_numar_rezervari), m_client_fidel(other.m_client_fidel) {}

//Destrcuctor
Client::~Client() {}

//Getteri si Setteri
int Client::GetNumarRezervari() const { return m_numar_rezervari; }
void Client::SetNumarRezervari(int numar_rezervari) {
    this->m_numar_rezervari = numar_rezervari;
    this->m_client_fidel = (numar_rezervari>=5);//Daca se schimba numarul de rezervari se poate schimba si fidelitatea
}
bool Client::IsClientFidel() const { return m_client_fidel; }



//Implementeaza functia pur virtuala Afisare din interfata
void Client::Afisare(std::ostream& os) const {
    Persoana::Afisare(os);

    os << ", Tip: " << GetTip()
       << ", Numar Rezervari: " << m_numar_rezervari
       << ", Client Fidel: " << (m_client_fidel ? "Da" : "Nu");
}
//Implementeaza functia pur virtuala GetTip din Persoana
std::string Client::GetTip() const {
    return "Client";
}

//Supraincarcare operatori
Client& Client::operator=(const Client& other) {
    if (this != &other) {
        Persoana::operator=(other);
        m_numar_rezervari = other.m_numar_rezervari;
        m_client_fidel = other.m_client_fidel;
    }
    return *this;
}

bool Client::operator==(const Client& other) const {
    return Persoana::operator==(other) &&
           m_numar_rezervari == other.m_numar_rezervari &&
           m_client_fidel == other.m_client_fidel;
}

std::ostream& operator<<(std::ostream& os, const Client& client) {
    client.Afisare(os);
    return os;
}

std::istream& operator>>(std::istream& is, Client& client) {
    is >> static_cast<Persoana&>(client);//Citeste numele,prenumele,cnp-ul si varsta de la Persoana


    client.SetNumarRezervari(0);
    return is;
}