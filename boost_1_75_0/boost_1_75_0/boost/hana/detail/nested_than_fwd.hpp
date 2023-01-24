/*!
@file
Forward declares `boost::hana::detail::nested_than`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_THAN_FWD_HPP
#define BOOST_HANA_DETAIL_NESTED_THAN_FWD_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Algorithm>
    struct nested_than_t {
        template <typename X>
        constexpr decltype(auto) operator()(X&& x) const;
    };

    //! @ingroup group-details
    //! Provides a `.than` static constexpr function object.
    //!
    //! When creating a binary function object of type `Algo` whose signature
    //! is `A x B -> Return`, `nested_than<Algo>` can be used as a base class
    //! of `Algo`. Doing so will provide a static constexpr member called
    //! `than`, which has the following signature:
    //! @code
    //!     B -> A -> Return
    //! @endcode
    //!
    //! Note that the function object `Algo` must be default-constructible,
    //! since it will be called as `Algo{}(arguments...)`.
    //!
    //! @note
    //! This function object is especially useful because it takes care of
    //! avoiding ODR violations caused by the nested static constexpr member.
    template <typename Algorithm>
    struct nested_than { static constexpr nested_than_t<Algorithm> than{}; };

    template <typename Algorithm>
    constexpr nested_than_t<Algorithm> nested_than<Algorithm>::than;
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_THAN_FWD_HPP

/* nested_than_fwd.hpp
MSswnK1pdATE6IJRFbrMv0FpdIzAUAdV/XswQp3wZpBmax+wdTzn0X35tgO8BDHuEM5jsTufv7jY4ZMKBLJRSVPuu2h3g8ZH2Qgqu1ZVP0lV9WNxcvmOUJbsVtSBc5dW2ncq49XD3zBedV5+vBpZHR+vOq84Xt33yGWUdnW80ijtWE1VaX+KDUOotL8QV9pZV0D60K6gtHisK6DSfuW2nq+V9Rg8VNZjHGnZbKq0jzeopAelfcwQpR0TKsMZhg8ZzjAMhjPj7EsNZxr2Kgz9Rq8WkMfaDIezPyp8/hut0n6ZCqtK+974KPSonyKnjjr7KF2PsVHGLD6Pb9qxJpdOBdl4o6jpMD7toSPN7uEjzUwcadovNdLg0RL/diw4TP61EWff/92IM1r/z484p2hT7qFjzZuUDL4kZbyJN6pWPcf6uaTrr0f1PCYLWMvheBOg4w1T0Ts1KvqzdLzZqfTJT7UqOlf3PFJH1nN1aA0dydWo++Z2x3woI8aYffUlmb1SMxAxzlMGIo2AWXudOhDN1g5EijAKczQLWlGNCBiaRcZ1GtnI6EHodBF088eohFR1eI2E7GARUU6iDr+Kyclt/6qc3DZLIycVHOgARPx0MMvV1Riy9Ki6Cy/fhxxS1t+Hfs6376SDFOVzPxuw7h5Q2w6F5Ef/+spG6JFvu7LxnYdiQrJjEQrJRu6pnyNn0J6tG6LT3z0wXKenPCr9
*/