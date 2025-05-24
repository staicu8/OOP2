#include "tip_camera.h"
#include <iostream>

//Implementare Constructor,Constructor cu parametrii si Constructor de copiere
TipCamera::TipCamera() : m_numar_maxim_persoane(0), m_are_balcon(false), m_are_vedere(false) {}

TipCamera::TipCamera(const std::string& denumire, int numarMaximPersoane, bool areBalcon, bool areVedere)
    : m_denumire(denumire), m_numar_maxim_persoane(numarMaximPersoane), m_are_balcon(areBalcon), m_are_vedere(areVedere) {}

TipCamera::TipCamera(const TipCamera& other)
    : m_denumire(other.m_denumire), m_numar_maxim_persoane(other.m_numar_maxim_persoane),
      m_are_balcon(other.m_are_balcon), m_are_vedere(other.m_are_vedere) {}

//Destructor
TipCamera::~TipCamera() {}

//Getteri si Setteri
std::string TipCamera::GetDenumire() const { return m_denumire; }
void TipCamera::SetDenumire(const std::string& denumire) { this->m_denumire = denumire; }
int TipCamera::GetNumarMaximPersoane() const { return m_numar_maxim_persoane; }
void TipCamera::SetNumarMaximPersoane(int numar) { this->m_numar_maxim_persoane = numar; }
bool TipCamera::HasBalcon() const { return m_are_balcon; }
void TipCamera::SetAreBalcon(bool areBalcon) { this->m_are_balcon = areBalcon; }
bool TipCamera::HasVedere() const { return m_are_vedere; }
void TipCamera::SetAreVedere(bool areVedere) { this->m_are_vedere = areVedere; }

//Implementeaza functia pur virtuala Afisare din interfata
void TipCamera::Afisare(std::ostream& os) const {
    os << "Tip: " << m_denumire
       << ", Capacitate: " << m_numar_maxim_persoane << " pers"
       << ", Balcon: " << (m_are_balcon ? "Da" : "Nu")
       << ", Vedere: " << (m_are_vedere ? "Da" : "Nu");
}

//Supraincarcare operatori
TipCamera& TipCamera::operator=(const TipCamera& other) {
    if (this != &other) {
        m_denumire = other.m_denumire;
        m_numar_maxim_persoane = other.m_numar_maxim_persoane;
        m_are_balcon = other.m_are_balcon;
        m_are_vedere = other.m_are_vedere;
    }
    return *this;
}

bool TipCamera::operator==(const TipCamera& other) const {
    return m_denumire == other.m_denumire &&
           m_numar_maxim_persoane == other.m_numar_maxim_persoane &&
           m_are_balcon == other.m_are_balcon &&
           m_are_vedere == other.m_are_vedere;
}


std::ostream& operator<<(std::ostream& os, const TipCamera& tipCamera) {
    tipCamera.Afisare(os);
    return os;
}

std::istream& operator>>(std::istream& is, TipCamera& tipCamera) {
    std::cout << "Denumire tip: "; is >> tipCamera.m_denumire;
    std::cout << "Capacitate maxima: "; is >> tipCamera.m_numar_maxim_persoane;
    std::cout << "Are balcon (1=Da, 0=Nu): ";
    int balconInput; is >> balconInput; tipCamera.m_are_balcon = (balconInput == 1);
    std::cout << "Are vedere (1=Da, 0=Nu): ";
    int vedereInput; is >> vedereInput; tipCamera.m_are_vedere = (vedereInput == 1);
    return is;
}
