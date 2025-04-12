#include "Hotel.h"      // Headerul clasei Hotel
#include <iostream>     // Pentru std::cout, std::cerr, std::endl
#include <vector>       // Pentru std::vector
#include <string>       // Pentru std::string
#include <stdexcept>    // Pentru std::runtime_error (desi nu il folosim activ)
#include <limits>       // Pentru std::numeric_limits (in operator>>)
#include <cstddef>      // Pentru NULL sau 0 ca pointer nul

// --- Constructori / Destructor ---

Hotel::Hotel() : numarStele(0) {
    // std::cout << "Constructor Hotel (default)" << std::endl;
}

Hotel::Hotel(const std::string& nume, const std::string& adresa, int numarStele)
    : nume(nume), adresa(adresa), numarStele(numarStele) {
    // std::cout << "Constructor Hotel (parametrizat): " << nume << std::endl;
}

// Constructor de copiere
Hotel::Hotel(const Hotel& other)
    : nume(other.nume), adresa(other.adresa), numarStele(other.numarStele),
      camere(other.camere), clienti(other.clienti), angajati(other.angajati),
      rezervari(other.rezervari) {
    // std::cout << "Constructor Hotel (copiere): " << nume << std::endl;
}

// Operator de atribuire
Hotel& Hotel::operator=(const Hotel& other) {
    // Verificare auto-atribuire
    if (this != &other) {
        nume = other.nume;
        adresa = other.adresa;
        numarStele = other.numarStele;
        // Atribuirea pentru vectori face automat copie in C++98
        camere = other.camere;
        clienti = other.clienti;
        angajati = other.angajati;
        rezervari = other.rezervari;
        // std::cout << "Operator= Hotel: " << nume << std::endl;
    }
    return *this;
}

// Destructor
Hotel::~Hotel() {
    // Vectorii de obiecte (nu pointeri) isi apeleaza automat destructorii
    // pentru fiecare element atunci cand obiectul Hotel este distrus.
    // Nu este necesar cod suplimentar aici pentru memoria membrilor din vectori.
    // std::cout << "Destructor Hotel: " << nume << std::endl;
}

// --- Getteri / Setteri ---

std::string Hotel::getNume() const { return nume; }
void Hotel::setNume(const std::string& nume) { this->nume = nume; }
std::string Hotel::getAdresa() const { return adresa; }
void Hotel::setAdresa(const std::string& adresa) { this->adresa = adresa; }
int Hotel::getNumarStele() const { return numarStele; }
void Hotel::setNumarStele(int stele) {
    // Optional: adauga validare pentru numarul de stele (ex: 1-5)
    this->numarStele=stele;
}

// --- Management Camere ---

// Gaseste camera dupa numar, returneaza pointer sau 0
Camera* Hotel::gasesteCamera(int numarCamera) {
    for (int i = 0; i < camere.size(); ++i) {
        if (camere[i].getNumar() == numarCamera) {
            return &camere[i]; // Returnam adresa obiectului din vector
        }
    }
    return 0; // Nu s-a gasit
}

// Varianta const a functiei gasesteCamera
const Camera* Hotel::gasesteCamera(int numarCamera) const {
    for (int i = 0; i < camere.size(); ++i) {
        if (camere[i].getNumar() == numarCamera) {
            return &camere[i];
        }
    }
    return 0;
}

// Adauga o camera in vector
void Hotel::adaugaCamera(const Camera& camera) {
    // Verificam daca exista deja o camera cu acelasi numar
    if (gasesteCamera(camera.getNumar()) != 0) {
        std::cerr << "Eroare Adaugare Camera: Camera cu numarul " << camera.getNumar() << " exista deja!" << std::endl;
        return;
    }
    camere.push_back(camera); // Adauga o copie a camerei in vector
    std::cout << "Camera Nr " << camera.getNumar() << " adaugata." << std::endl;
}

