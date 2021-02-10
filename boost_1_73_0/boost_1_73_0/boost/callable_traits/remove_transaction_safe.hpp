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
XUwPhf/i7fwMvAp0LLWy1uaGcBNpVuyQH4mHHy2RfFJ5Lv6J3cGkhwDit9pkVZMzHfiQazsuD+8tOWDeX5OyaWsHy+JQ1BT/iryOrvxPl6hwyLUydyF5dtjbp+zEBvZPu4fHo5aup3D8odEAQYstxCf6efzDj+M9yYJa2FXMO+2PBASdUBFH4pYAhdDUtUUrxT7K7HIptSgvXrEhXUgTuns23YzJLW+sdUjwin0CT2oL+zVqAnrs/7TfLXkGPtSLwAFtfVNKjXZwvRACa74PiA5VOW7zo41AazNcWZ2PBn8NiKaX58e0K+E+654iNiDkGTlrMJzl69SjKQPtYnZoNJ8Jnp7TyeXx8bMBNka9nrcbWfnbVBsdhiPB0MVQlkckdBjRmyRLYwl9AYWjOiJOq424K7s3gJ4DJkeESqKfp2fzFLeEdvwy1JhBYj3ukjlGBnZG0bVIKYkHnwptN3fmb49mx+n59GxOQb1nqTqJMSEjGaasVMi8c8hF78694DeqpKqu2eTDzdfw6uDu6cWWU4c7UZQHI7tzLdki3QrojB1ka8faH+evrzYe+nt5qNt9bQo25tOSs/dReHbOonw7cyRLEL55Hh15lZ6+GQ3aE6+o0b6hGKKzYYL4/s0xogIp4PwpfeevzU4yuH9m
*/