#ifndef PERSOANA_H
#define PERSOANA_H

#include <string>
#include <iostream>
#include "IAfisabil.h" // Include noua interfata

// Persoana este o clasa de baza abstracta SI implementeaza IAfisabil
class Persoana : public IAfisabil {
private:
    std::string nume;
    std::string prenume;
    std::string CNP;
    int varsta;

public:
    Persoana();
    Persoana(const std::string& nume, const std::string& prenume, const std::string& CNP, int varsta);
    Persoana(const Persoana& other);
    virtual ~Persoana(); // Destructorul ramane virtual

    // Getteri/Setteri (raman la fel)
    std::string getNume() const;
    void setNume(const std::string& nume);
    std::string getPrenume() const;
    void setPrenume(const std::string& prenume);
    std::string getCNP() const;
    void setCNP(const std::string& CNP);
    int getVarsta() const;
    void setVarsta(int varsta);

    // Implementarea interfetei IAfisabil (devine virtuala normala, nu pura)
    // O vom implementa in Persoana.cpp pentru datele comune.
    // Clasele derivate o pot suprascrie (override).
    virtual void afisare(std::ostream& os) const;

    // getTip ramane pur virtuala - specifica ierarhiei Persoana
    virtual std::string getTip() const = 0;

    // Operatori (raman la fel)
    Persoana& operator=(const Persoana& other);
    bool operator==(const Persoana& other) const;

    // Operatorii stream pot fi prieteni in continuare, dar implementarea se schimba
    friend std::ostream& operator<<(std::ostream& os, const Persoana& persoana);
    friend std::istream& operator>>(std::istream& is, Persoana& persoana);
};

#endif // PERSOANA_H