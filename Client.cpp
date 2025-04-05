#include "Client.h"
#include <iostream>

// Constructori
Client::Client() : Persoana(), numarRezervari(0), clientFidel(false) {
    // std::cout << "Constructor Client (default)" << std::endl;
}

Client::Client(const std::string& nume, const std::string& prenume, const std::string& CNP,
               int varsta, int numarRezervari, bool clientFidel)
    : Persoana(nume, prenume, CNP, varsta), numarRezervari(numarRezervari), clientFidel(clientFidel) {
    // std::cout << "Constructor Client (parametrizat): " << getNume() << std::endl;
}

Client::Client(const Client& other)
    : Persoana(other), numarRezervari(other.numarRezervari), clientFidel(other.clientFidel) {
    // std::cout << "Constructor Client (copiere): " << getNume() << std::endl;
}

// Destructor
Client::~Client() {
    // std::cout << "Destructor Client: " << getNume() << std::endl;
}

// Getteri și setteri
int Client::getNumarRezervari() const { return numarRezervari; }
void Client::setNumarRezervari(int numarRezervari) { this->numarRezervari = numarRezervari; }
bool Client::isClientFidel() const { return clientFidel; }
void Client::setClientFidel(bool clientFidel) { this->clientFidel = clientFidel; }

// Metode suprascrise
void Client::afisare() const {
    Persoana::afisare(); // Apelam metoda din clasa de baza
    std::cout << ", Tip: " << getTip() // Apelam getTip() local
              << ", Numar Rezervari: " << numarRezervari
              << ", Client Fidel: " << (clientFidel ? "Da" : "Nu");
}

std::string Client::getTip() const {
    return "Client";
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
    // Afiseaza partea de Persoana si apoi datele specifice Clientului
    os << static_cast<const Persoana&>(client) // Facem cast pentru a apela op<< din Persoana
       << ", Tip: Client"
       << ", Numar Rezervari: " << client.numarRezervari
       << ", Client Fidel: " << (client.clientFidel ? "Da" : "Nu");
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
    // Adauga validari daca e necesar
    return is;
}