// Sterge o camera dupa numar
bool Hotel::stergeCamera(int numarCamera) {
    int index_gasit = -1;
    for (int i = 0; i < camere.size(); ++i) {
        if (camere[i].getNumar() == numarCamera) {
            index_gasit = i;
            break;
        }
    }

    if (index_gasit != -1) {
        // Verifica daca aceasta camera este folosita intr-o rezervare activa inainte de a sterge
        bool folosita_in_rezervare = false;
        for (int j = 0; j < rezervari.size(); ++j) {
            if (rezervari[j].getCameraRef().getNumar() == numarCamera) {
                folosita_in_rezervare = true;
                break;
            }
        }
        if (folosita_in_rezervare) {
            std::cerr << "Eroare Stergere Camera: Camera Nr " << numarCamera << " este folosita intr-o rezervare activa si nu poate fi stearsa." << std::endl;
            return false;
        }

        camere.erase(camere.begin() + index_gasit); // Sterge elementul de la indexul gasit
        return true;
    } else {
        std::cerr << "Eroare Stergere Camera: Camera Nr " << numarCamera << " nu a fost gasita." << std::endl;
        return false;
    }
}

// Afiseaza toate camerele
void Hotel::afisareCamere() const {
    std::cout << "\n--- Camerele Hotelului " << nume << " ---" << std::endl;
    if (camere.empty()) {
        std::cout << "Nu exista camere inregistrate." << std::endl;
    } else {
        for (int i = 0; i < camere.size(); ++i) {
            std::cout << camere[i] << std::endl;
        }
    }
    std::cout << "----------------------------------" << std::endl;
}

// Afiseaza camerele libere
void Hotel::afisareCamereLibere() const {
    std::cout << "\n--- Camere Libere ---" << std::endl;
    bool gasit = false;
    for (int i = 0; i < camere.size(); ++i) {
        if (!camere[i].isOcupata()) {
            std::cout << camere[i] << std::endl;
            gasit = true;
        }
    }
    if (!gasit) {
        std::cout << "Nu exista camere libere momentan." << std::endl;
    }
    std::cout << "---------------------" << std::endl;
}

// Afiseaza camerele ocupate
void Hotel::afisareCamereOcupate() const {
    std::cout << "\n--- Camere Ocupate ---" << std::endl;
    bool gasit = false;
    for (int i = 0; i < camere.size(); ++i) {
        if (camere[i].isOcupata()) {
            std::cout << camere[i] << std::endl;
            gasit = true;
        }
    }
     if (!gasit) {
        std::cout << "Nu exista camere ocupate momentan." << std::endl;
    }
    std::cout << "--------------------" << std::endl;
}

// --- Management Clienti ---

// Gaseste client dupa CNP, returneaza pointer sau 0
Client* Hotel::gasesteClient(const std::string& CNP) {
    for (int i = 0; i < clienti.size(); ++i) {
        if (clienti[i].getCNP() == CNP) {
            return &clienti[i];
        }
    }
    return 0;
}
// Varianta const
const Client* Hotel::gasesteClient(const std::string& CNP) const {
    for (int i = 0; i < clienti.size(); ++i) {
        if (clienti[i].getCNP() == CNP) {
            return &clienti[i];
        }
    }
    return 0;
}

// Adauga client
void Hotel::adaugaClient(const Client& client) {
     if (gasesteClient(client.getCNP()) != 0) {
        std::cerr << "Eroare Adaugare Client: Clientul cu CNP " << client.getCNP() << " exista deja!" << std::endl;
        return;
    }
    clienti.push_back(client);
    std::cout << "Clientul " << client.getPrenume() << " " << client.getNume() << " adaugat." << std::endl;
}

