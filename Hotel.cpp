#include "Hotel.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <limits>
#include <cstddef> // Pentru NULL / 0

// --- Constructori ---
Hotel::Hotel() : numarStele(0) {
    // Vectorii de pointeri sunt initializati goi implicit
    // std::cout << "Constructor Hotel (default) - Pointeri" << std::endl;
}

Hotel::Hotel(const std::string& nume, const std::string& adresa, int numarStele)
    : nume(nume), adresa(adresa), numarStele(numarStele) {

}


Hotel::~Hotel() {
    // std::cout << "Destructor Hotel: Eliberare memorie pentru '" << nume << "'..." << std::endl;


    //std::cout << "  - Stergere Camere..." << std::endl;
    for (int i = 0; i < static_cast<int>(camere.size()); ++i) {
        delete camere[i];
    }



    //std::cout << "  - Stergere Clienti..." << std::endl;
    for (int i = 0; i < static_cast<int>(clienti.size()); ++i) {
        delete clienti[i];
    }
    clienti.clear();


    //std::cout << "  - Stergere Angajati..." << std::endl;
    for (int i = 0; i < static_cast<int>(angajati.size()); ++i) {
        delete angajati[i];
    }
    angajati.clear();


    // std::cout << "  - Stergere Rezervari..." << std::endl;
    for (int i = 0; i < static_cast<int>(rezervari.size()); ++i) {
        delete rezervari[i]; // Apeleaza destructorul Rezervare
    }
    rezervari.clear();

    // std::cout << "Destructor Hotel: Memorie eliberata." << std::endl;
}


std::string Hotel::getNume() const { return nume; }
void Hotel::setNume(const std::string& nume) { this->nume = nume; }
std::string Hotel::getAdresa() const { return adresa; }
void Hotel::setAdresa(const std::string& adresa) { this->adresa = adresa; }
int Hotel::getNumarStele() const { return numarStele; }
void Hotel::setNumarStele(int stele) { if (stele >= 0 && stele <= 5) this->numarStele = stele; else std::cerr << "..."; }



Camera* Hotel::gasesteCamera(int numarCamera) {
    for (int i = 0; i < static_cast<int>(camere.size()); ++i) {

        if (camere[i] != 0 && camere[i]->getNumar() == numarCamera) {
            return camere[i];
        }
    }
    return 0;
}
const Camera* Hotel::gasesteCamera(int numarCamera) const {
    for (int i = 0; i < static_cast<int>(camere.size()); ++i) {
        if (camere[i] != 0 && camere[i]->getNumar() == numarCamera) {
            return camere[i];
        }
    }
    return 0;
}

void Hotel::adaugaCamera(Camera* pCamera) {
    if (pCamera == 0) {
        std::cerr << "Eroare Adaugare Camera" << std::endl;
        return;
    }
    if (gasesteCamera(pCamera->getNumar()) != 0) {
        std::cerr << "Eroare Adaugare Camera: Camera cu numarul " << pCamera->getNumar() << " exista deja!" << std::endl;

        return;
    }
    camere.push_back(pCamera); // Adaugam pointerul in vector
    std::cout << "Camera Nr " << pCamera->getNumar() << " (pointer) adaugata." << std::endl;
}

bool Hotel::stergeCamera(int numarCamera) {
    int index_gasit = -1;
    for (int i = 0; i < static_cast<int>(camere.size()); ++i) {
        if (camere[i] != 0 && camere[i]->getNumar() == numarCamera) {
            index_gasit = i;
            break;
        }
    }

    if (index_gasit != -1) {

        bool folosita_in_rezervare = false;
        for (int j = 0; j < static_cast<int>(rezervari.size()); ++j) {

             if (rezervari[j] != 0 && rezervari[j]->getCameraRef().getNumar() == numarCamera) {
                folosita_in_rezervare = true;
                break;
            }
        }
        if (folosita_in_rezervare) {
            std::cerr << "Eroare Stergere Camera: Camera Nr " << numarCamera << " este folosita intr-o rezervare activa." << std::endl;
            return false;
        }


        delete camere[index_gasit]; //


        camere.erase(camere.begin() + index_gasit);
        return true;
    } else {
        std::cerr << "Eroare Stergere Camera: Camera Nr " << numarCamera << " nu a fost gasita." << std::endl;
        return false;
    }
}

