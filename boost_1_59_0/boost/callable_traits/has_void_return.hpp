/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_HAS_VOID_RETURN_HPP
#define BOOST_CLBL_TRTS_HAS_VOID_RETURN_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ has_void_return_hpp
/*`[section:ref_has_void_return has_void_return]
[heading Header]
``#include <boost/callable_traits/has_void_return.hpp>``
[heading Definition]
*/

// inherits from either std::true_type or std::false_type
template<typename T>
struct has_void_return;

//<-
template<typename T>
struct has_void_return
    : std::is_same<typename detail::traits<
        detail::shallow_decay<T>>::return_type, void> {};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct has_void_return_v {
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
constexpr bool has_void_return_v = //see below
//<-
    std::is_same<typename detail::traits<
        detail::shallow_decay<T>>::return_type, void>::value;

#endif

}} // namespace boost::callable_traits
//->


/*`
[heading Constraints]
* none

[heading Behavior]
* `std::false_type` is inherited by `has_void_return<T>` and is aliased by `typename has_void_return<T>::type`, except when one of the following criteria is met, in which case `std::true_type` would be similarly inherited and aliased:
  * `T` is a function, function pointer, or function reference where the function's return type is `void`.
  * `T` is a pointer to a member function whose return type is `void`.
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` function returns `void`.
* On compilers that support variable templates, `has_void_return_v<T>` is equivalent to `has_void_return<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`has_void_return_v<T>`]]
    [[`void()`]                         [`true`]]
    [[`void(int) const`]                [`true`]]
    [[`void(* const &)()`]              [`true`]]
    [[`void(&)()`]                      [`true`]]
    [[`void(foo::*)() const`]           [`true`]]
    [[`int(*)()`]                       [`false`]]
    [[`int(*&)()`]                      [`false`]]
    [[`int`]                            [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`void* foo::*`]                   [`false`]]
]

[heading Example Program]
[import ../example/has_void_return.cpp]
[has_void_return]
[endsect]
*/
//]

#endif

/* has_void_return.hpp
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
*/