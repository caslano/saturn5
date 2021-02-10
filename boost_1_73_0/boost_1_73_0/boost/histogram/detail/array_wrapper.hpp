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
Hk6Qh1nsL2C517c0CDETd6oNcYjNASlhDvqrrHowSMCH+OFv6fXDwuwOpBCMRvHgmTh8fwY/x1gWLbtcDBxg8muvg+SWVaYgUK91uAaB7gLh+uKwb/Ns7xinQo5YF6xCuN19oAWN8G+HX20O+ed+X9L2uPOhYhYmWNmpCMdTd5tMkW5KF69ESb/TsCfsZqBTmaOIBZd5ukZi1/jwWNWXqbPWYkhxHr0NLW7rA2uXFcsROxW0y9+AaZAgtWhhhabxaCl+QdAeIpWTNNn/e5infYNbiBvBetlkyIsFKFXYesMkhGrhq1EESGZszAt9wmSRbpBraJ/jZrPQBpekhe2djDgaLJ77Y2JuPxbnfnKz8W9Ax26yLAXBg/3svsFdDulWWO0rqhBvOBoyevuaptyOmYzrxCPx5EtiNlTo6VIW98Doe/Jl75hV02kIm5OSaEEKqWQ9xIxONEdW0OR+8vXPwN4Pnzw8brd3QfECwhGl+2ivRIlfgs5bxv6NGptVqYlLtSA1UY3Bk7LDJC1ZA+4FvC6vFEEcJn1i0YCwUTEy9CiYm8RewU0K3bgwdCR+jhCDUpDEIsBPcoIYO9VZVynTX3ich/sIdAAfoe3DfdzfQc+UyLzY5iFOkYpfArOxZj5qDZyZVzbzLwGNg0Og
*/