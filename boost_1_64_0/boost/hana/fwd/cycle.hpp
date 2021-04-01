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
LGVANL80sC7LVqN9Q1yoECdLLXRsRYYn9G4/psLhXb3OVHf/NIXadXaLgcj12EYGdIy7zHc8fwof+xVMZPSXMArTcdEdw+tBDNOEn2j/FFDwUiKDF1Dx7f31lF0rV83ONq2vKXyhXpl5aj5NDwOduxQJcAYxM7EDA+In+qhsc6FIYg0g2sbBe1kFreFNE859zND90iJ+0SLa6JN+HTgCImLZGelS0MJBvKDrWQ63DKelYc3rDeafh1/SCgwbfbEqVp73QqTP1NsNL5tCZF8P9Oul1ecP/zuMIFnCEfK4/TpBgERkH/JALfKCTPTZu/A5UFTRMdcSx9keuHrTJWgvxjIoqyqbvkMtIf1QBo/juQY+w3kU7qnN4CIz0Wi8tnNZaEokobQ8JbWwHHTdZEULJp9uXUHYbn4WRpVi1v5UhrHR+nzdMYaWwomBbGEoZXBTXU3cGW1+4j4epZg6Gm54jMvEhAXcCCW6y/00PF/nDDeKoLARz5zUTPTgLdaGI0BljV9aXwT91zhcQOuEGfDuVQyCGqcoce5dx0yK2J6FerSeeFq1e08P0Yxprg==
*/