#include "Rezervare.h"
#include <iostream>
#include <data.h>

int Rezervare::m_numar_total_rezervari = 0;


Rezervare::Rezervare() : m_id(++m_numar_total_rezervari), m_numar_zile(0), m_pret_total(0.0), m_platita(false) {}

Rezervare::Rezervare(const Client& m_client, const Camera& m_camera, const Data& m_data_check_in,
                     const Data& m_data_check_out, int m_numar_zile, bool m_platita)
    : m_id(++m_numar_total_rezervari), m_client(m_client), m_camera(m_camera), m_data_check_in(m_data_check_in),
      m_data_check_out(m_data_check_out), m_numar_zile(m_numar_zile), m_platita(m_platita) {
    CalculeazaPretTotal();
}

Rezervare::Rezervare(const Rezervare& other)
    : m_id(other.m_id), m_client(other.m_client), m_camera(other.m_camera), m_data_check_in(other.m_data_check_in),
      m_data_check_out(other.m_data_check_out), m_numar_zile(other.m_numar_zile),
      m_pret_total(other.m_pret_total), m_platita(other.m_platita) {}


Rezervare::~Rezervare() {}


int Rezervare::GetId() const { return m_id; }
const Client& Rezervare::GetClientRef() const { return m_client; }
void Rezervare::SetClient(const Client& m_client) { this->m_client = m_client; }
const Camera& Rezervare::GetCameraRef() const { return m_camera; }
void Rezervare::SetCamera(const Camera& m_camera) {
     this->m_camera = m_camera;
     CalculeazaPretTotal();
}
Data Rezervare::GetDataCheckIn() const { return m_data_check_in; }
void Rezervare::SetDataCheckIn(const Data& data) { this->m_data_check_in.zi = data.zi; }
Data Rezervare::GetDataCheckOut() const { return m_data_check_out; }
void Rezervare::SetDataCheckOut(const Data& data) { this->m_data_check_out.zi = data.zi; }
int Rezervare::GetNumarZile()const { return m_numar_zile; }
void Rezervare::SetNumarZile (int zile) {
    this->m_numar_zile = zile > 0 ? zile : 0;
    CalculeazaPretTotal();
}
double Rezervare::GetPretTotal() const { return m_pret_total; }
bool Rezervare::IsPlatita() const { return m_platita; }
void Rezervare::SetPlatita(bool m_platita) { this->m_platita = m_platita; }


void Rezervare::CalculeazaPretTotal(){
    if (m_numar_zile > 0) {
        m_pret_total = m_numar_zile * m_camera.GetPretPeNoapte();
    } else {
        m_pret_total = 0.0;
    }
}


void Rezervare::Afisare(std::ostream& os) const {
    os << "Rezervare id: " << m_id << ", platita: " << (m_platita ? "Da" : "Nu") << "\n";
    os << "   Perioada: " << m_data_check_in << " - " << m_data_check_out << " (" << m_numar_zile << " zile)\n";
    os << "   Pret Total: " << m_pret_total << " RON\n";
    os << "   client: [" << m_client << "]\n";
    os << "   camera: [" << m_camera << "]";
}


Rezervare& Rezervare::operator=(const Rezervare& other) {
    if (this != &other) {

        m_client = other.m_client;
        m_camera = other.m_camera;
        m_data_check_in = other.m_data_check_in;
        m_data_check_out = other.m_data_check_out;
        m_numar_zile = other.m_numar_zile;
        m_pret_total = other.m_pret_total;
        m_platita = other.m_platita;
    }
    return *this;
}

bool Rezervare::operator==(const Rezervare& other) const {
    return m_id == other.m_id;
}

std::ostream& operator<<(std::ostream& os, const Rezervare& rezervare) {
    rezervare.Afisare(os);
    return os;
}

std::istream& operator>>(std::istream& is, Rezervare& rezervare) {
    std::cout << "Data Check-In: "; is >> rezervare.m_data_check_in;
    std::cout << "Data Check-Out: "; is >> rezervare.m_data_check_out;
    std::cout << "Numar Zile: "; is >> rezervare.m_numar_zile;
    std::cout << "Este platita (1=Da, 0=Nu): ";
    int m_platitaInput;
    is >> m_platitaInput;
    rezervare.m_platita = (m_platitaInput == 1);
    rezervare.CalculeazaPretTotal();
    return is;
}
