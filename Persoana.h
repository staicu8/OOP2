#ifndef PERSOANA_H
#define PERSOANA_H

#include <string>
#include <iostream> // Necesat pentru std::ostream, std::istream

class Persoana {
private:
    std::string nume;
    std::string prenume;
    std::string CNP;
    int varsta;

public:
    // Constructori
    Persoana();
    Persoana(const std::string& nume, const std::string& prenume, const std::string& CNP, int varsta);
    Persoana(const Persoana& other);

    // Destructor virtual (important pentru clasele de baza)
    virtual ~Persoana();

    // Getteri și setteri
    std::string getNume() const;
    void setNume(const std::string& nume);
    std::string getPrenume() const;
    void setPrenume(const std::string& prenume);
    std::string getCNP() const;
    void setCNP(const std::string& CNP);
    int getVarsta() const;
    void setVarsta(int varsta);

    // Metode virtuale
    virtual void afisare() const;
    virtual std::string getTip() const; // Returneaza tipul persoanei (ex: "Client", "Angajat")

    // Operatori
    Persoana& operator=(const Persoana& other);
    bool operator==(const Persoana& other) const;

    // Declaratii friend pentru operatorii stream
    friend std::ostream& operator<<(std::ostream& os, const Persoana& persoana);
    friend std::istream& operator>>(std::istream& is, Persoana& persoana);
};

#endif // PERSOANA_H