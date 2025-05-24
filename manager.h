#ifndef MANAGER_H
#define MANAGER_H

#include "angajat.h"
#include <string>


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

    virtual std::string GetFunctie() const;

    //Initializeaza functia pur virtuala Afisare din interfata
    virtual void Afisare(std::ostream& os) const;

    void SetDepartament(const std::string& departament);
    std::string GetDepartament() const;



};

#endif // MANAGER_H