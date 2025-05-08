#ifndef CLIENT_H
#define CLIENT_H

#include "Persoana.h"
#include <string>
#include <iostream>

class Client : public Persoana {
private:
    int m_numar_rezervari;
    bool m_client_fidel;

public:
    Client();
    Client(const std::string& nume, const std::string& prenume, const std::string& cnp,
           int varsta, int numar_rezervari = 0, bool client_fidel = false);
    Client(const Client& other);
    ~Client();

    int GetNumarRezervari() const;
    void SetNumarRezervari(int numar_rezervari);
    bool IsClientFidel() const;
    void SetClientFidel(bool client_fidel);

    void Afisare(std::ostream& os) const;

    std::string GetTip() const;
    Client& operator=(const Client& other);
    bool operator==(const Client& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Client& client);
    friend std::istream& operator>>(std::istream& is, Client& client);
};

#endif // CLIENT_H