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
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
*/