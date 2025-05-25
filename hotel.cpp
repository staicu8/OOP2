#include "hotel.h"
#include <iostream>
#include <vector>
#include <string>



Hotel::Hotel() : m_numar_stele(0) {

}

Hotel::Hotel(const std::string& nume, const std::string& adresa, int numar_stele)
: m_nume(nume), m_adresa(adresa), m_numar_stele(numar_stele) {

}


Hotel::~Hotel() {

//Eliberare de memorie cand se apeleaza destructorul

//std::cout << " - Stergere Camere..." << std::endl;
for (int i = 0; i < m_camere.size(); ++i) {
    delete m_camere[i];
}
m_camere.clear();


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

//Getteri si Setteri
std::string Hotel::GetNume() const { return m_nume; }
void Hotel::SetNume(const std::string& nume) { this->m_nume = nume; }
std::string Hotel::GetAdresa() const { return m_adresa; }
void Hotel::SetAdresa(const std::string& adresa) { this->m_adresa = adresa; }
int Hotel::GetNumarStele() const { return m_numar_stele; }
void Hotel::SetNumarStele(int stele) { if (stele >= 0 && stele <= 5) this->m_numar_stele = stele; else std::cerr << "..."; }




//Parcurge vectorul de angajati si returneaza indexul angajatului cu cnp-ul dat sau -1 in caz contrar
int Hotel::_GasesteIndexAngajat(const std::string& CNP) const {
    for(int i=0;i<m_angajati.size();++i)
        if(m_angajati[i]->GetCNP()==CNP)
            return i;
    return -1;
}
//Parcurge vectorul de camere si returneaza indexul camerei cu numarul dat sau -1 in caz contrar
int Hotel::_GasesteIndexCamera(int numar) const {
    for(int i=0;i<m_camere.size();++i)
        if(m_camere[i]->GetNumar()==numar)
            return i;
    return -1;
}
//Parcurge vectorul de clienti si returneaza indexul clientului cu cnp-ul dat sau -1 in caz contrar
int Hotel::_GasesteIndexClient(const std::string& CNP) const {
    for(int i=0;i<m_clienti.size();++i)
        if(m_clienti[i]->GetCNP()==CNP)
            return i;
    return -1;
}
//Parcurge vectorul de rezervari si returneaza indexul rezervarii cu id-ul dat sau -1 in caz contrar
int Hotel::_GasesteIndexRezervare(int id_rezervare) const {
    for(int i=0;i<m_rezervari.size();++i)
        if(m_rezervari[i]->GetId()==id_rezervare)
            return i;
    return -1;
}


Camera* Hotel::GasesteCamera(int numar_camera) {
    int index=_GasesteIndexCamera(numar_camera);
    if (index!=-1)
        return m_camere[index];
    return 0;

}

//Adauga obicetul de tip Camera* in vector
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
//Sterge camera cu numar dat din vectorul de camere
bool Hotel::StergeCamera(int numar_camera) {
int index_gasit = _GasesteIndexCamera(numar_camera);
// for (int i = 0; i < m_camere.size(); ++i) {
// if (m_camere[i] != 0 && m_camere[i]->GetNumar() == numar_camera) {
// index_gasit = i;
// break;
// }
//}

if (index_gasit != -1) {//Daca a fost gasita camera
//Verifica daca este folosita intr-o rezervare
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

//Daca nu este folosita intr-o rezervare si a fost gasita
delete m_camere[index_gasit];
m_camere.erase(m_camere.begin() + index_gasit);

return true;
} else {
    std::cerr << "Eroare Stergere Camera: Camera Nr " << numar_camera << " nu a fost gasita." << std::endl;
    return false;
}
}
//Parcurge vectorul de camere si le afiseaza
void Hotel::AfisareCamere() const {
std::cout << "\n--- Camerele Hotelului " << m_nume << std::endl;
if (m_camere.empty()) {
    std::cout << "Nu exista camere inregistrate." << std::endl;
} else {
for (int i = 0; i < m_camere.size(); ++i) {
    if (m_camere[i] != 0) {
    std::cout << *(m_camere[i]) << std::endl; //Operatorul << supraincarcat
}


}
}

}
//Parcurge vectorul de camere si le afiseaza daca sunt libere
void Hotel::AfisareCamereLibere() const {
std::cout << "\n--- Camere Libere ---" << std::endl;
bool gasit = false;

for (int i = 0; i < m_camere.size(); ++i) {



    if (m_camere[i] != 0 && !m_camere[i]->IsOcupata()) {

        std::cout << *(m_camere[i]) << std::endl;
        gasit = true;
}

}
if (!gasit) {
    std::cout << "Nu exista camere libere momentan." << std::endl;
}
}
//Parcurge vectorul de camere si le afiseaza daca sunt ocupate
void Hotel::AfisareCamereOcupate() const {
std::cout << "\n--- Camere Ocupate ---" << std::endl;
bool gasit = false;

for (int i = 0; i < m_camere.size(); ++i) {



if (m_camere[i] != 0 && m_camere[i]->IsOcupata()) {

    std::cout << *(m_camere[i]) << std::endl;
    gasit = true;
}

}
if (!gasit) {
std::cout << "Nu exista camere ocupate momentan." << std::endl;
}

}



Client* Hotel::GasesteClient(const std::string& CNP) {
    int index=_GasesteIndexClient(CNP);
    if (index!=-1)
        return m_clienti[index];
    return 0;
}

//Adauga obicetul de tip Client* in vectorul de clienti
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

//Sterge clientul cu cnp-ul dat din vectorul de clienti
bool Hotel::StergeClient(const std::string& CNP) {
int index_gasit = -1;
for (int i = 0; i < m_clienti.size(); ++i) {
if (m_clienti[i] != 0 && m_clienti[i]->GetCNP() == CNP) {
    index_gasit = i;
    break;
}
}
if (index_gasit != -1) {//Daca clientul a fost gasit

bool are_rezervari = false;
for(int j=0; j<m_rezervari.size(); ++j) {
if(m_rezervari[j] != 0 && m_rezervari[j]->GetClientRef().GetCNP() == CNP) {
    are_rezervari = true;
    break;
}
}
if (are_rezervari) {
    std::cerr << "Eroare Stergere Client: Clientul cu CNP-ul " << CNP << " are o rezervare activa." << std::endl;
    return false;
}

//Daca nu are rezervari si a fost gasit
delete m_clienti[index_gasit];
m_clienti.erase(m_clienti.begin() + index_gasit);
return true;
} else {
return false;
}
}
//Parcurge vectorul de clienti si ii afiseaza
void Hotel::AfisareClienti() const {
    std::cout << "\n--- Clientii Hotelului " << m_nume << std::endl;
    if (m_clienti.empty()) {
        std::cout<<"Nu exista clienti"<<'\n';
    }
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
    int index=_GasesteIndexAngajat(CNP);
    if (index!=-1)
        return m_angajati[index];
    return 0;
}




//Adauga obicetul de tip Angajat* in vectorul de angajati
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

//Sterge din vectorul de angajati angajatul cu cnp-ul dat
bool Hotel::StergeAngajat(const std::string& CNP) {
    int index_gasit = -1;
    for (int i = 0; i < m_angajati.size(); ++i) {
        if (m_angajati[i] != 0 && m_angajati[i]->GetCNP() == CNP) {
                index_gasit = i;
                break;
    }
    }

    if (index_gasit != -1) {//Daca angajatul a fost gasit



// std::cout << "Stergere Angajat CNP " << CNP << std::endl;
    delete m_angajati[index_gasit];


    m_angajati.erase(m_angajati.begin() + index_gasit);
    return true;
} else {
    std::cerr << "Eroare Stergere Angajat: Angajatul cu CNP " << CNP << " nu a fost gasit." << std::endl;
    return false;
}
}

//Parcruge vectorul de angajati si ii afiseaza
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
    std::cout << "---------------------------- --------------" << std::endl;
}




