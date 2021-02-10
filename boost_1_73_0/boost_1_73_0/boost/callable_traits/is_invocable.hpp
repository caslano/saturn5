/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_IS_INVOCABLE_HPP
#define BOOST_CLBL_TRTS_IS_INVOCABLE_HPP

#include <boost/callable_traits/detail/core.hpp>
#include <boost/callable_traits/detail/is_invocable_impl.hpp>

namespace boost { namespace callable_traits {

//[ is_invocable_hpp
/*`[section:ref_is_invocable is_invocable]
[heading Header]
``#include <boost/callable_traits/is_invocable.hpp>``
[heading Definition]
*/

// inherits from either std::true_type or std::false_type
template<typename T, typename... Args>
struct is_invocable;

// inherits from either std::true_type or std::false_type
template<typename Ret, typename T, typename... Args>
struct is_invocable_r;

//<-
template<typename T, typename... Args>
struct is_invocable : detail::is_invocable_impl<T, Args...>::type {
    using type = typename detail::is_invocable_impl<T, Args...>::type;
};

template<typename Ret, typename T, typename... Args>
struct is_invocable_r
  : detail::is_invocable_r_impl<
        typename detail::is_invocable_impl<T, Args...>::type, Ret, T, Args...>::type
{
    using type = typename detail::is_invocable_r_impl<
        typename detail::is_invocable_impl<T, Args...>::type, Ret, T, Args...>::type;
};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T, typename... Args>
struct is_invocable_v {
    static_assert(std::is_same<T, detail::dummy>::value,
        "Variable templates not supported on this compiler.");
};

template<typename Ret, typename T, typename... Args>
struct is_invocable_r_v {
    static_assert(std::is_same<T, detail::dummy>::value,
        "Variable templates not supported on this compiler.");
};

#else
//->
// only available when variable templates are supported
template<typename T, typename... Args>
//<-
BOOST_CLBL_TRAITS_INLINE_VAR
//->
constexpr bool is_invocable_v = //see below
//<-
    detail::is_invocable_impl<detail::traits<T>, Args...>::type::value;
//->

// only available when variable templates are supported
template<typename Ret, typename T, typename... Args>
//<-
BOOST_CLBL_TRAITS_INLINE_VAR
//->
constexpr bool is_invocable_r_v = //see below
//<-
    detail::is_invocable_r_impl<
        typename detail::is_invocable_impl<T, Args...>::type,
        Ret, T, Args...>::type::value;
#endif

}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* none

[heading Behavior]
* standalone c++11 implementation of c++17 `std::is_invocable`, `std::is_invocable_r`
[note ref-qualified overloads of `operator()` with different signatures are not handled correctly yet.]

[heading Example Program]
[import ../example/is_invocable.cpp]
[is_invocable]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_IS_INVOCABLE_HPP

/* is_invocable.hpp
mPypvGRirB90WPWTjiSedIpWEYXhYPXNa5Oc7uzXxntBliN7GSajDWM+dXaka4A5y6BF5+t3vqOPurHXq9yzgB6/b5s6A9wvPY9n+sZZwNQOZut9KWBvIc0VHAbhKae8w42De0TlbyUjzP+u2faMRn1yHKd3bFo76NY8YfVwBnNL9po59VguX1zmdeySFLWsdO9f01pybzJ9LYoqOUPDnwYD4Iy7SMoMDkDneocJna7UYFDx4qHGrznOsbIXrhXgjAFT4zKGBwCEFN8JGvsNGKhY7HC1n3pO3RI4bG17/tj7NkSEA3LfTa+fH1o2RkloUccjt2X2bStvEZGbNDflbPRmIIVqLrjFArDqGxYA2NpUp8rCT1rpSoTc8P8gOAtyq9PQR93utDuarVqXxrd89tj8+wlz67GyQLqBTaKq6Oo03UDYCIceKo32T21RPtW3zMglfa0cwu+LdSW959QlTNNA34snnHzCJqlBtynmUZjASBMwpbGyvqsGWwiTPD6d3fa1cvSvi9Nq29uoGe5O5shqJ2m/nq49NKrP3+R9tpgbe/WnM/55djufXr85ojt9AEcUAVFjZbyKQli1/pmgTDhDzCVR0vmLWlcYA96ym3uVHroYB6MjHTXjGoI6ad54rcVFUw+PqL5E4EFj
*/