/*!
@file
Forward declares `boost::hana::cycle`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CYCLE_HPP
#define BOOST_HANA_FWD_CYCLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Combine a monadic structure with itself `n` times.
    //! @ingroup group-MonadPlus
    //!
    //! Given a monadic structure `xs` and a non-negative number `n`,
    //! `cycle` returns a new monadic structure which is the result of
    //! combining `xs` with itself `n` times using the `concat` operation.
    //! In other words,
    //! @code
    //!     cycle(xs, n) == concat(xs, concat(xs, ... concat(xs, xs)))
    //!                                       // ^^^^^ n times total
    //! @endcode
    //!
    //! Also note that since `concat` is required to be associative, we
    //! could also have written
    //! @code
    //!     cycle(xs, n) == concat(concat(... concat(xs, xs), xs), xs)
    //!                               // ^^^^^ n times total
    //! @endcode
    //!
    //! If `n` is zero, then the identity of `concat`, `empty`, is returned.
    //! In the case of sequences, this boils down to returning a sequence
    //! containing `n` copies of itself; for other models it might differ.
    //!
    //!
    //! Signature
    //! ---------
    //! Given an `IntegralConstant` `C` and a `MonadPlus` `M`, the signature is
    //! @f$ \mathrm{cycle} : M(T) \times C \to M(T) @f$.
    //!
    //! @param xs
    //! A monadic structure to combine with itself a certain number of times.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the number of times to
    //! combine the monadic structure with itself. If `n` is zero, `cycle`
    //! returns `empty`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/cycle.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto cycle = [](auto&& xs, auto const& n) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct cycle_impl : cycle_impl<M, when<true>> { };

    struct cycle_t {
        template <typename Xs, typename N>
        constexpr auto operator()(Xs&& xs, N const& n) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr cycle_t cycle{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CYCLE_HPP

/* cycle.hpp
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
*/