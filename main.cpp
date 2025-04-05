#include <iostream>
#include <string>
#include <vector>
#include <limits>   // Pentru std::numeric_limits
#include <stdexcept> // Pentru std::exception
#include <iomanip>  // Pentru std::fixed, std::setprecision (la afisare preturi)

// Includem header-ul principal al hotelului
#include "Hotel.h"
// Includem si TipCamera pentru a putea crea obiecte de acest tip direct in main
#include "TipCamera.h"
// Celelalte clase (Camera, Client, Angajat, Rezervare, Persoana) sunt incluse
// indirect prin Hotel.h sau prin headerele pe care Hotel.h le include.

// Functie pentru a curata bufferul de input (utila dupa citirea numerelor)
void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Functie pentru a afisa meniul principal
void afiseazaMeniu() {
    std::cout << "\n========== Meniu Gestiune Hotel ==========\n";
    std::cout << " 1. Adauga Camera\n";
    std::cout << " 2. Adauga Client\n";
    std::cout << " 3. Adauga Angajat\n";
    std::cout << " 4. Creeaza Rezervare\n";
    std::cout << " 5. Anuleaza Rezervare\n";
    std::cout << " 6. Marcheaza Rezervare ca Platita\n";
    std::cout << " 7. Afiseaza Toate Camerele\n";
    std::cout << " 8. Afiseaza Camerele Libere\n";
    std::cout << " 9. Afiseaza Clientii\n";
    std::cout << "10. Afiseaza Angajatii\n";
    std::cout << "11. Afiseaza Toate Rezervarile\n";
    std::cout << "12. Afiseaza Rezervarile unui Client (dupa CNP)\n";
    std::cout << "13. Afiseaza Detalii Generale Hotel\n";
    std::cout << "14. Calculeaza si Afiseaza Venit Total (din rezervari platite)\n";
    std::cout << " 0. Iesire\n";
    std::cout << "=========================================\n";
    std::cout << "Alegeti o optiune: ";
}

