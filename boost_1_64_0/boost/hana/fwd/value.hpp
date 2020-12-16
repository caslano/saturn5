/*!
@file
Forward declares `boost::hana::value`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_VALUE_HPP
#define BOOST_HANA_FWD_VALUE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return the compile-time value associated to a constant.
    //! @ingroup group-Constant
    //!
    //! This function returns the value associated to a `Constant`. That
    //! value is always a constant expression. The normal way of using
    //! `value` on an object `c` is
    //! @code
    //!     constexpr auto result = hana::value<decltype(c)>();
    //! @endcode
    //!
    //! However, for convenience, an overload of `value` is provided so that
    //! it can be called as:
    //! @code
    //!     constexpr auto result = hana::value(c);
    //! @endcode
    //!
    //! This overload works by taking a `const&` to its argument, and then
    //! forwarding to the first version of `value`. Since it does not use
    //! its argument, the result can still be a constant expression, even
    //! if the argument is not a constant expression.
    //!
    //! @note
    //! `value<T>()` is tag-dispatched as `value_impl<C>::%apply<T>()`, where
    //! `C` is the tag of `T`.
    //!
    //! @note
    //! `hana::value` is an overloaded function, not a function object.
    //! Hence, it can't be passed to higher-order algorithms. If you need
    //! an equivalent function object, use `hana::value_of` instead.
    //!
    //!
    //! Example
    //! -------
    //! @include example/value.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename T>
    constexpr auto value = []() -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename C, typename = void>
    struct value_impl : value_impl<C, when<true>> { };

    template <typename T>
    constexpr decltype(auto) value();

    template <typename T>
    constexpr decltype(auto) value(T const&)
    { return hana::value<T>(); }
#endif

    //! Equivalent to `value`, but can be passed to higher-order algorithms.
    //! @ingroup group-Constant
    //!
    //! This function object is equivalent to `value`, except it can be passed
    //! to higher order algorithms because it is a function object. `value`
    //! can't be passed to higher-order algorithms because it is implemented
    //! as an overloaded function.
    //!
    //! @note
    //! This function is a simple alias to `value`, and hence it is not
    //! tag-dispatched and can't be customized.
    //!
    //!
    //! Example
    //! -------
    //! @include example/value_of.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto value_of = [](auto const& c) -> decltype(auto) {
        return hana::value(c);
    };
#else
    struct value_of_t {
        template <typename T>
        constexpr decltype(auto) operator()(T const&) const
        { return hana::value<T>(); }
    };

    constexpr value_of_t value_of{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_VALUE_HPP

/* value.hpp
SFrqorF1cAzGcREHNslAldwv7QO0KcJf22i5xYZAGwIpjBvhJ9LFRbwyQsIgJjoZwFozTSAqqfifVIoph6dTrNoHKSK7rir1Oz3bMX6/6i+/zxn+IP4W4e9OCsPf8//hn8S/m4+R+FcTVrrWRbv1KV4a4RrjHeZdYAzkbAlExytSsEXOk68ONx+Jp8ZHohZoYWCdIOaBKfnCGdGTOE9QzD/W5MBilVR0kuQfNeI4pJdphwfl2stTThzSx0SHAhHn4z0fLQ11tYpfZMx05UTiuWIdZDjNnUSphfNEp3CdYdHMsjgXCU2/66f4pb563dFSVENzDD2IPpUXK/yZHg8mi1jwSYuxJlYSWaBgNZHEFZ+3pBQail9xf/uSjjwmUNdZ0gT4ddnrlw4yep0UfGnqMoHg/0TXwxXtPkpbYcmkbSr3ScjN8/32CdynRjHFedztDMJFR6Up3XelRCzlqZBSecWgYaz17dW3pOZCYx7wIBSCil4Gn701djTW4CNJITpqCULu8ViuOtDqrEa/oaplS12/+trEtn20/vIEnNbwteN1f8HBjtcWc/t6cbvxentXxni93zNjvLprL6fHq/mIrMGp+0wtPMdoz7UdnFfl4KwMcK0YDdGpnHG5g+HZOuy7H57nV5Uw/y/1akv1Uq/bw5dFnW5PqYccPjgCqjEO+UQlhReLTR5FIfK099o26zVD/jfQxNiSBioDZh9upBOI9Vbjcc0rMFOpezHg4u2uUnnay0pOn6Q7VBX3C1VcHZUX1j5TSSKix9EmlcGdkd1m3jKVd+JAU3PJAKaKnhc2wDijq2Lni7S9KnNY3IYFXPuyPSBf8SF8QBUWCcuNAjVDErGg1yRi00WshYbfj8L7aTarWXhFLx5OVYhEcHJ+NwN7kD95HuIVV+5s4f38/uLPZNbIkYS36TMo3GXHT0A83pZFDPpxjAXr7IKcVbQQN4xZbGVPvYU8FulZzJ5tFvbMYc8t0hMkzw3D1m5qPah+oPr1Uj4vCor6IUrjxA4erkOOTScsJICvQVo8LttT4pwTOGer432nK7HQa4m7xNmH0FkJl8zk6xJzx9qJdNOg65MsTp+P1R6kOJ3gDVP9XtTP2pU7iRrmMOROrJG96UQI0yEstvcwtWNLaw1eY7/j8yIE3x3thaI2ZmA89CdOAaBZ+wgicmI21k8ppoa5C+YK1Z8gMcD+N61K3nPKUNbXaAQwFrWjVKqLZHwDf16SwNzNtyT6DFa4FFCatbxXLUykbLHisLD51TAOrWHaGxZWNwfBtaWPPFHzkLFUunnhsLJaZEFY/D7VYuTzEd1G4rmFGdrfW2lnaWnwepo9UHB80gPXqhWYiu4JgpTBSGFYW8yqp6K6sykshWqW5L739QXChLSdj3gxeU8YqoTUVyxBAlq7tN+e3ssT0f7Ik7svx3vA3WjLKx1Blm+HxYVqQYudqjP0Zq4nONcHQ1SuYykX6+uHxXgzl5/4JDT0+ZFKpNRF6fo199Muy9iz/UUSqtP6MpiarqJqmJk9FL2pXa7CmNNa1Z1XgBIQqjpDw0L7oVngeFWgva9BRr8vShiSn30Jgmjex+MgtrQ4vQOZFRZXmWLQumCQl3L5X0Qcu7fFYC7HEFXA9zhMSDoRPaoauHNijlrehmhbbGp5u5ZWg49lZ+z2cWfQMSOzwWFxRS7yMI3oob2t8jAv1/xsnaQT35IfXZXH9m8OZ3kdcAFni6EkTuTwFxATisymG6r2eQ24fPYWrs/Qvk3fgpbnRQ3bVSExnDfErAk4zC5PLSiGkgbFJ39vQSbxC3m8MxIZ3UuvJvnsNC+x+/OOVzKkK3ZQQ3NRgMHxLx1iSoio6FcQDXc+V1o=
*/