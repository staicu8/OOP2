#include "Hotel.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Pentru std::find_if, std::remove_if
#include <iterator>  // Pentru std::distance
#include <stdexcept> // Pentru std::runtime_error
#include <limits>
// --- Implementare Functii Helper Private (exemple) ---

std::vector<Camera>::iterator Hotel::findCameraIterator(int numarCamera) {
    return std::find_if(camere.begin(), camere.end(),
                        [numarCamera](const Camera& cam) {
                            return cam.getNumar() == numarCamera;
                        });
}

std::vector<Client>::iterator Hotel::findClientIterator(const std::string& CNP) {
     return std::find_if(clienti.begin(), clienti.end(),
                        [&CNP](const Client& cl) { // Capturam CNP prin referinta
                            return cl.getCNP() == CNP;
                        });
}

std::vector<Angajat>::iterator Hotel::findAngajatIterator(const std::string& CNP) {
     return std::find_if(angajati.begin(), angajati.end(),
                        [&CNP](const Angajat& ang) {
                            return ang.getCNP() == CNP;
                        });
}

std::vector<Rezervare>::iterator Hotel::findRezervareIterator(int idRezervare) {
     return std::find_if(rezervari.begin(), rezervari.end(),
                        [idRezervare](const Rezervare& rez) {
                            return rez.getId() == idRezervare;
                        });
}


// --- Constructori / Destructor ---

Hotel::Hotel() : numarStele(0) {
    std::cout << "Constructor Hotel (default)" << std::endl;
}

Hotel::Hotel(const std::string& nume, const std::string& adresa, int numarStele)
    : nume(nume), adresa(adresa), numarStele(numarStele) {
     std::cout << "Constructor Hotel (parametrizat): " << nume << std::endl;
}

// Constructor de copiere (implementare simpla, face copii ale vectorilor)
Hotel::Hotel(const Hotel& other)
    : nume(other.nume), adresa(other.adresa), numarStele(other.numarStele),
      camere(other.camere), clienti(other.clienti), angajati(other.angajati),
      rezervari(other.rezervari) {
     std::cout << "Constructor Hotel (copiere): " << nume << std::endl;
}

// Operator= (implementare simpla)
Hotel& Hotel::operator=(const Hotel& other) {
    if (this != &other) {
        nume = other.nume;
        adresa = other.adresa;
        numarStele = other.numarStele;
        camere = other.camere; // Copiaza vectorii
        clienti = other.clienti;
        angajati = other.angajati;
        rezervari = other.rezervari;
         std::cout << "Operator= Hotel: " << nume << std::endl;
    }
    return *this;
}


Hotel::~Hotel() {
    // Nu e nevoie sa stergem elementele din vectori explicit aici,
    // deoarece vectorii contin obiecte (nu pointeri), iar destructorii
    // obiectelor (Camera, Client, etc.) vor fi apelati automat cand
    // vectorii sunt distrusi.
     std::cout << "Destructor Hotel: " << nume << std::endl;
}

// --- Getteri / Setteri ---

std::string Hotel::getNume() const { return nume; }
void Hotel::setNume(const std::string& nume) { this->nume = nume; }
std::string Hotel::getAdresa() const { return adresa; }
void Hotel::setAdresa(const std::string& adresa) { this->adresa = adresa; }
int Hotel::getNumarStele() const { return numarStele; }
void Hotel::setNumarStele(int stele) { this->numarStele = stele; } // Validare?

// --- Management Camere ---

void Hotel::adaugaCamera(const Camera& camera) {
    // Verificam daca exista deja o camera cu acelasi numar
    if (gasesteCamera(camera.getNumar()) != nullptr) {
        std::cerr << "Eroare: Camera cu numarul " << camera.getNumar() << " exista deja!" << std::endl;
        // Aruncam o exceptie sau pur si simplu nu adaugam
        // throw std::runtime_error("Camera cu acest numar exista deja.");
        return;
    }
    camere.push_back(camera); // Adaugam o copie a camerei in vector
    std::cout << "Camera Nr " << camera.getNumar() << " adaugata." << std::endl;
}

bool Hotel::stergeCamera(int numarCamera) {
    auto it = findCameraIterator(numarCamera);
    if (it != camere.end()) {
        // TODO: Verificare suplimentara - camera nu trebuie sa fie intr-o rezervare activa!
        // Daca este intr-o rezervare, stergerea ar trebui interzisa sau rezervarea anulata.
        // Aceasta logica lipseste aici.
        std::cout << "Stergere camera Nr " << numarCamera << "..." << std::endl;
        camere.erase(it);
        return true;
    } else {
        std::cerr << "Eroare: Camera Nr " << numarCamera << " nu a fost gasita pentru stergere." << std::endl;
        return false;
    }
}