void Hotel::afisareCamere() const {
    std::cout << "\n--- Camerele Hotelului " << nume  << std::endl;
    if (camere.empty()) {
        std::cout << "Nu exista camere inregistrate." << std::endl;
    } else {
        for (int i = 0; i < static_cast<int>(camere.size()); ++i) {
            if (camere[i] != 0) {
                std::cout << *(camere[i]) << std::endl;
            } else {
                 std::cout << "  -> Pointer nul la index " << i << std::endl;
            }
        }
    }

}
void Hotel::afisareCamereLibere() const {
    std::cout << "\n--- Camere Libere ---" << std::endl;
    bool gasit = false;

    for (int i = 0; i < static_cast<int>(camere.size()); ++i) {

        if (camere[i] != 0) {

            if (!camere[i]->isOcupata()) {

                std::cout << *(camere[i]) << std::endl;
                gasit = true;
            }
        }
    }
    if (!gasit) {
        std::cout << "Nu exista camere libere momentan." << std::endl;
    }
}
void Hotel::afisareCamereOcupate() const {
    std::cout << "\n--- Camere Ocupate ---" << std::endl;
    bool gasit = false;

    for (int i = 0; i < static_cast<int>(camere.size()); ++i) {

        if (camere[i] != 0) {

            if (camere[i]->isOcupata()) {

                std::cout << *(camere[i]) << std::endl;
                gasit = true;
            }
        }
    }
    if (!gasit) {
        std::cout << "Nu exista camere ocupate momentan." << std::endl;
    }

}



Client* Hotel::gasesteClient(const std::string& CNP) {
    for (int i = 0; i < static_cast<int>(clienti.size()); ++i) {
        if (clienti[i] != 0 && clienti[i]->getCNP() == CNP) {
            return clienti[i];
        }
    }
    return 0;
}
const Client* Hotel::gasesteClient(const std::string& CNP) const {
     for (int i = 0; i < static_cast<int>(clienti.size()); ++i) {
        if (clienti[i] != 0 && clienti[i]->getCNP() == CNP) {
            return clienti[i];
        }
    }
    return 0;
}

void Hotel::adaugaClient(Client* pClient) {
    if (pClient == 0) {
        return;
    }
    if (gasesteClient(pClient->getCNP()) != 0) {
        std::cerr << "Eroare Adaugare Client: Clientul cu CNP " << pClient->getCNP() << " exista deja!" << std::endl;

        return;
    }
    clienti.push_back(pClient);
    std::cout << "Clientul " << pClient->getPrenume() << " (pointer) adaugat." << std::endl;
}

bool Hotel::stergeClient(const std::string& CNP) {
    int index_gasit = -1;
    for (int i = 0; i < static_cast<int>(clienti.size()); ++i) {
        if (clienti[i] != 0 && clienti[i]->getCNP() == CNP) {
            index_gasit = i;
            break;
        }
    }
    if (index_gasit != -1) {

         bool are_rezervari = false;
         for(int j=0; j<static_cast<int>(rezervari.size()); ++j) {
             if(rezervari[j] != 0 && rezervari[j]->getClientRef().getCNP() == CNP) {
                 are_rezervari = true;
                 break;
             }
         }
         if (are_rezervari) {
             return false;
         }


         delete clienti[index_gasit];
         clienti.erase(clienti.begin() + index_gasit);
        return true;
    } else {
        return false;
    }
}

void Hotel::afisareClienti() const {
    std::cout << "\n--- Clientii Hotelului " << nume  << std::endl;
    if (clienti.empty()) { std::cout<<"Nu exista clienti"<<'\n'; }
    else {
        for (int i = 0; i < static_cast<int>(clienti.size()); ++i) {
            if (clienti[i] != 0) {
                std::cout << *(clienti[i]) << std::endl;
            }
        }
    }
    std::cout << "------------------------------------------" << std::endl;
}



Angajat* Hotel::gasesteAngajat(const std::string& CNP) {
    for (int i = 0; i < static_cast<int>(angajati.size()); ++i) {
        if (angajati[i] != 0 && angajati[i]->getCNP() == CNP) {
            return angajati[i];
        }
    }
    return 0;
}


const Angajat* Hotel::gasesteAngajat(const std::string& CNP) const {
     for (int i = 0; i < static_cast<int>(angajati.size()); ++i) {
        if (angajati[i] != 0 && angajati[i]->getCNP() == CNP) {
            return angajati[i];
        }
    }
    return 0;
}


