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


BOOST_HANA_NAMESPACE_BEGIN
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

    constexpr cycle_t cycle{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CYCLE_HPP

/* cycle.hpp
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
*/