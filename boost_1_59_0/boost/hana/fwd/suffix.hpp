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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr suffix_t suffix{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_SUFFIX_HPP

/* suffix.hpp
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
*/