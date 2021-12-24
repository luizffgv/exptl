#ifndef EXPTL_INTERNAL_ALGORITHM_HPP
#define EXPTL_INTERNAL_ALGORITHM_HPP

#include <algorithm> // copy
#include <concepts>  // assignable_from
#include <iterator> // cbegin, cend, input_iterator, iterator_traits, output_iterator
#include <type_traits> // is_same_v

namespace exptl
{

/**
 * @defgroup algorithm algorithm
 * @brief This header provides general algorithms to make your life easier.
 * @{
 */

/**
 * @brief Extracts elements from nested containers.
 *
 * @tparam T type of the elements to be extracted.
 * @tparam T2 `value_type` of the output iterator
 * @tparam In type of the input iterators
 * @tparam Out type of the output iterator
 *
 * @param begin Start of the range of elements to be extracted
 * @param end End of the range of elements to be extracted
 * @param out Output iterator to store the extracted elements
 */
template <typename T,
          typename T2 = T,
          std::input_iterator      In,
          std::output_iterator<T2> Out>
requires std::assignable_from<T2 &, T>
void flatten(In begin, In const end, Out out)
{
    if constexpr (std::is_same_v<T,
                                 typename std::iterator_traits<In>::value_type>)
        std::copy(begin, end, out);
    else
        while (begin != end)
        {
            typename std::iterator_traits<In>::value_type const &value{
              *begin++};
            flatten<T>(std::cbegin(value), std::cend(value), out);
        }
}

/** @example algorithm/hello_world.cpp
 * This is an example of how to use the flatten() function.
 *
 * It outputs "Hello, World!"
 */

/**
 * @}
 */

} // namespace exptl

#endif // #ifndef EXPTL_INTERNAL_ALGORITHM_HPP
