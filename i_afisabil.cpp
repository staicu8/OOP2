#include "i_afisabil.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const IAfisabil& obj) {
    obj.Afisare(os);
    return os;
}