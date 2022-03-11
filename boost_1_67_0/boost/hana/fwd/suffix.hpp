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
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
*/