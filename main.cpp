#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <stdexcept>
#include <iomanip>
#include <cstddef>

#include "Hotel.h"
#include "TipCamera.h"
// Nu mai e nevoie sa includem IAfisabil.h direct aici, e inclus prin celelalte

// Functie pentru a curata bufferul de input
void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Functie pentru a afisa meniul principal
void afiseazaMeniu() {
    std::cout << "\n========== Meniu Gestiune Hotel (C++98 + Interfata) ==========\n";
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
    std::cout << "13. Afiseaza Detalii Generale Hotel (metoda specifica)\n";
    std::cout << "14. Calculeaza si Afiseaza Venit Total\n";
    std::cout << "15. Afiseaza Detalii Hotel (via operator<<)\n"; // Optiune noua demo
    std::cout << " 0. Iesire\n";
    std::cout << "============================================================\n";
    std::cout << "Alegeti o optiune: ";
}

int main() {


    Hotel hotelPrincipal("Grand Hotel Interfata C++98", "Strada Abstracta Nr. 1", 4);
    std::cout << "Bun venit la sistemul de gestiune pentru " << hotelPrincipal.getNume() << "!" << std::endl;

    // --- Optional: Adaugam date initiale ---

        TipCamera tipSingle("Single", 1, false, false);
        TipCamera tipDouble("Double", 2, true, false);
        TipCamera tipApartament("Apartament", 4, true, true);
        hotelPrincipal.adaugaCamera(Camera(101, 250.00, false, tipSingle, 1));
        hotelPrincipal.adaugaCamera(Camera(201, 400.00, false, tipDouble, 2));
        hotelPrincipal.adaugaCamera(Camera(301, 750.00, false, tipApartament, 3));
        hotelPrincipal.adaugaClient(Client("Popescu", "Ion", "1900101123456", 34));
        hotelPrincipal.adaugaClient(Client("Ionescu", "Maria", "2950302654321", 29));
        hotelPrincipal.adaugaAngajat(Angajat("Admin", "User", "1801122000000", 44, "Manager", 8500.00, 15));



    // --- Sfarsit date initiale ---

    int optiune;
    do {
        afiseazaMeniu();

        while (!(std::cin >> optiune)) {
            std::cout << "Input invalid. Introduceti un numar intre 0 si 15: ";
            std::cin.clear();
            clearInputBuffer();
        }
        clearInputBuffer();

        switch (optiune) {
            case 1: { /* Adauga Camera */
                Camera c;
                std::cout << "\n--- Adauga Camera ---\n";
                std::cin >> c; hotelPrincipal.adaugaCamera(c);
                break;
            }
            case 2: {
                /* Adauga Client */
                Client cl;
                std::cout << "\n--- Adauga Client ---\n";
                std::cin >> cl;
                hotelPrincipal.adaugaClient(cl);
                break;
            }
            case 3: { /* Adauga Angajat */
                Angajat an;
                std::cout << "\n--- Adauga Angajat ---\n";
                std::cin >> an;
                hotelPrincipal.adaugaAngajat(an);
                break;
            }
            case 4: { /* Creeaza Rezervare */
                std::string cnp, dataIn, dataOut;
                int nrCam, nrZile;
                std::cout << "\n--- Creare Rezervare ---\n";
                std::cout << "CNP client: ";
                std::cin >> cnp;
                std::cout << "Nr camera: ";
                std::cin >> nrCam;
                std::cout << "Data In (YYYY-MM-DD): ";
                std::cin >> dataIn;
                std::cout << "Data Out (YYYY-MM-DD): ";
                std::cin >> dataOut;
                std::cout << "Nr zile: ";
                std::cin >> nrZile;
                clearInputBuffer();
                int idRez = hotelPrincipal.creeazaRezervare(cnp, nrCam, dataIn, dataOut, nrZile);
                if (idRez != -1)
                    { const Rezervare* r = hotelPrincipal.gasesteRezervare(idRez);
                        std::cout << "\nRezervare creata:\n" << *r << std::endl;
                    }
                else {
                    std::cout << "Creare rezervare esuata.\n";
                }
                break;
            }
            case 5: {
                /* Anuleaza Rezervare */
                int idRez;
                std::cout << "\n--- Anulare Rezervare ---\nID Rezervare: ";
                std::cin >> idRez;
                clearInputBuffer();
                if (hotelPrincipal.anuleazaRezervare(idRez))
                    std::cout << "Rezervare ID " << idRez << " anulata.\n";
                else
                     std::cout << "Anulare esuata.\n";
                break;
            }
             case 6: { /* Marcheaza Platita */
                int idRez;
                std::cout << "\n--- Marcare Platita ---\nID Rezervare: ";
                std::cin >> idRez;
                clearInputBuffer();
                Rezervare* r = hotelPrincipal.gasesteRezervare(idRez);
                if (r != 0)
                    { r->setPlatita(true);
                    std::cout << "Rezervare ID " << idRez << " marcata ca platita.\n";
                    }
                else {
                    std::cout << "Rezervare ID " << idRez << " negasita.\n";
                }
                break;
            }
            case 7: hotelPrincipal.afisareCamere(); break;
            case 8: hotelPrincipal.afisareCamereLibere(); break;
            case 9: hotelPrincipal.afisareClienti(); break;
            case 10: hotelPrincipal.afisareAngajati(); break;
            case 11: hotelPrincipal.afisareRezervari(); break;
            case 12: { /* Afisare Rez Client */
                std::string cnp;
                std::cout << "\n--- Afisare Rezervari Client ---\nCNP: ";
                std::cin >> cnp;
                clearInputBuffer();
                hotelPrincipal.afisareRezervariClient(cnp); break;
            }
             case 13: hotelPrincipal.afisareGenerala(std::cout); break; // Apelam metoda specifica
             case 14: { /* Calcul Venit */
                 double venit = hotelPrincipal.calculeazaVenitTotal();
                 std::cout << "\n--- Venit Total Actual ---\n" << venit << " RON\n------------------------\n"; break;
             }
             case 15: std::cout << "\n--- Detalii Hotel (op<<) ---\n" << hotelPrincipal << "\n---------------------------\n"; break; // Folosim operatorul <<
            case 0: std::cout << "Iesire din program...\n"; break;
            default: std::cout << "Optiune invalida. Incercati din nou.\n"; break;
        }

    } while (optiune != 0);

    std::cout << "Programul s-a incheiat." << std::endl;
    return 0;
}