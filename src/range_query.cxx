#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "simple_adt.h"

void SaveToFile(const std::string &filename, const adt::Adt<int> &t) {
  std::ofstream out(filename);
  adt::Adt<int>::save_dot(out, t);
}

std::string GetFileName(const std::string &name, const std::string &ext,
                        int i) {
  std::ostringstream out;
  out << name << std::setw(3) << std::setfill('0') << std::right << i << '.'
      << ext;
  return out.str();
}

template <class T> void print(std::ostream &os, std::vector<T> v) {
  for (const auto &a : v) {
    os << a << ", ";
  }
}

namespace sol {
const char kKey = 'k';
const char kQuery = 'q';

const int kOk = 1;
const int kInputError = 2;

template <typename C, typename T> int range_query(const C &s, T fst, T snd) {
  return s.CountByRange(fst, snd);
}

int ProcessInputStream(std::istream &in, std::ostream &out) {
  char command;
  int value;
  int first;
  int second;
#ifdef my_debug_1
  int i = 0;
#endif

  adt::Adt<int> tree;

  while (in >> command) {
    switch (command) {
    case kKey: {
      in >> value;
      tree.insert(value);
      break;
    }
    case kQuery: {
      in >> first >> second;
      if (first <= second) {
#ifdef my_debug_1
        ++i;
        SaveToFile(GetFileName("tree", "dot", i), tree);
#endif
        out << range_query(tree, first, second) << ' ';
      } else {
        return kInputError;
      }
      break;
    }
    }
  }

  out << '\n';

  return kOk;
}
} // namespace sol

int main() {
  std::ios::sync_with_stdio(false);
  int result = sol::ProcessInputStream(std::cin, std::cout);
  if (result != sol::kOk) {
    std::cerr << "Error :" << result << "\n";
  }
}
