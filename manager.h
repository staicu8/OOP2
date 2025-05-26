#ifndef MANAGER_H
#define MANAGER_H

#include "angajat.h"
#include <string>

//Mosteneste salariu si ani_experienta din Angajat
class Manager : public Angajat {
private:
    std::string m_departament_condus;


public:
    Manager();


    //Implementare Constructor,Constructor cu parametrii si Constructor de copiere
    Manager(const std::string& nume, const std::string& prenume, const std::string& cnp, int varsta,
            double salariu, int ani_experienta, const std::string& departament);
    Manager(const Manager& other);

    //Destructor
    virtual ~Manager();
    //Suprascrie functia pur virtuala GetFunctie din Angajat
    virtual std::string GetFunctie() const;

    //Suprascrie functia pur virtuala Afisare din interfata
    virtual void Afisare(std::ostream& os) const;

    //Getter si Setter
    void SetDepartament(const std::string& departament);
    std::string GetDepartament() const;

    //Supraincarcare operatorul >>
friend std::istream& operator>>(std::istream& is, Manager& manager);
};

#endif // MANAGER_H