/*!
@file
Forward declares `boost::hana::mod`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MOD_HPP
#define BOOST_HANA_FWD_MOD_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Generalized integer modulus.
    //! @ingroup group-EuclideanRing
    //!
    //! Given two elements of an EuclideanRing `x` and `y`, with `y`
    //! nonzero, `mod` returns the modulus of the division of `x` by `y`.
    //! In other words, `mod` can be seen as an equivalent to `%`.
    //!
    //! Cross-type version of the method
    //! --------------------------------
    //! The `mod` method is "overloaded" to handle distinct data types
    //! with certain properties. Specifically, `mod` is defined for
    //! _distinct_ data types `A` and `B` such that
    //! 1. `A` and `B` share a common data type `C`, as determined by the
    //!    `common` metafunction
    //! 2. `A`, `B` and `C` are all `EuclideanRing`s when taken individually
    //! 3. `to<C> : A -> B` and `to<C> : B -> C` are `Ring`-embeddings, as
    //!    determined by the `is_embedding` metafunction.
    //!
    //! In that case, `mod` is defined as
    //! @code
    //!     mod(x, y) = mod(to<C>(x), to<C>(y))
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/mod.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto mod = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct mod_impl : mod_impl<T, U, when<true>> { };

    struct mod_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr mod_t mod{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MOD_HPP

/* mod.hpp
CzPQxBEmEgqlUYN4begznwGpn3x7kctDERz5gwJDbG3T7h+nF6ZRvKtUbJ9n5NwVQzyen/K0jJTHmxONrHxqpq2PGTClcIWR7WleHHQ/1mCfOOfDV+grwbW4b4z+qKFh1C3YOV04jFaPi/QSKqtJoH2TvghUBrAkTNNzV78Ia+vZ2gKpovDKLPdLYXfFj1GHnLI3VdwlucNreDK5vOKSq4xduQ5otciujLWreXZ3oR1GpdHKJBOL/Q5feXTafyshOMm/bvaTf47tIgwQXhG1n1yssgpW5SW0OfXltFY5S/yiba4O7UvDZ3kQsCDf8IsRthCPEvWOAa6m9HqGpboVpOOKUzCk3L19WNpr10VEDDfQcYVxYlvJahJeMfh6fcT7+jhEnpaL6fn6YcpInNH6xCStAS0naoBx/lMh6UMSPAP2D0ypyHBgesyp+J6cHv3kGY08miKngayUiH2VHzsSmgKhSA++c1VkGWZeVwLL7zmGNiVqpky82KvD6ObWkV4Gz15FwnD14vRG4tNxgQb3g8HntFhoasZAijFQHUV+teaOD0Kn23WXmh+MCY4/iBDcda/+WEVa8EjfsZBUKr3QfDiY+6w64cmY4MKDLD5r2CTUl3sWWjbtQALlnOp3abwoE80CzV4j3KCNFz97krYMwE81z5KHNhRYxDf5qNkpjybKy/41ZzWGOy479JAvUAv40lCBJQ/M6IEhR/rkQDBuF4XP1KLf1KMr3/Gq/d0bS9XLhvgsCy53R6SJwkIYOoRhYigZb4A9tNDO/jkLLPP+Tv3HIWjPFjOb7C3EafcpHWjI9eQ2iLIZkeBZf0AFscr6lPm+nDLhG7QpU8Y0pNl7v/o2uZqkGaPNliPnAZg5ngmYB5Ah8S55pCWn0xEk9oto5Tb84jQSfMkzyBdDR8Jt5pAUXGFAUyC8Yne1mysHeMaLv2brsLPCtDs3ghKpI8mLX5iVTR7QBMtjLLgHgfOXVWw8/WpMK8y6PtDO8hG/r8bJiwRQqSZ96t3hPLVf8OZIbbMF3n/SmD6nIW5TWKXN/Ca17KDauGm7rUGJp8OMD01Vb3O9SLUpDASOVfqzg7cBaBV8vBkLN7eQsThVXFvEbUcKGfWVUlZJD+4F76v5nXh5UFT4H8Osx0OF3Qw5M3I73Ks110nqHIu6C4sVjkH+dNAEH8fpIudAJTR2xKVXGSOC1ULmw1RHUnY5+aeDY9VEtTP0Qf8NAgTABUmf5XEwwxkkLgy6Hk9H8TwexYkHgf9qaOwGYWtR9yODEgvB4Qcq3V7/tgUsC8kIdX9KX9jp7yo6SBYLb+wu31nCikgPpK6gKak+lvoz/JJ8hzeDOLugrQatk9If18KklhEWY6BbRvCgt+fhBRtFlmRZcsKVFnVP2OYTAy7XGCup6SnfiDLSjD2oocKn+JU+LLbKxV7Hj9qIpepMMv59pdgzl2Pa7+Fga5VDBnfJ4PBssmkWzy5UwpP9YnCWpm2B2mAefdOOnK6qdM3dhYebcqteU2U1yekjmX5Z4Fb0IHwBWiOTFRrJxh+R7JZqpqXM6ki0K1510PF0CGtsz6BlfgR/YbP0pYFbcL2hN7Tim4aBcZ3nkIzvZQbbAekLIbEmeDn3JhK8LIv59wpe5PnQuG/IQ37W5udzNBi98wVnRoAadvX1lvwge6XAaaq0BjjfgqneJzI4eIPFh93XIlBPxfI0AEYcJxk7XX0YHiMHwjd3xF3baBmLRGNEQ6qeCikgWf+7Jjt3+kuhlDCuUnLXdEeMfsHvTAJS+xCVxVYVMsrLTuM4TDv/mkr7XFYlbbmfTJtuOEBzL6qjXDlb0jBUQLMvGlEdjaApeC57ojD47YI5PE0otpQ=
*/