#include "Rezervare.h"
#include <iostream>
#include <data.h>

int Rezervare::numarTotalRezervari = 0;


Rezervare::Rezervare() : id(++numarTotalRezervari), numarZile(0), pretTotal(0.0), platita(false) {}

Rezervare::Rezervare(const Client& client, const Camera& camera, const Data& dataCheckIn,
                     const Data& dataCheckOut, int numarZile, bool platita)
    : id(++numarTotalRezervari), client(client), camera(camera), dataCheckIn(dataCheckIn),
      dataCheckOut(dataCheckOut), numarZile(numarZile), platita(platita) {
    calculeazaPretTotal();
}

Rezervare::Rezervare(const Rezervare& other)
    : id(other.id), client(other.client), camera(other.camera), dataCheckIn(other.dataCheckIn),
      dataCheckOut(other.dataCheckOut), numarZile(other.numarZile),
      pretTotal(other.pretTotal), platita(other.platita) {}


Rezervare::~Rezervare() {}


int Rezervare::getId() const { return id; }
const Client& Rezervare::getClientRef() const { return client; }
void Rezervare::setClient(const Client& client) { this->client = client; }
const Camera& Rezervare::getCameraRef() const { return camera; }
void Rezervare::setCamera(const Camera& camera) {
     this->camera = camera;
     calculeazaPretTotal();
}
Data Rezervare::getDataCheckIn() const { return dataCheckIn; }
void Rezervare::setDataCheckIn(const Data& data) { this->dataCheckIn.zi = data.zi; }
Data Rezervare::getDataCheckOut() const { return dataCheckOut; }
void Rezervare::setDataCheckOut(const Data& data) { this->dataCheckOut.zi = data.zi; }
int Rezervare::getNumarZile() const { return numarZile; }
void Rezervare::setNumarZile(int zile) {
    this->numarZile = zile > 0 ? zile : 0;
    calculeazaPretTotal();
}
double Rezervare::getPretTotal() const { return pretTotal; }
bool Rezervare::isPlatita() const { return platita; }
void Rezervare::setPlatita(bool platita) { this->platita = platita; }


void Rezervare::calculeazaPretTotal() {
    if (numarZile > 0) {
        pretTotal = numarZile * camera.getPretPeNoapte();
    } else {
        pretTotal = 0.0;
    }
}


void Rezervare::afisare(std::ostream& os) const {
    os << "Rezervare ID: " << id << ", Platita: " << (platita ? "Da" : "Nu") << "\n";
    os << "   Perioada: " << dataCheckIn << " - " << dataCheckOut << " (" << numarZile << " zile)\n";
    os << "   Pret Total: " << pretTotal << " RON\n";
    os << "   Client: [" << client << "]\n";
    os << "   Camera: [" << camera << "]";
}


Rezervare& Rezervare::operator=(const Rezervare& other) {
    if (this != &other) {

        client = other.client;
        camera = other.camera;
        dataCheckIn = other.dataCheckIn;
        dataCheckOut = other.dataCheckOut;
        numarZile = other.numarZile;
        pretTotal = other.pretTotal;
        platita = other.platita;
    }
    return *this;
}

bool Rezervare::operator==(const Rezervare& other) const {
    return id == other.id;
}

std::ostream& operator<<(std::ostream& os, const Rezervare& rezervare) {
    rezervare.afisare(os);
    return os;
}

std::istream& operator>>(std::istream& is, Rezervare& rezervare) {
    std::cout << "Data Check-In: "; is >> rezervare.dataCheckIn;
    std::cout << "Data Check-Out: "; is >> rezervare.dataCheckOut;
    std::cout << "Numar Zile: "; is >> rezervare.numarZile;
    std::cout << "Este platita (1=Da, 0=Nu): ";
    int platitaInput;
    is >> platitaInput;
    rezervare.platita = (platitaInput == 1);
    rezervare.calculeazaPretTotal();
    return is;
}
