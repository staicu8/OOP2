#include "Client.h"
#include <iostream>

// Constructori
Client::Client() : Persoana(), numarRezervari(0), clientFidel(false) {}

Client::Client(const std::string& nume, const std::string& prenume, const std::string& CNP,
               int varsta, int numarRezervari, bool clientFidel)
    : Persoana(nume, prenume, CNP, varsta), numarRezervari(numarRezervari), clientFidel(clientFidel) {}

Client::Client(const Client& other)
    : Persoana(other), numarRezervari(other.numarRezervari), clientFidel(other.clientFidel) {}

// Destructor
Client::~Client() {}

// Getteri și setteri
int Client::getNumarRezervari() const { return numarRezervari; }
void Client::setNumarRezervari(int numarRezervari) { this->numarRezervari = numarRezervari; }
bool Client::isClientFidel() const { return clientFidel; }
void Client::setClientFidel(bool clientFidel) { this->clientFidel = clientFidel; }

// Implementare/Suprascriere metode virtuale
void Client::afisare(std::ostream& os) const {
    Persoana::afisare(os); // Apelam implementarea din clasa de baza CU parametrul 'os'
    // Adaugam specificul Clientului
    os << ", Tip: " << getTip() // Apelam getTip() local
       << ", Numar Rezervari: " << numarRezervari
       << ", Client Fidel: " << (clientFidel ? "Da" : "Nu");
}

std::string Client::getTip() const {
    return "Client"; // Implementarea specifica pentru Client
}

// Operatori
Client& Client::operator=(const Client& other) {
    if (this != &other) {
        Persoana::operator=(other); // Apelam operatorul= din clasa de baza
        numarRezervari = other.numarRezervari;
        clientFidel = other.clientFidel;
    }
    return *this;
}

bool Client::operator==(const Client& other) const {
    // Comparam partea de Persoana si datele specifice Clientului
    return Persoana::operator==(other) &&
           numarRezervari == other.numarRezervari &&
           clientFidel == other.clientFidel;
}

// Implementarea operatorilor stream (prieteni)
std::ostream& operator<<(std::ostream& os, const Client& client) {
    // Apeleaza metoda virtuala afisare(os) specifica (Client::afisare)
    client.afisare(os);
    return os;
}

std::istream& operator>>(std::istream& is, Client& client) {
    // Citeste partea de Persoana si apoi datele specifice Clientului
    is >> static_cast<Persoana&>(client); // Citeste datele de Persoana
    std::cout << "Numar rezervari initiale: "; is >> client.numarRezervari;
    std::cout << "Este client fidel (1=Da, 0=Nu): ";
    int fidelInput;
    is >> fidelInput;
    client.clientFidel = (fidelInput == 1);
    return is;
}