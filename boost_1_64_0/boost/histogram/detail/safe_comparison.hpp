// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_SAFE_COMPARISON_HPP
#define BOOST_HISTOGRAM_DETAIL_SAFE_COMPARISON_HPP

#include <boost/mp11/utility.hpp>
#include <boost/type.hpp>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

template <class T>
auto make_unsigned(const T& t) noexcept {
  static_assert(std::is_integral<T>::value, "");
  return static_cast<std::make_unsigned_t<T>>(t);
}

template <class T>
using number_category =
    mp11::mp_if<std::is_integral<T>,
                mp11::mp_if<std::is_signed<T>, type<int>, type<unsigned>>, type<void>>;

// version of std::equal_to<> which handles signed and unsigned integers correctly
struct safe_equal {
  template <class T, class U>
  bool operator()(const T& t, const U& u) const noexcept {
    return impl(number_category<T>{}, number_category<U>{}, t, u);
  }

  template <class C1, class C2, class T, class U>
  bool impl(C1, C2, const T& t, const U& u) const noexcept {
    return t == u;
  }

  template <class T, class U>
  bool impl(type<int>, type<unsigned>, const T& t, const U& u) const noexcept {
    return t >= 0 && make_unsigned(t) == u;
  }

  template <class T, class U>
  bool impl(type<unsigned>, type<int>, const T& t, const U& u) const noexcept {
    return impl(type<int>{}, type<unsigned>{}, u, t);
  }
};

// version of std::less<> which handles signed and unsigned integers correctly
struct safe_less {
  template <class T, class U>
  bool operator()(const T& t, const U& u) const noexcept {
    return impl(number_category<T>{}, number_category<U>{}, t, u);
  }

  template <class C1, class C2, class T, class U>
  bool impl(C1, C2, const T& t, const U& u) const noexcept {
    return t < u;
  }

  template <class T, class U>
  bool impl(type<int>, type<unsigned>, const T& t, const U& u) const noexcept {
    return t < 0 || make_unsigned(t) < u;
  }

  template <class T, class U>
  bool impl(type<unsigned>, type<int>, const T& t, const U& u) const noexcept {
    return 0 < u && t < make_unsigned(u);
  }
};

// version of std::greater<> which handles signed and unsigned integers correctly
struct safe_greater {
  template <class T, class U>
  bool operator()(const T& t, const U& u) const noexcept {
    return safe_less()(u, t);
  }
};

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* safe_comparison.hpp
k66081pAKmWtSIIBTEcY6x6w4N8osqBk4zTrj4ewXJxPPIPIDL4RtED+5YhcPqy2nfqiKYng2Nofc6QSJO/EWsafAFxZl/480HIvzz42iD3u2uEgxA4RzClK9kXQbl+0YEL0QHmYoxEP1hmDWXqWhKZy0pB+lD/UutCxgIGBFJtSogg9cqVJ02xL0V1PiqUZbVNK8iuo7WPHkFmW5fgxJ0EubnLBe3jwlzOva9KkY7FPUn6Op3gmaXt2/4rEUSBzMhnbAnFFiuQj/tnlr2+a4A7k3jwl5EQEpEBNhDvmWnjIzPpooYwTfeukkVoLSsiPG/Q8maW4mw7+OTTIfUwW6ubIYAyqX3VyM9KKtHUfI4LG9JsGjQ+rK/fZpjo0/MI1zEoM3J120U6v/ThCccO/fNTX8kfgaMWj0eiPXBd/WUUWvqMA5Pgo0gtKR42s4gqhKAdyt2fr53PtZji6ftm3EC/bZ6zIrnNYYTCO0mOrdVURGiovr223O65brc3V1Xxz/+F372UiaEL794Q97peoyx7nrA75fOiEJjo5qvs/wzwJcivQZhLlwTRkAQ==
*/