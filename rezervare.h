#ifndef REZERVARE_H
#define REZERVARE_H

#include "client.h"
#include "camera.h"
#include <string>
#include <iostream>
#include <data.h>

class Rezervare : public IAfisabil {
private:
    static int m_numar_total_rezervari;//Membru static,reprezinta numarul total de rezervari facute in hotel
    int m_id;//Va fi calculat din numar_total_rezervari
    Client m_client;//Clientul care face rezervare
    Camera m_camera;//Camera rezervata
    Data m_data_check_in;
    Data m_data_check_out;
    int m_numar_zile;//Numarul de zile alre rezervire
    double m_pret_total;
    bool m_platita;

public:
    //Initializare Constructor,Constructor cu parametrii si Constructor de copiere
    Rezervare();
    Rezervare(const Client& client, const Camera& camera, const Data& data_check_in,
              const Data& data_check_out, int numar_zile, bool platita = false);
    Rezervare(const Rezervare& other);
    //Destructor
    ~Rezervare();
    //Getteri si Setteri
    int GetId() const;
    const Client& GetClientRef() const;
    void SetClient(const Client& client);
    const Camera& GetCameraRef() const;
    void SetCamera(const Camera& camera);
    Data GetDataCheckIn() const;
    void SetDataCheckIn(const Data& data);
    Data GetDataCheckOut() const;
    void SetDataCheckOut(const Data& data);
    int GetNumarZile() const;
    void SetNumarZile(int zile);
    double GetPretTotal() const;
    bool IsPlatita() const;
    void SetPlatita(bool platita);
    //Pretul total este pretul pe noapte * nr_de zile
    void CalculeazaPretTotal();
    //Initializeaza functia pur virtuala Afisare din interfata
    void Afisare(std::ostream& os) const;
//Supraincarcare operatori
    Rezervare& operator=(const Rezervare& other);
    bool operator==(const Rezervare& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Rezervare& rezervare);
    friend std::istream& operator>>(std::istream& is, Rezervare& rezervare);
};
double operator+(double suma,const Rezervare& r);
#endif // REZERVARE_H