void Hotel::adaugaAngajat(Angajat* pAngajat) {
    if (pAngajat == 0) { // Verificam pointerul primit
        std::cerr << "Eroare Adaugare Angajat: Se incearca adaugarea unui pointer nul!" << std::endl;
        return;
    }

    if (gasesteAngajat(pAngajat->getCNP()) != 0) {
        std::cerr << "Eroare Adaugare Angajat: Angajatul cu CNP " << pAngajat->getCNP() << " exista deja!" << std::endl;

        return;
    }
    angajati.push_back(pAngajat);
    std::cout << "Angajatul " << pAngajat->getPrenume() << " (pointer) adaugat." << std::endl;
}


bool Hotel::stergeAngajat(const std::string& CNP) {
    int index_gasit = -1;
     for (int i = 0; i < static_cast<int>(angajati.size()); ++i) {
        if (angajati[i] != 0 && angajati[i]->getCNP() == CNP) {
             index_gasit = i;
            break;
        }
    }

    if (index_gasit != -1) {



        // std::cout << "Stergere obiect Angajat CNP " << CNP << "..." << std::endl;
        delete angajati[index_gasit]; // !!! DELETE pe obiect !!!


        angajati.erase(angajati.begin() + index_gasit);
        return true;
    } else {
         std::cerr << "Eroare Stergere Angajat: Angajatul cu CNP " << CNP << " nu a fost gasit." << std::endl;
        return false;
    }
}


void Hotel::afisareAngajati() const {
    std::cout << "\n--- Angajatii Hotelului " << nume << std::endl;
    if (angajati.empty()) {
        std::cout << "Nu exista angajati inregistrati." << std::endl;
    } else {
        for (int i = 0; i < static_cast<int>(angajati.size()); ++i) {

            if (angajati[i] != 0) {
                std::cout << *(angajati[i]) << std::endl;
            } else {
                std::cout << "  -> Pointer nul la index " << i << std::endl;
            }
        }
    }
    std::cout << "------------------------------------------" << std::endl;
}





Rezervare* Hotel::gasesteRezervare(int idRezervare) {
    for (int i = 0; i < static_cast<int>(rezervari.size()); ++i) {
        if (rezervari[i] != 0 && rezervari[i]->getId() == idRezervare) {
            return rezervari[i];
        }
    }
    return 0;
}
const Rezervare* Hotel::gasesteRezervare(int idRezervare) const {
    for (int i = 0; i < static_cast<int>(rezervari.size()); ++i) {
        if (rezervari[i] != 0 && rezervari[i]->getId() == idRezervare) {
            return rezervari[i];
        }
    }
    return 0;
}


int Hotel::creeazaRezervare(const std::string& cnpClient, int numarCamera, const std::string& dataCheckIn,
                             const std::string& dataCheckOut, int numarZile) {
    Client* clientPtr = gasesteClient(cnpClient);
    if (clientPtr == 0) { return -1; }
    Camera* cameraPtr = gasesteCamera(numarCamera);
    if (cameraPtr == 0) { return -1; }
    if (cameraPtr->isOcupata()) {  return -1; }
    if (numarZile <= 0) {  return -1; }


    Rezervare* pNouaRezervare = 0;
    try {
         pNouaRezervare = new Rezervare(*clientPtr, *cameraPtr, dataCheckIn, dataCheckOut, numarZile);
    } catch (const std::bad_alloc&) {
        std::cerr << "Eroare critica: Nu s-a putut aloca memorie pentru rezervare!" << std::endl;
        return -1;
    }


    rezervari.push_back(pNouaRezervare);


    cameraPtr->setOcupata(true);


    clientPtr->setNumarRezervari(clientPtr->getNumarRezervari() + 1);

    std::cout << "Rezervare (pointer) creata cu succes! ID: " << pNouaRezervare->getId() << std::endl;
    return pNouaRezervare->getId();
}


