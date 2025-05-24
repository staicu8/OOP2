#include "angajat.h"
#include <iostream>

//Constructor
Angajat::Angajat() : Persoana(), m_salariu(0.0), m_ani_experienta(0) {}
//Constructor Parametrizat
Angajat::Angajat(std::string nume, std::string prenume, std::string cnp,
                 int varsta, double salariu, int ani_experienta)
    : Persoana(nume, prenume, cnp, varsta), m_salariu(salariu), m_ani_experienta(ani_experienta) {}
//Constructor de copiere
Angajat::Angajat(const Angajat& other)
    : Persoana(other), m_salariu(other.m_salariu), m_ani_experienta(other.m_ani_experienta) {}

//Destructor
Angajat::~Angajat() {}

//Getteri si setteri
double Angajat::GetSalariu() const { return m_salariu; }
void Angajat::SetSalariu(double salariu) {

    this->m_salariu = salariu;
}
int Angajat::GetAniExperienta() const { return m_ani_experienta; }
void Angajat::SetAniExperienta(int ani) { this->m_ani_experienta = ani; }

//Implementeaza functia pur virtuala Afisare din interfata
void Angajat::Afisare(std::ostream& os) const {
    Persoana::Afisare(os);

    os << ", Tip: " << GetTip()
       << ", Salariu: " << m_salariu << " RON"
       << ", Experienta: " << m_ani_experienta << " ani";
}
//Implementeaza functia pur virtuala din Persoana
std::string Angajat::GetTip() const {
    return "Angajat";
}
//Supraincarcarea operatorilor
Angajat& Angajat::operator=(const Angajat& other) {
    //Folosim operatorul = supraincarcat din Persoana sa atribuim acelasi nume,prenume,etc
    if (this != &other) {
        Persoana::operator=(other);
        m_salariu = other.m_salariu;
        m_ani_experienta = other.m_ani_experienta;
    }
    return *this;
}

bool Angajat::operator==(const Angajat& other) const {
    //Folosim operatorul = supraincarcat din Persoana sa verificam daca au acelasi nume,prenume,etc
    return Persoana::operator==(other) &&
           m_salariu == other.m_salariu &&
           m_ani_experienta == other.m_ani_experienta;
}

std::ostream& operator<<(std::ostream& os, const Angajat& angajat) {
    //Folosim functia de afisare
    angajat.Afisare(os);
    return os;
}

std::istream& operator>>(std::istream& is, Angajat& angajat) {
    //Folosim operatorul >> supraincarcat din persoana pentru a citi nume,prenume,etc
    is >> static_cast<Persoana&>(angajat);
    std::cout << "Salariu: "; is >> angajat.m_salariu;
    std::cout << "Ani experienta: "; is >> angajat.m_ani_experienta;
    return is;
}