#ifndef CAMERA_H
#define CAMERA_H

#include "TipCamera.h"
#include <string>
#include <iostream>

class Camera : public IAfisabil {
private:
    int m_numar;
    double m_pret_pe_noapte;
    bool m_ocupata;
    TipCamera m_tip;
    int m_etaj;

public:
    Camera();
    Camera(int numar, double pret_pe_noapte, bool ocupata, const TipCamera& tip, int etaj);
    Camera(const Camera& other);
    ~Camera();

    int GetNumar() const;
    void SetNumar(int numar);
    double GetPretPeNoapte() const;
    void SetPretPeNoapte(double pret);
    bool IsOcupata() const;
    void SetOcupata(bool ocupata);
    TipCamera GetTip() const;
    const TipCamera& GetTipRef() const;
    void SetTip(const TipCamera& tip);
    int GetEtaj() const;
    void SetEtaj(int etaj);

    void Afisare(std::ostream& os) const;

    Camera& operator=(const Camera& other);
    bool operator==(const Camera& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Camera& camera);
    friend std::istream& operator>>(std::istream& is, Camera& camera);
};

#endif // CAMERA_H