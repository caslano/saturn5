// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_WEIGHT_HPP
#define BOOST_HISTOGRAM_WEIGHT_HPP

#include <utility>

namespace boost {
namespace histogram {

/** Weight holder and type envelope.

  You should not construct these directly, use the weight() helper function.

  @tparam Underlying arithmetic type.
*/
template <class T>
struct weight_type {
  /// Access underlying value.
  T value;

  /// Allow implicit conversions of types when the underlying value type allows them.
  template <class U>
  operator weight_type<U>() const {
    return weight_type<U>{static_cast<U>(value)};
  }
};

/** Helper function to mark argument as weight.

  @param t argument to be forward to the histogram.
*/
template <class T>
auto weight(T&& t) noexcept {
  return weight_type<T>{std::forward<T>(t)};
}

} // namespace histogram
} // namespace boost

#endif

/* weight.hpp
dDZcg8u3UKjJOtPL7Vbw+jOefHyoFTKFnussTFmj6aXOt29SAATaSvesNgmn3Z6sh/Nxw1Eyop5YAG6UCTh5yuX6SbPwm+qY0fLyTjoub/TQ8vIm/Xj0U+XAyPsbfMmKLS+/reeY+R204tVY2rQZ3DsVMwisFnmsC4wsTnFfH4ji9bdOR98POjVxR28xI08aFznefhB5erL65/X0DQ5n9Tgo1OR9/wZJ0ENg0XUHYOgm68twsxPnTPmajEe31baNQO+Ty12LTQtlCpUj6Txuh10nRVOQth6t0VmLLw7typt8rOy2zXPktykf6puN339Pa2M1latjTPLqCEPqv1BLAwQKAAAAAAAtZ0pSAAAAAAAAAAAAAAAAFQAJAGN1cmwtbWFzdGVyL3BhY2thZ2VzL1VUBQABtkgkYFBLAwQKAAAAAAAtZ0pSAAAAAAAAAAAAAAAAHQAJAGN1cmwtbWFzdGVyL3BhY2thZ2VzL0FuZHJvaWQvVVQFAAG2SCRgUEsDBAoAAAAIAC1nSlJS5NjOWgkAAF8VAAAnAAkAY3VybC1tYXN0ZXIvcGFja2FnZXMvQW5kcm9pZC9BbmRyb2lkLm1rVVQFAAG2SCRgrVhrb9s4Fv28/hVEWkziXUtuu9jFTHeyWNdxGmNcJ7Cd
*/