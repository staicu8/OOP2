#ifndef ANGAJAT_H
#define ANGAJAT_H

#include "Persoana.h" // Include si IAfisabil indirect
#include <string>
#include <iostream>

class Angajat : public Persoana {
private:
    std::string functie;
    double salariu;
    int aniExperienta;

public:
    Angajat();
    Angajat(std::string nume, std::string prenume, std::string CNP,int varsta, const std::string& functie, double salariu, int aniExperienta);
    Angajat(const Angajat& other);
    ~Angajat(); // Destructor (fara override in C++98)

    // Getteri / Setteri specifici
    std::string getFunctie() const;
    void setFunctie(const std::string& functie);
    double getSalariu() const;
    void setSalariu(double salariu);
    int getAniExperienta() const;
    void setAniExperienta(int ani);

    // Suprascriem metoda virtuala afisare din Persoana (IAfisabil)
    void afisare(std::ostream& os) const; // Fara override in C++98
    // Suprascriem metoda pur virtuala getTip din Persoana
    std::string getTip() const; // Fara override in C++98

    // Operatori
    Angajat& operator=(const Angajat& other);
    bool operator==(const Angajat& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Angajat& angajat);
    friend std::istream& operator>>(std::istream& is, Angajat& angajat);
};

#endif // ANGAJAT_H