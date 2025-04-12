#ifndef IAFISABIL_H
#define IAFISABIL_H

#include <iostream> // Necesar pentru std::ostream

// Definitia interfetei pure IAfisabil
class IAfisabil {
public:
    // Destructor virtual - esential pentru interfete!
    virtual ~IAfisabil() {}

    // Functia pur virtuala care defineste contractul interfetei
    // Orice clasa care mosteneste IAfisabil TREBUIE sa implementeze afisare.
    // Primeste stream-ul ca parametru pentru flexibilitate.
    virtual void afisare(std::ostream& os) const = 0;
};

// Optional: Un operator global << care poate lucra cu orice obiect IAfisabil
// Acesta permite scrierea std::cout << *pointer_catre_IAfisabil;
// sau std::cout << referinta_catre_IAfisabil;
inline std::ostream& operator<<(std::ostream& os, const IAfisabil& obj) {
    obj.afisare(os); // Apeleaza metoda virtuala specifica obiectului real
    return os;
}

#endif // IAFISABIL_H