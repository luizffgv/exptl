#include <exptl/algorithm> // flatten
#include <iostream>        // cout
#include <iterator>        // cbegin, cend, ostream_iterator
#include <vector>          // vector

using exptl::flatten;
using std::cbegin;
using std::cend;
using std::cout;
using std::ostream_iterator;
using std::vector;

int main()
{
    vector<vector<vector<int>>> v[][3]{
      {{}, {{{72}}}, {{{101, 108}}}},
      {{{{108, 111}, {44, 32, 87}}}, {{{111}}, {{114}}, {{108}}}, {{{100}}}},
      {{{{33}, {10}}}}};

    flatten<int>(std::cbegin(v), std::cend(v), ostream_iterator<char>(cout));
}
