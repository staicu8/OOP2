
#include "IAfisabil.h"
#include <iostream>


std::ostream& operator<<(std::ostream& os, const IAfisabil& obj) {
    obj.afisare(os);
    return os;
}