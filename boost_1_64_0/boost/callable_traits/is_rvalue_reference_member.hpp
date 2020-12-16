/*

@Copyright Barrett Adair 2015-2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_IS_RVALUE_REFERENCE_MEMBER_HPP
#define BOOST_CLBL_TRTS_IS_RVALUE_REFERENCE_MEMBER_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ is_rvalue_reference_member_hpp
/*`[section:ref_is_rvalue_reference_member is_rvalue_reference_member]
[heading Header]
``#include <boost/callable_traits/is_rvalue_reference_member.hpp>``
[heading Definition]
*/


// inherits from either std::true_type or std::false_type
template<typename T>
struct is_rvalue_reference_member;

//<-
template<typename T>
struct is_rvalue_reference_member : detail::traits<
    detail::shallow_decay<T>>::is_rvalue_reference_member {

    using type = typename detail::traits<
        detail::shallow_decay<T>>::is_rvalue_reference_member;
};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct is_rvalue_reference_member_v {
    static_assert(std::is_same<T, detail::dummy>::value,
        "Variable templates not supported on this compiler.");
};

#else
//->
// only available when variable templates are supported
template<typename T>
//<-
BOOST_CLBL_TRAITS_INLINE_VAR
//->
constexpr bool is_rvalue_reference_member_v = //see below
//<-
    detail::traits<detail::shallow_decay<T>>::is_rvalue_reference_member::value;

#endif

}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* none

[heading Behavior]
* `is_rvalue_reference_member<T>::value` is `true` when either: 
  * `T` is a function type with a '&&' member qualifier
  * `T` is a pointer to a member function with a '&&' member qualifiers
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` has a '&&' member qualifier
* On compilers that support variable templates, `is_rvalue_reference_member_v<T>` is equivalent to `is_rvalue_reference_member<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`is_rvalue_reference_member_v<T>`]]
    [[`int() const &&`]                 [`true`]]
    [[`int(foo::*)() &&`]               [`true`]]
    [[`int() const`]                    [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int(foo::* volatile)() const`]   [`false`]]
    [[`int() const`]                    [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int() &`]                        [`false`]]
    [[`int(*)()`]                       [`false`]]
    [[`int`]                            [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`const int foo::*`]               [`false`]]
]

[heading Example Program]
[import ../example/is_rvalue_reference_member.cpp]
[is_rvalue_reference_member]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_IS_RVALUE_REFERENCE_MEMBER_HPP

/* is_rvalue_reference_member.hpp
11d359Xlx9rBL9AjmnNO/RKoPnjfbXzvN7pO6HTJ5jXMUeHe3mZ1r9Hx++lrE+ESf5PvfUXHTzfj9zGPW12J/4JXfDl/zGtVqNif1nWgMn2KT/xkr+t1Z4m/0vt+Qhrr+4nyvZ8Q1/p+Yt4/JF7N949hxN0n8Z4x0w4w01rfP7zvF8St/n6h1wmMkP1+ULWmDoco3+vvTq0Lva6V6dW970D9vafCrL8zmN/8p6+XTfyujUu9wpIDXC/Vn75e1vecH+FK5Ec0RrMH50fLX+X80A+B5rNYHmbvuivb0fpYDpQ0W1Uks4zXofqc0Xm18q5XJNTniGlvW6WOROtrXT+xvynvLW5A9bmi0zX3rx/me3N9xL6dXzbUU6g+R3S6pt7XPvNafK7YLlX58o6RaS/2XBj2f7PhFok3jefXzqwq3Ni8138u4azRTj0LU5578Bp0T4TnXrzc929Y+/f2dL3J874+6vpAoL4+Bjj+GQGO/x64TVmNUR34WNdKGbt6NKFt5xnjgja+3+XNh8c+e+qx1mNXM8Ld4WeXZt35bdMZPz29aVjccQXfdDvwsSirMS2Zh24+Y0OHXC/kekfdEOml3/tIgc3hkTAFXgWHwAEwBw6EeTAVlsDBcDZMg+fCIXAJHAaXw6PhKjgSlsF0+DY8Fv4Ej4cNKcM42AWeAofALJgFc+AcOBkuhVPh3XAGfAkWwY/hbPgdnAMj2L+5sA08E/aG8/j/KLgAToDnwxy4CE6CS2ApnA0XwDnwWrgU3gGXwQfgFXAjvBJuhVfB3TL/Xz9zwDr6ehyJXoYq/V5Aa7ha+7UMZsJ74WS4Ds6A6+E8eD+8HD4Eb4YPw3u0fQN8DD4FH4c74Gb4NXwW/gA3wZ/hbbBC7Po9iMr7BKyry+n9HsQb+n2ct2AafBsOh9vhcfAdOBG+C6fDHXA+/ABeBT+CH8AvIKq+Nv2jrzX6uurvn8b6vZgmsCOMhZ1hR3gkbArHwxbaT63gebA1XAQT4GLYFl6r492h4z2t422G8bBc57sDtoe7YAdPfZYx1y2Me2ZUP97qP9bKGKvP+Ko5trqdvGL8xlZ3ucNK6qi+aE6JPcZqiy222GKLLb+zdybgURRZAK6eXMiZBJjEAAECyA3hviUgNwJBUZDDEEggkZDEJEBQVnFR8UDF9cKb9RZQWcRrRUVBwRtXRNZrEdF1PZHDa13df968qfRMZiTuqt+639RH5aeqXlVXV1XXdNerfh11URd1URd1URd1UVcT96vo/xeVlOX9DHv/ffr/86ztP/m2grgEtef2HX4j/2nxRUAnk5uXJwd362ByTZquM/cTuQ9NPUpui0QJtGvNpIkOzNpEWiRpY22aV8oZR7i3hPebxrIbII71uTaBfLgim+9FkUs1XrUh9bCES0wyKzS9TItqOjROVWVy7Pc3L5Rwa5PGunAc4W2JrFHi0d3K/4fUSG+GnSW7DowuL8jG0qIgO2H7Yoy4WtRfIuAD5Cs9EGjjvMKFYdpY21HljrZtdaGEPyGdL7Xjp+PDtTH5bBuPJ3y+hL+gn9GkyhGsPTCro0nT9fplInuQ/mDvPn42PrRtfefymcglq86djAdF30+NurnkT7O61E0in+Lq2zxrI6vxQauvJVy9LDsWdOzVk/S2/rCVr2ffLRlFP96IH1nD/swK6c9REfrzgjgj7jl8A/xW/Eus6W8+GOjP+SXua6aT9qfafFO5c81AM8DadzvnkC/uKHc/2mvsLyL/kEnkbxb+BHpQ+tiWlRzaj9qGtJaU25g2rGvbrfUh7TMtY6eUsYT1+AG27bNFpid5WvnlbFx/1muPCR0L0rcDJH0CYavznl+qdRlH+g9ynK6kx9s=
*/