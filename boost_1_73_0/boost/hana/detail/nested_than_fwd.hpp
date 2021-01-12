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
KmASwH1V1bTPRLHSIibXV4WChn+wc7TsPEcgiS2Rn/VrZWecYW73C36Kre0PS+ztvhzb4OVL7DuyjIVLAdBp9r5GhPfauz7CbSZcifDiJeL4aLHP/n/Nkhsqrisf5E89i7viMMZo5GEJQXs9qxwhrSiWVtxeI+H1CxBW9kxc3Ygzdcwaia84ytwkJtmbBDeuPp/l8vcH7XIqCj/+sJ4+6wrJk8qzxO3nC3Sv+P1rZOGsNHYK
*/