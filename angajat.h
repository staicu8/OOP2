#ifndef ANGAJAT_H
#define ANGAJAT_H

#include "Persoana.h"
#include <string>
#include <iostream>
//Clasa abstracta
//Mosteneste nume,prenume,cnp,varsta din Persoana
class Angajat : public Persoana {
private:

    double m_salariu;
    int m_ani_experienta;

//Protected ca fiecare clasa mostenita sa poata sa isi modifice
protected:
    void SetAniExperienta(int ani);
public:
    //Constructor
    Angajat();

//Constructor cu parametrii
    Angajat(std::string nume, std::string prenume, std::string cnp, int varsta, double salariu, int ani_experienta);

    //Construct de copiere
    Angajat(const Angajat& other);

    //Destructor virtual
    virtual ~Angajat();


    //Metoda pur virtuala,va fi implementata de fiecare clasa mostenita si va afisa functia pe care o ocupa
    //un angajat=>clasa abstracta
    virtual std::string GetFunctie() const=0;
    //Getteri si Setteri
    double GetSalariu() const;
    void SetSalariu(double salariu);
    int GetAniExperienta() const;


//Initializeaza functia pur virtuala Afisare din interfata
    void Afisare(std::ostream& os) const;

//Initializeaza functia pur virtuala din Persoana
    std::string GetTip() const;

    //Supraincarcare Operatori
    Angajat& operator=(const Angajat& other);
    bool operator==(const Angajat& other) const;

    //Friend pentru a putea avea acces la atributele private
    friend std::ostream& operator<<(std::ostream& os, const Angajat& angajat);
    friend std::istream& operator>>(std::istream& is, Angajat& angajat);
};

#endif // ANGAJAT_H