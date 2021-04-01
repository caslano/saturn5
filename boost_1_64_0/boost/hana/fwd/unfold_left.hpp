/*!
@file
Forward declares `boost::hana::unfold_left`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_UNFOLD_LEFT_HPP
#define BOOST_HANA_FWD_UNFOLD_LEFT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Dual operation to `fold_left` for sequences.
    //! @ingroup group-Sequence
    //!
    //! While `fold_left` reduces a structure to a summary value from the left,
    //! `unfold_left` builds a sequence from a seed value and a function,
    //! starting from the left.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Sequence` `S`, an initial value `state` of tag `I`, an
    //! arbitrary Product `P` and a function \f$ f : I \to P(I, T) \f$,
    //! `unfold_left<S>` has the following signature:
    //! \f[
    //!     \mathtt{unfold\_left}_S : I \times (I \to P(I, T)) \to S(T)
    //! \f]
    //!
    //! @tparam S
    //! The tag of the sequence to build up.
    //!
    //! @param state
    //! An initial value to build the sequence from.
    //!
    //! @param f
    //! A function called as `f(state)`, where `state` is an initial value,
    //! and returning
    //! 1. `nothing` if it is done producing the sequence.
    //! 2. otherwise, `just(make<P>(state, x))`, where `state` is the new
    //!    initial value used in the next call to `f`, `x` is an element to
    //!    be appended to the resulting sequence, and `P` is an arbitrary
    //!    `Product`.
    //!
    //!
    //! Fun fact
    //! ---------
    //! In some cases, `unfold_left` can undo a `fold_left` operation:
    //! @code
    //!     unfold_left<S>(fold_left(xs, state, f), g) == xs
    //! @endcode
    //!
    //! if the following holds
    //! @code
    //!     g(f(x, y)) == just(make_pair(x, y))
    //!     g(state) == nothing
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/unfold_left.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename S>
    constexpr auto unfold_left = [](auto&& state, auto&& f) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct unfold_left_impl : unfold_left_impl<S, when<true>> { };

    template <typename S>
    struct unfold_left_t;

    template <typename S>
    constexpr unfold_left_t<S> unfold_left{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_UNFOLD_LEFT_HPP

/* unfold_left.hpp
8e5tWn8Vx31G74Rjb/aDedPXWR7GGU//Vt1h0Lig7l2i5/O1dFNqx9UpnGq80G3RVUo4nKYgG5C7bbvw4Ok67psrWeXMwqOTczBMkSahqmb5YIngrHVsi5YjAuK8LL/G822G6VRYY6/aNJ7dYhU6O5AG61UKe3+LZd2Bzrh5HIYRgzeta2XJgBAa9VZKTKDwKpTHRzxEmAh2JF8BeRb4LsmXXB7Yl2Ugx09pe4VNs9mFI91oHog9Inn6s1Gt82t5lAdReudFfxbH1yhxoP8I3/A7C8Yrp0CLDW1Uq5dejX501XN6bb0dAiBB7Vzj+GRgCSVfzTSdpLO6EZ8bg/Cwp+Zd7iUuS50M978iDiB07cPswlgtegwHbTAMKoe8K7ue1RB2LuLrBVHifGGLPeo6SwLSNbyf8ENv1y0Cn6V/hKky0SdQRu+YvRotyJ/HJ8o3ousOqb343d+EUKT5rvk8LPas+F2/fHXLOh8OEA5xmlIQ9ZjIxQ313TaD4WLncOmcLN9LCizrxtf5MRlhx4oZFCgntcgGs7+QNWHKGHdfILMSap22VRDOqYhU1Q==
*/