// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_COMMON_TYPE_HPP
#define BOOST_HISTOGRAM_DETAIL_COMMON_TYPE_HPP

#include <boost/histogram/detail/detect.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>
#include <tuple>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {
// clang-format off
template <class T, class U>
using common_axes = mp11::mp_cond<
  is_tuple<T>, T,
  is_tuple<U>, U,
  is_sequence_of_axis<T>, T,
  is_sequence_of_axis<U>, U,
  std::true_type, T
>;
// clang-format on

// Non-PODs rank highest, then floats, than integers; types with more capacity are higher
template <class Storage>
static constexpr std::size_t type_rank() {
  using T = typename Storage::value_type;
  return !std::is_pod<T>::value * 10000 + std::is_floating_point<T>::value * 100 +
         10 * sizeof(T) + 2 * is_array_like<Storage>::value +
         is_vector_like<Storage>::value;
  ;
}

template <class T, class U>
using common_storage = mp11::mp_if_c<(type_rank<T>() >= type_rank<U>()), T, U>;
} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* common_type.hpp
Dk8iE/fixYK9qge557lSc56TFs4pY5TjHvHK3QyV7OnKKkbI6LulLtnzNzaDkKFsFnhR9UJztCHlcVHlxFPv/12FzWl2OSpVWdPhSqJpTFQkR+sGnbtk3zjeaerO8nfFSp6XKv81tvwL8pbP/mH5xr6QsX9hS39557XM0kCf6dgd/+tJuzV131NjQiWbkOWREqSU4I3MVCLM4npQ9z1vnTlNpmADaGpxBdUh7mgH0w+7O9Jf
*/