#include <cstddef>          // size_t
#include <exptl/functional> // composable
#include <functional>       // plus
#include <iostream>         // cout, endl
#include <utility>          // swap

using exptl::composable;
using std::cout;
using std::endl;
using std::plus;
using std::size_t;
using std::swap;

int main(void)
{
    auto constexpr ref{[](auto &val) { return [&]() { return val; }; }};
    auto constexpr add{[](int &rhs)
                       { return [&](int lhs) { return plus{}(lhs, rhs); }; }};
    auto constexpr store{[](int &lhs) {
        return [&](int rhs) -> decltype(auto) { return lhs = rhs; };
    }};
    auto constexpr print{[](int val) { cout << val << endl; }};
    auto constexpr transpose{[](int &rhs)
                             {
                                 return [&](int &lhs)
                                 {
                                     swap(lhs, rhs);
                                     return lhs;
                                 };
                             }};

    int  x{};
    int  y{1};
    auto fib_next{composable{ref(x)} + add(y) + store(y) + transpose(x)
                  + print};
    for (size_t i{}; i < 20; ++i)
        fib_next();
}