// Sterge client dupa CNP
bool Hotel::stergeClient(const std::string& CNP) {
    int index_gasit = -1;
    for (int i = 0; i < clienti.size(); ++i) {
        if (clienti[i].getCNP() == CNP) {
            index_gasit = i;
            break;
        }
    }

    if (index_gasit != -1) {
        //Verifica daca clientul are rezervari active.
        bool are_rezervari = false;
        for (int j = 0; j < rezervari.size(); ++j) {
            if (rezervari[j].getClientRef().getCNP() == CNP) {
                are_rezervari = true;
                break;
            }
        }
        if (are_rezervari) {
             std::cerr << "Eroare Stergere Client: Clientul CNP " << CNP << " are rezervari active si nu poate fi sters." << std::endl;
            return false;
        }

        // Daca nu are rezervari, il stergem
        clienti.erase(clienti.begin() + index_gasit);
        return true;
    } else {
         std::cerr << "Eroare Stergere Client: Clientul cu CNP " << CNP << " nu a fost gasit." << std::endl;
        return false;
    }
}

// Afiseaza toti clientii
void Hotel::afisareClienti() const {
     std::cout << "\n--- Clientii Hotelului " << nume << " ---" << std::endl;
    if (clienti.empty()) {
        std::cout << "Nu exista clienti inregistrati." << std::endl;
    } else {
        for (int i = 0; i < clienti.size(); ++i) {
            std::cout << clienti[i] << std::endl;
        }
    }
    std::cout << "---------------------------------" << std::endl;
}

// --- Management Angajati ---

// Gaseste angajat dupa CNP, returneaza pointer sau 0
Angajat* Hotel::gasesteAngajat(const std::string& CNP) {
    for (int i = 0; i < angajati.size(); ++i) {
        if (angajati[i].getCNP() == CNP) {
            return &angajati[i];
        }
    }
    return 0;
}
// Varianta const
const Angajat* Hotel::gasesteAngajat(const std::string& CNP) const {
     for (int i = 0; i < angajati.size(); ++i) {
        if (angajati[i].getCNP() == CNP) {
            return &angajati[i];
        }
    }
    return 0;
}

// Adauga angajat
void Hotel::adaugaAngajat(const Angajat& angajat) {
    if (gasesteAngajat(angajat.getCNP()) != 0) {
        std::cerr << "Eroare Adaugare Angajat: Angajatul cu CNP " << angajat.getCNP() << " exista deja!" << std::endl;
        return;
    }
    angajati.push_back(angajat);
    std::cout << "Angajatul " << angajat.getPrenume() << " " << angajat.getNume() << " adaugat." << std::endl;
}

// Sterge angajat dupa CNP
bool Hotel::stergeAngajat(const std::string& CNP) {
    int index_gasit = -1;
     for (int i = 0; i < angajati.size(); ++i) {
        if (angajati[i].getCNP() == CNP) {
             index_gasit = i;
            break;
        }
    }

    if (index_gasit != -1) {

        angajati.erase(angajati.begin() + index_gasit);
        return true;
    } else {
         std::cerr << "Eroare Stergere Angajat: Angajatul cu CNP " << CNP << " nu a fost gasit." << std::endl;
        return false;
    }
}

// Afiseaza toti angajatii
void Hotel::afisareAngajati() const {
    std::cout << "\n--- Angajatii Hotelului " << nume << " ---" << std::endl;
    if (angajati.empty()) {
        std::cout << "Nu exista angajati inregistrati." << std::endl;
    } else {
        for (int i = 0; i < angajati.size(); ++i) {
            std::cout << angajati[i] << std::endl;
        }
    }
    std::cout << "-----------------------------------" << std::endl;
}


// --- Management Rezervari ---

// Gaseste rezervare dupa ID, returneaza pointer sau 0
Rezervare* Hotel::gasesteRezervare(int idRezervare) {
     for (int i = 0; i < rezervari.size(); ++i) {
        if (rezervari[i].getId() == idRezervare) {
            return &rezervari[i];
        }
    }
    return 0;
}
// Varianta const
const Rezervare* Hotel::gasesteRezervare(int idRezervare) const {
    for (int i = 0; i < rezervari.size(); ++i) {
        if (rezervari[i].getId() == idRezervare) {
            return &rezervari[i];
        }
    }
    return 0;
}

