/*
@file is_transaction_safe

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE_HPP
#define BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ is_transaction_safe_hpp
/*`[section:ref_is_transaction_safe is_transaction_safe]
[heading Header]
``#include <boost/callable_traits/is_transaction_safe.hpp>``
[heading Definition]
*/


// inherits from either std::true_type or std::false_type
template<typename T>
struct is_transaction_safe;

//<-
template<typename T>
struct is_transaction_safe : detail::traits<
    detail::shallow_decay<T>>::is_transaction_safe {

    using type = typename detail::traits<
        detail::shallow_decay<T>>::is_transaction_safe;
};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct is_transaction_safe_v {
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
constexpr bool is_transaction_safe_v = //see below
//<-
    detail::traits<detail::shallow_decay<T>>::is_transaction_safe::value;

#endif

}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* none
*
[heading Behavior]
* `is_transaction_safe<T>::value` is `true` when either: 
  * `T` is a function type, function pointer type, function reference type, or member function pointer type where the function has a `transaction_safe` specifier
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` has a `transaction_safe` specifier
* On compilers that support variable templates, `is_transaction_safe_v<T>` is equivalent to `is_transaction_safe<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`is_transaction_safe_v<T>`]]
    [[`int() const transaction_safe`]   [`true`]]
    [[`int(*)() transaction_safe`]      [`true`]]
    [[`int(&)() transaction_safe`]      [`true`]]
    [[`int(foo::* const)() transaction_safe`] [`true`]]
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
[import ../example/is_transaction_safe.cpp]
[is_transaction_safe]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE_HPP

/* is_transaction_safe.hpp
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
*/