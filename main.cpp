#include <iostream>
#include <string>
#include <iomanip>
#include "hotel.h"
#include "tip_camera.h"
#include "camera.h"
#include "client.h"
#include "angajat.h"
#include "manager.h"
#include "camerista.h"
#include "bucatar.h"
#include "persoana.h"
#include "rezervare.h"
#include "data.h"


void AfiseazaMeniu() {
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
    Hotel hotel_principal("Staicu's Hotel  ", "Strada Grozavesti", 5);
    std::cout << "Bun venit la sistemul de gestiune pentru " << hotel_principal.GetNume()<<'\n';

//Initializeaza tipuri de camere
    TipCamera tip_single("Single", 1, false, false);

    TipCamera tip_double("Double", 2, true, false);
    TipCamera tip_apartament("Apartament", 4, true, true);

    //Adauga si initializeaza camerele
    hotel_principal.AdaugaCamera(new Camera(101, 250.00, false, tip_single, 1));
    hotel_principal.AdaugaCamera(new Camera(201, 400.00, false, tip_double, 2));
    hotel_principal.AdaugaCamera(new Camera(301, 750.00, false, tip_apartament, 3));

    //Adauga si initializeaza clientii
    hotel_principal.AdaugaClient(new Client("Popescu", "Ion", "1900101123456", 34));
    hotel_principal.AdaugaClient(new Client("Ionescu", "Andreea", "2950302654321", 29));


    Persoana* cl=new Client("Mircea","Andrei","2219910000121",20);
    hotel_principal.AdaugaClient(static_cast<Client*> (cl));//Downcasting

    //Adauga si initializeaza angajatii
    Angajat* bucatar_sef=new Bucatar("Mihai","Raul","200019988271",45,7000,10,"Mancare Traditionala","Bucatar Sef");
    Angajat* ajutor_bucatar=new Bucatar("Visan","Delia","2987155411",25,5000,2,"Patiserie","Ajutor de bucatar");

    hotel_principal.AdaugaAngajat((bucatar_sef));
    hotel_principal.AdaugaAngajat((ajutor_bucatar));
    hotel_principal.AdaugaAngajat(new Manager("Staicu", "Octavian", "1801122000000", 50, 8500.00, 20,"Administratie"));

    int optiune = -1;
    do {
        AfiseazaMeniu();

        std::cout << "Introduceti optiunea: ";
        std::cin >> optiune;


        switch (optiune) {
            case 1: {// Adauga Camera;
                Camera* p_cam_noua = new Camera();

                std::cout << "\n--- Adaugare Camera Noua ---\n";

                std::cin >> (*p_cam_noua);

                hotel_principal.AdaugaCamera(p_cam_noua);
                break;
            }
            case 2: {// Adauga Client
                Client* p_client_nou = new Client();

                std::cout << "\n--- Adaugare Client Nou ---\n";


                std::cin >> (*p_client_nou);

                hotel_principal.AdaugaClient(p_client_nou);
                break;
            }
            case 3: {// Adauga Angajat
                int optiune_angajat = 0;
                std::cout << "\n--- Adaugare Angajat Nou ---\n";
                std::cout << "Selectati tipul de angajat:\n";
                std::cout << "  1. Manager\n";
                std::cout << "  2. Bucatar\n";
                std::cout << "  3. Camerista\n";
                std::cout << "Optiune tip: ";
                std::cin >> optiune_angajat;


                Angajat* p_angajat_nou = 0;
//Verificare pentru tipul de angajat
                switch (optiune_angajat) {
                    case 1: {
                        Manager* pMgr = new Manager();
                        std::cout << "--- Date Manager ---\n";
                        std::cin >> (*pMgr);
                        p_angajat_nou = pMgr;
                        break;
                    }

                    case 2: {
                        Bucatar* pBuc = new Bucatar();
                        std::cout << "--- Date Bucatar ---\n";
                        std::cin >> (*pBuc);
                        p_angajat_nou = pBuc;
                        break;
                    }
                    case 3: {
                        Camerista* pCam = new Camerista();
                        std::cout << "--- Date Bucatar ---\n";
                        std::cin >> (*pCam);
                        p_angajat_nou = pCam;
                        break;
                    }
                    default:
                        std::cout << "Optiune tip angajat invalida.\n";
                    break;
                }

                if (p_angajat_nou != 0) {
                    hotel_principal.AdaugaAngajat(p_angajat_nou);
                    std::cout << "Angajat adaugat cu succes!" << std::endl;

                }
                break;
            }
            case 4: {//Creeaza Rezervare
                std::string cnp; int nr_cam = 0, nr_zile = 0;
                Data data_inceput,data_sfarsit;
                //Citire date
                std::cout << "\n--- Creare Rezervare ---\n";
                std::cout << "CNP client: ";
                std::cin >> cnp;
                std::cout << "Nr camera: ";
                std::cin >> nr_cam;
                std::cout << "Data In (YYYY-MM-DD): ";

                std::cin >> data_inceput;
                std::cout << "Data Out (YYYY-MM-DD): ";
                std::cin >> data_sfarsit;

                std::cout << "Nr zile: ";
                std::cin >> nr_zile;


                int id_rez = hotel_principal.CreeazaRezervare(cnp, nr_cam, data_inceput, data_sfarsit, nr_zile);
                if (id_rez == -1) {
                    std::cout << "Crearea rezervarii a esuat." << std::endl;
                } else {
                    const Rezervare* r = hotel_principal.GasesteRezervare(id_rez);
                    if(r != 0)// Daca s-a creat
                        std::cout << "\nRezervare creata:\n" << *r << std::endl;
                }
                break;
            }
            case 5: {// Anuleaza Rezervare
                int id_rez = 0;

                std::cout << "\n--- Anulare Rezervare ---\nID Rezervare: ";
                std::cin >> id_rez;
                hotel_principal.AnuleazaRezervare(id_rez);


                break;
            }
            case 6: {// Marcheaza Rezervare ca Platita
                int id_rez = 0;
                std::cout << "\n--- Marcare Platita ---\nID Rezervare: ";
                std::cin >> id_rez;

                Rezervare* r = hotel_principal.GasesteRezervare(id_rez);
                if (r != 0)//Daca a fost gasita rezervarea
                        {
                    r->SetPlatita(true);
                    std::cout << "Rezervare ID " << id_rez << " marcata ca platita.\n";
                } else {
                    std::cout << "Rezervare ID " << id_rez << " negasita.\n";
                }
                break;
            }

            case 7: hotel_principal.AfisareCamere(); break;
            case 8: hotel_principal.AfisareCamereLibere(); break;
            case 9: hotel_principal.AfisareCamereOcupate(); break;
            case 10: hotel_principal.AfisareClienti(); break;
            case 11: hotel_principal.AfisareAngajati(); break;
            case 12: hotel_principal.AfisareRezervari(); break;
            case 13: {// Afiseaza Rezervarile unui Client (dupa CNP)
                std::string cnp;
                std::cout << "\n--- Afisare Rezervari Client ---\nCNP: ";
                std::cin >> cnp;
                hotel_principal.AfisareRezervariClient(cnp);
                break;
            }
            case 14: {// Calculeaza si Afiseaza Venit Total
                double venit = hotel_principal.CalculeazaVenitTotal();
                std::cout << "\n--- Venit Total Actual ---\n" << venit << " RON\n------------------------\n";
                break;
            }
            case 15: std::cout << "\n--- Detalii Hotel ---\n" << hotel_principal << "\n---------------------------\n"; break;
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