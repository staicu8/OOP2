#include "Client.h"
#include <iostream>


Client::Client() : Persoana(), numarRezervari(0), clientFidel(false) {}

Client::Client(const std::string& nume, const std::string& prenume, const std::string& CNP,
               int varsta, int numarRezervari, bool clientFidel)
    : Persoana(nume, prenume, CNP, varsta), numarRezervari(numarRezervari), clientFidel(clientFidel) {}

Client::Client(const Client& other)
    : Persoana(other), numarRezervari(other.numarRezervari), clientFidel(other.clientFidel) {}


Client::~Client() {}


int Client::getNumarRezervari() const { return numarRezervari; }
void Client::setNumarRezervari(int numarRezervari) { this->numarRezervari = numarRezervari; }
bool Client::isClientFidel() const { return clientFidel; }
void Client::setClientFidel(bool clientFidel) { this->clientFidel = clientFidel; }


void Client::afisare(std::ostream& os) const {
    Persoana::afisare(os);

    os << ", Tip: " << getTip()
       << ", Numar Rezervari: " << numarRezervari
       << ", Client Fidel: " << (clientFidel ? "Da" : "Nu");
}

std::string Client::getTip() const {
    return "Client";
}


Client& Client::operator=(const Client& other) {
    if (this != &other) {
        Persoana::operator=(other);
        numarRezervari = other.numarRezervari;
        clientFidel = other.clientFidel;
    }
    return *this;
}

bool Client::operator==(const Client& other) const {

    return Persoana::operator==(other) &&
           numarRezervari == other.numarRezervari &&
           clientFidel == other.clientFidel;
}


std::ostream& operator<<(std::ostream& os, const Client& client) {

    client.afisare(os);
    return os;
}

std::istream& operator>>(std::istream& is, Client& client) {

    is >> static_cast<Persoana&>(client);
    std::cout << "Numar rezervari initiale: "; is >> client.numarRezervari;
    std::cout << "Este client fidel (1=Da, 0=Nu): ";
    int fidelInput;
    is >> fidelInput;
    client.clientFidel = (fidelInput == 1);
    return is;
}