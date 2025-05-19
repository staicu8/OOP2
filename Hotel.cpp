#include "Hotel.h"
#include <iostream>
#include <vector>
#include <string>



Hotel::Hotel() : m_numar_stele(0) {

}

Hotel::Hotel(const std::string& nume, const std::string& adresa, int numar_stele)
: m_nume(nume), m_adresa(adresa), m_numar_stele(numar_stele) {

}


Hotel::~Hotel() {



//std::cout << " - Stergere Camere..." << std::endl;
for (int i = 0; i < m_camere.size(); ++i) {
delete m_camere[i];
}



//std::cout << " - Stergere Clienti..." << std::endl;
for (int i = 0; i < m_clienti.size(); ++i) {
delete m_clienti[i];
}
m_clienti.clear();


//std::cout << " - Stergere Angajati..." << std::endl;
for (int i = 0; i < m_angajati.size(); ++i) {
delete m_angajati[i];
}
m_angajati.clear();


// std::cout << " - Stergere Rezervari..." << std::endl;
for (int i = 0; i < m_rezervari.size(); ++i) {
delete m_rezervari[i];
}
m_rezervari.clear();


}


std::string Hotel::GetNume() const { return m_nume; }
void Hotel::SetNume(const std::string& nume) { this->m_nume = nume; }
std::string Hotel::GetAdresa() const { return m_adresa; }
void Hotel::SetAdresa(const std::string& adresa) { this->m_adresa = adresa; }
int Hotel::GetNumarStele() const { return m_numar_stele; }
void Hotel::SetNumarStele(int stele) { if (stele >= 0 && stele <= 5) this->m_numar_stele = stele; else std::cerr << "..."; }



Camera* Hotel::GasesteCamera(int numar_camera) {
for (int i = 0; i < m_camere.size(); ++i) {

if (m_camere[i] != 0 && m_camere[i]->GetNumar() == numar_camera) {
return m_camere[i];
}
}
return 0;
}
const Camera* Hotel::GasesteCamera(int numar_camera) const {
for (int i = 0; i < m_camere.size(); ++i) {
if (m_camere[i] != 0 && m_camere[i]->GetNumar() == numar_camera) {
return m_camere[i];
}
}
return 0;
}

void Hotel::AdaugaCamera(Camera* p_camera) {
if (p_camera == 0) {
std::cerr << "Eroare Adaugare Camera" << std::endl;
return;
}
if (GasesteCamera(p_camera->GetNumar()) != 0) {
std::cerr << "Eroare Adaugare Camera: Camera cu numarul " << p_camera->GetNumar() << " exista deja!" << std::endl;

return;
}
m_camere.push_back(p_camera);
std::cout << "Camera Nr " << p_camera->GetNumar() << " adaugata." << std::endl;
}

bool Hotel::StergeCamera(int numar_camera) {
int index_gasit = -1;
for (int i = 0; i < m_camere.size(); ++i) {
if (m_camere[i] != 0 && m_camere[i]->GetNumar() == numar_camera) {
index_gasit = i;
break;
}
}

if (index_gasit != -1) {

bool folosita_in_rezervare = false;
for (int j = 0; j < m_rezervari.size(); ++j) {

if (m_rezervari[j] != 0 && m_rezervari[j]->GetCameraRef().GetNumar() == numar_camera) {
folosita_in_rezervare = true;
break;
}
}
if (folosita_in_rezervare) {
std::cerr << "Eroare Stergere Camera: Camera Nr " << numar_camera << " este folosita intr-o rezervare activa." << std::endl;
return false;
}


delete m_camere[index_gasit];


m_camere.erase(m_camere.begin() + index_gasit);
return true;
} else {
std::cerr << "Eroare Stergere Camera: Camera Nr " << numar_camera << " nu a fost gasita." << std::endl;
return false;
}
}