// Returneaza pointer la camera din vector (sau nullptr daca nu e gasita)
Camera* Hotel::gasesteCamera(int numarCamera) {
    auto it = findCameraIterator(numarCamera);
    if (it != camere.end()) {
        // Returnam adresa elementului gasit in vector
        return &(*it);
    }
    return nullptr;
}
// Varianta const
const Camera* Hotel::gasesteCamera(int numarCamera) const {
     // Reimplementam logica de cautare aici sau folosim const_iterator
     auto it = std::find_if(camere.begin(), camere.end(),
                        [numarCamera](const Camera& cam) {
                            return cam.getNumar() == numarCamera;
                        });
     if (it != camere.end()) {
        return &(*it);
    }
    return nullptr;
}


void Hotel::afisareCamere() const {
    std::cout << "\n--- Camerele Hotelului " << nume << " ---\n";
    if (camere.empty()) {
        std::cout << "Nu exista camere inregistrate.\n";
        return;
    }
    for (const auto& cam : camere) {
        std::cout << cam << std::endl; // Folosim operatorul<< din Camera
    }
    std::cout << "----------------------------------\n";
}

void Hotel::afisareCamereLibere() const {
    std::cout << "\n--- Camere Libere ---\n";
    bool gasit = false;
    for (const auto& cam : camere) {
        if (!cam.isOcupata()) {
            std::cout << cam << std::endl;
            gasit = true;
        }
    }
    if (!gasit) {
        std::cout << "Nu exista camere libere momentan.\n";
    }
    std::cout << "---------------------\n";
}

void Hotel::afisareCamereOcupate() const {
    std::cout << "\n--- Camere Ocupate ---\n";
     bool gasit = false;
    for (const auto& cam : camere) {
        if (cam.isOcupata()) {
            std::cout << cam << std::endl;
            gasit = true;
        }
    }
     if (!gasit) {
        std::cout << "Nu exista camere ocupate momentan.\n";
    }
    std::cout << "---------------------\n";
}

// --- Management Clienti ---

void Hotel::adaugaClient(const Client& client) {
    // Verificam daca exista deja un client cu acelasi CNP
     if (gasesteClient(client.getCNP()) != nullptr) {
        std::cerr << "Eroare: Clientul cu CNP " << client.getCNP() << " exista deja!" << std::endl;
        return;
    }
    clienti.push_back(client);
    std::cout << "Clientul " << client.getPrenume() << " " << client.getNume() << " adaugat." << std::endl;
}

bool Hotel::stergeClient(const std::string& CNP) {
    auto it = findClientIterator(CNP);
    if (it != clienti.end()) {
         // TODO: Verificare suplimentara - clientul nu trebuie sa aiba rezervari active!
        std::cout << "Stergere client CNP " << CNP << "..." << std::endl;
        clienti.erase(it);
        return true;
    } else {
         std::cerr << "Eroare: Clientul cu CNP " << CNP << " nu a fost gasit pentru stergere." << std::endl;
        return false;
    }
}

Client* Hotel::gasesteClient(const std::string& CNP) {
    auto it = findClientIterator(CNP);
    return (it != clienti.end()) ? &(*it) : nullptr;
}
const Client* Hotel::gasesteClient(const std::string& CNP) const {
     auto it = std::find_if(clienti.begin(), clienti.end(),
                        [&CNP](const Client& cl) {
                            return cl.getCNP() == CNP;
                        });
    return (it != clienti.end()) ? &(*it) : nullptr;
}


void Hotel::afisareClienti() const {
     std::cout << "\n--- Clientii Hotelului " << nume << " ---\n";
    if (clienti.empty()) {
        std::cout << "Nu exista clienti inregistrati.\n";
        return;
    }
    for (const auto& cl : clienti) {
        std::cout << cl << std::endl; // Folosim op<< din Client
    }
    std::cout << "---------------------------------\n";
}

// --- Management Angajati --- (similar cu Clienti)

void Hotel::adaugaAngajat(const Angajat& angajat) {
    if (gasesteAngajat(angajat.getCNP()) != nullptr) {
        std::cerr << "Eroare: Angajatul cu CNP " << angajat.getCNP() << " exista deja!" << std::endl;
        return;
    }
    angajati.push_back(angajat);
    std::cout << "Angajatul " << angajat.getPrenume() << " " << angajat.getNume() << " adaugat." << std::endl;
}

