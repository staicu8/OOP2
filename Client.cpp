#include "Client.h"
#include <iostream>

Client::Client() : Persoana(), m_numar_rezervari(0), m_client_fidel(false) {}

Client::Client(const std::string& nume, const std::string& prenume, const std::string& cnp,
               int varsta, int numar_rezervari, bool client_fidel)
    : Persoana(nume, prenume, cnp, varsta), m_numar_rezervari(numar_rezervari), m_client_fidel(client_fidel) {}

Client::Client(const Client& other)
    : Persoana(other), m_numar_rezervari(other.m_numar_rezervari), m_client_fidel(other.m_client_fidel) {}

Client::~Client() {}

int Client::GetNumarRezervari() const { return m_numar_rezervari; }
void Client::SetNumarRezervari(int numar_rezervari) { this->m_numar_rezervari = numar_rezervari; }
bool Client::IsClientFidel() const { return m_client_fidel; }
void Client::SetClientFidel(bool client_fidel) { this->m_client_fidel = client_fidel; }

void Client::Afisare(std::ostream& os) const {
    Persoana::Afisare(os);

    os << ", Tip: " << GetTip()
       << ", Numar Rezervari: " << m_numar_rezervari
       << ", Client Fidel: " << (m_client_fidel ? "Da" : "Nu");
}

std::string Client::GetTip() const {
    return "Client";
}

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
    is >> static_cast<Persoana&>(client);
    std::cout << "Numar rezervari initiale: "; is >> client.m_numar_rezervari;
    std::cout << "Este client fidel (1=Da, 0=Nu): ";
    int fidel_input;
    is >> fidel_input;
    client.m_client_fidel = (fidel_input == 1);
    return is;
}