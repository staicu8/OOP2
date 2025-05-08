#ifndef PERSOANA_H
#define PERSOANA_H

#include <string>
#include <iostream>
#include "IAfisabil.h"

class Persoana : public IAfisabil {
private:
    std::string m_nume;
    std::string m_prenume;
    std::string m_cnp;
    int m_varsta;

public:
    Persoana();
    Persoana(const std::string& nume, const std::string& prenume, const std::string& cnp, int varsta);
    Persoana(const Persoana& other);
    virtual ~Persoana();

    std::string GetNume() const;
    void SetNume(const std::string& nume);
    std::string GetPrenume() const;
    void SetPrenume(const std::string& prenume);
    std::string GetCNP() const;
    void SetCNP(const std::string& cnp);
    int GetVarsta() const;
    void SetVarsta(int varsta);

    virtual void Afisare(std::ostream& os) const;

    virtual std::string GetTip() const = 0;

    Persoana& operator=(const Persoana& other);
    bool operator==(const Persoana& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Persoana& persoana);
    friend std::istream& operator>>(std::istream& is, Persoana& persoana);
};

#endif // PERSOANA_H