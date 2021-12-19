#ifndef EXPTL_INTERNAL_FUNCTIONAL_HPP
#define EXPTL_INTERNAL_FUNCTIONAL_HPP

#include <utility> // std::forward

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
        auto lambda{[=, fn{fn}](auto &&...args) mutable -> decltype(auto)
                    { return rhs(fn(std::forward<decltype(args)>(args)...)); }};

        return composable<decltype(lambda)>{lambda};
    }

    template <typename... Args>
    decltype(auto) operator()(Args &&...args)
    {
        return fn(std::forward<Args>(args)...);
    }

    template <typename... Args>
    decltype(auto) operator()(Args &&...args) const
    {
        return fn(std::forward<Args>(args)...);
    }
};

} // namespace exptl

#endif // #ifndef EXPTL_INTERNAL_FUNCTIONAL_HPP
