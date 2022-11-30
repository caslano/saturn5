/*
 *
@Copyright Barrett Adair 2015-2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_IS_VOLATILE_MEMBER_HPP
#define BOOST_CLBL_TRTS_IS_VOLATILE_MEMBER_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ is_volatile_member_hpp
/*`[section:ref_is_volatile_member is_volatile_member]
[heading Header]
``#include <boost/callable_traits/is_volatile_member.hpp>``
[heading Definition]
*/


// inherits from either std::true_type or std::false_type
template<typename T>
struct is_volatile_member;

//<-
template<typename T>
struct is_volatile_member : detail::traits<
    detail::shallow_decay<T>>::is_volatile_member {

    using type = typename detail::traits<
        detail::shallow_decay<T>>::is_volatile_member;
};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct is_volatile_member_v {
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
constexpr bool is_volatile_member_v = //see below
//<-
    detail::traits<detail::shallow_decay<T>>::is_volatile_member::value;

#endif

}} // namespace boost::callable_traits
//->


/*`
[heading Constraints]
* none

[heading Behavior]
* `is_volatile_member<T>::value` is `true` when either: 
  * `T` is a function type with a `volatile` member qualifier
  * `T` is a pointer to a member function with a `volatile` member qualifier
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` has a `volatile` member qualifier
* On compilers that support variable templates, `is_volatile_member_v<T>` is equivalent to `is_volatile_member<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`is_volatile_member_v<T>`]]
    [[`int() volatile`]                 [`true`]]
    [[`int() const volatile`]           [`true`]]
    [[`int() volatile &&`]              [`true`]]
    [[`int(foo::*)() volatile`]         [`true`]]
    [[`int(foo::* const)() volatile`]   [`true`]]
    [[`int(foo::*)() const volatile`]   [`true`]]
    [[`int(foo::*)() const volatile &&`][`true`]]
    [[`int()`]                          [`false`]]
    [[`int() const`]                    [`false`]]
    [[`int() &&`]                       [`false`]]
    [[`int(*)()`]                       [`false`]]
    [[`int`]                            [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`volatile int foo::*`]            [`false`]]
]

[heading Example Program]
[import ../example/is_volatile_member.cpp]
[is_volatile_member]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_IS_VOLATILE_MEMBER_HPP

/* is_volatile_member.hpp
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
*/