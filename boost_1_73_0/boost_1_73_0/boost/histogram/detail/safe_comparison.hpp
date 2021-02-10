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
KYdlK4Rv2jQNRgypDLo7GQyUt91ltlSe4FrAehlwj21Susxab8hSynC59VHXTBLdTqZ5PZjYvcBRJfcExxkYlurs1cKRegYTJfYPRTQd7SdXJkA1uo6rvjFL5ixhZDLQsTHx1EemVdR/gWLuI3s1dN9l42S6TQx9HorC3RZGIDffbMc2S/t3gg0J/6xreFZPadLln/WtS9Mj79l1GbDuVk2YamNMZn/u++y8rG+BRSWlhbC5jikszZ7xwJmGS56OOwigYw/VTbTzUsGCCGDpZ++5z84coJ95xkCd9QmiiWqw5zHgBJ2ILHgYM0RQu2b8YRnkeNIdWsy6pxjMiL7ucA3Pu3Vc1ZhJidZmsFcOfSLo4JCs713HoFN6jsMal8zgakapM0yq9zKTKuS3ySNKLibZ8caVUTE0Lw2fb7rVBfKkGnHsMHG8CwZDg+z5LUqk3EQdbB1ftE3XdVxK2Ew/PcMAnbEPEQUeJKrD3xTH6f7d7Pljx1IWSW6sYJBxQKxRSDBUYIQooHoZKCVA1C4D6w4d1WW1s8MShMYau6bnDG/M4PaK2SI3ygvsSQncjapXv1UGpBp2wE18HqHN/HQ1p4wiWis4qdVXAaxF6y8GpitT1q4AaxDKH6q6ATpVvRy7Fpv6rm3ndmj2lXfB
*/