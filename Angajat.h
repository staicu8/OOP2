#ifndef ANGAJAT_H
#define ANGAJAT_H

#include "Persoana.h" // Include clasa de baza
#include <string>
#include <iostream>

class Angajat : public Persoana {
private:
    std::string functie;
    double salariu;
    int aniExperienta;

public:
    // Constructori
    Angajat();
    Angajat(const std::string& nume, const std::string& prenume, const std::string& CNP,
            int varsta, const std::string& functie, double salariu, int aniExperienta);
    Angajat(const Angajat& other);

    // Destructor
    ~Angajat() override;

    // Getteri și setteri
    std::string getFunctie() const;
    void setFunctie(const std::string& functie);
    double getSalariu() const;
    void setSalariu(double salariu);
    int getAniExperienta() const;
    void setAniExperienta(int ani);

    // Metode suprascrise
    void afisare() const override;
    std::string getTip() const override;

    // Operatori
    Angajat& operator=(const Angajat& other);
    bool operator==(const Angajat& other) const; // Poate compara si date specifice angajatului

    // Declaratii friend
    friend std::ostream& operator<<(std::ostream& os, const Angajat& angajat);
    friend std::istream& operator>>(std::istream& is, Angajat& angajat);
};

#endif // ANGAJAT_H