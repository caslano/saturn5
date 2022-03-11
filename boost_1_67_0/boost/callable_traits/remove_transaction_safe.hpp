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