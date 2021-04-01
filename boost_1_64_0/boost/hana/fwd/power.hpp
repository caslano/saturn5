/*!
@file
Forward declares `boost::hana::power`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_POWER_HPP
#define BOOST_HANA_FWD_POWER_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Elevate a ring element to its `n`th power.
    //! @ingroup group-Ring
    //!
    //! Specifically, `power(x, n)`, is equivalent to multiplying `x` with
    //! itself `n` times using the Ring's multiplication. If the power is
    //! equal to `zero`, the Ring's identity (`one`) is returned.
    //!
    //! @param x
    //! A `Ring` element that is elevated to its `n`th power.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the power to which `x`
    //! is elevated.
    //!
    //!
    //! @note
    //! Only the tag of `x` is used for tag-dispatching.
    //!
    //! Example
    //! -------
    //! @include example/power.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto power = [](auto&& x, auto const& n) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename R, typename = void>
    struct power_impl : power_impl<R, when<true>> { };

    struct power_t {
        template <typename X, typename N>
        constexpr decltype(auto) operator()(X&& x, N const& n) const;
    };

    constexpr power_t power{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_POWER_HPP

/* power.hpp
M5G2udXgGCLLlRNGZQxPUi+scyjMSHe+Ca+Mty/63siruCYUZzq/veOhNqHsXvlT0bR3LrlOqnc6ygKJp7IEV8ajjN6prcqRl42qgEcLzy8LmR8i+0TEdJ8NIQG25u6XJQoxH4nXmnCKg2CtoIfn8GXQYvViK6CPZ9M80j9muXbz5vp0YDDb5bv5uZbF56+L4HLZ2tBYlDV1G8htTEBKgXRLbUYrzFSky4JNm3cfirkf7J4AcdEOvkcvCxhTEUepBs43WPPtrE6Gm6/o14cYGI90U80Jh4AV2/uCOK36j7fCpsFdmDfaXF5O2UuIL1cBmk6K0slMdp3Bf7/NDAqeNSR+yTV/d42PYF3p6FnE54Dr5lFbTh9mou8aHYGQs4cQHgk4sGfXfHs7UQniAEPi4B8WYi9ywYesEqjlUl8dAOYiqOaiXux349dFbh8NNUoBMoPIcOCqrbwNl0NB1EvM+lmiklcDUpEuewrTpxL78s9dbx1ZN/isU1/3YkZKv+MxbkqpJyMaMgSkNnv1tT3Nw44+uD185qN6oWKVQYo9g2KnIfSMbYt0X+hryQ==
*/