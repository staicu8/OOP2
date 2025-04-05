#ifndef HOTEL_H
#define HOTEL_H

#include <string>
#include <vector>
#include <iostream>

// Includem fisierele header pentru clasele continute in vectori
#include "Camera.h"
#include "Client.h"
#include "Angajat.h"
#include "Rezervare.h"

// Alternativ, am putea folosi forward declarations aici DACA NU am folosi std::vector<Clasa>
// (ex: std::vector<Clasa*>), dar std::vector necesita definitia completa a tipului.
// class Camera;
// class Client;
// class Angajat;
// class Rezervare;

class Hotel {
private:
    std::string nume;
    std::string adresa;
    int numarStele;
    std::vector<Camera> camere;
    std::vector<Client> clienti;
    std::vector<Angajat> angajati;
    std::vector<Rezervare> rezervari;

    // Functii helper private pentru a gasi elemente in vectori (exemple)
    // Acestea ar returna un iterator sau index pentru a permite modificarea/stergerea
    std::vector<Camera>::iterator findCameraIterator(int numarCamera);
    std::vector<Client>::iterator findClientIterator(const std::string& CNP);
    std::vector<Angajat>::iterator findAngajatIterator(const std::string& CNP);
    std::vector<Rezervare>::iterator findRezervareIterator(int idRezervare);

public:
    // Constructori
    Hotel();
    Hotel(const std::string& nume, const std::string& adresa, int numarStele);
    // Constructorul de copiere si op= pot fi complicati din cauza vectorilor;
    // le implementam sau le declaram delete daca nu dorim copierea hotelului.
    Hotel(const Hotel& other);
    Hotel& operator=(const Hotel& other);

    // Destructor
    ~Hotel();

    // Getteri și setteri
    std::string getNume() const;
    void setNume(const std::string& nume);
    std::string getAdresa() const;
    void setAdresa(const std::string& adresa);
    int getNumarStele() const;
    void setNumarStele(int stele);

    // Metode pentru gestionarea camerelor
    void adaugaCamera(const Camera& camera);
    bool stergeCamera(int numarCamera); // Returneaza true daca a reusit
    Camera* gasesteCamera(int numarCamera); // Returneaza pointer la camera din vector (sau nullptr)
    const Camera* gasesteCamera(int numarCamera) const; // Varianta const
    void afisareCamere() const;
    void afisareCamereLibere() const;
    void afisareCamereOcupate() const;

    // Metode pentru gestionarea clienților
    void adaugaClient(const Client& client);
    bool stergeClient(const std::string& CNP); // Returneaza true daca a reusit
    Client* gasesteClient(const std::string& CNP); // Returneaza pointer sau nullptr
    const Client* gasesteClient(const std::string& CNP) const; // Varianta const
    void afisareClienti() const;

    // Metode pentru gestionarea angajaților
    void adaugaAngajat(const Angajat& angajat);
    bool stergeAngajat(const std::string& CNP); // Returneaza true daca a reusit
    Angajat* gasesteAngajat(const std::string& CNP); // Returneaza pointer sau nullptr
    const Angajat* gasesteAngajat(const std::string& CNP) const; // Varianta const
    void afisareAngajati() const;

    // Metode pentru gestionarea rezervărilor
    // Returneaza ID-ul rezervarii create sau -1 in caz de eroare
    int creeazaRezervare(const std::string& cnpClient, int numarCamera, const std::string& dataCheckIn,
                         const std::string& dataCheckOut, int numarZile);
    bool anuleazaRezervare(int idRezervare); // Returneaza true daca a reusit
    Rezervare* gasesteRezervare(int idRezervare); // Returneaza pointer sau nullptr
    const Rezervare* gasesteRezervare(int idRezervare) const; // Varianta const
    void afisareRezervari() const;
    void afisareRezervariClient(const std::string& CNP) const;

    // Alte metode
    void afisareGenerala() const; // Renumit din afisare() pentru claritate
    double calculeazaVenitTotal() const; // Calculeaza venit din rezervarile platite

    // Operatori
    // op= este declarat mai sus
    // op== nu are sens clar pentru hoteluri

    // Declaratii friend
    friend std::ostream& operator<<(std::ostream& os, const Hotel& hotel);
    friend std::istream& operator>>(std::istream& is, Hotel& hotel); // Citirea unui hotel intreg e complexa
};

#endif // HOTEL_H