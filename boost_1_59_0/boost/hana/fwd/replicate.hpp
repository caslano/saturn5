/*!
@file
Forward declares `boost::hana::replicate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REPLICATE_HPP
#define BOOST_HANA_FWD_REPLICATE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Create a monadic structure by combining a lifted value with itself
    //! `n` times.
    //! @ingroup group-MonadPlus
    //!
    //! Given a value `x`, a non-negative `IntegralConstant` `n` and the tag
    //! of a monadic structure `M`, `replicate` creates a new monadic structure
    //! which is the result of combining `x` with itself `n` times inside the
    //! monadic structure. In other words, `replicate` simply `lift`s `x` into
    //! the monadic structure, and then combines that with itself `n` times:
    //! @code
    //!     replicate<M>(x, n) == cycle(lift<M>(x), n)
    //! @endcode
    //!
    //! If `n` is zero, then the identity of the `concat` operation is returned.
    //! In the case of sequences, this corresponds to creating a new sequence
    //! holding `n` copies of `x`.
    //!
    //!
    //! Signature
    //! ---------
    //! Given an `IntegralConstant` `C` and MonadPlus `M`, the signature is
    //! @f$ \mathtt{replicate}_M : T \times C \to M(T) @f$.
    //!
    //! @tparam M
    //! The tag of the returned monadic structure. It must be a
    //! model of the MonadPlus concept.
    //!
    //! @param x
    //! The value to lift into a monadic structure and then combine with
    //! itself.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the number of times to
    //! combine `lift<M>(x)` with itself. If `n == 0`, `replicate` returns
    //! `empty<M>()`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/replicate.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename M>
    constexpr auto replicate = [](auto&& x, auto const& n) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct replicate_impl : replicate_impl<M, when<true>> { };

    template <typename M>
    struct replicate_t {
        template <typename X, typename N>
        constexpr auto operator()(X&& x, N const& n) const;
    };

    template <typename M>
    BOOST_HANA_INLINE_VARIABLE constexpr replicate_t<M> replicate{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_REPLICATE_HPP

/* replicate.hpp
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
*/