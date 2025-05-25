#include "bucatar.h"
#include <iostream>

//Constructor,foloseste lista de initalizare din Angajat
Bucatar::Bucatar()
    : Angajat(), m_specializare_culinara("Nespecificat"), m_rang_bucatar("Nespecificat") {

}
//Constructor cu parametrii
Bucatar::Bucatar(std::string nume, std::string prenume, std::string cnp, int varsta,
                 double salariu, int ani_experienta_generala,
                 const std::string& specializare, const std::string& rang)
    : Angajat(nume, prenume, cnp, varsta, salariu, ani_experienta_generala),
      m_specializare_culinara(specializare), m_rang_bucatar(rang) {

}
//Constructor de copiere
Bucatar::Bucatar(const Bucatar& other)
    : Angajat(other), m_specializare_culinara(other.m_specializare_culinara), m_rang_bucatar(other.m_rang_bucatar) {}

//Destructor
Bucatar::~Bucatar() {}

//Implementeaza functia pur virtuala din Angajat
std::string Bucatar::GetFunctie() const {
        return "Bucatar";
}

//Getteri si setteri
void Bucatar::SetSpecializare(const std::string& specializare) {
    m_specializare_culinara = specializare;
}
std::string Bucatar::GetSpecializare() const {
    return m_specializare_culinara;
}
void Bucatar::SetRang(const std::string& rang) {
    m_rang_bucatar = rang;
}
std::string Bucatar::GetRang() const {
    return m_rang_bucatar;
}

//Implementeaza functia pur virtuala Afisare din interfata
void Bucatar::Afisare(std::ostream& os) const {
    Angajat::Afisare(os);
    os<<",Functie:"<<GetFunctie();
    os<<",Rang:" << m_rang_bucatar;
    os << ", Specializare: " << m_specializare_culinara;
}
//Supraincarcare operatorul >>
std::istream& operator>>(std::istream& is,Bucatar &bucatar) {
    is>>static_cast<Angajat&>(bucatar);
    std::cout<<"Specializare culinara:";
    is>>bucatar.m_specializare_culinara;
    std::cout<<"Rang bucatar:";
    is>>bucatar.m_rang_bucatar;
    return is;
}