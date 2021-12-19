#ifndef EXPTL_INTERNAL_FUNCTIONAL_HPP
#define EXPTL_INTERNAL_FUNCTIONAL_HPP

#include <functional> // std::invoke
#include <utility>    // std::forward

namespace exptl
{

template <typename Fn>
class composable
{
    Fn fn;

public:
    composable(Fn fn) : fn{fn} {}

    template <typename Fn2>
    auto operator+(Fn2 rhs) const
    {
        auto lambda{
          [=, fn{fn}](auto &&...args) mutable -> decltype(auto)
          {
              return std::invoke(
                rhs, std::invoke(fn, std::forward<decltype(args)>(args)...));
          }};

        return composable<decltype(lambda)>{lambda};
    }

    template <typename... Args>
    decltype(auto) operator()(Args &&...args)
    {
        return std::invoke(fn, std::forward<Args>(args)...);
    }

    template <typename... Args>
    decltype(auto) operator()(Args &&...args) const
    {
        return std::invoke(fn, std::forward<Args>(args)...);
    }
};

} // namespace exptl

#endif // #ifndef EXPTL_INTERNAL_FUNCTIONAL_HPP
