#ifndef CAMERA_H
#define CAMERA_H

#include "TipCamera.h" // Include definitia TipCamera
#include <string>
#include <iostream>

class Camera {
private:
    int numar;
    double pretPeNoapte;
    bool ocupata;
    TipCamera tip; // Contine un obiect TipCamera
    int etaj;

public:
    // Constructori
    Camera();
    Camera(int numar, double pretPeNoapte, bool ocupata, const TipCamera& tip, int etaj);
    Camera(const Camera& other);

    // Destructor
    ~Camera();

    // Getteri și setteri
    int getNumar() const;
    void setNumar(int numar);
    double getPretPeNoapte() const;
    void setPretPeNoapte(double pret);
    bool isOcupata() const;
    void setOcupata(bool ocupata);
    TipCamera getTip() const; // Returneaza o copie a obiectului TipCamera
    const TipCamera& getTipRef() const; // Returneaza referinta constanta (mai eficient)
    void setTip(const TipCamera& tip);
    int getEtaj() const;
    void setEtaj(int etaj);

    // Metode
    void afisare() const; // Afiseaza detaliile camerei

    // Operatori
    Camera& operator=(const Camera& other);
    bool operator==(const Camera& other) const; // Compara pe baza numarului camerei

    // Declaratii friend
    friend std::ostream& operator<<(std::ostream& os, const Camera& camera);
    friend std::istream& operator>>(std::istream& is, Camera& camera);
};

#endif // CAMERA_H