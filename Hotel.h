#ifndef HOTEL_H
#define HOTEL_H

#include <string>
#include <vector>
#include <iostream>

#include "Camera.h"
#include "Client.h"
#include "Angajat.h"
#include "Rezervare.h"
#include "IAfisabil.h" // Include interfata

class Hotel : public IAfisabil { // Mosteneste interfata
private:
    std::string nume;
    std::string adresa;
    int numarStele;
    std::vector<Camera> camere;
    std::vector<Client> clienti;
    std::vector<Angajat> angajati;
    std::vector<Rezervare> rezervari;

public:
    Hotel();
    Hotel(const std::string& nume, const std::string& adresa, int numarStele);
    Hotel(const Hotel& other);
    Hotel& operator=(const Hotel& other);
    ~Hotel();

    // Getteri / Setteri
    std::string getNume() const;
    void setNume(const std::string& nume);
    std::string getAdresa() const;
    void setAdresa(const std::string& adresa);
    int getNumarStele() const;
    void setNumarStele(int stele);

    // Metode camere
    void adaugaCamera(const Camera& camera);
    bool stergeCamera(int numarCamera);
    Camera* gasesteCamera(int numarCamera);
    const Camera* gasesteCamera(int numarCamera) const;
    void afisareCamere() const;
    void afisareCamereLibere() const;
    void afisareCamereOcupate() const;

    // Metode clienti
    void adaugaClient(const Client& client);
    bool stergeClient(const std::string& CNP);
    Client* gasesteClient(const std::string& CNP);
    const Client* gasesteClient(const std::string& CNP) const;
    void afisareClienti() const;

    // Metode angajati
    void adaugaAngajat(const Angajat& angajat);
    bool stergeAngajat(const std::string& CNP);
    Angajat* gasesteAngajat(const std::string& CNP);
    const Angajat* gasesteAngajat(const std::string& CNP) const;
    void afisareAngajati() const;

    // Metode rezervari
    int creeazaRezervare(const std::string& cnpClient, int numarCamera, const std::string& dataCheckIn,
                         const std::string& dataCheckOut, int numarZile);
    bool anuleazaRezervare(int idRezervare);
    Rezervare* gasesteRezervare(int idRezervare);
    const Rezervare* gasesteRezervare(int idRezervare) const;
    void afisareRezervari() const;
    void afisareRezervariClient(const std::string& CNP) const;

    // Alte metode
    void afisareGenerala(std::ostream& os) const; // Modificat sa primeasca os
    double calculeazaVenitTotal() const;

    // Implementarea interfetei IAfisabil
    void afisare(std::ostream& os) const;

    // Operatori
    friend std::ostream& operator<<(std::ostream& os, const Hotel& hotel);
    friend std::istream& operator>>(std::istream& is, Hotel& hotel);
};

#endif // HOTEL_H