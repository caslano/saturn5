/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_HAS_VARARGS_HPP
#define BOOST_CLBL_TRTS_HAS_VARARGS_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ has_varargs_hpp
/*`[section:ref_has_varargs has_varargs]
[heading Header]
``#include <boost/callable_traits/has_varargs.hpp>``
[heading Definition]
*/


// inherits from either std::true_type or std::false_type
template<typename T>
struct has_varargs;

//<-
template<typename T>
struct has_varargs : detail::traits<
    detail::shallow_decay<T>>::has_varargs {

    using type = typename detail::traits<
        detail::shallow_decay<T>>::has_varargs;
};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct has_varargs_v {
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
constexpr bool has_varargs_v = //see below
//<-
    detail::traits<detail::shallow_decay<T>>::has_varargs::value;

#endif

}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* none

[heading Behavior]
* `std::false_type` is inherited by `has_varargs<T>` and is aliased by `typename has_varargs<T>::type`, except when one of the following criteria is met, in which case `std::true_type` would be similarly inherited and aliased:
  * `T` is a function, function pointer, or function reference where the function's parameter list includes C-style variadics.
  * `T` is a pointer to a member function with C-style variadics in the parameter list.
  * `T` is a function object with a non-overloaded `operator()`, which has C-style variadics in the parameter list of its `operator()`.
* On compilers that support variable templates, `has_varargs_v<T>` is equivalent to `has_varargs<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`has_varargs_v<T>`]]
    [[`void(...)`]                      [`true`]]
    [[`void(int, ...) const`]           [`true`]]
    [[`void(* volatile)(...)`]          [`true`]]
    [[`void(&)(...)`]                   [`true`]]
    [[`void(foo::*)(...) const`]        [`true`]]
    [[`void(*)()`]                      [`false`]]
    [[`void(*&)()`]                     [`false`]]
    [[`int`]                            [`false`]]
    [[`const int`]                      [`false`]]
    [[`int foo::*`]                     [`false`]]
]

[heading Example Program]
[import ../example/has_varargs.cpp]
[has_varargs]
[endsect]
*/
//]

#endif

/* has_varargs.hpp
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
*/