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

void test1() {
  adt::Adt<int> t;
  for (int i = 0; i < 6; ++i) {
    t.probe(i);
  }

  auto v = t.GetPreorderVector();
  std::cout << "Preorder:\n";
  print(std::cout, v);
  std::cout << "\n";
  auto v1 = t.GetInorderVector();
  std::cout << "Inorder:\n";
  print(std::cout, v1);
  std::cout << "\n";

  SaveToFile(GetFileName("tree", "dot", 1), t);
  for (int i = 15; i > 5; --i) {
    t.probe(i);
  }

  auto v3 = t.GetPreorderVector();
  std::cout << "Preorder:\n";
  print(std::cout, v3);
  std::cout << "\n";
  auto v4 = t.GetInorderVector();
  std::cout << "Inorder:\n";
  print(std::cout, v4);
  std::cout << "\n";

  SaveToFile(GetFileName("tree", "dot", 2), t);
  t.probe(16);
  SaveToFile(GetFileName("tree", "dot", 3), t);
}

void test2() {

  adt::Adt<int> t;
  std::cout << "Sequence:\n";
  for (int i = 0; i < 16; ++i) {
    t.probe(i);
    SaveToFile(GetFileName("tree", "dot", 10 + 2 * i), t);
    t.probe(32 - i);
    std::cout << i << ", " << 32 - i << ", ";

    SaveToFile(GetFileName("tree", "dot", 11 + 2 * i), t);
  }
  std::cout << "\n";

  auto v = t.GetPreorderVector();
  std::cout << "Preorder:\n";
  print(std::cout, v);
  std::cout << "\n";
  auto v1 = t.GetInorderVector();
  std::cout << "Inorder:\n";
  print(std::cout, v1);
  std::cout << "\n";
}

int main() {
  adt::Adt<int> t;
  std::vector<int> source = {100, 50, 150, 20, 120, 200, 110, 135, 170, 300};

  int i = 0;
  for (int a : source) {
    t.probe(a);
    SaveToFile(GetFileName("tree", "dot", 10 + i), t);
    ++i;
  }
  int a = 130;
  t.probe(a);
  source.push_back(a);
  SaveToFile(GetFileName("tree", "dot", 50), t);

  std::cout << "Sequence:\n";
  print(std::cout, source);
  std::cout << "\n";
  auto v1 = t.GetInorderVector();
  std::cout << "Inorder:\n";
  print(std::cout, v1);
  std::cout << "\n";
  auto v2 = t.GetInorderAvlBalanceVector();
  std::cout << "Balance:\n";
  print(std::cout, v2);
  std::cout << "\n";
  auto v = t.GetPreorderVector();
  std::cout << "Preorder:\n";
  print(std::cout, v);
  std::cout << "\n";
}
