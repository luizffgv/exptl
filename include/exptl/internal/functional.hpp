#ifndef EXPTL_INTERNAL_FUNCTIONAL_HPP
#define EXPTL_INTERNAL_FUNCTIONAL_HPP

#include <functional> // std::invoke
#include <utility>    // std::forward

namespace exptl
{

/**
 * @defgroup functional functional
 * @brief This header provides utilities to deal with function objects, much
 * like the Standard Library header `<functional>`.
 * @{
 */

/**
 * @brief Wraps around a callable object to provide function composition.
 *
 * @tparam Fn The callable object type.
 */
template <typename Fn>
class composable
{
    Fn fn;

public:
    /**
     * @brief Creates a composable<Fn> wrapping the callable fn.
     *
     * @param fn The callable object to wrap.
     */
    composable(Fn fn) : fn{fn} {}

    /**
     * @brief Returns the composition of this composable and rhs.
     *
     * Given that `fn` is the currently wrapped callable, returns a composable
     * that wraps around a callable which invokes `rhs(fn(args))` when called
     * with the arguments `args`.
     *
     * @tparam Fn2 Type of the callable object to compose with.
     *
     * @param rhs The callable object to compose with.
     */
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

    /**
     * @brief Calls the wrapped function the provided arguments.
     *
     * @tparam Args Type of the arguments to pass to the wrapped function.
     *
     * @param args The arguments to pass to the wrapped function.
     *
     * @return The result of calling the wrapped function.
     */
    template <typename... Args>
    decltype(auto) operator()(Args &&...args)
    {
        return std::invoke(fn, std::forward<Args>(args)...);
    }

    /**
     * @brief Calls the wrapped function with the provided arguments.
     *
     * Only allowed when the wrapped callable is equality preserving.
     *
     * @tparam Args Type of the arguments to pass to the wrapped function.
     *
     * @param args The arguments to pass to the wrapped function.
     *
     * @return The result of calling the wrapped function.
     */
    template <typename... Args>
    decltype(auto) operator()(Args &&...args) const
    {
        return std::invoke(fn, std::forward<Args>(args)...);
    }
};

/**
 * @}
 */

} // namespace exptl

#endif // #ifndef EXPTL_INTERNAL_FUNCTIONAL_HPP
