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
mB+mF3Xokf4HlqiHD2gsUSrt85gjPjWo2KA1QXk+0ZigVBe3x/wzvajnYPu3bFPbfqOQP9k2tQ7v3X72EKFtKsYDgG1AK6zC7C3sd6bM+J3iHgelzYDVu6c7yYd3oiShlQg70XioeTn+F9UVNfa3QBPMy6r88LG/6QrxmD//GON5/8FEVe73N1Gs6Qc/bmQlnPyxnyky5XY+A9GPQ9nLmjZnSOqkqMqG0x6PQ9wix/9HEpuSTvP4eyzIaWIbyIzceELhaeMJhaeNJ9RyBuKw05UJjWD3CfmYj1aLgM8XG+QAn3/maX5un5enmVT2wcUGbcb+fzqq9FDNiCArA6oONTedVrYwaPVXAmULJl8ewheVyhBQt51XhNvrz6rq7b1FjbDg1iKDEq3y3wwUmBcMlrGciRUMq0afUjAG9X6OM6wvn2/Avviq/uyRf9Uf5n+DOv/um86VX5rJnaOBw/Wuj7E9doO3sd2yoREAzRv+/wJgTcc6GVHcN7VtNFRbSxFGGa2MbZrRjFivGY2Wbl9DL7zp9j9f5lEe72Xe0aMiR4oXcrz7kap6awgte9QkoX2EqjTmi3fSi0vliyrVSNnrh96actc2AA09v07BzZrn4LiARQ0q7zDl7joJhQ6xQjWbTiph5n6NNF/u1kr706ZzO8obmd6Se/Db3naUR9apYeaP+JT96i3vsqPXoY0mRG57pE/5t3zK91jX2EZz
*/