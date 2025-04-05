#ifndef REZERVARE_H
#define REZERVARE_H

#include "Client.h" // Include definitia Client
#include "Camera.h" // Include definitia Camera
#include <string>
#include <iostream>

class Rezervare {
private:
    static int numarTotalRezervari; // Contor static pentru ID-uri
    int id;
    Client client; // Contine obiect Client (copie)
    Camera camera; // Contine obiect Camera (copie) - Atentie, starea 'ocupata' aici e independenta!
    std::string dataCheckIn;
    std::string dataCheckOut;
    int numarZile;
    double pretTotal; // Calculat
    bool platita;

public:
    // Constructori
    Rezervare();
    Rezervare(const Client& client, const Camera& camera, const std::string& dataCheckIn,
              const std::string& dataCheckOut, int numarZile, bool platita = false);
    Rezervare(const Rezervare& other);

    // Destructor
    ~Rezervare();

    // Getteri și setteri
    int getId() const;
    // Returnam referinte constante pentru eficienta si pentru a vedea starea curenta
    const Client& getClientRef() const;
    void setClient(const Client& client);
    const Camera& getCameraRef() const;
    void setCamera(const Camera& camera); // Permite schimbarea camerei unei rezervari? Reanalizeaza logica.
    std::string getDataCheckIn() const;
    void setDataCheckIn(const std::string& data);
    std::string getDataCheckOut() const;
    void setDataCheckOut(const std::string& data);
    int getNumarZile() const;
    void setNumarZile(int zile); // Ar trebui sa recalculeze pretul?
    double getPretTotal() const;
    // void setPretTotal(double pret); // Pretul e calculat, nu setat direct
    bool isPlatita() const;
    void setPlatita(bool platita);

    // Metode
    void calculeazaPretTotal(); // Metoda pentru a (re)calcula pretul
    void afisare() const;

    // Operatori
    Rezervare& operator=(const Rezervare& other);
    bool operator==(const Rezervare& other) const; // Compara pe baza ID-ului

    // Declaratii friend
    friend std::ostream& operator<<(std::ostream& os, const Rezervare& rezervare);
    friend std::istream& operator>>(std::istream& is, Rezervare& rezervare); // Citirea unei rezervari necesita context (Client, Camera existenti) - dificil de implementat generic
};

#endif // REZERVARE_H