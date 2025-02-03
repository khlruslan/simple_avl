#include <iostream>

#include "simple_adt.h"

int main(){
  adt::Adt<int> t;
  auto pos = t.insert(6);
  pos = t.insert(4);
  pos = t.insert(5);
  pos = t.insert(10);
  pos = t.insert(8);
  pos = t.insert(9);
  pos = t.insert(7);
  pos = t.insert(3);
  pos = t.insert(1);
  pos = t.insert(2);
  adt::Adt<int>::save_dot(std::cout,t);
  return 0;
}
