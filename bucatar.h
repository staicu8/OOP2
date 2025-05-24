#ifndef BUCATAR_H
#define BUCATAR_H

#include "angajat.h"
#include <string>
#include <iostream>
//Mosteneste salariu si ani de experienta
class Bucatar : public Angajat {
private:
    std::string m_specializare_culinara;//De exemplu Mancare italiana,Traditionala
    std::string m_rang_bucatar;//De exemplu Bucatar Sef,Ajutor de bucatar

public:
    //Initializare Constructor,Constructor cu parametrii si Constructor de copiere
    Bucatar();
    Bucatar(std::string nume, std::string prenume, std::string cnp, int varsta,
            double salariu, int ani_experienta_generala,
            const std::string& specializare, const std::string& rang);
    Bucatar(const Bucatar& other);
    virtual ~Bucatar();

//Initializeaza functia pur virtuala din Persoana
    virtual std::string GetFunctie() const;

    //Initializeaza functia pur virtuala Afisare din interfata
    virtual void Afisare(std::ostream& os) const;

//Getteri si Setteri
    void SetSpecializare(const std::string& specializare);
    std::string GetSpecializare() const;
    void SetRang(const std::string& rang);
    std::string GetRang() const;
};

#endif // BUCATAR_H