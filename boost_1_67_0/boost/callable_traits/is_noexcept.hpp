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