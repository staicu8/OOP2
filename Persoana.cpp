#include "Persoana.h"
#include <iostream>


Persoana::Persoana() : varsta(0) {}
Persoana::Persoana(const std::string& nume, const std::string& prenume, const std::string& CNP, int varsta)
    : nume(nume), prenume(prenume), CNP(CNP), varsta(varsta) {}
Persoana::Persoana(const Persoana& other)
    : nume(other.nume), prenume(other.prenume), CNP(other.CNP), varsta(other.varsta) {}
Persoana::~Persoana() {}
std::string Persoana::getNume() const { return nume; }
void Persoana::setNume(const std::string& nume) { this->nume = nume; }
std::string Persoana::getPrenume() const { return prenume; }
void Persoana::setPrenume(const std::string& prenume) { this->prenume = prenume; }
std::string Persoana::getCNP() const { return CNP; }
void Persoana::setCNP(const std::string& CNP) { this->CNP = CNP; }
int Persoana::getVarsta() const { return varsta; }
void Persoana::setVarsta(int varsta) { this->varsta = varsta; }
Persoana& Persoana::operator=(const Persoana& other) { /* ... */ return *this; }
bool Persoana::operator==(const Persoana& other) const { return CNP == other.CNP; }
std::istream& operator>>(std::istream& is, Persoana& persoana) {
    std::cout << "Nume: "; // <-- Promptul
    is >> persoana.nume;   // <-- Citirea
    std::cout << "Prenume: "; // <-- Promptul
    is >> persoana.prenume; // <-- Citirea
    std::cout << "CNP: "; // <-- Promptul
    is >> persoana.CNP;     // <-- Citirea
    std::cout << "Varsta: "; // <-- Promptul
    is >> persoana.varsta; // <-- Citirea
    return is;
}

// --- Implementare metoda virtuala din IAfisabil ---

void Persoana::afisare(std::ostream& os) const {
    os << "Nume: " << nume << ", Prenume: " << prenume<< ", CNP: " << CNP << ", Varsta: " << varsta;

}





std::ostream& operator<<(std::ostream& os, const Persoana& persoana) {
    persoana.afisare(os);
    return os;
}