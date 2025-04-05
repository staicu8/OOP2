#ifndef TIPCAMERA_H
#define TIPCAMERA_H

#include <string>
#include <iostream>

class TipCamera {
private:
    std::string denumire;
    int numarMaximPersoane;
    bool areBalcon;
    bool areVedere; // Ex: vedere la mare, vedere la gradina etc.

public:
    // Constructori
    TipCamera();
    TipCamera(const std::string& denumire, int numarMaximPersoane, bool areBalcon, bool areVedere);
    TipCamera(const TipCamera& other);

    // Destructor
    ~TipCamera();

    // Getteri și setteri
    std::string getDenumire() const;
    void setDenumire(const std::string& denumire);
    int getNumarMaximPersoane() const;
    void setNumarMaximPersoane(int numar);
    bool hasBalcon() const;
    void setAreBalcon(bool areBalcon);
    bool hasVedere() const;
    void setAreVedere(bool areVedere);

    // Operatori
    TipCamera& operator=(const TipCamera& other);
    bool operator==(const TipCamera& other) const;

    // Declaratii friend
    friend std::ostream& operator<<(std::ostream& os, const TipCamera& tipCamera);
    friend std::istream& operator>>(std::istream& is, TipCamera& tipCamera);
};

#endif // TIPCAMERA_H