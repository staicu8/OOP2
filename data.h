#ifndef DATA_H
#define DATA_H

#include <iostream>

struct Data {
    int zi, luna, an;

    Data() {}
    Data(int z, int l, int a);
};

std::ostream& operator<<(std::ostream& os, const Data& d);
std::istream& operator>>(std::istream& is, Data& d);

#endif //DATA_H