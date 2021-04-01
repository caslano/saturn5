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
5AMwnCgUSqVnw84lhZsPUetDTaDG5XubTfHt6dEUCN2C/IMWhj2Vp13+x3ipYKiorpnW9Yif4hDalxHtCiXPv5/i9aHpFcIctVtpesb8QUKQLERqPvWaWqH0kLnnBRjbNJVNy0fRL0D6iVlo/I4mWlLXnYNS43NGwx69HbDlTXitXqzmgSbm8xWCLQ/FSEmG4IjzVIqzA8EhvOOz0QxTb3g8lAU9tF1n5G8pCFTw60fm/ZrWKjni8gn6CHS4VpvUDwET2LH8ZjwiS4/cdT+LewGh5xzY1Kuei3dRGmE8UgdmohlPrVu8IqZOvfGvscVkBW6rTWOTpjBO6o+4d9VwUjDlK905HYKjX4LOKaXISJwAG+6W3xETiSFul+Khuh6Rewc/niYMz0ko20nkO/1RjmpWFnBWtXrw/vd4tzg9o1i14WVajLX75uLwQOWHppi1l1ktz5uw9/YrWN4v7qs3RBk1FMMQqnI/To2gCbvecMyM8lGsS7FBFcZR34C/ZNGkL3cK9tx3lyXZ24mQw6WO5we+8iMojui7E0zQveqxvqj2Nk7miXo1O2Sn/g==
*/