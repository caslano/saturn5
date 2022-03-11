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