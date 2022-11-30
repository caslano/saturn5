/*
@file is_noexcept

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_IS_NOEXCEPT_HPP
#define BOOST_CLBL_TRTS_IS_NOEXCEPT_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ is_noexcept_hpp
/*`[section:ref_is_noexcept is_noexcept]
[heading Header]
``#include <boost/callable_traits/is_noexcept.hpp>``
[heading Definition]
*/

// inherits from either std::true_type or std::false_type
template<typename T>
struct is_noexcept;

//<-
template<typename T>
struct is_noexcept : detail::traits<detail::shallow_decay<T>>::is_noexcept {
    using type = typename detail::traits<
        detail::shallow_decay<T>>::is_noexcept;
};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct is_noexcept_v {
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
constexpr bool is_noexcept_v = //see below
//<-
    detail::traits<detail::shallow_decay<T>>::is_noexcept::value;

#endif

}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* none
*
[heading Behavior]
* `is_noexcept<T>::value` is `true` when either: 
  * `T` is a function type, function pointer type, function reference type, or member function pointer type where the function has a `noexcept` specifier
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` has a `noexcept` specifier
* On compilers that support variable templates, `is_noexcept_v<T>` is equivalent to `is_noexcept<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`is_noexcept_v<T>`]]
    [[`int() const noexcept`]           [`true`]]
    [[`int(* const &)() noexcept`]      [`true`]]
    [[`int(&)() noexcept`]              [`true`]]
    [[`int(foo::*)() noexcept`]         [`true`]]
    [[`int() const`]                    [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int(foo::*)() const`]            [`false`]]
    [[`int() const`]                    [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int() &`]                        [`false`]]
    [[`int(*)()`]                       [`false`]]
    [[`int`]                            [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`const int foo::*`]               [`false`]]
]

[heading Example Program]
[import ../example/is_noexcept.cpp]
[is_noexcept]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_IS_NOEXCEPT_HPP

/* is_noexcept.hpp
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
*/