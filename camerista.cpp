#include "Camerista.h"
#include <iostream>

//Implementare Constructor,Constructor cu parametrii,Constructor de copiere
Camerista::Camerista()
    : Angajat(), m_zona_responsabilitate("Nespecificata"), m_are_training_special_curatenie(false) {

}

Camerista::Camerista(std::string nume, std::string prenume, std::string cnp, int varsta,
                     double salariu, int ani_experienta_generala,
                     const std::string& zona, bool training_special)
    : Angajat(nume, prenume, cnp, varsta, salariu, ani_experienta_generala),
      m_zona_responsabilitate(zona), m_are_training_special_curatenie(training_special) {


}

Camerista::Camerista(const Camerista& other)
    : Angajat(other), m_zona_responsabilitate(other.m_zona_responsabilitate),
      m_are_training_special_curatenie(other.m_are_training_special_curatenie) {}


//Destructor
Camerista::~Camerista() {}

//Getteri si Setteri
std::string Camerista::GetFunctie() const {
    return "Camerista";
}

void Camerista::SetZonaResponsabilitate(const std::string& zona) {
    m_zona_responsabilitate = zona;
}
std::string Camerista::GetZonaResponsabilitate() const {
    return m_zona_responsabilitate;
}

void Camerista::SetAreTrainingSpecial(bool are_training) {
    m_are_training_special_curatenie = are_training;
}
bool Camerista::AreTrainingSpecial() const {
    return m_are_training_special_curatenie;
}

void Camerista::RaporteazaCameraCuratata(int numar_camera) {
    std::cout << GetFunctie() << " " << GetPrenume() << " raporteaza: Camera "
              << numar_camera << " este acum curata." << std::endl;
}

void Camerista::Afisare(std::ostream& os) const {
    Angajat::Afisare(os); // Apeleaza Afisare din clasa de baza Angajat
    os<<",Functie:"<<GetFunctie();
    os << ", Training Special Curatenie: " << (m_are_training_special_curatenie ? "Da" : "Nu");
}
//Supraincarcare operatorul >>
std::istream& operator>>(std::istream& is,Camerista &camerista) {
    is>>static_cast<Angajat&>(camerista);
    std::cout<<"Zona de responsibilitate:";
    is>>camerista.m_zona_responsabilitate;
    std::cout<<"Are training special de curatenie? 1(DA),0(NU):";
    is>>camerista.m_are_training_special_curatenie;
    return is;
}