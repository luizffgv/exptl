#include <array>
#include <exptl/algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <ranges>
#include <string>

int main()
{
    std::array<std::function<bool(int)>, 2> funcs{
      [](int v) { return !(v % 3); }, [](int v) { return !(v % 5); }};

    std::map<decltype(funcs)::const_iterator, std::string> words{
      {funcs.cbegin(), "Fizz"}, {funcs.cbegin() + 1, "Buzz"}};

    for (auto value : std::views::iota(1, 21))
    {
        auto result{exptl::classify(value, funcs)};

        if (result.size())
            for (auto const &it : result)
                std::cout << words[it];
        else
            std::cout << value;

        std::cout << std::endl;
    }
}