bool Hotel::stergeAngajat(const std::string& CNP) {
     auto it = findAngajatIterator(CNP);
    if (it != angajati.end()) {
        std::cout << "Stergere angajat CNP " << CNP << "..." << std::endl;
        angajati.erase(it);
        return true;
    } else {
         std::cerr << "Eroare: Angajatul cu CNP " << CNP << " nu a fost gasit pentru stergere." << std::endl;
        return false;
    }
}

Angajat* Hotel::gasesteAngajat(const std::string& CNP) {
     auto it = findAngajatIterator(CNP);
    return (it != angajati.end()) ? &(*it) : nullptr;
}
const Angajat* Hotel::gasesteAngajat(const std::string& CNP) const {
     auto it = std::find_if(angajati.begin(), angajati.end(),
                        [&CNP](const Angajat& ang) {
                            return ang.getCNP() == CNP;
                        });
    return (it != angajati.end()) ? &(*it) : nullptr;
}

void Hotel::afisareAngajati() const {
    std::cout << "\n--- Angajatii Hotelului " << nume << " ---\n";
    if (angajati.empty()) {
        std::cout << "Nu exista angajati inregistrati.\n";
        return;
    }
    for (const auto& ang : angajati) {
        std::cout << ang << std::endl; // Folosim op<< din Angajat
    }
    std::cout << "-----------------------------------\n";
}


// --- Management Rezervari ---

int Hotel::creeazaRezervare(const std::string& cnpClient, int numarCamera, const std::string& dataCheckIn,
                             const std::string& dataCheckOut, int numarZile) {
    // 1. Gaseste clientul
    Client* clientPtr = gasesteClient(cnpClient);
    if (!clientPtr) {
        std::cerr << "Eroare Rezervare: Clientul cu CNP " << cnpClient << " nu exista." << std::endl;
        return -1;
    }

    // 2. Gaseste camera
    Camera* cameraPtr = gasesteCamera(numarCamera);
    if (!cameraPtr) {
        std::cerr << "Eroare Rezervare: Camera cu numarul " << numarCamera << " nu exista." << std::endl;
        return -1;
    }

    // 3. Verifica disponibilitatea camerei
    if (cameraPtr->isOcupata()) {
        std::cerr << "Eroare Rezervare: Camera " << numarCamera << " este deja ocupata." << std::endl;
        return -1;
    }

     // 4. Verifica numarul de zile
    if (numarZile <= 0) {
         std::cerr << "Eroare Rezervare: Numarul de zile trebuie sa fie pozitiv." << std::endl;
         return -1;
    }

    // 5. Creeaza rezervarea (folosind obiectele gasite, nu pointeri!)
    //    Constructorul Rezervare va face copii ale clientului si camerei.
    try {
        Rezervare nouaRezervare(*clientPtr, *cameraPtr, dataCheckIn, dataCheckOut, numarZile);
        // Important: Marcam camera *din hotel* ca fiind ocupata
        cameraPtr->setOcupata(true);
        // Adaugam rezervarea in vector
        rezervari.push_back(nouaRezervare);
        std::cout << "Rezervare creata cu succes! ID: " << nouaRezervare.getId() << std::endl;
        // Actualizam numarul de rezervari al clientului
        clientPtr->setNumarRezervari(clientPtr->getNumarRezervari() + 1);
        // TODO: Logica pentru client fidel?
        // if (clientPtr->getNumarRezervari() >= 5) clientPtr->setClientFidel(true);

        return nouaRezervare.getId(); // Returnam ID-ul rezervarii create
    } catch (const std::exception& e) {
        // Prinde eventuale exceptii din constructorul Rezervare (desi putin probabil aici)
        std::cerr << "Eroare la crearea obiectului Rezervare: " << e.what() << std::endl;
        return -1;
    }
}

