/*!
@file
Forward declares `boost::hana::lift`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_LIFT_HPP
#define BOOST_HANA_FWD_LIFT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Lift a value into an `Applicative` structure.
    //! @ingroup group-Applicative
    //!
    //! `lift<A>` takes a normal value and embeds it into a structure whose
    //! shape is represented by the `A` `Applicative`. Note that the value
    //! may be a function, in which case the created structure may be
    //! `ap`plied to another `Applicative` structure containing values.
    //!
    //!
    //! Signature
    //! ---------
    //! Given an Applicative `A`, the signature is
    //! @f$ \mathtt{lift}_A : T \to A(T) @f$.
    //!
    //! @tparam A
    //! A tag representing the `Applicative` into which the value is lifted.
    //!
    //! @param x
    //! The value to lift into the applicative.
    //!
    //!
    //! Example
    //! -------
    //! @include example/lift.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename A>
    constexpr auto lift = [](auto&& x) {
        return tag-dispatched;
    };
#else
    template <typename A, typename = void>
    struct lift_impl : lift_impl<A, when<true>> { };

    template <typename A>
    struct lift_t {
        template <typename X>
        constexpr auto operator()(X&& x) const;
    };

    template <typename A>
    constexpr lift_t<A> lift{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_LIFT_HPP

/* lift.hpp
nQF5YodRgrfDKCFHCUFay0uV9rBEPSoPrUQMVz9v1qFmivzjGksqTAPep5yHtxnl/A4vXM7t2w5RjmhBSYedEJZ/FDes2dkjFLxiXvBD07omG3Iscl3CLuzGRmTHsyRwe/vmPgf5KW8+SkPnIeKTUJ/AKsvC/HQExmlzd0lBQGrb1OkqApDjxCzD6lWHSkieBt26wVviFG5Hh+6Abw1SAP8KNJde4XH6XjaLyWUPVyyQQJWETdAWle+tQka52KpSnigjL4BkgbAc9CfrAMdPyEoin5ZKs3UI43q+hzxyi2kkNJA2xDlYSrh7HMhrpCmFiH45wplircAD6O0m6bwQEgucRYcVBDkvrLHFrwIfVhLWLymVEvRVOBxNqMO7j5qI7YQI9RFji9NVJhlvoLMi8oSbM+5AP4bPmL/nz/BXCN+AD9H2EG/CJ7sZOzgxCb8ip22g4adTn6axelh+ud3ESu6wzOX5rimyj3sjlfl9zA/fo2G5F7NA+PAdkb/6TR+7/IjukzcpwMdzNtjnvOyEZ4jeBL6foTewRaem/KnF8h9kXYEufTbeX9Bx2V9//+jpibrfYdtKw95tXETU54ltdHqafOLQpNQXaPEK2M6z13+qXXFcOz/A7Ezfu8xEWcGYcpcoyxVhTZxBuwhEE21Fq6Mj4lqcF3lcu4WejpW0Er41hPfNiARhjG83SioRlbiegApuCOo4608WbKRTc9+XCDCzF5JunY56/8nGBxnjY493dPl36dE/2dy3JHKeF0jrfxabzJVaycjNMZiV22vhQhn5bmPrdXW73auKtaC1MbcK+1xuFpIWixAUdFoEggqaBKQ+s7OzhFErQp/nRf3Mc+qQZFGXaIm9rXVvoEqOTIx8P6fFt5GvRVdehsBCLv0VjUZCi1/k5AOba4tov1WI1CVFkNIXqYsYRvHd8Rf2xGd5RHCnuKpL3eJNV3ixsJ8N/MWk91q1M1l6NZUdALWWHtfFgWsRnKcPFiiytfQWZXjXrAlUFfZNsYSH6sKIJIoaI6ofxvZ1y0hEIlBTqot/U30R1SXuuqnoUlTtBZ0CNCdO6Os4oc+Y7bRezjhlr32NDwregPM4/BJLZo4goif/nS6FWHNU/Nz2DbS+upZm1tekA/m5Yzf24edabrPQHs0Qteye6OUdWl927pQbj375GfjJgwrJ9x5SFt+4LyIblCObXC45IO3pvzuR7b6ZnUACTX0u7oLMesk0iK9yl/THwYIez5JyOz2dS8qzcJBFa4FBDyirI4k636wsaonliWrXTtOurYLccK4jeeSK9ZHnxT7Q6nNrxlSvISJeU3M5mOoLH9lPFBFxP+KHJsqeeN2Z04OXLPPFwS9gkyABOr7mHJVFNWfhNLOompVkE5UwrqYcIOM/5VP2WeJ9NNYPJHSM3uCCxWUDTvEhJvLUYkktnJDZkSCtHzmiyUTWXsogLIuY4afohLFZGltOG4XBYXkTmKBK4K5HeN+DbBHpqLvi0PjTw1eENhn40/TBNkczXcPCYIBOrp2TpW7JPJOtgenifD+fF529zrpayN8Co/qVUQ2tH0ZRZOgGxZloxJlsxQzDjclPE96oPSeWdtaeVQO2btgPLCz8hLq9vhAGXR6+4ZcOmp4tl/J0dHV+kwRQaY/7hrPpZS9ePkP8zAR7rCfLff3JeIdMzh2R825iNDca5bIH4w/SdPVxAFBAuOqV6RXWdVReRxMfV7hLGJOX5EqQsV93hnGk1d+z6Gv+zYu+jPdRjiZINi5m6mTdUSfQnrg2AINyYSbgHcUQ5aZH04os2hws6mGeLWA26oHvmE5S80A+Om9S8Ucp2UlWJqM7baoEkwTh5NdNVqA4UilfeKo=
*/