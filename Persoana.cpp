#include "Persoana.h"
#include <iostream> // Inclus pentru implementarea operatorilor << si >> daca e nevoie

// Constructori
Persoana::Persoana() : varsta(0) {
    // Implementare constructor default
    // std::cout << "Constructor Persoana (default)" << std::endl;
}

Persoana::Persoana(const std::string& nume, const std::string& prenume, const std::string& CNP, int varsta)
    : nume(nume), prenume(prenume), CNP(CNP), varsta(varsta) {
    // Implementare constructor parametrizat
    // std::cout << "Constructor Persoana (parametrizat): " << nume << std::endl;
}

Persoana::Persoana(const Persoana& other)
    : nume(other.nume), prenume(other.prenume), CNP(other.CNP), varsta(other.varsta) {
    // Implementare constructor de copiere
    // std::cout << "Constructor Persoana (copiere): " << nume << std::endl;
}

// Destructor
Persoana::~Persoana() {
    // Implementare destructor
    // std::cout << "Destructor Persoana: " << nume << std::endl;
}

// Getteri și setteri
std::string Persoana::getNume() const { return nume; }
void Persoana::setNume(const std::string& nume) { this->nume = nume; }
std::string Persoana::getPrenume() const { return prenume; }
void Persoana::setPrenume(const std::string& prenume) { this->prenume = prenume; }
std::string Persoana::getCNP() const { return CNP; }
void Persoana::setCNP(const std::string& CNP) { this->CNP = CNP; } // Atentie la validare CNP in implementarea reala
int Persoana::getVarsta() const { return varsta; }
void Persoana::setVarsta(int varsta) { this->varsta = varsta; } // Atentie la validare varsta

// Metode virtuale
void Persoana::afisare() const {
    std::cout << "Nume: " << nume << ", Prenume: " << prenume
              << ", CNP: " << CNP << ", Varsta: " << varsta;
}

std::string Persoana::getTip() const {
    return "Persoana"; // Tipul de baza
}

// Operatori
Persoana& Persoana::operator=(const Persoana& other) {
    if (this != &other) {
        nume = other.nume;
        prenume = other.prenume;
        CNP = other.CNP;
        varsta = other.varsta;
    }
    return *this;
}

bool Persoana::operator==(const Persoana& other) const {
    // Comparatie bazata pe CNP, presupunand ca este unic
    return CNP == other.CNP;
}

// Implementarea operatorilor stream (prieteni)
std::ostream& operator<<(std::ostream& os, const Persoana& persoana) {
    os << "Nume: " << persoana.nume << ", Prenume: " << persoana.prenume
       << ", CNP: " << persoana.CNP << ", Varsta: " << persoana.varsta;
    return os;
}

std::istream& operator>>(std::istream& is, Persoana& persoana) {
    std::cout << "Nume: "; is >> persoana.nume;
    std::cout << "Prenume: "; is >> persoana.prenume;
    std::cout << "CNP: "; is >> persoana.CNP;
    std::cout << "Varsta: "; is >> persoana.varsta;
    // Adauga validari daca e necesar
    return is;
}