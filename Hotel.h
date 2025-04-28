#ifndef HOTEL_H
#define HOTEL_H

#include <string>
#include <vector> // Necesar pentru std::vector
#include <iostream>

// Includem doar headerele claselor ALE CAROR POINTERI ii stocam
#include "Camera.h"
#include "Client.h"
#include "Angajat.h"
#include "Rezervare.h"
#include "IAfisabil.h"


class Hotel : public IAfisabil {
private:
    std::string nume;
    std::string adresa;
    int numarStele;


    std::vector<Camera*> camere;
    std::vector<Client*> clienti;
    std::vector<Angajat*> angajati;
    std::vector<Rezervare*> rezervari;


    Hotel(const Hotel& other);
    Hotel& operator=(const Hotel& other);

public:

    Hotel();
    Hotel(const std::string& nume, const std::string& adresa, int numarStele);
    ~Hotel(); // ACUM este FOARTE important

    // Getteri / Setteri
    std::string getNume() const;
    void setNume(const std::string& nume);
    std::string getAdresa() const;
    void setAdresa(const std::string& adresa);
    int getNumarStele() const;
    void setNumarStele(int stele);


    void adaugaCamera(Camera* pCamera);
    void adaugaClient(Client* pClient);
    void adaugaAngajat(Angajat* pAngajat);
    bool stergeCamera(int numarCamera);
    bool stergeClient(const std::string& CNP);
    bool stergeAngajat(const std::string& CNP);
    bool anuleazaRezervare(int idRezervare);

    Camera* gasesteCamera(int numarCamera);
    const Camera* gasesteCamera(int numarCamera) const;
    Client* gasesteClient(const std::string& CNP);
    const Client* gasesteClient(const std::string& CNP) const;
    Angajat* gasesteAngajat(const std::string& CNP);
    const Angajat* gasesteAngajat(const std::string& CNP) const;
    Rezervare* gasesteRezervare(int idRezervare);
    const Rezervare* gasesteRezervare(int idRezervare) const;

    int creeazaRezervare(const std::string& cnpClient, int numarCamera, const std::string& dataCheckIn,
                         const std::string& dataCheckOut, int numarZile);


    void afisareCamere() const;
    void afisareCamereLibere() const;
    void afisareCamereOcupate() const;
    void afisareClienti() const;
    void afisareAngajati() const;
    void afisareRezervari() const;
    void afisareRezervariClient(const std::string& CNP) const;


    void afisareGenerala(std::ostream& os) const;
    double calculeazaVenitTotal() const;

//Interfata IAsfisabil
    void afisare(std::ostream& os) const;


    friend std::ostream& operator<<(std::ostream& os, const Hotel& hotel);
    friend std::istream& operator>>(std::istream& is, Hotel& hotel);
};

#endif // HOTEL_H