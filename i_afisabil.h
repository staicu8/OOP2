#ifndef IAFISABIL_H
#define IAFISABIL_H

#include <iostream>
//Interfata pentru toate obiectele care pot fi afisate
class IAfisabil {
public:
    virtual ~IAfisabil() {}

    virtual void Afisare(std::ostream& os) const = 0;
};


//Supraincarcare operaoturl <<
std::ostream& operator<<(std::ostream& os, const IAfisabil& obj);

#endif // IAFISABIL_H