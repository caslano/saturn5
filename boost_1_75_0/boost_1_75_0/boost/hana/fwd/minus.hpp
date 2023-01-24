/*!
@file
Forward declares `boost::hana::minus`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MINUS_HPP
#define BOOST_HANA_FWD_MINUS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Subtract two elements of a group.
    //! @ingroup group-Group
    //!
    //! Specifically, this performs the `Monoid` operation on the first
    //! argument and on the inverse of the second argument, thus being
    //! equivalent to:
    //! @code
    //!     minus(x, y) == plus(x, negate(y))
    //! @endcode
    //!
    //!
    //! Cross-type version of the method
    //! --------------------------------
    //! The `minus` method is "overloaded" to handle distinct data types
    //! with certain properties. Specifically, `minus` is defined for
    //! _distinct_ data types `A` and `B` such that
    //! 1. `A` and `B` share a common data type `C`, as determined by the
    //!    `common` metafunction
    //! 2. `A`, `B` and `C` are all `Group`s when taken individually
    //! 3. `to<C> : A -> B` and `to<C> : B -> C` are `Group`-embeddings, as
    //!    determined by the `is_embedding` metafunction.
    //!
    //! The definition of `minus` for data types satisfying the above
    //! properties is obtained by setting
    //! @code
    //!     minus(x, y) = minus(to<C>(x), to<C>(y))
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/minus.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto minus = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct minus_impl : minus_impl<T, U, when<true>> { };

    struct minus_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr minus_t minus{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MINUS_HPP

/* minus.hpp
W8+unb9TBwDZnwhJDGYNT9rxmuaT1sFSGhKWZNmCf6keejmexrdkvZBXT7Mce3PlTQu3FVs/sgmCJys8xI46E5vwrvuMsppdxHHyCBecP9pgfAVb381aFPN/WPWSk3MUIZ2gpgQMXYtefHV7vCloTEq/y65l2J1UO6w6J+/DErsW2n1rXyBLuojcaBkLMmnSdu20H5oQZvA8mqSsMT6y0ev3mYDNQkymbsMAGWYKn5wSta+njPKbGu40z9A2TAmUpTZx7dipUs16XVP47KcavYzTp7EdLJV3RR011ZXz2nCTQ/rEDR3pFOmIPTEAd5rLvB8r0Y5aJ4vwYIbwIXGnJ7pGIrFYbu4ois/MXcnTdu2ksP5X46cHGTs9TlcfbHB8lqwvhtj1DPVdWByTi377viRDJ9KJAyH9CKOgrt4Ptn3KpCo/meI5Jh5CgNKKeh59gKBMF71yq64Nusdp//Ch72kbXYHmk+3TJ/osohtWb4IN+ZK3kMB3WLuCebI2sLdiYRF3gkHx4F8lRwR1Oa/cQYQBC/kQnOWkbpUQxZBwmoOKZU2zYbOrIBCOSH/IbAhE5Cb8Vx3XNN0pYITOTOMRNWQahgmWX1fmSRBU5fENMRj8Y67jcbXGAIsmYaFbLr4O/TmG2a4T7KGwR6iYJh9bEbiTOyYA1nsc8mcaPujpg/md2TMn1A7dLgq3aFdU+FVrjjCblPMSt2XK7hFP
*/