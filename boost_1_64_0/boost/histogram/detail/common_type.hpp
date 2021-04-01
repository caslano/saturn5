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
qDWfU7Lf6wK8lsh6Acv7yTx61qAC3HWJiHtrzOz3pqOeAyXazp/K8QQ6zdkSd0O43Hlw++g/sotOflJ7MmLGs1/MsE+TQdJPxkDKiXhIT43bajMNPtsmWisWoepo4pHjEfP7ByJ2ljpF3pniM5jZfTVK1ryR4pDYxk+9BpkKprhyThN567OclegWIEXsdz6hqX6hSdHl/enH8y4y5cXZrG6xXk5rPqE1BHAUi0bKqrw13KhTN7UG9hrG/q5G7NUIqwBBdaMYtL/unH3cFcXMz5zrF6RuZV98p9IC7M8q6FESVhPYp+SXoePAFSdeu5PFINZURtZOoo6KaoBR6CHGjblMIMd1vIpHQvlo6rUdo8EORLbstOHhxoK7JNUqk15nWw+KawkzeDypeH0dVv3as+P2GV4Kcuw0UG2t/GWUegsPSSst+0q8ZSUDHXEOiD1elPFskOfp33VPi2poXF6OLPZaEUgufrqws9pV89MD/LsxHHfs1ob8mRPXq8R7Ao3Ke2R1lqmiKw5r9V9fKLq74UWnGcM0MXIhZTyN4mTkPtJOSJq53i5N0w0/qQ==
*/