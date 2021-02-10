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
zMdUsdwhAAaenG6YWMhQizjmmIbSVlCm+esY/vz84GcQ5le6zi6fOerajU4c7+HtJEm4x0sv3VXkTbOFYXiH7bm3QF+EHT4Cm/KUkV7/E7JXZgmocgpLG+1l8lg+VPU/Nz2mtCSXcsqEQPrNTQEy7CCPl0lQJKl6lLpfq1nGD0LBHT5sg7iDByN0peMpQ2JzmsOu0+62eph7o47IPKgb6WGszU3GqjmPX6hX6VdEbET6JWkdo7fr66Jua3Opt3li1BdR5UshUafsIPjUnmprhxw5BFq1x1oSaJobeopYSVWWcCTf2DMDOOvo+YpEnqk1thetx/8DjLW/Hs/9yVvvvgNaTmKt4XV2X/F4ikjO8gmqdr+cMrNATl5WYJFKLRT5WNHMuqQ+GQKlOfnpxLudojXdBmUq4ukdrup+prPbKuUF3aRj/5toqNSQ0KxrOkJ30/jM5OEpQLCGTvR8okjaCwoDzQepFXhiOMmIcAgHykxtYXZcwslPwZrHH1MHqrlCOOWvWS/s6KXgAWVIFcIplbUG6zc/qS4kABV7kcUrdMS32SXIbcjmykqnxo8ilTu/6Uyz0nYiaMvnF83hBbu9cCOlhvG+J2N8NtQifEpzvXx+SfxMyLeCLyW16nqVlhi5UUVDhxR7pCMe5llz
*/