bool Hotel::anuleazaRezervare(int idRezervare) {
    auto it = findRezervareIterator(idRezervare);
    if (it != rezervari.end()) {
        // Gasim camera asociata cu rezervarea *in hotel* pentru a o elibera
        int numarCameraRezervata = it->getCameraRef().getNumar();
        Camera* cameraPtr = gasesteCamera(numarCameraRezervata);

        if (cameraPtr) {
            cameraPtr->setOcupata(false); // Eliberam camera din hotel
             std::cout << "Camera Nr " << numarCameraRezervata << " a fost eliberata." << std::endl;
        } else {
            std::cerr << "Avertisment: Camera asociata rezervarii ID " << idRezervare
                      << " (Nr " << numarCameraRezervata << ") nu a fost gasita in hotel!" << std::endl;
        }

         // Optional: Decrementam numarul de rezervari al clientului
         Client* clientPtr = gasesteClient(it->getClientRef().getCNP());
         if (clientPtr) {
             int nrRez = clientPtr->getNumarRezervari();
             if (nrRez > 0) {
                 clientPtr->setNumarRezervari(nrRez - 1);
             }
         }


        std::cout << "Anulare rezervare ID " << idRezervare << "..." << std::endl;
        rezervari.erase(it); // Stergem rezervarea din vector
        return true;
    } else {
        std::cerr << "Eroare: Rezervarea cu ID " << idRezervare << " nu a fost gasita." << std::endl;
        return false;
    }
}

Rezervare* Hotel::gasesteRezervare(int idRezervare) {
    auto it = findRezervareIterator(idRezervare);
    return (it != rezervari.end()) ? &(*it) : nullptr;
}
const Rezervare* Hotel::gasesteRezervare(int idRezervare) const {
     auto it = std::find_if(rezervari.begin(), rezervari.end(),
                        [idRezervare](const Rezervare& rez) {
                            return rez.getId() == idRezervare;
                        });
    return (it != rezervari.end()) ? &(*it) : nullptr;
}


void Hotel::afisareRezervari() const {
     std::cout << "\n--- Rezervarile Hotelului " << nume << " ---\n";
    if (rezervari.empty()) {
        std::cout << "Nu exista rezervari inregistrate.\n";
        return;
    }
    for (const auto& rez : rezervari) {
        std::cout << rez << "\n--------------------\n"; // Folosim op<< din Rezervare
    }
}

void Hotel::afisareRezervariClient(const std::string& CNP) const {
     std::cout << "\n--- Rezervarile Clientului cu CNP: " << CNP << " ---\n";
     bool gasit = false;
     // Verificam intai daca clientul exista
     const Client* clientPtr = gasesteClient(CNP);
     if (!clientPtr) {
         std::cout << "Clientul cu CNP " << CNP << " nu a fost gasit." << std::endl;
         return;
     }

     std::cout << "Client: " << clientPtr->getPrenume() << " " << clientPtr->getNume() << std::endl;

     for (const auto& rez : rezervari) {
         // Comparam CNP-ul clientului din rezervare cu cel cautat
         if (rez.getClientRef().getCNP() == CNP) {
             std::cout << rez << "\n--------------------\n";
             gasit = true;
         }
     }
      if (!gasit) {
         std::cout << "Clientul nu are rezervari inregistrate.\n";
     }
}

// --- Alte Metode ---

void Hotel::afisareGenerala() const {
    std::cout << "\n========== Detalii Hotel ==========\n";
    std::cout << "Nume: " << nume << " (" << numarStele << " stele)\n";
    std::cout << "Adresa: " << adresa << "\n";
    std::cout << "----------------------------------\n";
    std::cout << "Numar total camere: " << camere.size() << "\n";
    std::cout << "Numar clienti inregistrati: " << clienti.size() << "\n";
    std::cout << "Numar angajati: " << angajati.size() << "\n";
    std::cout << "Numar rezervari active: " << rezervari.size() << "\n";
    std::cout << "=================================\n";
}

double Hotel::calculeazaVenitTotal() const {
    double venit = 0.0;
    for (const auto& rez : rezervari) {
        if (rez.isPlatita()) {
            venit += rez.getPretTotal();
        }
    }
    return venit;
}


// --- Operatori Friend ---

std::ostream& operator<<(std::ostream& os, const Hotel& hotel) {
    os << "Hotel: " << hotel.nume << " (" << hotel.numarStele << " stele), Adresa: " << hotel.adresa << "\n";
    os << "   Camere: " << hotel.camere.size()
       << ", Clienti: " << hotel.clienti.size()
       << ", Angajati: " << hotel.angajati.size()
       << ", Rezervari: " << hotel.rezervari.size();
    return os;
}

std::istream& operator>>(std::istream& is, Hotel& hotel) {
    std::cout << "Nume hotel: "; is >> hotel.nume;
    std::cout << "Adresa hotel: ";
    // Citeste restul liniei pentru adresa, poate contine spatii
    // Ignora newline ramas de la citirea anterioara
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(is, hotel.adresa);
    std::cout << "Numar stele: "; is >> hotel.numarStele;
    // Nu citim vectorii aici, acestia se populeaza prin metodele add...
    return is;
}