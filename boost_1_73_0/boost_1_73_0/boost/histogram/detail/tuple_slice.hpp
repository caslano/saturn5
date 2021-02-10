// Copyright 2015-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_TUPLE_SLICE_HPP
#define BOOST_HISTOGRAM_DETAIL_TUPLE_SLICE_HPP

#include <boost/mp11/integer_sequence.hpp>
#include <tuple>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

template <std::size_t I, class T, std::size_t... K>
decltype(auto) tuple_slice_impl(T&& t, mp11::index_sequence<K...>) {
  return std::forward_as_tuple(std::get<(I + K)>(std::forward<T>(t))...);
}

template <std::size_t I, std::size_t N, class Tuple>
decltype(auto) tuple_slice(Tuple&& t) {
  constexpr auto S = std::tuple_size<std::decay_t<Tuple>>::value;
  static_assert(I + N <= S, "I, N must be a valid subset");
  return tuple_slice_impl<I>(std::forward<Tuple>(t), mp11::make_index_sequence<N>{});
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* tuple_slice.hpp
WQDvpa1F3FNuI5sfLE958X8vKkQyot6kd0WIML2X3bz2DU253sveXRtcaL8oA4kKwKdiA+Z2mPMIu4n3ohrkh4FqZL+XVwzVAPl7URGgp97VxO/z3B7KKJyLumBcGsq+/3NRCfgIuEMi+88xe8nyvAlbFylGxDnmYh27JtE7cS7qgOt7Y0gH/IVGnWQsAZxnejzZmYSI+V+7ycY6gFKFqoCiPsQZKTTuiWpgO6mLgu8MbxiooV6d8RxTjbHFcPvjSffavGNqS8lJuRD1g8tibPDADOP5hj9RnZQvMLesDqcBTUN1cbyQlwz2p2fdMFUeW3z7roooqgtPZacI4oWoKZT6NxeifvwysXq1vFoXwnFRvKwqk0tn2LdM73vRpMwHXClpGlh0pulgHJCVnR+HgtiO66rHNyvCcrwBUsALC6Lx4BQjkBSF3Rtv6lq2oexvlyJOfNVoOOpUI3iCDU3TkSKqrSMFiWrpixTdKYyv75DidVKUpxhOcSbqJz2keIooh4bXs1QTBdHQSgoK4VxCTrAUwYjDgs2FMVKDo+FQwdDqukyR6X5u1CViQDboZcDmSfWZHFvgagS+JDcyEJjN4ib4qNUxRS6m7t+C47auFzj1y9X113KzDRxgYFzFri9lTGk3cmW44GAJ1AtN
*/