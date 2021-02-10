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
JiRKyLMyQHBKjucEcPbcSx50W/B8Ry7ldzF4P57OuLv8H3FgEQ/H4R4JLdPElyET+RAEuKKk4AMZzlQuQjhalWgYpF/lNECvsGI26kIJR897w5FncYw7N9hbnHBKBuRpq5tSXerxwc7LAqVGDYB2p5wJzXMrkPZbNVMTI3dytDt/6iuXgcdEMDjEEWwTj8wTdc9+qybRlOAPyiD76vpacvVhwapLY26ltwrn1Dvp5glTKDgX2CAuP8hNQPG7GCiOsxEo0j5ufIxfdA+7h67Q+YRRF7A7J1Rd4lGtl/GcM56BQ7XRZHs41thbbvHVVA28q8of8VVYJOA0oXDdxLmhPchRiVBlFxNyRpTZ9ebIsMHN89QqszdwMLFM1/RFYWMWV6I2xmxGy52hX7OBuchzANluWj8bl9P0f9jT7z9uAjscJ/1L1Ea9vYHmR8l9aTONRJIsBLhvXKQ+onw+zbExXjtQSi5H7RohwxhWODzA2Ttl83Do/VoYx0Pu9O/JoHd62pv1qtK02aZblaoFnQ1HA8ozMDP+0YKjDyv4CPHYWc5Kzq4u+txZgns0/HFQVmYG9I+amD1u69XlaNwDC9ofNaCfqjT0QODwHaNv+3aDBMPZRK9zy91IMSPg4b1m2OIicTnMVBVARXJRXNeN
*/