// Creeaza o noua rezervare
int Hotel::creeazaRezervare(const std::string& cnpClient, int numarCamera, const std::string& dataCheckIn,
                             const std::string& dataCheckOut, int numarZile) {

    Client* clientPtr = gasesteClient(cnpClient);
    if (clientPtr == 0) {
        std::cerr << "Eroare Creare Rezervare: Clientul cu CNP " << cnpClient << " nu exista." << std::endl;
        return -1;
    }


    Camera* cameraPtr = gasesteCamera(numarCamera);
    if (cameraPtr == 0) {
        std::cerr << "Eroare Creare Rezervare: Camera cu numarul " << numarCamera << " nu exista." << std::endl;
        return -1;
    }


    if (cameraPtr->isOcupata()) {
        std::cerr << "Eroare Creare Rezervare: Camera " << numarCamera << " este deja ocupata." << std::endl;
        return -1;
    }


    if (numarZile <= 0) {
         std::cerr << "Eroare Creare Rezervare: Numarul de zile trebuie sa fie pozitiv." << std::endl;
         return -1;
     }


    Rezervare nouaRezervare(*clientPtr, *cameraPtr, dataCheckIn, dataCheckOut, numarZile);
    cameraPtr->setOcupata(true);
    rezervari.push_back(nouaRezervare);
    clientPtr->setNumarRezervari(clientPtr->getNumarRezervari() + 1);
    // Optional: Actualizeaza starea de client fidel
    if (clientPtr->getNumarRezervari() >= 5 && !clientPtr->isClientFidel()) {
      clientPtr->setClientFidel(true);
       std::cout << "Clientul " << clientPtr->getNume() << " a devenit client fidel!" << std::endl;
    }

    std::cout << "Rezervare creata cu succes! ID: " << nouaRezervare.getId() << std::endl;
    return nouaRezervare.getId();
}

// Anuleaza o rezervare dupa ID
bool Hotel::anuleazaRezervare(int idRezervare) {
    int index_gasit = -1;
    for (int i = 0; i < static_cast<int>(rezervari.size()); ++i) {
        if (rezervari[i].getId() == idRezervare) {
            index_gasit = i;
            break;
        }
    }

    if (index_gasit != -1) {

        int numarCameraRezervata = rezervari[index_gasit].getCameraRef().getNumar();

        Camera* cameraPtr = gasesteCamera(numarCameraRezervata);

        if (cameraPtr != 0) {
            cameraPtr->setOcupata(false);
            std::cout << "Info Anulare: Camera Nr " << numarCameraRezervata << " a fost eliberata." << std::endl;
        } else {

            std::cerr << "Camera Nr " << numarCameraRezervata
                      << " asociata rezervarii ID " << idRezervare << " nu a fost gasita in lista hotelului!" << std::endl;
        }

        Client* clientPtr = gasesteClient(rezervari[index_gasit].getClientRef().getCNP());
        if (clientPtr != 0) {
             int nrRez = clientPtr->getNumarRezervari();
             if (nrRez > 0) {
                 clientPtr->setNumarRezervari(nrRez - 1);
             }



              if (clientPtr->getNumarRezervari() < 5 && clientPtr->isClientFidel()) {
                  clientPtr->setClientFidel(false);
              }
         }


        rezervari.erase(rezervari.begin() + index_gasit);
        return true;
    } else {
        // Rezervarea nu a fost gasita
        std::cerr << "Rezervarea cu ID " << idRezervare << " nu a fost gasita." << std::endl;
        return false;
    }
}

