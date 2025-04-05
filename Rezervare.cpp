#include "Rezervare.h"
#include <iostream>

// Definirea si initializarea membrului static
int Rezervare::numarTotalRezervari = 0;

// Constructori
Rezervare::Rezervare() : id(++numarTotalRezervari), numarZile(0), pretTotal(0.0), platita(false) {
    // std::cout << "Constructor Rezervare (default), ID=" << id << std::endl;
}

Rezervare::Rezervare(const Client& client, const Camera& camera, const std::string& dataCheckIn,
                     const std::string& dataCheckOut, int numarZile, bool platita)
    : id(++numarTotalRezervari), client(client), camera(camera), dataCheckIn(dataCheckIn),
      dataCheckOut(dataCheckOut), numarZile(numarZile), platita(platita) {
    calculeazaPretTotal(); // Calculam pretul la constructie
    // ATENTIE: Acest constructor NU modifica starea 'ocupata' a camerei originale din Hotel.
    // Logica de ocupare/eliberare trebuie gestionata in clasa Hotel.
    // std::cout << "Constructor Rezervare (parametrizat), ID=" << id << std::endl;
}

Rezervare::Rezervare(const Rezervare& other)
    : id(other.id), // Copiem ID-ul sau generam unul nou? Aici il copiem.
      client(other.client), camera(other.camera), dataCheckIn(other.dataCheckIn),
      dataCheckOut(other.dataCheckOut), numarZile(other.numarZile),
      pretTotal(other.pretTotal), platita(other.platita) {
    // Daca ID-ul ar trebui sa fie unic, ar trebui incrementat numarTotalRezervari si aici:
    // id = ++numarTotalRezervari;
    // std::cout << "Constructor Rezervare (copiere), ID=" << id << std::endl;
}

// Destructor
Rezervare::~Rezervare() {
    // std::cout << "Destructor Rezervare, ID=" << id << std::endl;
}

// Getteri și setteri
int Rezervare::getId() const { return id; }
const Client& Rezervare::getClientRef() const { return client; }
void Rezervare::setClient(const Client& client) { this->client = client; }
const Camera& Rezervare::getCameraRef() const { return camera; }
void Rezervare::setCamera(const Camera& camera) {
     this->camera = camera;
     calculeazaPretTotal(); // Recalculam pretul daca se schimba camera
}
std::string Rezervare::getDataCheckIn() const { return dataCheckIn; }
void Rezervare::setDataCheckIn(const std::string& data) { this->dataCheckIn = data; }
std::string Rezervare::getDataCheckOut() const { return dataCheckOut; }
void Rezervare::setDataCheckOut(const std::string& data) { this->dataCheckOut = data; }
int Rezervare::getNumarZile() const { return numarZile; }
void Rezervare::setNumarZile(int zile) {
    this->numarZile = zile > 0 ? zile : 0;
    calculeazaPretTotal(); // Recalculam pretul
}
double Rezervare::getPretTotal() const { return pretTotal; }
bool Rezervare::isPlatita() const { return platita; }
void Rezervare::setPlatita(bool platita) { this->platita = platita; }

// Metode
void Rezervare::calculeazaPretTotal() {
    if (numarZile > 0) {
        pretTotal = numarZile * camera.getPretPeNoapte();
        // TODO: Adauga eventuale discounturi pentru client fidel etc.
        // if (client.isClientFidel()) { pretTotal *= 0.9; }
    } else {
        pretTotal = 0.0;
    }
}

void Rezervare::afisare() const {
    std::cout << "Rezervare ID: " << id << ", Platita: " << (platita ? "Da" : "Nu") << std::endl;
    std::cout << "   Perioada: " << dataCheckIn << " - " << dataCheckOut << " (" << numarZile << " zile)" << std::endl;
    std::cout << "   Pret Total: " << pretTotal << " RON" << std::endl;
    std::cout << "   Client: " << client.getPrenume() << " " << client.getNume() << " (CNP: " << client.getCNP() << ")" << std::endl;
    std::cout << "   Camera: Nr " << camera.getNumar() << " [" << camera.getTipRef() << "]"; // Folosim operatorul<< din TipCamera
}

// Operatori
Rezervare& Rezervare::operator=(const Rezervare& other) {
    if (this != &other) {
        // Nu copiem ID-ul, fiecare rezervare ramane cu ID-ul ei initial
        client = other.client;
        camera = other.camera;
        dataCheckIn = other.dataCheckIn;
        dataCheckOut = other.dataCheckOut;
        numarZile = other.numarZile;
        pretTotal = other.pretTotal; // Sau recalculeazaPretTotal()? Depinde de logica dorita.
        platita = other.platita;
    }
    return *this;
}

bool Rezervare::operator==(const Rezervare& other) const {
    // Comparam pe baza ID-ului unic
    return id == other.id;
}

// Implementarea operatorilor stream (prieteni)
std::ostream& operator<<(std::ostream& os, const Rezervare& rezervare) {
    os << "Rezervare ID: " << rezervare.id << ", Platita: " << (rezervare.platita ? "Da" : "Nu") << "\n"
       << "   Perioada: " << rezervare.dataCheckIn << " - " << rezervare.dataCheckOut << " (" << rezervare.numarZile << " zile)\n"
       << "   Pret Total: " << rezervare.pretTotal << " RON\n"
       << "   Client: [" << rezervare.client << "]\n" // Folosim op<< din Client
       << "   Camera: [" << rezervare.camera << "]"; // Folosim op<< din Camera
    return os;
}

std::istream& operator>>(std::istream& is, Rezervare& rezervare) {
    // Citirea directa a unei rezervari e complexa pt ca necesita obiecte Client si Camera preexistente
    // si interactiune cu Hotelul pentru a asigura consistenta (ex: camera sa fie libera).
    // De obicei, rezervarile sunt create prin metode ale clasei Hotel.
    std::cout << "Citirea directa a unei rezervari nu este suportata standard.\n";
    std::cout << "Folositi metodele clasei Hotel pentru a crea rezervari.\n";
    // Poate citi doar datele simple, dar lasa obiectele Client/Camera neinitializate corect:
    std::cout << "Data Check-In: "; is >> rezervare.dataCheckIn;
    std::cout << "Data Check-Out: "; is >> rezervare.dataCheckOut;
    std::cout << "Numar Zile: "; is >> rezervare.numarZile;
    std::cout << "Este platita (1=Da, 0=Nu): ";
    int platitaInput; is >> platitaInput; rezervare.platita = (platitaInput == 1);
    rezervare.calculeazaPretTotal(); // Recalculeaza pretul, desi camera/client pot fi invalide
    return is;
}