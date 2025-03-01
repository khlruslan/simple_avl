#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

const char kQuery = 'q';
const char kKey = 'k';
const char kSpace = ' ';

std::string GetFileName(const std::string &name, const std::string &ext,
                        int i) {
  std::ostringstream out;
  out << name << std::setw(3) << std::setfill('0') << std::right << i << '.'
      << ext;
  return out.str();
}

int main() {
  int first = 0;
  int last = 1000000000;

  std::random_device rd;  // a seed source for the random number engine
  std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> distrib(first, last);

  int k = 100;
  int mul = 10;
  int scale = 5;

  for (int n = 2; n < 8; ++n) {
    auto file_name = GetFileName("", "dat", n);
    std::ofstream out(file_name);
    for (int i = 0; i < k; ++i) {
      if (i % scale == 0) {
        int a = distrib(gen);
        int b = distrib(gen);
        out << kQuery << ' ' << std::min(a, b) << ' ' << std::max(a, b) << ' ';
      } else {
        out << kKey << ' ' << distrib(gen) << ' ';
      }
    }
    out << kQuery << ' ' << first << ' ' << last << '\n';
    k *= mul;
  }
}
