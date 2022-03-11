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
+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
*/