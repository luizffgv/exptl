#include <exptl/algorithm> // flatten
#include <iostream>        // cout
#include <iterator>        // ostream_iterator
#include <span>            // span
#include <vector>          // vector

int main()
{
    using exptl::flatten;
    using std::cout, std::ostream_iterator, std::span, std::vector;

    vector<vector<vector<int>>> v[][3]{
      {{}, {{{72}}}, {{{101, 108}}}},
      {{{{108, 111}, {44, 32, 87}}}, {{{111}}, {{114}}, {{108}}}, {{{100}}}},
      {{{{33}, {10}}}}};

    flatten<int>(span{v}, ostream_iterator<char>(cout));
}
