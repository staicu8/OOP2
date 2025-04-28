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
    virtual ~Persoana();


    std::string getNume() const;
    void setNume(const std::string& nume);
    std::string getPrenume() const;
    void setPrenume(const std::string& prenume);
    std::string getCNP() const;
    void setCNP(const std::string& CNP);
    int getVarsta() const;
    void setVarsta(int varsta);

    virtual void afisare(std::ostream& os) const;


    virtual std::string getTip() const = 0;


    Persoana& operator=(const Persoana& other);
    bool operator==(const Persoana& other) const;


    friend std::ostream& operator<<(std::ostream& os, const Persoana& persoana);
    friend std::istream& operator>>(std::istream& is, Persoana& persoana);
};

#endif // PERSOANA_H