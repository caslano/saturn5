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
zIgqIEXBYr75Xn2w2byGsqiGjp+MeLatb1UugD9KNjvV2z0Hxo7BTj30AyDCLm84H4cXBYCJO01/fa7dM4Eb9QkWfSsAkYRVwjhK833ide/1gA/DYAIFZnkPqCY7v4zQr4PBr0jAyylkicMWw42kiwn4xQdg7cW3yiix9khHbCpOwdUbenmiMaMulM+VaIamoVHjRaxYmByq/FBY3Eohmtzgo6NZxy/71lpdnlWWYQTVrMCZSB/TCp44tp7krZP3GYf++9W5h1o2TefJbK3ApG0L13NgWr7LR/5Ffi9wMoyxhPMQ40JDy9/9G1R4oJihGXNKofY9X8WrhcQfz2MpMRzvVVH88erO+dfLbJjnNCJi5Esxjg5I1HOD9xnVB4MibPHMBY8TGhC2HaQkUX67/5n80+cKOZ1iCDxNqcMxnuwSOm5ArHaIFVroLvwQidfQ3UuftSR9iNlaXu/zDX3FwP079DX97CEjAsgNGXHUe3WkJSqgYkqec5akCTHBsmuDvAgSPHlBq454dG3nMD1bhJKGxQi9r13XbPQ/q8M8ZLz2CxVc6eCemblqcA==
*/