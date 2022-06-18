#ifndef EXPTL_INTERNAL_ALGORITHM_HPP
#define EXPTL_INTERNAL_ALGORITHM_HPP

#include <algorithm> // copy, ranges::copy, ranges::for_each
#include <concepts>  // assignable_from, predicate
#include <iterator> // cbegin, cend, input_iterator, iter_reference_t, iter_value_t, output_iterator
#include <ranges> // ranges::begin, ranges::borrowed_iterator_t, ranges::end, ranges::forward_range, ranges::input_range, ranges::iterator_t, ranges::range_value_t
#include <type_traits> // is_same_v
#include <vector>      // vector

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
    if constexpr (std::is_same_v<T, typename std::iter_value_t<In>>)
        std::copy(begin, end, out);
    else
        while (begin != end)
        {
            typename std::iter_reference_t<In> const value{*begin++};
            flatten<T>(std::cbegin(value), std::cend(value), out);
        }
}

/** @example algorithm/hello_world.cpp
 * This is an example of how to use the flatten() function.
 *
 * It outputs "Hello, World!"
 */

/**
 * @brief Extracts elements from nested containers.
 *
 * @tparam T type of the elements to be extracted.
 * @tparam In Type of the input range.
 * @tparam Out Type of the output iterator.
 *
 * @param range Input range of elements to be extracted.
 * @param out Output iterator to store the extracted elements.
 */
template <typename T,
          typename T2 = T,
          std::ranges::input_range In,
          std::output_iterator<T2> Out>
requires std::assignable_from<T2 &, T>
void flatten(In range, Out out)
{
    if constexpr (std::is_same_v<T, typename std::iter_value_t<In>>)
        std::ranges::copy(range, out);
    else
        std::ranges::for_each(
          range,
          [&out](auto const &value)
          { flatten<T>(std::cbegin(value), std::cend(value), out); });
}

/** @example algorithm/hello_world_ranges.cpp
 * This is an example of how to use the flatten() function, using ranges.
 *
 * It outputs "Hello, World!"
 */

/**
 * @brief Checks a value against a range of predicates and returns a vector of
 *        iterators to the satisfied predicates.
 *
 * @tparam T The type of the value to be checked.
 * @tparam In The type of the range of predicates.
 * @param value The value to be checked.
 * @param range The range of predicates to apply.
 * @return Vector of iterators to the satisfied predicates.
 *         Iterators are @c std::ranges::dangling if @p range does not model
 *         @c std::ranges::borrowed_range.
 */
template <typename T, std::ranges::forward_range In>
requires std::predicate<std::ranges::range_value_t<In const>, T const &>
  std::vector<std::ranges::borrowed_iterator_t<In const>> constexpr classify(
    T const value, In &&range)
{
    std::vector<std::ranges::iterator_t<In const>> result;

    for (auto it{std::ranges::begin(range)}; it != std::ranges::end(range);
         ++it)
        if ((*it)(value))
            result.emplace_back(it);

    return result;
}

/** @example algorithm/classify_fizzbuzz.cpp
 * This is an example of how to use the classify() function to write FizzBuzz
 * numbers.
 */

/** @example algorithm/classify_dangling.cpp
 * This is an example of how the classify() function returns
 * @c std::ranges::dangling when @p range is a temporary.
 */

/**
 * @}
 */

} // namespace exptl

#endif // #ifndef EXPTL_INTERNAL_ALGORITHM_HPP
