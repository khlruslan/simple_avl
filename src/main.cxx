#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

#include "simple_adt.h"

void SaveToFile(const std::string& filename, const adt::Adt<int>& t){
  std::ofstream out(filename);
  adt::Adt<int>::save_dot(out, t);
}

std::string GetFileName(const std::string &name, const std::string& ext, int i){
  std::ostringstream out;
  out << name <<std::setw(3) << std::setfill('0') << std::right << i << '.' << ext;
  return out.str();
}

int main(){
  adt::Adt<int> t;
  for (int i = 0 ; i < 63 ; ++i){
    t.probe(i);
    SaveToFile(GetFileName("tree", "dot", i+1), t);
  }
  return 0;
}
