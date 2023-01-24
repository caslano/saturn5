// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_ARRAY_WRAPPER_HPP
#define BOOST_HISTOGRAM_DETAIL_ARRAY_WRAPPER_HPP

#include <boost/core/nvp.hpp>
#include <boost/histogram/detail/span.hpp>
#include <boost/histogram/detail/static_if.hpp>
#include <boost/mp11/function.hpp>
#include <boost/mp11/utility.hpp>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

template <class T, class = decltype(&T::template save_array<int>)>
struct has_save_array_impl;

template <class T, class = decltype(&T::template load_array<int>)>
struct has_load_array_impl;

template <class T>
using has_array_optimization = mp11::mp_or<mp11::mp_valid<has_save_array_impl, T>,
                                           mp11::mp_valid<has_load_array_impl, T>>;

template <class T>
struct array_wrapper {
  using pointer = T*;

  pointer ptr;
  std::size_t size;

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    static_if_c<(has_array_optimization<Archive>::value &&
                 std::is_trivially_copyable<T>::value)>(
        [this](auto& ar) {
          // cannot use and therefore bypass save_array / load_array interface, because
          // it requires exact type boost::serialization::array_wrapper<T>
          static_if_c<Archive::is_loading::value>(
              [this](auto& ar) { ar.load_binary(this->ptr, sizeof(T) * this->size); },
              [this](auto& ar) { ar.save_binary(this->ptr, sizeof(T) * this->size); },
              ar);
        },
        [this](auto& ar) {
          for (auto&& x : boost::histogram::detail::make_span(this->ptr, this->size))
            ar& make_nvp("item", x);
        },
        ar);
  }
};

template <class T>
auto make_array_wrapper(T* t, std::size_t s) {
  return array_wrapper<T>{t, s};
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* array_wrapper.hpp
fJ89Oby5MJ+cIjlybAub6C2G4r2Ig8z6eDeBCnGM8wxew26of2UESNyN5PxFfnkQOjkKXXMyBt2JQMOz+2Mu8B4YoNEBhnNhO7BqK3IYyGopageuRQ9PfawPSxIFjO1BFhi6Ux8HKdRgl9QjogFPXn1wj4PWbM9GAkgUJsypXc5BklxJoBKwSA0R0YQEDy7Zi3g0Nkm0S+hVGlRVzi/Y2S3Z2FpGOd8Sg3mKtpiXo+vEF4rOiipXCD1qLOg5GqE/jNqlT6bLXCTW89aLDD4m8hvCfSuV26utHWrXbHyDbwOFAzPhFHP3bA8U4HH2HXlaGBwTAhp2s6lPXYMHtgheKFxsoUAhIcWhT/DQQV5lpYPuUYwKiNd9Zc/THV+QqJHf9VYg1rBwzzg8uN3zIVunJ/BLC+w+W0XWDQ4fVEqAZ8U9EQhcc86X3LNloMEdE070r4zOHi0uTnoPDu67SeguH2W/7xfDz3reosBmYCDsjhHIF5DGhelFkNig0HudoMvrzuTptcENWVcnj2ujeS+RpT3QcUY1CqvRF+g1YYfcXiDWnyzMwJyM2vp/Dzr+q2PIzfG/HEOc5zzskuMvoJNAw1THIti0I2r190AMmrCSj3mSFlhnODAVHFDLfN2fPDlT777lXryWMyTn7E3XzxCkjx/2gaWymiBS0SZCjlQmKKXARl6PXmVmJgTJBt14ZeaKTvZel55yceP0PGuC
*/