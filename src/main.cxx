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
  std::vector<int> data = {5, 4, 13, 8, 9, 7, 1, 3, 2, 6};
  int i = 0;
  for (auto n : data){
    t.probe_root(n);
    SaveToFile(GetFileName("tree", "dot", ++i), t);
  }
  return 0;
}
