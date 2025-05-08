#ifndef TIPCAMERA_H
#define TIPCAMERA_H

#include <string>
#include <iostream>
#include "IAfisabil.h"

class TipCamera : public IAfisabil {
private:
    std::string m_denumire;
    int m_numar_maxim_persoane;
    bool m_are_balcon;
    bool m_are_vedere;

public:
    TipCamera();
    TipCamera(const std::string& denumire, int numarMaximPersoane, bool areBalcon, bool areVedere);
    TipCamera(const TipCamera& other);
    ~TipCamera();


    std::string GetDenumire() const;
    void SetDenumire(const std::string& denumire);
    int GetNumarMaximPersoane() const;
    void SetNumarMaximPersoane(int numar);
    bool HasBalcon() const;
    void SetAreBalcon(bool areBalcon);
    bool HasVedere() const;
    void SetAreVedere(bool areVedere);


    void Afisare(std::ostream& os) const;

    // Operatori
    TipCamera& operator=(const TipCamera& other);
    bool operator==(const TipCamera& other) const;
    friend std::ostream& operator<<(std::ostream& os, const TipCamera& tipCamera);
    friend std::istream& operator>>(std::istream& is, TipCamera& tipCamera);
};

#endif // TIPCAMERA_H