// Afiseaza toate rezervarile
void Hotel::afisareRezervari() const {
     std::cout << "\n--- Rezervarile Hotelului " << nume << " ---" << std::endl;
    if (rezervari.empty()) {
        std::cout << "Nu exista rezervari inregistrate." << std::endl;
    } else {
        for (int i = 0; i < rezervari.size(); ++i) {
            std::cout << rezervari[i] << "\n--------------------" << std::endl;
        }
    }
}

// Afiseaza rezervarile unui anumit client
void Hotel::afisareRezervariClient(const std::string& CNP) const {
     std::cout << "\n--- Rezervarile Clientului cu CNP: " << CNP << " ---" << std::endl;
     bool gasit = false;
     const Client* clientPtr = gasesteClient(CNP);
     if (clientPtr == 0) {
         std::cout << "Clientul cu CNP " << CNP << " nu a fost gasit." << std::endl;
         std::cout << "--------------------------------------------" << std::endl;
         return;
     }

     std::cout << "Client: " << clientPtr->getPrenume() << " " << clientPtr->getNume() << std::endl;
     std::cout << "--------------------------------------------" << std::endl;

     // Parcurgem rezervarile
     for (int i = 0; i < rezervari.size(); ++i) {
         // Verificam daca CNP-ul clientului din rezervare corespunde
         if (rezervari[i].getClientRef().getCNP() == CNP) {
             std::cout << rezervari[i] << "\n--------------------" << std::endl;
             gasit = true;
         }
     }

      if (!gasit) {
         std::cout << "Acest client nu are rezervari inregistrate." << std::endl;
         std::cout << "--------------------------------------------" << std::endl;
     }
}

// --- Alte Metode ---

// Afiseaza detalii generale despre hotel
// void Hotel::afisareGenerala(std::ostream& os) const {
//     os << "\n========== Detalii Hotel ==========" << std::endl; // Folosim endl aici
//     os << "Nume: " << nume << " (" << numarStele << " stele)" << std::endl;
//     os << "Adresa: " << adresa << std::endl;
//     os << "----------------------------------" << std::endl;
//     os << "Numar total camere: " << camere.size() << std::endl;
//     os << "Numar clienti inregistrati: " << clienti.size() << std::endl;
//     os << "Numar angajati: " <<angajati.size()<< std::endl;
//     os << "Numar rezervari active: " << rezervari.size() << std::endl;
//     os << "=================================" << std::endl;
// }

// Calculeaza venitul total din rezervarile platite
double Hotel::calculeazaVenitTotal() const {
    double venit = 0.0;
    for (int i = 0; i < static_cast<int>(rezervari.size()); ++i) {
        if (rezervari[i].isPlatita()) {
            venit += rezervari[i].getPretTotal();
        }
    }
    return venit;
}

// Implementarea metodei virtuale din interfata IAfisabil
void Hotel::afisare(std::ostream& os) const {
    os << "\n========== Detalii Hotel ==========" << std::endl; // Folosim endl aici
    os << "Nume: " << nume << " (" << numarStele << " stele)" << std::endl;
    os << "Adresa: " << adresa << std::endl;
    os << "----------------------------------" << std::endl;
    os << "Numar total camere: " << camere.size() << std::endl;
    os << "Numar clienti inregistrati: " << clienti.size() << std::endl;
    os << "Numar angajati: " <<angajati.size()<< std::endl;
    os << "Numar rezervari active: " << rezervari.size() << std::endl;
    os << "=================================" << std::endl;
}

// --- Operatori Friend ---

// Operatorul << apeleaza metoda afisare(os)
std::ostream& operator<<(std::ostream& os, const Hotel& hotel) {
    hotel.afisare(os);
    return os;
}

// Operatorul >> citeste datele de baza ale hotelului
std::istream& operator>>(std::istream& is, Hotel& hotel) {
    std::cout << "Nume hotel: ";
    std::getline(is, hotel.nume);
    std::cout << "Adresa hotel: ";
    std::getline(is, hotel.adresa);
    std::cout << "Numar stele: ";
    is >> hotel.numarStele;
    return is;
}