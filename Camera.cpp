#include "Camera.h"
#include <iostream>

// Constructori
Camera::Camera() : numar(0), pretPeNoapte(0.0), ocupata(false), tip(), etaj(0) {}

Camera::Camera(int numar, double pretPeNoapte, bool ocupata, const TipCamera& tip, int etaj)
    : numar(numar), pretPeNoapte(pretPeNoapte), ocupata(ocupata), tip(tip), etaj(etaj) {}

Camera::Camera(const Camera& other)
    : numar(other.numar), pretPeNoapte(other.pretPeNoapte), ocupata(other.ocupata),
      tip(other.tip), etaj(other.etaj) {}

// Destructor
Camera::~Camera() {}

// Getteri și setteri
int Camera::getNumar() const { return numar; }
void Camera::setNumar(int numar) { this->numar = numar; }
double Camera::getPretPeNoapte() const { return pretPeNoapte; }
void Camera::setPretPeNoapte(double pret) { this->pretPeNoapte = pret; }
bool Camera::isOcupata() const { return ocupata; }
void Camera::setOcupata(bool ocupata) { this->ocupata = ocupata; }
TipCamera Camera::getTip() const { return tip; }
const TipCamera& Camera::getTipRef() const { return tip; }
void Camera::setTip(const TipCamera& tip) { this->tip = tip; }
int Camera::getEtaj() const { return etaj; }
void Camera::setEtaj(int etaj) { this->etaj = etaj; }

// Implementare IAfisabil
void Camera::afisare(std::ostream& os) const {
    os << "Camera Nr: " << numar << ", Etaj: " << etaj
       << ", Pret/Noapte: " << pretPeNoapte << " RON"
       << ", Stare: " << (ocupata ? "Ocupata" : "Libera") << "\n"
       << "   [" << tip << "]"; // Folosim operatorul<< din TipCamera
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
    // Comparam doar pe baza numarului
    return numar == other.numar;
}

// Operator << apeleaza acum afisare(os)
std::ostream& operator<<(std::ostream& os, const Camera& camera) {
    camera.afisare(os);
    return os;
}

std::istream& operator>>(std::istream& is, Camera& camera) {
    std::cout << "Numar camera: "; is >> camera.numar;
    std::cout << "Pret pe noapte: "; is >> camera.pretPeNoapte;
    std::cout << "Etaj: "; is >> camera.etaj;
    std::cout << "Introduceti detalii tip camera:\n";
    is >> camera.tip; // Folosim operatorul>> din TipCamera
    camera.ocupata = false; // Presupunem libera la citire initiala
    return is;
}