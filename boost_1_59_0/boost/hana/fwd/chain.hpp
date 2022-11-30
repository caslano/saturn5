/*!
@file
Forward declares `boost::hana::chain`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CHAIN_HPP
#define BOOST_HANA_FWD_CHAIN_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Feed a monadic value into a monadic computation.
    //! @ingroup group-Monad
    //!
    //! Given a monadic value and a monadic function, `chain` feeds the
    //! monadic value into the function, thus performing some Monad-specific
    //! effects, and returns the result. An implementation of `chain` must
    //! satisfy
    //! @code
    //!     chain(xs, f) == flatten(transform(xs, f))
    //! @endcode
    //!
    //!
    //! Signature
    //! ---------
    //! For a monad `M`, given a monadic value of type `M(A)` and a monadic
    //! function @f$ f : A \to M(B) @f$, `chain` has the signature
    //! @f$
    //!     \mathtt{chain} : M(A) \times (A \to M(B)) \to M(B)
    //! @f$.
    //!
    //! @param xs
    //! A monadic value to be fed to the function `f`.
    //!
    //! @param f
    //! A function taking a normal value in the `xs` structure, and returning
    //! a monadic value. This function is called as  `f(x)`, where `x` is an
    //! element of the structure `xs`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/chain.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto chain = [](auto&& xs, auto&& f) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct chain_impl : chain_impl<M, when<true>> { };

    struct chain_t {
        template <typename Xs, typename F>
        constexpr decltype(auto) operator()(Xs&& xs, F&& f) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr chain_t chain{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CHAIN_HPP

/* chain.hpp
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
*/