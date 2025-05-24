#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "hotel.h"
#include "tip_camera.h"
#include "camera.h"
#include "client.h"
#include "angajat.h"
#include "manager.h"
#include "bucatar.h"
#include "persoana.h"
#include "rezervare.h"
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
}

int main() {
    std::cout << std::fixed << std::setprecision(2);

    //Initializeaza hotelul
    Hotel hotelPrincipal("Staicu's Hotel  ", "Strada Grozavesti", 5);
    std::cout << "Bun venit la sistemul de gestiune pentru " << hotelPrincipal.GetNume() << "!" << std::endl;

//Initializeaza tipuri de camere
    TipCamera tipSingle("Single", 1, false, false);
    TipCamera tipDouble("Double", 2, true, false);
    TipCamera tipApartament("Apartament", 4, true, true);

    //Adauga si initializeaza camerele
    hotelPrincipal.AdaugaCamera(new Camera(101, 250.00, false, tipSingle, 1));
    hotelPrincipal.AdaugaCamera(new Camera(201, 400.00, false, tipDouble, 2));
    hotelPrincipal.AdaugaCamera(new Camera(301, 750.00, false, tipApartament, 3));

    //Adauga si initializeaza clientii
    hotelPrincipal.AdaugaClient(new Client("Popescu", "Ion", "1900101123456", 34));
    hotelPrincipal.AdaugaClient(new Client("Ionescu", "Andreea", "2950302654321", 29));


    Persoana* cl=new Client("Mircea","Andrei","2219910000121",20);
    hotelPrincipal.AdaugaClient(static_cast<Client*> (cl));//Downcasting

    //Adauga si initializeaza angajatii
    Angajat* bucatar_sef=new Bucatar("Mihai","Raul","200019988271",45,7000,10,"Mancare Traditionala","Bucatar Sef");
    Angajat* ajutor_bucatar=new Bucatar("Visan","Delia","2987155411",25,5000,2,"Patiserie","Ajutor de bucatar");

    hotelPrincipal.AdaugaAngajat((bucatar_sef));
    hotelPrincipal.AdaugaAngajat((ajutor_bucatar));
    hotelPrincipal.AdaugaAngajat(new Manager("Staicu", "Octavian", "1801122000000", 50, 8500.00, 20,"Administratie"));

    int optiune = -1;
    do {
        afiseazaMeniu();

        std::cout << "Introduceti optiunea: ";
        std::cin >> optiune;


        switch (optiune) {
            case 1: {// Adauga Camera;
                Camera* pCamNoua = new Camera();

                std::cout << "\n--- Adaugare Camera Noua ---\n";

                std::cin >> (*pCamNoua);

                hotelPrincipal.AdaugaCamera(pCamNoua);
                break;
            }
            case 2: {// Adauga Client
                Client* pClientNou = new Client();

                std::cout << "\n--- Adaugare Client Nou ---\n";


                std::cin >> (*pClientNou);

                hotelPrincipal.AdaugaClient(pClientNou);
                break;
            }
            case 3: {// Adauga Angajat
                int OptiuneAngajat = 0;
                std::cout << "\n--- Adaugare Angajat Nou ---\n";
                std::cout << "Selectati tipul de angajat:\n";
                std::cout << "  1. Manager\n";
                std::cout << "  2. Bucatar\n";
                std::cout << "Optiune tip: ";
                std::cin >> OptiuneAngajat;


                Angajat* pAngajatNou = 0;
//Verificare pentru tipul de angajat
                switch (OptiuneAngajat) {
                    case 1: {
                        Manager* pMgr = new Manager();
                        std::cout << "--- Date Manager ---\n";
                        std::cin >> (*pMgr);
                        pAngajatNou = pMgr;
                        break;
                    }

                    case 2: {
                        Bucatar* pBuc = new Bucatar();
                        std::cout << "--- Date Bucatar ---\n";
                        std::cin >> (*pBuc);
                        pAngajatNou = pBuc;
                        break;
                    }
                    default:
                        std::cout << "Optiune tip angajat invalida.\n";
                    break;
                }

                if (pAngajatNou != 0) {
                    hotelPrincipal.AdaugaAngajat(pAngajatNou);
                    std::cout << "Angajat adaugat cu succes!" << std::endl;

                }
                break;
            }
            case 4: {//Creeaza Rezervare
                std::string cnp; int nrCam = 0, nrZile = 0;
                Data data_inceput,data_sfarsit;
                //Citire date
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
                    if(r != 0)// Daca s-a creat
                        std::cout << "\nRezervare creata:\n" << *r << std::endl;
                }
                break;
            }
            case 5: {// Anuleaza Rezervare
                int idRez = 0;

                std::cout << "\n--- Anulare Rezervare ---\nID Rezervare: ";
                std::cin >> idRez;
                hotelPrincipal.AnuleazaRezervare(idRez);


                break;
            }
            case 6: {// Marcheaza Rezervare ca Platita
                int idRez = 0;
                std::cout << "\n--- Marcare Platita ---\nID Rezervare: ";
                std::cin >> idRez;

                Rezervare* r = hotelPrincipal.GasesteRezervare(idRez);
                if (r != 0)//Daca a fost gasita rezervarea
                        {
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
            case 13: {// Afiseaza Rezervarile unui Client (dupa CNP)
                std::string cnp;
                std::cout << "\n--- Afisare Rezervari Client ---\nCNP: ";
                std::cin >> cnp;
                hotelPrincipal.AfisareRezervariClient(cnp);
                break;
            }
            case 14: {// Calculeaza si Afiseaza Venit Total
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