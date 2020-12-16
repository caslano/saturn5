// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_ACCUMULATOR_TRAITS_HPP
#define BOOST_HISTOGRAM_DETAIL_ACCUMULATOR_TRAITS_HPP

#include <boost/histogram/detail/priority.hpp>
#include <boost/histogram/fwd.hpp>
#include <tuple>
#include <type_traits>

namespace boost {

// forward declare accumulator_set so that it can be matched below
namespace accumulators {
template <class, class, class>
struct accumulator_set;
}

namespace histogram {
namespace detail {

template <bool WeightSupport, class... Ts>
struct accumulator_traits_holder {
  static constexpr bool weight_support = WeightSupport;
  using args = std::tuple<Ts...>;
};

// member function pointer with weight_type as first argument is better match
template <class R, class T, class U, class... Ts>
accumulator_traits_holder<true, Ts...> accumulator_traits_impl_call_op(
    R (T::*)(boost::histogram::weight_type<U>, Ts...));

template <class R, class T, class U, class... Ts>
accumulator_traits_holder<true, Ts...> accumulator_traits_impl_call_op(
    R (T::*)(boost::histogram::weight_type<U>&, Ts...));

template <class R, class T, class U, class... Ts>
accumulator_traits_holder<true, Ts...> accumulator_traits_impl_call_op(
    R (T::*)(boost::histogram::weight_type<U>&&, Ts...));

template <class R, class T, class U, class... Ts>
accumulator_traits_holder<true, Ts...> accumulator_traits_impl_call_op(
    R (T::*)(const boost::histogram::weight_type<U>&, Ts...));

// member function pointer only considered if all specializations above fail
template <class R, class T, class... Ts>
accumulator_traits_holder<false, Ts...> accumulator_traits_impl_call_op(R (T::*)(Ts...));

template <class T>
auto accumulator_traits_impl(T&, priority<1>)
    -> decltype(accumulator_traits_impl_call_op(&T::operator()));

template <class T>
auto accumulator_traits_impl(T&, priority<1>)
    -> decltype(std::declval<T&>() += 0, accumulator_traits_holder<true>{});

template <class T>
auto accumulator_traits_impl(T&, priority<0>) -> accumulator_traits_holder<false>;

// for boost.accumulators compatibility
template <class S, class F, class W>
accumulator_traits_holder<false, S> accumulator_traits_impl(
    boost::accumulators::accumulator_set<S, F, W>&, priority<1>) {
  static_assert(std::is_same<W, void>::value,
                "accumulator_set with weights is not directly supported, please use "
                "a wrapper class that implements the Accumulator concept");
}

template <class T>
using accumulator_traits =
    decltype(accumulator_traits_impl(std::declval<T&>(), priority<1>{}));

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* accumulator_traits.hpp
DV2BsZpdQINHQEFzJWSZfi5z84X2Xiqwx7KBVXCVTcbegRanPlyawwC9YBB2RikDe9YEdikD+2LkPsCuUMAYDvDnswDN9wHN1D/ai0qeyD0TyRTUJhPqTIZ6075Q8xRUvI5RI4N2hw6TwUniuD0fZe9nF7tZTLDrMz67jyOjVDu5s5jM0rgzGLXWniFSiZDOVzaWGQatn1texT9gwEuWO9W5BEZGvkeRj0tSyV6XzkK/8ZHcEmY8wPP7JAYHsjQNN9OMj2kBu4AgEpGWUG5aLUiipUJeHKQKWXgk79C4YlF33sfLbZ9F9wt6pQvqxGG+Dtwn54yjeXHZEAbC84xYfAy9sPBvbONukvL/FST/n6e7qZ17QYfykePhw7Gtx8MY6qgxwVq7JXCScYtZwxm+WtTwPF3DyYqM3p8QT+nwCjKK/d2iqYYLG85WTemdjd/FKD3yBG8IaVp2Ha30tZ2GMe/IBn76bwzcOopnmDfl9og8qC0emWAqIebJawwrJaJQl1ETfgrtSnutV70J9lpQ8dTkKqOtWaEVvJOqvY36D2c0sPXR2+OllZA3DEWz1zd1NAyQ6OCu+hnFv2xqxwr03Cm08e5wQi1JmPBNdXRJddHrREcX2Gn36cN4mAGiMRvnH99OOyTZnqgnoT0ElWwy6tbTOh9vfjrait9qWvHOoJenqCdhEYHn7NAwNi++5mTTAvgE3wTZifN9vwQ9DJDGcDGDtZfHKYuz8+yeULk95EpnJwjpZGM2Ji+TjdBmsRHa4UcrOx0kpb71Yi0dPU0M6WFeQFQg19crJXmUiDRUA0YUJ9D/v50o1yD5dVHYwRmyTnO5Tg+cY44iXaszVa3cuAR0jHSf9KhcjEFyrO8BHA840YYe7TzgbfpJG/AOfgLTjZyHIAl2G3MDXapMHGqMNzw2ly3kpBfAOI+5bF22Zk9U7bB5fHNlnX7Jdeqm6zQhVqk7x2qakQB9NiXlFCg7OGo0rk6qkJZwdl9N5GHhOYX2U71swlbixhD7WO4v0aILvRUqy+LdVY/IyNOLsTO0eZ1HfHO+DjzWI8LSDoEpLK5anVS1PGKGTECkLyuO2G3edpLhv+2j9+dzfMcbxQ+R7sdYJG3W6yti5yOY8WAhrN3rIPnJMvlsnXxcLDkllhkGgkB0hr4yw+U6Q34sQzuYuDzvFcUxEk8PovCBpaZmhc+KQU+SepLcDm6w0jz6+lFS0vJAukoNpYfIjXy6+Cd7VwIYZXGFd7ObZCEJu8gGAkSJJmgkQaMbNEjQAAkBRAku2cVy1dbjN1JFTABbBOmCzfITta316G21tvbSVguoWLNESEDlEEUEFVBLJ6wgRAvh3H7vzT//HgQE1N4Lm/3/mTfXmzdv3rx582bredwSda7sBPzBxfwfUjZLcj6x5mtyhfUQ8bbOnAF7zPczkvKoyBt7m64qai+okUeOKfzeHp9EogeN2OpS+t6PGAvuOgemT87N61feMQ0zuNIaOXbye8uB+X6BtP3cUtdpgkpEZczJkudYJhsU+3nd+RvtH2v4J8j2bCG/sjD9Ej+61lxT7wSMoc+Hzr2EV6w+8fh1jGPGlHPB0/jLLSmkag7rxXHKIeRi5YkpmxF1Q3feN84DBF0yP7Un9fS4yxir7PUIbgYMf6Ie0SP/kwjoQRdiB/CrO/VNrCsZyCITb8j4DRyOrsGGwd+QGeFTbxc/7cdOa9FLA7lOlBwto8E8FVQyxz5MtvSP4+VaaZNz0ZmR2DUpMMtL0S/x2P/SaXz+rSp2fppKMxIIeZaXLP1AXYZ54FjancN7jjq7GETr8XXjm4VvHr6F4tXhxlo0CAyTSoAaIwQmTpqB2NUlAqr9XqhDlvg=
*/