Rezervare* Hotel::GasesteRezervare(int id_rezervare) {
    int index=_GasesteIndexRezervare(id_rezervare);
    if (index!=-1)
        return m_rezervari[index];
    return 0;
}


int Hotel::CreeazaRezervare(const std::string& cnp_client, int numar_camera,const Data& data_check_in,
const Data& data_check_out, int numar_zile) {
    Client* client_ptr = GasesteClient(cnp_client);
    if (client_ptr == 0) { return -1; } //Daca exist clientul
    Camera* camera_ptr = GasesteCamera(numar_camera);
    if (camera_ptr == 0) { return -1; }//Daca exista camera
    if (camera_ptr->IsOcupata()) { return -1; }//Daca nu este ocupata camera
    if (numar_zile <= 0) { return -1; }//Daca e valid numarul de zile


    Rezervare* p_noua_rezervare = new Rezervare(*client_ptr, *camera_ptr, data_check_in, data_check_out, numar_zile);
    m_rezervari.push_back(p_noua_rezervare);
    camera_ptr->SetOcupata(true);//Ocupa camera
    client_ptr->SetNumarRezervari(client_ptr->GetNumarRezervari() + 1);//Creste numarul de rezervari pentru acel client
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

if (index_gasit != -1) {//Daca a fost gasita rezervarea
    Rezervare* p_rezervare_de_sters = m_rezervari[index_gasit];

    int numar_camera_rezervata = p_rezervare_de_sters->GetCameraRef().GetNumar();
    Camera* camera_ptr = GasesteCamera(numar_camera_rezervata);
    camera_ptr->SetOcupata(false);//Elibereaza camera
    Client* client_ptr = GasesteClient(p_rezervare_de_sters->GetClientRef().GetCNP());
    int nr_rez = client_ptr->GetNumarRezervari();
    if (nr_rez > 0) client_ptr->SetNumarRezervari(nr_rez - 1);//Scade numarul de rezervari
    delete p_rezervare_de_sters;
    m_rezervari.erase(m_rezervari.begin() + index_gasit);
    std::cout << "Rezervare ID " << id_rezervare << " anulata." << std::endl;
    return true;
} else {
    std::cerr << "Eroare : Rezervarea cu ID " << id_rezervare << " nu a fost gasita." << std::endl;
    return false;
}
}

