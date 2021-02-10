/*!
@file
Forward declares `boost::hana::suffix`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SUFFIX_HPP
#define BOOST_HANA_FWD_SUFFIX_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Inserts a value after each element of a monadic structure.
    //! @ingroup group-MonadPlus
    //!
    //! Given a monadic structure `xs` and a value `z` (called the suffix),
    //! `suffix` returns a new monadic structure such that
    //! @code
    //!     suffix(xs, z) == flatten(transform(xs, [](auto x) {
    //!         return concat(lift<M>(x), lift<M>(z));
    //!     }))
    //! @endcode
    //!
    //! For sequences, this simply corresponds to inserting the suffix after
    //! each element of the sequence. For example, given a sequence
    //! `[x1, ..., xn]`, `suffix` will return
    //! @code
    //!     [x1, z, x2, z, ..., xn, z]
    //! @endcode
    //! As explained above, this can be generalized to other MonadPlus models,
    //! with various levels of interest.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M`, the signature is
    //! @f$ \mathtt{suffix} : M(T) \times T \to M(T) @f$.
    //!
    //! @param xs
    //! A monadic structure.
    //!
    //! @param sfx
    //! A value (the suffix) to insert after each element of a monadic
    //! structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/suffix.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto suffix = [](auto&& xs, auto&& sfx) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct suffix_impl : suffix_impl<M, when<true>> { };

    struct suffix_t {
        template <typename Xs, typename Sfx>
        constexpr auto operator()(Xs&& xs, Sfx&& sfx) const;
    };

    constexpr suffix_t suffix{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SUFFIX_HPP

/* suffix.hpp
3x1SywpXPKGsakJoJJcF5z+aee3LI3LJFeUQETZDslENdTQHVbEHMc9gE9zKnKJumqCso3VSdUdlgw2t1UfQ1jBD44hq1UcMPW1BgyWlOjaA3KIYLJCGakg6yCdA0mwdB9H02hFBLzljAOcQBUxuFqnZD8kdVeO5GGPspwIavsiuob8TbJFpqnNFBgSKKTZfK3AxOi5lJHTiswZGOmcu425uLpPGBiJy3F5xj9FVnx5AsSKhIpoTiXoARsQkoWt07bceNsTHauNCrDSErahoYLmKggmEqYRBsxKW0kBm4xBMYpUMIhR8pTacPQSAj2IOov0I3qADgmQNGiJ+zsAHCWMMKnp2vuCXM1nDzhV8VoMzBbYXQHkCh8bJEnRrGXeowcng+OT49RF/0R5HJBR7emmE3FN3jIK9olmUw3JZJJPp8FPS9EI/hkarSIxDYxf8u2pFml7xz6nNFn9SwsFrmUlHc1hoHBSaIUgNCLJQsQDJDQezQT7L2Zunro3dJkZbNH7Ko1jms2LnUfJXMsy+PKN/XqSzov64Bx2QBOd4lnKKRXGin4Lj2Mynw3Iyox/S47UMi46iWO2P6sdB1FWx7We4hVHxgm++QeUl88WCqLz5qvmxvm+9ofe1vyFTngv/JWm9su3MbIqAnU1p
*/