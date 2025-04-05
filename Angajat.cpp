#include "Angajat.h"
#include <iostream>

// Constructori
Angajat::Angajat() : Persoana(), salariu(0.0), aniExperienta(0) {
    // std::cout << "Constructor Angajat (default)" << std::endl;
}

Angajat::Angajat(const std::string& nume, const std::string& prenume, const std::string& CNP,
                 int varsta, const std::string& functie, double salariu, int aniExperienta)
    : Persoana(nume, prenume, CNP, varsta), functie(functie), salariu(salariu), aniExperienta(aniExperienta) {
    // std::cout << "Constructor Angajat (parametrizat): " << getNume() << std::endl;
}

Angajat::Angajat(const Angajat& other)
    : Persoana(other), functie(other.functie), salariu(other.salariu), aniExperienta(other.aniExperienta) {
     // std::cout << "Constructor Angajat (copiere): " << getNume() << std::endl;
}

// Destructor
Angajat::~Angajat() {
     // std::cout << "Destructor Angajat: " << getNume() << std::endl;
}

// Getteri și setteri
std::string Angajat::getFunctie() const { return functie; }
void Angajat::setFunctie(const std::string& functie) { this->functie = functie; }
double Angajat::getSalariu() const { return salariu; }
void Angajat::setSalariu(double salariu) { this->salariu = salariu; } // Validare salariu?
int Angajat::getAniExperienta() const { return aniExperienta; }
void Angajat::setAniExperienta(int ani) { this->aniExperienta = ani; } // Validare ani?

// Metode suprascrise
void Angajat::afisare() const {
    Persoana::afisare(); // Apelam metoda din clasa de baza
    std::cout << ", Tip: " << getTip()
              << ", Functie: " << functie
              << ", Salariu: " << salariu << " RON"
              << ", Experienta: " << aniExperienta << " ani";
}

std::string Angajat::getTip() const {
    return "Angajat";
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
    os << static_cast<const Persoana&>(angajat) // Afisam partea de Persoana
       << ", Tip: Angajat"
       << ", Functie: " << angajat.functie
       << ", Salariu: " << angajat.salariu << " RON"
       << ", Experienta: " << angajat.aniExperienta << " ani";
    return os;
}

std::istream& operator>>(std::istream& is, Angajat& angajat) {
    is >> static_cast<Persoana&>(angajat); // Citim datele de Persoana
    std::cout << "Functie: "; is >> angajat.functie;
    std::cout << "Salariu: "; is >> angajat.salariu;
    std::cout << "Ani experienta: "; is >> angajat.aniExperienta;
    // Adauga validari
    return is;
}