//Parcurge vectorul de rezervari si le afiseaza
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

void Hotel::AfisareRezervariClient(const std::string& CNP)  {
    std::cout << "\n--- Rezervarile Clientului cu CNP: " << CNP << std::endl;
    bool gasit = false;
    Client* client_ptr = GasesteClient(CNP);
    if (client_ptr == 0) {
        std::cout<<"Clientul cu CNP "<<CNP<<" nu exista"<<'\n';
        return;
    }

    //Daca a fost gasit clientul
    std::cout << "Client: " << client_ptr->GetPrenume() << " " << client_ptr->GetNume() << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    //Parcurge rezervarile
    for (int i = 0; i < m_rezervari.size(); ++i) {
        if (m_rezervari[i] != 0 && m_rezervari[i]->GetClientRef().GetCNP() == CNP) {
            std::cout << *(m_rezervari[i]) << "\n--------------------" << std::endl;
            gasit = true;
    }
    }
    if (!gasit) {//Daca nu au fost gasite rezervari
    std::cout<<"Clientul cu CNP "<<CNP<<" nu are rezervari."<<'\n';
}
}





double Hotel::CalculeazaVenitTotal() const {
    double venit = 0.0;
    for(int i=0;i<m_rezervari.size();++i)
        if(m_rezervari[i]->IsPlatita())
        venit=venit+(*m_rezervari[i]);//Operatorul + supraincarcat
    return venit;
}
//Implementeaza functia pur virtuala Afisare din interfata
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

//Supraincarcare operatori
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