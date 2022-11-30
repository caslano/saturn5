/*
@file add_transaction_safe

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_ADD_TRANSACTION_SAFE_HPP
#define BOOST_CLBL_TRTS_ADD_TRANSACTION_SAFE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(add_transaction_safe)
BOOST_CLBL_TRTS_SFINAE_MSG(add_transaction_safe, cannot_add_transaction_safe_to_this_type)

#ifndef BOOST_CLBL_TRTS_ENABLE_TRANSACTION_SAFE
template<typename T>
struct add_transaction_safe_t {
    static_assert(std::is_same<T, detail::dummy>::value,
        "transaction_safe not supported by this configuration.");
};

template<typename T>
struct add_transaction_safe {
    static_assert(std::is_same<T, detail::dummy>::value,
        "transaction_safe not supported by this configuration.");
};

#else

//[ add_transaction_safe_hpp
/*`
[section:ref_add_transaction_safe add_transaction_safe]
[heading Header]
``#include <boost/callable_traits/add_transaction_safe.hpp>``
[heading Definition]
*/


template<typename T>
using add_transaction_safe_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::add_transaction_safe,
        cannot_add_transaction_safe_to_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct add_transaction_safe_impl {};

    template<typename T>
    struct add_transaction_safe_impl <T, typename std::is_same<
        add_transaction_safe_t<T>, detail::dummy>::type>
    {
        using type = add_transaction_safe_t<T>;
    };
}
//->

template<typename T>
struct add_transaction_safe
  : detail::add_transaction_safe_impl<T> {};

//<-
#endif // #ifndef BOOST_CLBL_TRTS_ENABLE_TRANSACTION_SAFE
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
* Adds the `transaction_safe` specifier to `T`, if not already present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_transaction_safe_t<T>`]]
    [[`int()`]                          [`int() transaction_safe`]]
    [[`int (&)()`]                      [`int(&)() transaction_safe`]]
    [[`int (*)()`]                      [`int(*)() transaction_safe`]]
    [[`int(foo::*)()`]                  [`int(foo::*)() transaction_safe`]]
    [[`int(foo::*)() &`]                [`int(foo::*)() & transaction_safe`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)() && transaction_safe`]]
    [[`int(foo::*)() const`]            [`int(foo::*)() const transaction_safe`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)() transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (*&)()`]                     [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_transaction_safe.cpp]
[add_transaction_safe]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_ADD_TRANSACTION_SAFE_HPP

/* add_transaction_safe.hpp
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
*/