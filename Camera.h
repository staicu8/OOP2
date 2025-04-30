#ifndef CAMERA_H
#define CAMERA_H

#include "TipCamera.h" // TipCamera include IAfisabil
#include <string>
#include <iostream>

class Camera : public IAfisabil {
private:
    int numar;
    double pretPeNoapte;
    bool ocupata;
    TipCamera tip;
    int etaj;

public:
    Camera();
    Camera(int numar, double pretPeNoapte, bool ocupata, const TipCamera& tip, int etaj);
    Camera(const Camera& other);
    ~Camera();


    int getNumar() const;
    void setNumar(int numar);
    double getPretPeNoapte() const;
    void setPretPeNoapte(double pret);
    bool isOcupata() const;
    void setOcupata(bool ocupata);
    TipCamera getTip() const;
    const TipCamera& getTipRef() const;
    void setTip(const TipCamera& tip);
    int getEtaj() const;
    void setEtaj(int etaj);


    void afisare(std::ostream& os) const;

    Camera& operator=(const Camera& other);
    bool operator==(const Camera& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Camera& camera);
    friend std::istream& operator>>(std::istream& is, Camera& camera);
};

#endif // CAMERA_H