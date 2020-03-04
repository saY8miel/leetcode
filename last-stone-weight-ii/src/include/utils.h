#ifndef IH
#define IH

#include <string>
#include <climits>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <vector>
#include <numeric>
#include <unordered_set>
#include <set>

using namespace std;

template <class S>
void write(const S& s) {
  copy(s.begin(), s.end(), ostream_iterator<typename S::value_type>(cout, " "));
  cout << "\n";
}

#endif
