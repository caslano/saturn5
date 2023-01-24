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
gVekjhHvfhD0QtR/3QGyISzrAzLxTtkvQi/TphogKeUExTeykhAZX947Eb0jG54j78jwR7h3BMpIxw+Sd+Qgdhu75+0f4W4WaurmZIo5ZJ8AECzv0/J5E1lFXgt0uTx/UAk+XKspU52sdZm0BpeJ1VS0E6MP0a09FTuT4dB2RHGcFGha2nAbBSFSP7Rvlh2mfmA0o+kgmMCWEtOm4MrJK8i3waeJYQNGZSpelPssSEDk115elFssaGWEdwyjCUE4ugCyhuPknfwSbQvLNH3KP6D5JnHK9TKagD8lCePcbh8PzhQ6T1y1RQ4artgizU/jos2X7l4Bw5qS7xBt2ZyzP5xNpshrVSeKgCaWePw/mYSYeegxyCObtNkgYnuVkvCKsqLhlbS2kohAJScC3XBIGZWszr5F3BTZ0adOeqW3KVKqwjpVqhOlAZ7w3SJnISwc7HuI39hADDZAh9oznWltFRomY7WLPe2eBg9ZJW9nECRvPXeirNUag7Ku5MGEAB6MOgAQvTaSbEFrZd5QiHR1KHYUW6t5RccrZmU7xVI23NeeInvkDFYXzcoDMbo7Y6VdDLbLnpT1fj0pdsWTcra37EnZyT0pagiixpEiNxken3uWO1JK4du/sG/HnE1Y9HNtQMxZxmca0MZPjgXVVnaZIM72ks/KIWkKuuEb4QPkP61TMAEcKTe9yRrlCivvRQFSbZkEdzkMvhRGKe/q
*/