#include "Angajat.h"
#include <iostream>

Angajat::Angajat() : Persoana(), m_salariu(0.0), m_ani_experienta(0) {}

Angajat::Angajat(std::string nume, std::string prenume, std::string cnp,
                 int varsta, const std::string& functie, double salariu, int ani_experienta)
    : Persoana(nume, prenume, cnp, varsta), m_functie(functie), m_salariu(salariu), m_ani_experienta(ani_experienta) {}

Angajat::Angajat(const Angajat& other)
    : Persoana(other), m_functie(other.m_functie), m_salariu(other.m_salariu), m_ani_experienta(other.m_ani_experienta) {}

Angajat::~Angajat() {}

std::string Angajat::GetFunctie() const { return m_functie; }
void Angajat::SetFunctie(const std::string& functie) { this->m_functie = functie; }
double Angajat::GetSalariu() const { return m_salariu; }
void Angajat::SetSalariu(double salariu) { this->m_salariu = salariu; }
int Angajat::GetAniExperienta() const { return m_ani_experienta; }
void Angajat::SetAniExperienta(int ani) { this->m_ani_experienta = ani; }

void Angajat::Afisare(std::ostream& os) const {
    Persoana::Afisare(os);

    os << ", Tip: " << GetTip()
       << ", Functie: " << m_functie
       << ", Salariu: " << m_salariu << " RON"
       << ", Experienta: " << m_ani_experienta << " ani";
}

std::string Angajat::GetTip() const {
    return "Angajat";
}

Angajat& Angajat::operator=(const Angajat& other) {
    if (this != &other) {
        Persoana::operator=(other);
        m_functie = other.m_functie;
        m_salariu = other.m_salariu;
        m_ani_experienta = other.m_ani_experienta;
    }
    return *this;
}

bool Angajat::operator==(const Angajat& other) const {
    return Persoana::operator==(other) &&
           m_functie == other.m_functie &&
           m_salariu == other.m_salariu &&
           m_ani_experienta == other.m_ani_experienta;
}

std::ostream& operator<<(std::ostream& os, const Angajat& angajat) {
    angajat.Afisare(os);
    return os;
}

std::istream& operator>>(std::istream& is, Angajat& angajat) {
    is >> static_cast<Persoana&>(angajat);
    std::cout << "Functie: "; is >> angajat.m_functie;
    std::cout << "Salariu: "; is >> angajat.m_salariu;
    std::cout << "Ani experienta: "; is >> angajat.m_ani_experienta;
    return is;
}