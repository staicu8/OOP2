#ifndef IAFISABIL_H
#define IAFISABIL_H

#include <iostream>

class IAfisabil {
public:
    virtual ~IAfisabil() {}

    virtual void Afisare(std::ostream& os) const = 0;
};

std::ostream& operator<<(std::ostream& os, const IAfisabil& obj);

#endif // IAFISABIL_H