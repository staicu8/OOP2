#include "Angajat.h"
#include <iostream>

// Constructori
Angajat::Angajat() : Persoana(), salariu(0.0), aniExperienta(0) {}

Angajat::Angajat(std::string nume, std::string prenume, std::string CNP,
                 int varsta, const std::string& functie, double salariu, int aniExperienta)
    : Persoana(nume, prenume, CNP, varsta), functie(functie), salariu(salariu), aniExperienta(aniExperienta) {}

Angajat::Angajat(const Angajat& other)
    : Persoana(other), functie(other.functie), salariu(other.salariu), aniExperienta(other.aniExperienta) {}

// Destructor
Angajat::~Angajat() {}

// Getteri și setteri
std::string Angajat::getFunctie() const { return functie; }
void Angajat::setFunctie(const std::string& functie) { this->functie = functie; }
double Angajat::getSalariu() const { return salariu; }
void Angajat::setSalariu(double salariu) { this->salariu = salariu; }
int Angajat::getAniExperienta() const { return aniExperienta; }
void Angajat::setAniExperienta(int ani) { this->aniExperienta = ani; }

// Implementare/Suprascriere metode virtuale
void Angajat::afisare(std::ostream& os) const {
    Persoana::afisare(os); // Apelam implementarea din clasa de baza CU parametrul 'os'
    // Adaugam specificul Angajatului
    os << ", Tip: " << getTip() // Apelam getTip() local
       << ", Functie: " << functie
       << ", Salariu: " << salariu << " RON"
       << ", Experienta: " << aniExperienta << " ani";
}

std::string Angajat::getTip() const {
    return "Angajat"; // Implementarea specifica pentru Angajat
}

// Operatori
Angajat& Angajat::operator=(const Angajat& other) {
    if (this != &other) {
        Persoana::operator=(other); // Apelam op= din baza
        functie = other.functie;
        salariu = other.salariu;
        aniExperienta = other.aniExperienta;
    }
    return *this;
}

bool Angajat::operator==(const Angajat& other) const {
    // Comparam partea de Persoana si datele specifice Angajatului
    return Persoana::operator==(other) &&
           functie == other.functie &&
           salariu == other.salariu && // Atentie la compararea double!
           aniExperienta == other.aniExperienta;
}

// Implementarea operatorilor stream (prieteni)
std::ostream& operator<<(std::ostream& os, const Angajat& angajat) {
    // Apeleaza metoda virtuala afisare(os) specifica (Angajat::afisare)
    angajat.afisare(os);
    return os;
}

std::istream& operator>>(std::istream& is, Angajat& angajat) {
    is >> static_cast<Persoana&>(angajat); // Citim datele de Persoana
    std::cout << "Functie: "; is >> angajat.functie;
    std::cout << "Salariu: "; is >> angajat.salariu;
    std::cout << "Ani experienta: "; is >> angajat.aniExperienta;
    return is;
}