void Hotel::AfisareCamere() const {
std::cout << "\n--- Camerele Hotelului " << m_nume << std::endl;
if (m_camere.empty()) {
std::cout << "Nu exista camere inregistrate." << std::endl;
} else {
for (int i = 0; i < m_camere.size(); ++i) {
if (m_camere[i] != 0) {
std::cout << *(m_camere[i]) << std::endl;
}


}
}

}
void Hotel::AfisareCamereLibere() const {
std::cout << "\n--- Camere Libere ---" << std::endl;
bool gasit = false;

for (int i = 0; i < m_camere.size(); ++i) {

if (m_camere[i] != 0) {

if (!m_camere[i]->IsOcupata()) {

std::cout << *(m_camere[i]) << std::endl;
gasit = true;
}
}
}
if (!gasit) {
std::cout << "Nu exista camere libere momentan." << std::endl;
}
}
void Hotel::AfisareCamereOcupate() const {
std::cout << "\n--- Camere Ocupate ---" << std::endl;
bool gasit = false;

for (int i = 0; i < m_camere.size(); ++i) {

if (m_camere[i] != 0) {

if (m_camere[i]->IsOcupata()) {

std::cout << *(m_camere[i]) << std::endl;
gasit = true;
}
}
}
if (!gasit) {
std::cout << "Nu exista camere ocupate momentan." << std::endl;
}

}



Client* Hotel::GasesteClient(const std::string& CNP) {
for (int i = 0; i < m_clienti.size(); ++i) {
if (m_clienti[i] != 0 && m_clienti[i]->GetCNP() == CNP) {
return m_clienti[i];
}
}
return 0;
}
const Client* Hotel::GasesteClient(const std::string& CNP) const {
for (int i = 0; i < m_clienti.size(); ++i) {
if (m_clienti[i] != 0 && m_clienti[i]->GetCNP() == CNP) {
return m_clienti[i];
}
}
return 0;
}

void Hotel::AdaugaClient(Client* p_client) {
if (p_client == 0) {
return;
}
if (GasesteClient(p_client->GetCNP()) != 0) {
std::cerr << "Eroare Adaugare Client: Clientul cu CNP " << p_client->GetCNP() << " exista deja!" << std::endl;

return;
}
m_clienti.push_back(p_client);
std::cout << "Clientul " << p_client->GetPrenume() << " adaugat." << std::endl;
}

bool Hotel::StergeClient(const std::string& CNP) {
int index_gasit = -1;
for (int i = 0; i < m_clienti.size(); ++i) {
if (m_clienti[i] != 0 && m_clienti[i]->GetCNP() == CNP) {
index_gasit = i;
break;
}
}
if (index_gasit != -1) {

bool are_rezervari = false;
for(int j=0; j<m_rezervari.size(); ++j) {
if(m_rezervari[j] != 0 && m_rezervari[j]->GetClientRef().GetCNP() == CNP) {
are_rezervari = true;
break;
}
}
if (are_rezervari) {
return false;
}


delete m_clienti[index_gasit];
m_clienti.erase(m_clienti.begin() + index_gasit);
return true;
} else {
return false;
}
}

void Hotel::AfisareClienti() const {
std::cout << "\n--- Clientii Hotelului " << m_nume << std::endl;
if (m_clienti.empty()) { std::cout<<"Nu exista clienti"<<'\n'; }
else {
for (int i = 0; i < m_clienti.size(); ++i) {
if (m_clienti[i] != 0) {
std::cout << *(m_clienti[i]) << std::endl;
}
}
}
std::cout << "------------------------------------------" << std::endl;
}



Angajat* Hotel::GasesteAngajat(const std::string& CNP) {
for (int i = 0; i < m_angajati.size(); ++i) {
if (m_angajati[i] != 0 && m_angajati[i]->GetCNP() == CNP) {
return m_angajati[i];
}
}
return 0;
}


const Angajat* Hotel::GasesteAngajat(const std::string& CNP) const {
for (int i = 0; i < m_angajati.size(); ++i) {
if (m_angajati[i] != 0 && m_angajati[i]->GetCNP() == CNP) {
return m_angajati[i];
}
}
return 0;
}


