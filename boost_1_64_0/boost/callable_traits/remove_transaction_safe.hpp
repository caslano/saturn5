/*
@file remove_transaction_safe

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_REMOVE_TRANSACTION_SAFE_HPP
#define BOOST_CLBL_TRTS_REMOVE_TRANSACTION_SAFE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(remove_transaction_safe)
BOOST_CLBL_TRTS_SFINAE_MSG(remove_transaction_safe, cannot_remove_transaction_safe_from_this_type)

//[ remove_transaction_safe_hpp
/*`
[section:ref_remove_transaction_safe remove_transaction_safe]
[heading Header]
``#include <boost/callable_traits/remove_transaction_safe.hpp>``
[heading Definition]
*/

template<typename T>
using remove_transaction_safe_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::remove_transaction_safe,
        cannot_remove_transaction_safe_from_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct remove_transaction_safe_impl {};

    template<typename T>
    struct remove_transaction_safe_impl <T, typename std::is_same<
        remove_transaction_safe_t<T>, detail::dummy>::type>
    {
        using type = remove_transaction_safe_t<T>;
    };
}

//->

template<typename T>
struct remove_transaction_safe : detail::remove_transaction_safe_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`

[heading Constraints]
* `T` must be one of the following:
  * function type
  * function pointer type
  * function reference type
  * member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Removes the member `transaction_safe` specifier from `T`, if present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`remove_transaction_safe_t<T>`]]
    [[`int() const transaction_safe`]   [`int() const`]]
    [[`int(*)() transaction_safe`]      [`int(*)()`]]
    [[`int(&)() transaction_safe`]      [`int(&)()`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)()`]]
    [[`int() const`]                    [`int() const`]]
    [[`int(*)()`]                       [`int(*)()`]]
    [[`int(&)()`]                       [`int(&)()`]]
    [[`int`]                            [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/remove_transaction_safe.cpp]
[remove_transaction_safe]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_REMOVE_TRANSACTION_SAFE_HPP

/* remove_transaction_safe.hpp
E5D3GGmC8ADV83U9v4UVbk3W49qnkA/x1Ujg0cG28rqJtIDqrTKICUxb0aY2ewAW28DeGZY1+mXnd5wFzUP6LF9y3Rgh+8VtbUcYpPTknR+7hWRTYnyUZm9m20+6yNahXeWugZmmOt+uYBQOhn3UWretKljmRM26KOLB7TnNKUILnDfakEj6Ps1r1EYeBD7bnNdkW/t6Yn2FX4jXl5ANOy+4sn0Ans5uScwgxwVKzw2q1k1uJWbZx1wcDMUuU4Cg2RyKAx9e3qsy5JJNKS//rOCykhS6Fp7zUm2tG/4Eb6vMuvzk0arGejKwKHtBPaUe3nj0QyiGHd1L4rn6LWvSKVwvAxirJ9N8n+Z9gufi9dW7PfPhBbMACV2gPq+XsRKPg/XohQiv7lBkAQoXQ61vBKjwkv6c++5aSNA8JgVJ7vp06bIfCTr8bIQDYWRd670cySL+DN6syHXCM/r4OUH+chs2InUtZ/hllhCRam3Ze4nBhhkzhDnH5saQ+OefNiFovk1adwWRSNo2l8mqnjoHkQ5eLWdfKPk2TCDh9wG/XY7Nn8zwiR0gaTWs+g==
*/