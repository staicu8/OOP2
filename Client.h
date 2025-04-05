#ifndef CLIENT_H
#define CLIENT_H

#include "Persoana.h" // Include clasa de baza
#include <string>
#include <iostream>

class Client : public Persoana {
private:
    int numarRezervari;
    bool clientFidel;

public:
    // Constructori
    Client();
    Client(const std::string& nume, const std::string& prenume, const std::string& CNP,
           int varsta, int numarRezervari = 0, bool clientFidel = false);
    Client(const Client& other);

    // Destructor
    ~Client() override;

    // Getteri și setteri
    int getNumarRezervari() const;
    void setNumarRezervari(int numarRezervari);
    bool isClientFidel() const;
    void setClientFidel(bool clientFidel);

    // Metode suprascrise
    void afisare() const override;
    std::string getTip() const override;

    // Operatori
    Client& operator=(const Client& other);
    bool operator==(const Client& other) const; // Poate compara si date specifice clientului

    // Declaratii friend
    friend std::ostream& operator<<(std::ostream& os, const Client& client);
    friend std::istream& operator>>(std::istream& is, Client& client);
};

#endif // CLIENT_H