int main() {
    // Setam precizia pentru afisarea double-urilor (preturi)
    std::cout << std::fixed << std::setprecision(2);

    // Cream obiectul Hotel
    Hotel hotelPrincipal("Grand Hotel Staicu", "Bulevardul Grozavesti Nr. 1024", 5);
    std::cout << "Bun venit la sistemul de gestiune pentru " << hotelPrincipal.getNume() << "!" << std::endl;

    // --- Optional: Adaugam date initiale pentru testare ---

    // Tipuri de camera
    TipCamera tipSingle("Single", 1, false, false);
    TipCamera tipDouble("Double", 2, true, false);
    TipCamera tipApartament("Apartament", 4, true, true);

    // Camere
    hotelPrincipal.adaugaCamera(Camera(101, 250.00, false, tipSingle, 1));
    hotelPrincipal.adaugaCamera(Camera(102, 250.00, false, tipSingle, 1));
    hotelPrincipal.adaugaCamera(Camera(201, 400.00, false, tipDouble, 2));
    hotelPrincipal.adaugaCamera(Camera(202, 420.00, false, tipDouble, 2));
    hotelPrincipal.adaugaCamera(Camera(301, 750.00, false, tipApartament, 3));

    // Clienti
    hotelPrincipal.adaugaClient(Client("Popescu", "Ion", "1900101123456", 34));
    hotelPrincipal.adaugaClient(Client("Ionescu", "Maria", "2950302654321", 29));

    // Angajati
    hotelPrincipal.adaugaAngajat(Angajat("Admin", "User", "1801122000000", 44, "Manager", 8500.00, 15));
    hotelPrincipal.adaugaAngajat(Angajat("Georgescu", "Andreea", "2850510111222", 39, "Receptioner", 4200.00, 5));

    std::cout << "\nDate initiale incarcate cu succes.\n";


    int optiune;
    do {
        afiseazaMeniu();

        // Citim optiunea si validam inputul
        while (!(std::cin >> optiune)) {
            std::cout << "Input invalid. Introduceti un numar intre 0 si 14: ";

        }
         // Curata newline ramas dupa citirea numarului


            switch (optiune) {
                case 1: { // Adauga Camera
                    Camera camNoua; // Cream o camera goala
                    std::cout << "\n--- Adaugare Camera Noua ---\n";
                    // Folosim operatorul >> suprascris pentru Camera (care include si citirea TipCamera)
                    std::cin >> camNoua;
                    // clearInputBuffer(); // Operatorul>> ar trebui sa consume newline-ul, dar verificam
                    hotelPrincipal.adaugaCamera(camNoua);
                    break;
                }
                case 2: { // Adauga Client
                    Client clientNou;
                    std::cout << "\n--- Adaugare Client Nou ---\n";
                    // Folosim operatorul >> suprascris pentru Client
                    std::cin >> clientNou;
                    // clearInputBuffer();
                    hotelPrincipal.adaugaClient(clientNou);
                    break;
                }
                case 3: { // Adauga Angajat
                    Angajat angajatNou;
                     std::cout << "\n--- Adaugare Angajat Nou ---\n";
                    // Folosim operatorul >> suprascris pentru Angajat
                    std::cin >> angajatNou;
                    // clearInputBuffer();
                    hotelPrincipal.adaugaAngajat(angajatNou);
                    break;
                }
                case 4: { // Creeaza Rezervare
                    std::string cnp, dataIn, dataOut;
                    int nrCam, nrZile;
                     std::cout << "\n--- Creare Rezervare Noua ---\n";
                    std::cout << "Introduceti CNP client: ";
                    std::cin >> cnp;
                    std::cout << "Introduceti numarul camerei dorite: ";
                    std::cin >> nrCam;
                    std::cout << "Introduceti data check-in (YYYY-MM-DD): ";
                    std::cin >> dataIn;
                    std::cout << "Introduceti data check-out (YYYY-MM-DD): ";
                    std::cin >> dataOut;
                    std::cout << "Introduceti numarul de zile: ";
                    std::cin >> nrZile;
                    clearInputBuffer();

                    int idRez = hotelPrincipal.creeazaRezervare(cnp, nrCam, dataIn, dataOut, nrZile);
                    if (idRez != -1) {
                        // Afisam rezervarea creata pentru confirmare
                        const Rezervare* rezPtr = hotelPrincipal.gasesteRezervare(idRez);
                        if (rezPtr) {
                             std::cout << "\nRezervare creata:\n" << *rezPtr << std::endl;
                        }
                    } else {
                         std::cout << "Crearea rezervarii a esuat." << std::endl;
                    }
                    break;
                }
                case 5: { // Anuleaza Rezervare
                    int idRez;
                     std::cout << "\n--- Anulare Rezervare ---\n";
                    std::cout << "Introduceti ID-ul rezervarii de anulat: ";
                    std::cin >> idRez;
                    clearInputBuffer();
                    if (hotelPrincipal.anuleazaRezervare(idRez)) {
                        std::cout << "Rezervarea ID " << idRez << " a fost anulata." << std::endl;
                    } else {
                         std::cout << "Anularea rezervarii ID " << idRez << " a esuat (ID invalid?)." << std::endl;
                    }
                    break;
                }
                 case 6: { // Marcheaza Rezervare ca Platita
                    int idRez;
                    std::cout << "\n--- Marcare Rezervare Platita ---\n";
                    std::cout << "Introduceti ID-ul rezervarii de marcat ca platita: ";
                    std::cin >> idRez;
                    clearInputBuffer();
                    Rezervare* rezPtr = hotelPrincipal.gasesteRezervare(idRez);
                    if (rezPtr) {
                        rezPtr->setPlatita(true);
                        std::cout << "Rezervarea ID " << idRez << " a fost marcata ca platita." << std::endl;
                    } else {
                        std::cout << "Rezervarea ID " << idRez << " nu a fost gasita." << std::endl;
                    }
                    break;
                }
                case 7: // Afiseaza Toate Camerele
                    hotelPrincipal.afisareCamere();
                    break;
                case 8: // Afiseaza Camerele Disponibile
                    hotelPrincipal.afisareCamereLibere();
                    break;
                case 9: // Afiseaza Clientii
                    hotelPrincipal.afisareClienti();
                    break;
                case 10: // Afiseaza Angajatii
                    hotelPrincipal.afisareAngajati();
                    break;
                case 11: // Afiseaza Toate Rezervarile
                    hotelPrincipal.afisareRezervari();
                    break;
                case 12: { // Afiseaza Rezervarile unui Client
                    std::string cnp;
                    std::cout << "\n--- Afisare Rezervari Client ---\n";
                    std::cout << "Introduceti CNP-ul clientului: ";
                    std::cin >> cnp;
                    clearInputBuffer();
                    hotelPrincipal.afisareRezervariClient(cnp);
                    break;
                }
                 case 13: // Afiseaza Detalii Generale Hotel
                    hotelPrincipal.afisareGenerala();
                    // Sau folosind operatorul<<:
                    // std::cout << "\n--- Detalii Hotel (via operator<<) ---\n";
                    // std::cout << hotelPrincipal << std::endl;
                    // std::cout << "--------------------------------------\n";
                    break;
                 case 14: { // Calculeaza si Afiseaza Venit Total
                     double venit = hotelPrincipal.calculeazaVenitTotal();
                     std::cout << "\n--- Venit Total (din rezervari platite) ---\n";
                     std::cout << "Venit total curent: " << venit << " RON" << std::endl;
                     std::cout << "-------------------------------------------\n";
                     break;
                 }
                case 0: // Iesire
                    std::cout << "Iesire din program...\n";
                    break;
                default:
                    std::cout << "Optiune invalida. Incercati din nou.\n";
                    break;
            }


        // Pauza inainte de a afisa meniul din nou (cu exceptia iesirii)
        if (optiune != 0) {
            std::cout << "\nApasati Enter pentru a continua...";
            // std::cin.get(); // Poate necesita 2 apeluri
            // O alternativa mai robusta:
             std::string dummy;
             // Folosim direct clearInputBuffer daca e apelat imediat dupa o citire numerica
             // Daca a fost o citire de string, s-ar putea sa fie deja gol bufferul
             // std::getline(std::cin, dummy); // Cel mai sigur mod de a astepta Enter
             clearInputBuffer(); // Incearca sa consume orice, inclusiv doar Enter
        }

    } while (optiune != 0);

    std::cout << "Programul s-a incheiat." << std::endl;

    // Destructorul obiectului 'hotelPrincipal' va fi apelat automat aici,
    // eliberand memoria (daca s-ar fi folosit alocare dinamica in Hotel)
    // si distrugand obiectele continute in vectori.

    return 0;
}