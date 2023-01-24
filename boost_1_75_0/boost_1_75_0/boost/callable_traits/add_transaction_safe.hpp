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
kuAeDuk0k6mND7ODdDnlelfGMvXZizrIpep2JksdWSOsPCBngfLZqfBZ0Wgq6pJTOyAj1FQ0MYCttqKSfvBtKCZ9A2M5kjFE/a5nFzWTlEhtxOFnA+iz/Fkv/tlEafnFQB35xdzOaOlkKWKUDHNBnBKN+TDRD3vrFUga5HdMdmDIogeXAryNxrfraX6pkCtjJSCTCZEpPyBYF1PCmEM0dSHqovop9hzFf1eePNmQYXgpCevl0ql5Fxg1QHyK2QUttlMccG2GZ/zBRPPL2Nys+RjWkhtKSWdKYVRYA5JUp1LyXynoTdYCHDqcNyRAWaTA71wbwWfk2kg+R0PQZbhI60hweXIdLlJB2rdTWW/wSrr2HK03ga+31XqolgXp22+nOvHScp86F+upTjyvM5vqxKuJchfCE54otyKSdNJkXPLUwqfYgpKjO1oPxBP7qqzO+qfY6sTYlcmCayMl7TciBc6DG+WcuqRIgM9uDqKlVNCZL1nmIG11l8lcYD3S1B2wlKi9mtd1mqpuc99ikCwz8uHrvzzkobzpwdh7yATDU5UaC1j1amQ56rFvdBI35IZOhT7t6okHdceblpayHsA7wo62bEKqtT4pnv00PteT0VnuCXz+ftb5GE/CopO1ATEexlYeA++jaz356dyyQ667/4TinKw3Qg3IQ9JFQYraENbuVeCPoINPlESsCul80WPQ2XJPmHLPd8IUvvlY
*/