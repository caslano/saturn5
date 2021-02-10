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
r6BhUEtWkhoqJrITe87rNUjrCgWlwMLMTJgqf5RIDdd9/hZGeOKEyFGOl84ft0qjw6ILJnJ/hqYuuuPUsis/YRVuC/jj/FyZazad8eim2/0el6+UdS+Tmg/oTXuOJPaIMeWdq9Di3MCcoS5y5MgJq2Rs+0+nqVrLoHiNMVpQKR2kBSwq/ELMOGnCdHJDG0tIdnrUygB5saCZAMMGh86EwdyLScFg/BMznu4GkcZ8bMpnwAjDXs9cJ3e0YJEVYOL6keWKbLeUERJ5DDPF+eMMHAxtBTABb2Ecxa2/oBOb4nGIC7ZbuQ9L4L34ZJberZXjUm5HlafvWmuklBkh5ICOSov7hEV6U2BtAzPzCnOiillo4A3G2HbdThVm8PrL9iutnHKz6TGZ3K69Vy+hXlkWXkwcjAArE7gkO9pfhLZXVftSnIFtrZ6c4L0VmCS5YO2zfiQgQn9jARFEKF08wpiEAXUY7TnRQ0bnjR6u1WpxtF5sLsg5c+HJQEewGV51OrFRrbaq2PCWXXQ6a2Ghwa68hF2Z5O7PW8jKRdZ7WklVZcS/8+aV5M0TiXzV5P937ry/c+dVOWCeOiO9wanyF2JtBMRn4ZRjFhq1RpJMsL0jT5fDbO1fcXHbBOhATAAOFh28A2GYg9wyvMbAH8eA
*/