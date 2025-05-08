#include "Camera.h"
#include <iostream>

Camera::Camera() : m_numar(0), m_pret_pe_noapte(0.0), m_ocupata(false), m_tip(), m_etaj(0) {}

Camera::Camera(int numar, double pret_pe_noapte, bool ocupata, const TipCamera& tip, int etaj)
    : m_numar(numar), m_pret_pe_noapte(pret_pe_noapte), m_ocupata(ocupata), m_tip(tip), m_etaj(etaj) {}

Camera::Camera(const Camera& other)
    : m_numar(other.m_numar), m_pret_pe_noapte(other.m_pret_pe_noapte), m_ocupata(other.m_ocupata),
      m_tip(other.m_tip), m_etaj(other.m_etaj) {}

Camera::~Camera() {}

int Camera::GetNumar() const { return m_numar; }
void Camera::SetNumar(int numar) { this->m_numar = numar; }
double Camera::GetPretPeNoapte() const { return m_pret_pe_noapte; }
void Camera::SetPretPeNoapte(double pret) { this->m_pret_pe_noapte = pret; }
bool Camera::IsOcupata() const { return m_ocupata; }
void Camera::SetOcupata(bool ocupata) { this->m_ocupata = ocupata; }
TipCamera Camera::GetTip() const { return m_tip; }
const TipCamera& Camera::GetTipRef() const { return m_tip; }
void Camera::SetTip(const TipCamera& tip) { this->m_tip = tip; }
int Camera::GetEtaj() const { return m_etaj; }
void Camera::SetEtaj(int etaj) { this->m_etaj = etaj; }

void Camera::Afisare(std::ostream& os) const {
    os << "Camera Nr: " << m_numar << ", Etaj: " << m_etaj
       << ", Pret/Noapte: " << m_pret_pe_noapte << " RON"
       << ", Stare: " << (m_ocupata ? "Ocupata" : "Libera") << "\n"
       << " [" << m_tip << "]";
}

Camera& Camera::operator=(const Camera& other) {
    if (this != &other) {
        m_numar = other.m_numar;
        m_pret_pe_noapte = other.m_pret_pe_noapte;
        m_ocupata = other.m_ocupata;
        m_tip = other.m_tip;
        m_etaj = other.m_etaj;
    }
    return *this;
}

bool Camera::operator==(const Camera& other) const {
    return m_numar == other.m_numar;
}

std::ostream& operator<<(std::ostream& os, const Camera& camera) {
    camera.Afisare(os);
    return os;
}

std::istream& operator>>(std::istream& is, Camera& camera) {
    std::cout << "Numar camera: "; is >> camera.m_numar;
    std::cout << "Pret pe noapte: "; is >> camera.m_pret_pe_noapte;
    std::cout << "Etaj: "; is >> camera.m_etaj;
    std::cout << "Introduceti detalii tip camera:\n";
    is >> camera.m_tip;
    camera.m_ocupata = false;
    return is;
}