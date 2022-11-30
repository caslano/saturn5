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
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
*/