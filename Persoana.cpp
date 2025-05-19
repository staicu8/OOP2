#include "Persoana.h"
#include <iostream>

Persoana::Persoana() : m_varsta(0) {}
Persoana::Persoana(const std::string& nume, const std::string& prenume, const std::string& cnp, int varsta)
    : m_nume(nume), m_prenume(prenume), m_cnp(cnp), m_varsta(varsta) {}
Persoana::Persoana(const Persoana& other)
    : m_nume(other.m_nume), m_prenume(other.m_prenume), m_cnp(other.m_cnp), m_varsta(other.m_varsta) {}
Persoana::~Persoana() {}

std::string Persoana::GetNume() const { return m_nume; }
void Persoana::SetNume(const std::string& nume) { this->m_nume = nume; }
std::string Persoana::GetPrenume() const { return m_prenume; }
void Persoana::SetPrenume(const std::string& prenume) { this->m_prenume = prenume; }
std::string Persoana::GetCNP() const { return m_cnp; }
void Persoana::SetCNP(const std::string& cnp) { this->m_cnp = cnp; }
int Persoana::GetVarsta() const { return m_varsta; }
void Persoana::SetVarsta(int varsta) { this->m_varsta = varsta; }

Persoana& Persoana::operator=(const Persoana& other) { return *this; }
bool Persoana::operator==(const Persoana& other) const { return m_cnp == other.m_cnp; }

std::istream& operator>>(std::istream& is, Persoana& persoana) {
    std::cout << "Nume: ";
    is >> persoana.m_nume;
    std::cout << "Prenume: ";
    is >> persoana.m_prenume;
    std::cout << "CNP: ";
    is >> persoana.m_cnp;
    std::cout << "Varsta: ";
    is >> persoana.m_varsta;
    return is;
}

void Persoana::Afisare(std::ostream& os) const {
    os << "Nume: " << m_nume << ", Prenume: " << m_prenume << ", CNP: " << m_cnp << ", Varsta: " << m_varsta;
}

std::ostream& operator<<(std::ostream& os, const Persoana& persoana) {
    persoana.Afisare(os);
    return os;
}