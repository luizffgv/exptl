#include <array>
#include <exptl/algorithm>
#include <ranges>
#include <type_traits>

// true
static_assert(
  std::is_same_v<std::ranges::range_value_t<decltype(exptl::classify(
                   0, std::array{[](int v) { return v; }}))>,
                 std::ranges::dangling>);
