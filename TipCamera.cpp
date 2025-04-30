#include "TipCamera.h"
#include <iostream>


TipCamera::TipCamera() : numarMaximPersoane(0), areBalcon(false), areVedere(false) {}

TipCamera::TipCamera(const std::string& denumire, int numarMaximPersoane, bool areBalcon, bool areVedere)
    : denumire(denumire), numarMaximPersoane(numarMaximPersoane), areBalcon(areBalcon), areVedere(areVedere) {}

TipCamera::TipCamera(const TipCamera& other)
    : denumire(other.denumire), numarMaximPersoane(other.numarMaximPersoane),
      areBalcon(other.areBalcon), areVedere(other.areVedere) {}


TipCamera::~TipCamera() {}


std::string TipCamera::getDenumire() const { return denumire; }
void TipCamera::setDenumire(const std::string& denumire) { this->denumire = denumire; }
int TipCamera::getNumarMaximPersoane() const { return numarMaximPersoane; }
void TipCamera::setNumarMaximPersoane(int numar) { this->numarMaximPersoane = numar; }
bool TipCamera::hasBalcon() const { return areBalcon; }
void TipCamera::setAreBalcon(bool areBalcon) { this->areBalcon = areBalcon; }
bool TipCamera::hasVedere() const { return areVedere; }
void TipCamera::setAreVedere(bool areVedere) { this->areVedere = areVedere; }


void TipCamera::afisare(std::ostream& os) const {
    os << "Tip: " << denumire
       << ", Capacitate: " << numarMaximPersoane << " pers"
       << ", Balcon: " << (areBalcon ? "Da" : "Nu")
       << ", Vedere: " << (areVedere ? "Da" : "Nu");
}


TipCamera& TipCamera::operator=(const TipCamera& other) {
    if (this != &other) {
        denumire = other.denumire;
        numarMaximPersoane = other.numarMaximPersoane;
        areBalcon = other.areBalcon;
        areVedere = other.areVedere;
    }
    return *this;
}

bool TipCamera::operator==(const TipCamera& other) const {
    return denumire == other.denumire &&
           numarMaximPersoane == other.numarMaximPersoane &&
           areBalcon == other.areBalcon &&
           areVedere == other.areVedere;
}


std::ostream& operator<<(std::ostream& os, const TipCamera& tipCamera) {
    tipCamera.afisare(os);
    return os;
}

std::istream& operator>>(std::istream& is, TipCamera& tipCamera) {
    std::cout << "Denumire tip: "; is >> tipCamera.denumire;
    std::cout << "Capacitate maxima: "; is >> tipCamera.numarMaximPersoane;
    std::cout << "Are balcon (1=Da, 0=Nu): ";
    int balconInput; is >> balconInput; tipCamera.areBalcon = (balconInput == 1);
    std::cout << "Are vedere (1=Da, 0=Nu): ";
    int vedereInput; is >> vedereInput; tipCamera.areVedere = (vedereInput == 1);
    return is;
}