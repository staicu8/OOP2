

#include "data.h"
#include <iostream>

Data::Data(int z, int l, int a) {
  this->zi = z;
  this->luna = l;
  this->an = a;
}
//Supraincarcare Operatori
std::ostream& operator<<(std::ostream& os, const Data& d) {
  os << d.zi << "." << d.luna << "." << d.an;
  return os;
}

std::istream& operator>>(std::istream& is, Data& d) {
  is >> d.zi >> d.luna >> d.an;
  return is;
}