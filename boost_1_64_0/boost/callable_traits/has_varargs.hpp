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
RrfSwzrMSi5ZM1Zmbafn9cG7MKImKw/42Tnt2rwD4ggay85ALyiYQyYi2I/Frqg1FAHBF4JwC5a0lGHbdgWArisESsD5yB1YVaaW/2Jx+nAozNpR1afvCEDlyQrij4NxC0aC5Ilh7Hhg2u4jKs5vWvBDfLANhqs5yvlyHLecEqkUaiwbPTfMTYmeArSORG6SjZzlIEHZoXlrEyYi6l15gfCcZ2eQMwls1Q9807sszaBRKdJ5rmOX4y3OsiqoOygXrvDuBqxepL1WWi3XU5Pk2r9kAigPJi/RZDRLyK5njdkT54LHDd3ItMef272mz5siczIkUQp9ToMp1eY7U9AaPQdgMcLw53AE9TCARpZgTbAZB0ZZv3ShPcCHMHZzu3QifuqwOKpKxd0V+yOs2sO7nFMXjVaamXXEh9TT8i2247jIyuX12AG0Ire1lTLTN/b9mMUQ5w0Nn/eHtyFytUIlycg24BuIAyOw9oTBZ6jXi6eHXu3HPVUtcCNYMCtITVMN2t7i5yVHL+ZmOAgzLQ9e8EsQT/XTiOlkAbNzDqAD2EEZMnvdo2lWBjBogg==
*/