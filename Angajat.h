#ifndef ANGAJAT_H
#define ANGAJAT_H

#include "Persoana.h"
#include <string>
#include <iostream>

class Angajat : public Persoana {
private:
    std::string m_functie;
    double m_salariu;
    int m_ani_experienta;

public:
    Angajat();
    Angajat(std::string nume, std::string prenume, std::string cnp, int varsta, const std::string& functie, double salariu, int ani_experienta);
    Angajat(const Angajat& other);
    ~Angajat();

    std::string GetFunctie() const;
    void SetFunctie(const std::string& functie);
    double GetSalariu() const;
    void SetSalariu(double salariu);
    int GetAniExperienta() const;
    void SetAniExperienta(int ani);

    void Afisare(std::ostream& os) const;

    std::string GetTip() const;

    Angajat& operator=(const Angajat& other);
    bool operator==(const Angajat& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Angajat& angajat);
    friend std::istream& operator>>(std::istream& is, Angajat& angajat);
};

#endif // ANGAJAT_H