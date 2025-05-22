#ifndef REZERVARE_H
#define REZERVARE_H

#include "Client.h"
#include "Camera.h"
#include <string>
#include <iostream>
#include <data.h>

class Rezervare : public IAfisabil {
private:
    static int m_numar_total_rezervari;
    int m_id;
    Client m_client;
    Camera m_camera;
    Data m_data_check_in;
    Data m_data_check_out;
    int m_numar_zile;
    double m_pret_total;
    bool m_platita;

public:
    Rezervare();
    Rezervare(const Client& client, const Camera& camera, const Data& data_check_in,
              const Data& data_check_out, int numar_zile, bool platita = false);
    Rezervare(const Rezervare& other);
    ~Rezervare();

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

    void CalculeazaPretTotal();

    void Afisare(std::ostream& os) const;

    Rezervare& operator=(const Rezervare& other);
    bool operator==(const Rezervare& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Rezervare& rezervare);
    friend std::istream& operator>>(std::istream& is, Rezervare& rezervare);
};
double operator+(double suma,const Rezervare& r);
#endif // REZERVARE_H