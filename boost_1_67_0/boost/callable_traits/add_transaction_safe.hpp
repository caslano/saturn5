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