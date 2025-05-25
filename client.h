#ifndef CLIENT_H
#define CLIENT_H

#include "persoana.h"
#include <string>
#include <iostream>

class Client : public Persoana {
private:
    int m_numar_rezervari;
    bool m_client_fidel;//Daca are mai mult de 5 rezervari

public:
    //Initializare Constructor,Constructor cu parametrii si Constructor de copiere
    Client();
    Client(const std::string& nume, const std::string& prenume, const std::string& cnp,
           int varsta, int numar_rezervari = 0);
    Client(const Client& other);

    //Destructor
    ~Client();


//Getteri si Setteri
    int GetNumarRezervari() const;
    void SetNumarRezervari(int numar_rezervari);
    bool IsClientFidel() const;
    // void SetClientFidel(bool client_fidel);

    //Suprascrie functia pur virtuala Afisare din interfata
    void Afisare(std::ostream& os) const;

    //Suprascrie functia pur virtuala GetTip din Persoana
    std::string GetTip() const;

    //Supraincarcare operatori
    Client& operator=(const Client& other);
    bool operator==(const Client& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Client& client);
    friend std::istream& operator>>(std::istream& is, Client& client);
};

#endif // CLIENT_H