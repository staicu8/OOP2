#include "Camera.h"
#include <iostream>

// Constructori
Camera::Camera() : numar(0), pretPeNoapte(0.0), ocupata(false), tip(), etaj(0) {
    // std::cout << "Constructor Camera (default)" << std::endl;
}

Camera::Camera(int numar, double pretPeNoapte, bool ocupata, const TipCamera& tip, int etaj)
    : numar(numar), pretPeNoapte(pretPeNoapte), ocupata(ocupata), tip(tip), etaj(etaj) {
    // std::cout << "Constructor Camera (parametrizat): Nr " << numar << std::endl;
}

Camera::Camera(const Camera& other)
    : numar(other.numar), pretPeNoapte(other.pretPeNoapte), ocupata(other.ocupata),
      tip(other.tip), etaj(other.etaj) {
    // std::cout << "Constructor Camera (copiere): Nr " << numar << std::endl;
}

// Destructor
Camera::~Camera() {
    // std::cout << "Destructor Camera: Nr " << numar << std::endl;
}

// Getteri și setteri
int Camera::getNumar() const { return numar; }
void Camera::setNumar(int numar) { this->numar = numar; } // Validare unicitate? (la nivel de Hotel)
double Camera::getPretPeNoapte() const { return pretPeNoapte; }
void Camera::setPretPeNoapte(double pret) { this->pretPeNoapte = pret; } // Validare pret >= 0?
bool Camera::isOcupata() const { return ocupata; }
void Camera::setOcupata(bool ocupata) { this->ocupata = ocupata; }
TipCamera Camera::getTip() const { return tip; } // Returneaza copie
const TipCamera& Camera::getTipRef() const { return tip; } // Returneaza referinta
void Camera::setTip(const TipCamera& tip) { this->tip = tip; }
int Camera::getEtaj() const { return etaj; }
void Camera::setEtaj(int etaj) { this->etaj = etaj; }

// Metode
void Camera::afisare() const {
    std::cout << "Camera Nr: " << numar << ", Etaj: " << etaj
              << ", Pret/Noapte: " << pretPeNoapte << " RON"
              << ", Stare: " << (ocupata ? "Ocupata" : "Libera") << std::endl;
    std::cout << "   " << tip; // Folosim operatorul<< din TipCamera
}

// Operatori
Camera& Camera::operator=(const Camera& other) {
    if (this != &other) {
        numar = other.numar;
        pretPeNoapte = other.pretPeNoapte;
        ocupata = other.ocupata;
        tip = other.tip;
        etaj = other.etaj;
    }
    return *this;
}

bool Camera::operator==(const Camera& other) const {
    // Comparam doar pe baza numarului, presupunand ca e unic in hotel
    return numar == other.numar;
}

// Implementarea operatorilor stream (prieteni)
std::ostream& operator<<(std::ostream& os, const Camera& camera) {
    os << "Camera Nr: " << camera.numar << ", Etaj: " << camera.etaj
       << ", Pret/Noapte: " << camera.pretPeNoapte << " RON"
       << ", Stare: " << (camera.ocupata ? "Ocupata" : "Libera") << "\n"
       << "   [" << camera.tip << "]"; // Folosim operatorul<< din TipCamera
    return os;
}

std::istream& operator>>(std::istream& is, Camera& camera) {
    std::cout << "Numar camera: "; is >> camera.numar;
    std::cout << "Pret pe noapte: "; is >> camera.pretPeNoapte;
    std::cout << "Etaj: "; is >> camera.etaj;
    std::cout << "Introduceti detalii tip camera:\n";
    is >> camera.tip; // Folosim operatorul>> din TipCamera
    camera.ocupata = false; // Presupunem libera la citire initiala
    // Adauga validari
    return is;
}