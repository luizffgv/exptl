#ifndef EXPTL_INTERNAL_ALGORITHM_HPP
#define EXPTL_INTERNAL_ALGORITHM_HPP

#include <concepts> // assignable_from
#include <iterator> // cbegin, cend, input_iterator, iterator_traits, output_iterator
#include <type_traits> // is_same_v

namespace exptl
{

template <typename T,
          typename T2 = T,
          std::input_iterator      In,
          std::output_iterator<T2> Out>
requires std::assignable_from<T2 &, T>
void flatten(In begin, In const end, Out out)
{
    if constexpr (std::is_same_v<T,
                                 typename std::iterator_traits<In>::value_type>)
        while (begin != end)
            *out++ = *begin++;
    else
        while (begin != end)
        {
            typename std::iterator_traits<In>::value_type const &value{
              *begin++};
            flatten<T>(std::cbegin(value), std::cend(value), out);
        }
}

} // namespace exptl

#endif // #ifndef EXPTL_INTERNAL_ALGORITHM_HPP
