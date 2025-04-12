#include "Rezervare.h"
#include <iostream>

// Definirea si initializarea membrului static
int Rezervare::numarTotalRezervari = 0;

// Constructori
Rezervare::Rezervare() : id(++numarTotalRezervari), numarZile(0), pretTotal(0.0), platita(false) {}

Rezervare::Rezervare(const Client& client, const Camera& camera, const std::string& dataCheckIn,
                     const std::string& dataCheckOut, int numarZile, bool platita)
    : id(++numarTotalRezervari), client(client), camera(camera), dataCheckIn(dataCheckIn),
      dataCheckOut(dataCheckOut), numarZile(numarZile), platita(platita) {
    calculeazaPretTotal();
}

Rezervare::Rezervare(const Rezervare& other)
    : id(other.id), client(other.client), camera(other.camera), dataCheckIn(other.dataCheckIn),
      dataCheckOut(other.dataCheckOut), numarZile(other.numarZile),
      pretTotal(other.pretTotal), platita(other.platita) {
    // id = ++numarTotalRezervari; // Daca vrem ID unic la copiere
}

// Destructor
Rezervare::~Rezervare() {}

// Getteri și setteri
int Rezervare::getId() const { return id; }
const Client& Rezervare::getClientRef() const { return client; }
void Rezervare::setClient(const Client& client) { this->client = client; }
const Camera& Rezervare::getCameraRef() const { return camera; }
void Rezervare::setCamera(const Camera& camera) {
     this->camera = camera;
     calculeazaPretTotal();
}
std::string Rezervare::getDataCheckIn() const { return dataCheckIn; }
void Rezervare::setDataCheckIn(const std::string& data) { this->dataCheckIn = data; }
std::string Rezervare::getDataCheckOut() const { return dataCheckOut; }
void Rezervare::setDataCheckOut(const std::string& data) { this->dataCheckOut = data; }
int Rezervare::getNumarZile() const { return numarZile; }
void Rezervare::setNumarZile(int zile) {
    this->numarZile = zile > 0 ? zile : 0;
    calculeazaPretTotal();
}
double Rezervare::getPretTotal() const { return pretTotal; }
bool Rezervare::isPlatita() const { return platita; }
void Rezervare::setPlatita(bool platita) { this->platita = platita; }

// Metode
void Rezervare::calculeazaPretTotal() {
    if (numarZile > 0) {
        pretTotal = numarZile * camera.getPretPeNoapte();
        // Discounturi etc.
    } else {
        pretTotal = 0.0;
    }
}

// Implementare IAfisabil
void Rezervare::afisare(std::ostream& os) const {
    os << "Rezervare ID: " << id << ", Platita: " << (platita ? "Da" : "Nu") << "\n"; // Folosim \n pentru newline in stream
    os << "   Perioada: " << dataCheckIn << " - " << dataCheckOut << " (" << numarZile << " zile)\n";
    os << "   Pret Total: " << pretTotal << " RON\n";
    os << "   Client: [" << client << "]\n"; // Folosim op<< din Client
    os << "   Camera: [" << camera << "]";   // Folosim op<< din Camera
}

// Operatori
Rezervare& Rezervare::operator=(const Rezervare& other) {
    if (this != &other) {
        // Nu copiem ID-ul
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

// Operator << apeleaza acum afisare(os)
std::ostream& operator<<(std::ostream& os, const Rezervare& rezervare) {
    rezervare.afisare(os);
    return os;
}

std::istream& operator>>(std::istream& is, Rezervare& rezervare) {
    std::cout << "Citirea directa a unei rezervari nu este suportata standard.\n";
    std::cout << "Folositi metodele clasei Hotel pentru a crea rezervari.\n";
    std::cout << "Data Check-In: "; is >> rezervare.dataCheckIn;
    std::cout << "Data Check-Out: "; is >> rezervare.dataCheckOut;
    std::cout << "Numar Zile: "; is >> rezervare.numarZile;
    std::cout << "Este platita (1=Da, 0=Nu): ";
    int platitaInput; is >> platitaInput; rezervare.platita = (platitaInput == 1);
    rezervare.calculeazaPretTotal();
    return is;
}