void Hotel::AdaugaAngajat(Angajat* p_angajat) {
if (p_angajat == 0) {
std::cerr << "Eroare Adaugare Angajat" << std::endl;
return;
}

if (GasesteAngajat(p_angajat->GetCNP()) != 0) {
std::cerr << "Eroare Adaugare Angajat: Angajatul cu CNP " << p_angajat->GetCNP() << " exista deja!" << std::endl;

return;
}
m_angajati.push_back(p_angajat);
std::cout << "Angajatul " << p_angajat->GetPrenume() << " adaugat." << std::endl;
}


bool Hotel::StergeAngajat(const std::string& CNP) {
int index_gasit = -1;
for (int i = 0; i < m_angajati.size(); ++i) {
if (m_angajati[i] != 0 && m_angajati[i]->GetCNP() == CNP) {
index_gasit = i;
break;
}
}

if (index_gasit != -1) {



// std::cout << "Stergere Angajat CNP " << CNP << std::endl;
delete m_angajati[index_gasit];


m_angajati.erase(m_angajati.begin() + index_gasit);
return true;
} else {
std::cerr << "Eroare Stergere Angajat: Angajatul cu CNP " << CNP << " nu a fost gasit." << std::endl;
return false;
}
}


void Hotel::AfisareAngajati() const {
std::cout << "\n--- Angajatii Hotelului " << m_nume << std::endl;
if (m_angajati.empty()) {
std::cout << "Nu exista angajati inregistrati." << std::endl;
} else {
for (int i = 0; i < m_angajati.size(); ++i) {

if (m_angajati[i] != 0) {
std::cout << *(m_angajati[i]) << std::endl;
}


}
}
std::cout << "------------------------------------------" << std::endl;
}




Rezervare* Hotel::GasesteRezervare(int id_rezervare) {
for (int i = 0; i < m_rezervari.size(); ++i) {
if (m_rezervari[i] != 0 && m_rezervari[i]->GetId() == id_rezervare) {
return m_rezervari[i];
}
}
return 0;
}
const Rezervare* Hotel::GasesteRezervare(int id_rezervare) const {
for (int i = 0; i < m_rezervari.size(); ++i) {
if (m_rezervari[i] != 0 && m_rezervari[i]->GetId() == id_rezervare) {
return m_rezervari[i];
}
}
return 0;
}


int Hotel::CreeazaRezervare(const std::string& cnp_client, int numar_camera,const Data& data_check_in,
const Data& data_check_out, int numar_zile) {
Client* client_ptr = GasesteClient(cnp_client);
if (client_ptr == 0) { return -1; }
Camera* camera_ptr = GasesteCamera(numar_camera);
if (camera_ptr == 0) { return -1; }
if (camera_ptr->IsOcupata()) { return -1; }
if (numar_zile <= 0) { return -1; }


Rezervare* p_noua_rezervare = 0;
try {
p_noua_rezervare = new Rezervare(*client_ptr, *camera_ptr, data_check_in, data_check_out, numar_zile);
} catch (const std::bad_alloc&) {
std::cerr << "Eroare critica: Nu s-a putut aloca memorie pentru rezervare!" << std::endl;
return -1;
}


m_rezervari.push_back(p_noua_rezervare);


camera_ptr->SetOcupata(true);


client_ptr->SetNumarRezervari(client_ptr->GetNumarRezervari() + 1);

std::cout << "Rezervare creata cu succes! ID: " << p_noua_rezervare->GetId() << std::endl;
return p_noua_rezervare->GetId();
}


bool Hotel::AnuleazaRezervare(int id_rezervare) {
int index_gasit = -1;
for (int i = 0; i < m_rezervari.size(); ++i) {
if (m_rezervari[i] != 0 && m_rezervari[i]->GetId() == id_rezervare) {
index_gasit = i;
break;
}
}

if (index_gasit != -1) {
Rezervare* p_rezervare_de_sters = m_rezervari[index_gasit];


int numar_camera_rezervata = p_rezervare_de_sters->GetCameraRef().GetNumar();
Camera* camera_ptr = GasesteCamera(numar_camera_rezervata);
if (camera_ptr != 0) {
camera_ptr->SetOcupata(false);
} else {
std::cerr << "Avertisment Anulare: Camera Nr " << numar_camera_rezervata << " negasita!" << std::endl;
}


Client* client_ptr = GasesteClient(p_rezervare_de_sters->GetClientRef().GetCNP());
if (client_ptr != 0) {
int nr_rez = client_ptr->GetNumarRezervari();
if (nr_rez > 0) client_ptr->SetNumarRezervari(nr_rez - 1);
}


delete p_rezervare_de_sters;


m_rezervari.erase(m_rezervari.begin() + index_gasit);

std::cout << "Rezervare ID " << id_rezervare << " anulata." << std::endl;
return true;
} else {
std::cerr << "Eroare Anulare: Rezervarea cu ID " << id_rezervare << " nu a fost gasita." << std::endl;
return false;
}
}


