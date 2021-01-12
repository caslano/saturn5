/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_IS_CONST_MEMBER_HPP
#define BOOST_CLBL_TRTS_IS_CONST_MEMBER_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ is_const_member_hpp
/*`[section:ref_is_const_member is_const_member]
[heading Header]
``#include <boost/callable_traits/is_const_member.hpp>``
[heading Definition]
*/

// inherits from either std::true_type or std::false_type
template<typename T>
struct is_const_member;

//<-
template<typename T>
struct is_const_member
    : detail::traits<detail::shallow_decay<T>>::is_const_member {
    using type = typename detail::traits<
        detail::shallow_decay<T>>::is_const_member;
};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct is_const_member_v {
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
constexpr bool is_const_member_v = //see below
//<-
    detail::traits<detail::shallow_decay<T>>::is_const_member::value;

#endif

}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* none

[heading Behavior]
* `is_const_member<T>::value` is `true` when either:
  * `T` is a function type with a `const` member qualifier
  * `T` is a pointer to a member function with a `const` member qualifier
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` has a `const` member qualifier
* On compilers that support variable templates, `is_const_member_v<T>` is equivalent to `is_const_member<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`is_const_member_v<T>`]]
    [[`int() const`]                    [`true`]]
    [[`int() const volatile`]           [`true`]]
    [[`int() const & transaction_safe`] [`true`]]
    [[`int() const &&`]                 [`true`]]
    [[`int(foo::*&)() const`]           [`true`]]
    [[`int(foo::*)() const volatile`]   [`true`]]
    [[`int(foo::*)() const volatile &&`][`true`]]
    [[`int(foo::* const)() const`]      [`true`]]
    [[`int()`]                          [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int() &&`]                       [`false`]]
    [[`int(*)()`]                       [`false`]]
    [[`int`]                            [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`const int foo::*`]               [`false`]]
]

[heading Example Program]
[import ../example/is_const_member.cpp]
[is_const_member]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_IS_CONST_MEMBER_HPP

/* is_const_member.hpp
te673VT78I1SXxw/RNYFKNfvdwNHy30r8GwZz/lP1WdcoFPOPwM02tqfGir/B4GyXA/x+LSd7XQH8Azgr4EhOY+xPcySOmW5r7HcTNAkllvhUfutzh4lryuwA/s7sn8CsBvwW+z/q/Lrfj+15Oj9/gSPavfeHtt8z/ydXebBWTx+nQsslHYJrJD2aDSnX83pj3dJP4/TV3H6ah73wrZxbUcL5f0B948VtnFtZwv8VzP/NWaz
*/