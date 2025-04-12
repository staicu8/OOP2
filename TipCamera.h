#ifndef TIPCAMERA_H
#define TIPCAMERA_H

#include <string>
#include <iostream>
#include "IAfisabil.h" // Include interfata

class TipCamera : public IAfisabil { // Mosteneste interfata
private:
    std::string denumire;
    int numarMaximPersoane;
    bool areBalcon;
    bool areVedere;

public:
    TipCamera();
    TipCamera(const std::string& denumire, int numarMaximPersoane, bool areBalcon, bool areVedere);
    TipCamera(const TipCamera& other);
    ~TipCamera();

    // Getteri / Setteri
    std::string getDenumire() const;
    void setDenumire(const std::string& denumire);
    int getNumarMaximPersoane() const;
    void setNumarMaximPersoane(int numar);
    bool hasBalcon() const;
    void setAreBalcon(bool areBalcon);
    bool hasVedere() const;
    void setAreVedere(bool areVedere);

    // Implementarea interfetei IAfisabil
    void afisare(std::ostream& os) const;

    // Operatori
    TipCamera& operator=(const TipCamera& other);
    bool operator==(const TipCamera& other) const;
    friend std::ostream& operator<<(std::ostream& os, const TipCamera& tipCamera);
    friend std::istream& operator>>(std::istream& is, TipCamera& tipCamera);
};

#endif // TIPCAMERA_H