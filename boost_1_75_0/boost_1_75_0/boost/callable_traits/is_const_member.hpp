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
QwpGRuIyI437sNzGFbu8ogqe3+fLEPdIU1PkqIJJrH6hliEWahlieU8tQ6RyzmVSwXDiiIUyR9yAHLE/dhabq1mlU2u6zc/mQ1j+9GXw7fHDeXDBgp7Qe+7+0cQXVCGJXRylskUKppPZotUrMr/Kiy16hd1p4gs68b5AB/YP9wrM7/2zhPbdxnzRf4BBVn4jzGA48XCNF1/s/TQY/5sKMAiq5FH5FqbyEQtc7c0CTbnzWsG93+iClFZAjXtfwz5RuwM36UMW8iai8pG3me+a7BuVX7kbovIf3+03Kr/B2BwDm3VMy8D+yEZcDpduXOLNkF7cSbgcLuN/BcUKEQOLkFr7lL9vp3fQ9bflWD6CDwJjEgSKSagtV5nYme6NmFjkTi8mtrTc4M293G5gaNLEKZyDwenFnF2RlKDRAVEqWIjf4FaqrDIKKqC7Ck8BxIXS5rvboNxg3NdoygvUKxIPxZgyBbc1jgm/xASTmehZ+PvSD80H7I/QzIToXMst8av3ov3Bmc/vl9K9DEXox+N7DaoIpKabUgyiBZTBQX6aonmaqjz1zY5lyk2GXFeqwbVGwPvl5G4OUbznkGpFVq27dWOzMlm1GXrMV1bKFC49SMgpDWBcDEHtsq10iKuhy6h6V0F4/OApTNooh1+ACjvYj3X6/MlRkwnHiqU3nqatCcXNbE04S8S4WLI9g1sTioGnZEw0cNZwCEne2DmN
*/