void Hotel::AfisareRezervari() const {
std::cout << "\n--- Rezervarile Hotelului " << m_nume << std::endl;
if (m_rezervari.empty()) {
std::cout<<"Nu exista rezervari"<<'\n';
}
else {
for (int i = 0; i < m_rezervari.size(); ++i) {
if (m_rezervari[i] != 0) {
std::cout << *(m_rezervari[i]) << "\n--------------------" << std::endl;
}
}
}
}

void Hotel::AfisareRezervariClient(const std::string& CNP) const {
std::cout << "\n--- Rezervarile Clientului cu CNP: " << CNP << std::endl;
bool gasit = false;
const Client* client_ptr = GasesteClient(CNP);
if (client_ptr == 0) {
return;
}
std::cout << "Client: " << client_ptr->GetPrenume() << " " << client_ptr->GetNume() << std::endl;
std::cout << "--------------------------------------------" << std::endl;
for (int i = 0; i < static_cast<int>(m_rezervari.size()); ++i) {
if (m_rezervari[i] != 0 && m_rezervari[i]->GetClientRef().GetCNP() == CNP) {
std::cout << *(m_rezervari[i]) << "\n--------------------" << std::endl;
gasit = true;
}
}
if (!gasit) {
std::cout<<"Clientul cu CNP "<<CNP<<" nu are rezervari."<<'\n';
}
}


void Hotel::AfisareGenerala(std::ostream& os) const {

os << "\n========== Detalii Hotel ==========" << std::endl;
os << "Nume: " << m_nume << " (" << m_numar_stele << " stele)" << std::endl;
os << "Adresa: " << m_adresa << std::endl;
os << "----------------------------------" << std::endl;
os << "Numar total camere: " << m_camere.size() << std::endl;
os << "Numar clienti inregistrati: " << m_clienti.size() << std::endl;
os << "Numar angajati: " << m_angajati.size() << std::endl;
os << "Numar rezervari active: " << m_rezervari.size() << std::endl;
os << "=================================" << std::endl;
}

double Hotel::CalculeazaVenitTotal() const {
double venit = 0.0;
for (int i = 0; i < m_rezervari.size(); ++i) {

if (m_rezervari[i] != 0 && m_rezervari[i]->IsPlatita()) {
venit += m_rezervari[i]->GetPretTotal();
}
}
return venit;
}

void Hotel::Afisare(std::ostream& os) const {

os << "\n========== Detalii Hotel ==========" << std::endl;
os << "Nume: " << m_nume << " (" << m_numar_stele << " stele)" << std::endl;
os << "Adresa: " << m_adresa << std::endl;
os << "----------------------------------" << std::endl;
os << "Numar total camere: " << m_camere.size() << std::endl;
os << "Numar clienti inregistrati: " << m_clienti.size() << std::endl;
os << "Numar angajati: " << m_angajati.size() << std::endl;
os << "Numar rezervari active: " << m_rezervari.size() << std::endl;
os << "=================================" << std::endl;
}


std::ostream& operator<<(std::ostream& os, const Hotel& hotel) {
hotel.Afisare(os);
return os;
}

std::istream& operator>>(std::istream& is, Hotel& hotel) {
std::cout << "Nume hotel: ";
std::getline(is, hotel.m_nume);
std::cout << "Adresa hotel: ";
std::getline(is, hotel.m_adresa);
std::cout << "Numar stele: ";
is >> hotel.m_numar_stele;
return is;
}