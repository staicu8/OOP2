#ifndef REZERVARE_H
#define REZERVARE_H

#include "Client.h"
#include "Camera.h"
#include <string>
#include <iostream>
#include <data.h>
class Rezervare : public IAfisabil {
private:
    static int numarTotalRezervari;
    int id;
    Client client;
    Camera camera;
    Data dataCheckIn;
    Data dataCheckOut;
    int numarZile;
    double pretTotal;
    bool platita;

public:
    Rezervare();
    Rezervare(const Client& client, const Camera& camera, const Data& dataCheckIn,
              const Data& dataCheckOut, int numarZile, bool platita = false);
    Rezervare(const Rezervare& other);
    ~Rezervare();

    int getId() const;
    const Client& getClientRef() const;
    void setClient(const Client& client);
    const Camera& getCameraRef() const;
    void setCamera(const Camera& camera);
    Data getDataCheckIn() const;
    void setDataCheckIn(const Data& data);
    Data getDataCheckOut() const;
    void setDataCheckOut(const Data& data);
    int getNumarZile() const;
    void setNumarZile(int zile);
    double getPretTotal() const;
    bool isPlatita() const;
    void setPlatita(bool platita);


    void calculeazaPretTotal();

    void afisare(std::ostream& os) const;

    Rezervare& operator=(const Rezervare& other);
    bool operator==(const Rezervare& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Rezervare& rezervare);
    friend std::istream& operator>>(std::istream& is, Rezervare& rezervare);
};

#endif // REZERVARE_H