#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "Hotel.h"
#include "TipCamera.h"
#include "Camera.h"
#include "Client.h"
#include "Angajat.h"
#include "Persoana.h"
#include "Rezervare.h"
#include "data.h"
void afiseazaMeniu() {
    std::cout << "\n========== Meniu Gestiune Hotel  ==========\n";
    std::cout << " 1. Adauga Camera\n";
    std::cout << " 2. Adauga Client\n";
    std::cout << " 3. Adauga Angajat\n";
    std::cout << " 4. Creeaza Rezervare\n";
    std::cout << " 5. Anuleaza Rezervare\n";
    std::cout << " 6. Marcheaza Rezervare ca Platita\n";
    std::cout << " 7. Afiseaza Toate Camerele\n";
    std::cout << " 8. Afiseaza Camerele Libere\n";
    std::cout << " 9. Afiseaza Camerele Ocupate\n";
    std::cout << "10. Afiseaza Clientii\n";
    std::cout << "11. Afiseaza Angajatii\n";
    std::cout << "12. Afiseaza Toate Rezervarile\n";
    std::cout << "13. Afiseaza Rezervarile unui Client (dupa CNP)\n";
    std::cout << "14. Calculeaza si Afiseaza Venit Total\n";
    std::cout << "15. Afiseaza Detalii Hotel \n";
    std::cout << " 0. Iesire\n";
    std::cout << "======================================================\n";
    std::cout << "Alegeti o optiune: ";
}

int main() {
    std::cout << std::fixed << std::setprecision(2);

    Hotel hotelPrincipal("Staicu's Hotel  ", "Strada Grozavesti", 5);
    std::cout << "Bun venit la sistemul de gestiune pentru " << hotelPrincipal.GetNume() << "!" << std::endl;


    TipCamera tipSingle("Single", 1, false, false);
    TipCamera tipDouble("Double", 2, true, false);
    TipCamera tipApartament("Apartament", 4, true, true);

    hotelPrincipal.AdaugaCamera(new Camera(101, 250.00, false, tipSingle, 1));
    hotelPrincipal.AdaugaCamera(new Camera(201, 400.00, false, tipDouble, 2));
    hotelPrincipal.AdaugaCamera(new Camera(301, 750.00, false, tipApartament, 3));

    hotelPrincipal.AdaugaClient(new Client("Popescu", "Ion", "1900101123456", 34));
    hotelPrincipal.AdaugaClient(new Client("Ionescu", "Andreea", "2950302654321", 29));

    Persoana* cl=new Client("Mircea","Andrei","2219910000121",20);
    hotelPrincipal.AdaugaClient(static_cast<Client*> (cl));

    Persoana* ang=new Angajat("Mihai","Raul","200019988271",45,"Barman",7000,10);
    hotelPrincipal.AdaugaAngajat(static_cast<Angajat*> (ang));
    hotelPrincipal.AdaugaAngajat(new Angajat("Staicu", "Octavian", "1801122000000", 50, "Manager", 8500.00, 20));

    int optiune = -1;
    do {
        afiseazaMeniu();

        std::cout << "Introduceti optiunea (doar cifre!): ";
        std::cin >> optiune;


        switch (optiune) {
            case 1: {
                Camera* pCamNoua = new Camera();

                std::cout << "\n--- Adaugare Camera Noua ---\n";

                std::cin >> (*pCamNoua);

                hotelPrincipal.AdaugaCamera(pCamNoua);
                break;
            }
            case 2: {
                Client* pClientNou = new Client();

                std::cout << "\n--- Adaugare Client Nou ---\n";

                std::cin >> (*pClientNou);

                hotelPrincipal.AdaugaClient(pClientNou);
                break;
            }
            case 3: {
                Angajat* pAngajatNou = new Angajat();

                std::cout << "\n--- Adaugare Angajat Nou ---\n";

                std::cin >> (*pAngajatNou);

                hotelPrincipal.AdaugaAngajat(pAngajatNou);
                break;
            }
            case 4: {
                std::string cnp, dataIn, dataOut; int nrCam = 0, nrZile = 0;
                Data data_inceput,data_sfarsit;
                std::cout << "\n--- Creare Rezervare ---\n";
                std::cout << "CNP client: ";
                std::cin >> cnp;
                std::cout << "Nr camera: ";
                std::cin >> nrCam;
                std::cout << "Data In (YYYY-MM-DD): ";

                std::cin >> data_inceput;
                std::cout << "Data Out (YYYY-MM-DD): ";
                std::cin >> data_sfarsit;

                std::cout << "Nr zile: ";
                std::cin >> nrZile;


                int idRez = hotelPrincipal.CreeazaRezervare(cnp, nrCam, data_inceput, data_sfarsit, nrZile);
                if (idRez == -1) {
                    std::cout << "Crearea rezervarii a esuat." << std::endl;
                } else {
                    const Rezervare* r = hotelPrincipal.GasesteRezervare(idRez);
                    if(r != 0) std::cout << "\nRezervare creata:\n" << *r << std::endl;
                }
                break;
            }
            case 5: {
                int idRez = 0;
                std::cout << "\n--- Anulare Rezervare ---\nID Rezervare: ";
                std::cin >> idRez;

                if (!hotelPrincipal.AnuleazaRezervare(idRez)) {


                } else {
                    std::cout << "Rezervare ID " << idRez << " anulata.\n";
                }
                break;
            }
            case 6: {
                int idRez = 0;
                std::cout << "\n--- Marcare Platita ---\nID Rezervare: ";
                std::cin >> idRez;

                Rezervare* r = hotelPrincipal.GasesteRezervare(idRez);
                if (r != 0) {
                    r->SetPlatita(true);
                    std::cout << "Rezervare ID " << idRez << " marcata ca platita.\n";
                } else {
                    std::cout << "Rezervare ID " << idRez << " negasita.\n";
                }
                break;
            }

            case 7: hotelPrincipal.AfisareCamere(); break;
            case 8: hotelPrincipal.AfisareCamereLibere(); break;
            case 9: hotelPrincipal.AfisareCamereOcupate(); break;
            case 10: hotelPrincipal.AfisareClienti(); break;
            case 11: hotelPrincipal.AfisareAngajati(); break;
            case 12: hotelPrincipal.AfisareRezervari(); break;
            case 13: {
                std::string cnp;
                std::cout << "\n--- Afisare Rezervari Client ---\nCNP: ";
                std::cin >> cnp;
                hotelPrincipal.AfisareRezervariClient(cnp);
                break;
            }
            case 14: {
                double venit = hotelPrincipal.CalculeazaVenitTotal();
                std::cout << "\n--- Venit Total Actual ---\n" << venit << " RON\n------------------------\n";
                break;
            }
            case 15: std::cout << "\n--- Detalii Hotel ---\n" << hotelPrincipal << "\n---------------------------\n"; break;
            case 0:
                std::cout << "Iesire din program...\n";
            break;
            default:
                std::cout << "Optiune invalida.\n";
            break;
        }

    }
    while (optiune != 0);


    std::cout << "Programul s-a incheiat." << std::endl;
    return 0;
}