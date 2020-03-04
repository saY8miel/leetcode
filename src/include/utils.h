#ifndef IH
#define IH

#include <algorithm>
#include <bitset>
#include <climits>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

template <class S>
void write(const S& s) {
  copy(s.begin(), s.end(), ostream_iterator<typename S::value_type>(cout, " "));
  cout << "\n";
}

#endif