bool Hotel::anuleazaRezervare(int idRezervare) {
    int index_gasit = -1;
    for (int i = 0; i < static_cast<int>(rezervari.size()); ++i) {
        if (rezervari[i] != 0 && rezervari[i]->getId() == idRezervare) {
            index_gasit = i;
            break;
        }
    }

    if (index_gasit != -1) {
        Rezervare* pRezervareDeSters = rezervari[index_gasit];


        int numarCameraRezervata = pRezervareDeSters->getCameraRef().getNumar();
        Camera* cameraPtr = gasesteCamera(numarCameraRezervata);
        if (cameraPtr != 0) {
            cameraPtr->setOcupata(false);
        } else {
             std::cerr << "Avertisment Anulare: Camera Nr " << numarCameraRezervata << " negasita!" << std::endl;
        }


        Client* clientPtr = gasesteClient(pRezervareDeSters->getClientRef().getCNP());
        if (clientPtr != 0) {
             int nrRez = clientPtr->getNumarRezervari();
             if (nrRez > 0) clientPtr->setNumarRezervari(nrRez - 1);
         }

        // Stergem obiectul Rezervare de pe heap
        delete pRezervareDeSters;


        rezervari.erase(rezervari.begin() + index_gasit);

        std::cout << "Rezervare ID " << idRezervare << " anulata (obiect sters)." << std::endl;
        return true;
    } else {
        std::cerr << "Eroare Anulare: Rezervarea cu ID " << idRezervare << " nu a fost gasita." << std::endl;
        return false;
    }
}


void Hotel::afisareRezervari() const {
     std::cout << "\n--- Rezervarile Hotelului " << nume << " (Pointeri) ---" << std::endl;
    if (rezervari.empty()) {
        std::cout<<"Nu exista rezervari"<<'\n';
    }
    else {
        for (int i = 0; i < static_cast<int>(rezervari.size()); ++i) {
             if (rezervari[i] != 0) {
                std::cout << *(rezervari[i]) << "\n--------------------" << std::endl; // Dereferentiere
             }
        }
    }
}

void Hotel::afisareRezervariClient(const std::string& CNP) const {
    std::cout << "\n--- Rezervarile Clientului cu CNP: " << CNP << " (Pointeri) ---" << std::endl;
    bool gasit = false;
    const Client* clientPtr = gasesteClient(CNP);
    if (clientPtr == 0) { /*...*/ return; }
    std::cout << "Client: " << clientPtr->getPrenume() << " " << clientPtr->getNume() << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    for (int i = 0; i < static_cast<int>(rezervari.size()); ++i) {
         if (rezervari[i] != 0 && rezervari[i]->getClientRef().getCNP() == CNP) {
             std::cout << *(rezervari[i]) << "\n--------------------" << std::endl; // Dereferentiere
             gasit = true;
         }
     }
     if (!gasit) {
         std::cout<<"Clientul cu CNP "<<CNP<<" nu are rezervari."<<'\n';
     }
}


void Hotel::afisareGenerala(std::ostream& os) const {

     os << "\n========== Detalii Hotel ==========" << std::endl;
    os << "Nume: " << nume << " (" << numarStele << " stele)" << std::endl;
    os << "Adresa: " << adresa << std::endl;
    os << "----------------------------------" << std::endl;
    os << "Numar total camere: " << static_cast<int>(camere.size()) << std::endl;
    os << "Numar clienti inregistrati: " << static_cast<int>(clienti.size()) << std::endl;
    os << "Numar angajati: " << static_cast<int>(angajati.size()) << std::endl;
    os << "Numar rezervari active: " << static_cast<int>(rezervari.size()) << std::endl;
    os << "=================================" << std::endl;
}

double Hotel::calculeazaVenitTotal() const {
    double venit = 0.0;
    for (int i = 0; i < static_cast<int>(rezervari.size()); ++i) {

        if (rezervari[i] != 0 && rezervari[i]->isPlatita()) {
            venit += rezervari[i]->getPretTotal();
        }
    }
    return venit;
}

// Implementare IAfisabil
void Hotel::afisare(std::ostream& os) const {

    os << "\n========== Detalii Hotel ==========" << std::endl;
    os << "Nume: " << nume << " (" << numarStele << " stele)" << std::endl;
    os << "Adresa: " << adresa << std::endl;
    os << "----------------------------------" << std::endl;
    os << "Numar total camere: " << static_cast<int>(camere.size()) << std::endl;
    os << "Numar clienti inregistrati: " << static_cast<int>(clienti.size()) << std::endl;
    os << "Numar angajati: " << static_cast<int>(angajati.size()) << std::endl;
    os << "Numar rezervari active: " << static_cast<int>(rezervari.size()) << std::endl;
    os << "=================================" << std::endl;
}


std::ostream& operator<<(std::ostream& os, const Hotel& hotel) {
    hotel.afisare(os);
    return os;
}

std::istream& operator>>(std::istream& is, Hotel& hotel) {
    std::cout << "Nume hotel: ";
    std::getline(is, hotel.nume);
    std::cout << "Adresa hotel: ";
    std::getline(is, hotel.adresa);
    std::cout << "Numar stele: ";
    is >> hotel.numarStele;
    return is;
}