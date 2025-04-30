#ifndef CLIENT_H
#define CLIENT_H

#include "Persoana.h"
#include <string>
#include <iostream>

class Client : public Persoana {
private:
    int numarRezervari;
    bool clientFidel;

public:
    Client();
    Client(const std::string& nume, const std::string& prenume, const std::string& CNP,
           int varsta, int numarRezervari = 0, bool clientFidel = false);
    Client(const Client& other);
    ~Client();


    int getNumarRezervari() const;
    void setNumarRezervari(int numarRezervari);
    bool isClientFidel() const;
    void setClientFidel(bool clientFidel);


    void afisare(std::ostream& os) const;

    std::string getTip() const;
    Client& operator=(const Client& other);
    bool operator==(const Client& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Client& client);
    friend std::istream& operator>>(std::istream& is, Client& client);
};

#endif // CLIENT_H