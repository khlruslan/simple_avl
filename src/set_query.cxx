#include <fstream>
#include <iterator>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

namespace sol {
const char kKey = 'k';
const char kQuery = 'q';

const int kOk = 1;
const int kInputError = 2;

template <typename C, typename T> int range_query(const C &s, T fst, T snd) {
	if (fst > snd){
		return 0;
	}
	auto it1 = s.lower_bound(fst);
	auto it2 = s.upper_bound(snd);

  return std::distance(it1, it2);
}

int ProcessInputStream(std::istream &in, std::ostream &out) {
  char command;
  int value;
  int first;
  int second;

  std::set<int> tree;

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
