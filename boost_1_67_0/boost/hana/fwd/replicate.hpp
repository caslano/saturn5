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


BOOST_HANA_NAMESPACE_BEGIN
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
    constexpr replicate_t<M> replicate{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REPLICATE_HPP

/* replicate.hpp
+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
*/