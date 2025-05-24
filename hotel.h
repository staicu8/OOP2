#ifndef HOTEL_H
#define HOTEL_H

#include <string>
#include <vector>
#include <iostream>


#include "camera.h"
#include "client.h"
#include "angajat.h"
#include "rezervare.h"
#include "i_afisabil.h"


class Hotel : public IAfisabil {
private:
std::string m_nume;
std::string m_adresa;
int m_numar_stele;


std::vector<Camera*> m_camere;
std::vector<Client*> m_clienti;
std::vector<Angajat*> m_angajati;
std::vector<Rezervare*> m_rezervari;

//Privati pentru a nu putea copia sau atribui un hotel
Hotel(const Hotel& other);
Hotel& operator=(const Hotel& other);

    //Metode private care returneaza index-ul corespunzator din vector
    int _GasesteIndexAngajat(const std::string& CNP) const;
    int _GasesteIndexCamera(int numar) const;
    int _GasesteIndexClient(const std::string& CNP) const;
    int _GasesteIndexRezervare(int id_rezervare) const;
public:
    //Initializare Constructor,Constructor cu parametrii
Hotel();
Hotel(const std::string& nume, const std::string& adresa, int numar_stele);

    //Destructor
~Hotel();

//Getteri si setteri
std::string GetNume() const;
void SetNume(const std::string& nume);
std::string GetAdresa() const;
void SetAdresa(const std::string& adresa);
int GetNumarStele() const;
void SetNumarStele(int stele);

//Metodele pentru functionalitate

void AdaugaCamera(Camera* p_camera);
void AdaugaClient(Client* p_client);
void AdaugaAngajat(Angajat* p_angajat);
bool StergeCamera(int numar_camera);
bool StergeClient(const std::string& CNP);
bool StergeAngajat(const std::string& CNP);
bool AnuleazaRezervare(int id_rezervare);

    //Metode care returneaza un pointer catre obicetul corespunzator
Camera* GasesteCamera(int numar_camera);
Client* GasesteClient(const std::string& CNP);
Angajat* GasesteAngajat(const std::string& CNP);
Rezervare* GasesteRezervare(int id_rezervare);


int CreeazaRezervare(const std::string &cnp_client, int numar_camera, const Data &data_check_in,
const Data &data_check_out, int numar_zile);


void AfisareCamere() const;
void AfisareCamereLibere() const;
void AfisareCamereOcupate() const;
void AfisareClienti() const;
void AfisareAngajati() const;
void AfisareRezervari() const;
void AfisareRezervariClient(const std::string& CNP) ;


double CalculeazaVenitTotal() const;

    //Initializeaza functia pur virtuala Afisare din interfata

void Afisare(std::ostream& os) const;

//Supraincarcare operatori
friend std::ostream& operator<<(std::ostream& os, const Hotel& hotel);
friend std::istream& operator>>(std::istream& is, Hotel& hotel);
};

#endif // HOTEL_H