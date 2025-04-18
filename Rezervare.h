#ifndef REZERVARE_H
#define REZERVARE_H

#include "Client.h" // Client include Persoana->IAfisabil
#include "Camera.h" // Camera include TipCamera->IAfisabil
#include <string>
#include <iostream>

class Rezervare : public IAfisabil { // Mosteneste interfata
private:
    static int numarTotalRezervari;
    int id;
    Client client; // Contine obiect Client (copie)
    Camera camera; // Contine obiect Camera (copie)
    std::string dataCheckIn;
    std::string dataCheckOut;
    int numarZile;
    double pretTotal;
    bool platita;

public:
    Rezervare();
    Rezervare(const Client& client, const Camera& camera, const std::string& dataCheckIn,
              const std::string& dataCheckOut, int numarZile, bool platita = false);
    Rezervare(const Rezervare& other);
    ~Rezervare();

    // Getteri / Setteri
    int getId() const;
    const Client& getClientRef() const;
    void setClient(const Client& client);
    const Camera& getCameraRef() const;
    void setCamera(const Camera& camera);
    std::string getDataCheckIn() const;
    void setDataCheckIn(const std::string& data);
    std::string getDataCheckOut() const;
    void setDataCheckOut(const std::string& data);
    int getNumarZile() const;
    void setNumarZile(int zile);
    double getPretTotal() const;
    bool isPlatita() const;
    void setPlatita(bool platita);

    // Metode
    void calculeazaPretTotal();
    // Implementarea interfetei IAfisabil
    void afisare(std::ostream& os) const;

    // Operatori
    Rezervare& operator=(const Rezervare& other);
    bool operator==(const Rezervare& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Rezervare& rezervare);
    friend std::istream& operator>>(std::istream& is, Rezervare& rezervare);
};

#endif // REZERVARE_H