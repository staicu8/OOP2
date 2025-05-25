#ifndef CAMERISTA_H
#define CAMERISTA_H

#include "angajat.h"
#include <string>
#include <iostream>

//Mosteneste salariu si ani_experienta din Angajat
class Camerista : public Angajat {
private:
    std::string m_zona_responsabilitate; // De exemplu: "Etajele 1-3", "Aripa Sud"
    bool m_are_training_special_curatenie;

public:
    //Initializare Constructor,Constructor cu parametrii,Constructor de copiere
    Camerista();
    Camerista(std::string nume, std::string prenume, std::string cnp, int varsta,
              double salariu, int ani_experienta_generala,
              const std::string& zona, bool training_special);
    Camerista(const Camerista& other);

    //Destructor virtual
    virtual ~Camerista();

    //Suprascrie functia pur virtuala GetFunctie din Angajat
    virtual std::string GetFunctie() const;

    //Suprascrie functia pur virtuala Afisare din interfata
    virtual void Afisare(std::ostream& os) const;


    //Getteri si Setteri
    void SetZonaResponsabilitate(const std::string& zona);
    std::string GetZonaResponsabilitate() const;
    void SetAreTrainingSpecial(bool are_training);
    bool AreTrainingSpecial() const;

    void RaporteazaCameraCuratata(int numar_camera);
    //Supraincarcare operatorul >>
    friend std::istream& operator>>(std::istream& is, Camerista& c);
};

#endif // CAMERISTA_H