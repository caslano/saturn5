/*!
@file
Forward declares `boost::hana::drop_back`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_DROP_BACK_HPP
#define BOOST_HANA_FWD_DROP_BACK_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Drop the last `n` elements of a finite sequence, and return the rest.
    //! @ingroup group-Sequence
    //!
    //! Given a finite `Sequence` `xs` with a linearization of `[x1, ..., xm]`
    //! and a non-negative `IntegralConstant` `n`, `drop_back(xs, n)` is a
    //! sequence with the same tag as `xs` whose linearization is
    //! `[x1, ..., xm-n]`. If `n` is not given, it defaults to an
    //! `IntegralConstant` with a value equal to `1`.
    //!
    //! In case `length(xs) <= n`, `drop_back` will simply drop the whole
    //! sequence without failing, thus returning an empty sequence.
    //!
    //!
    //! @param xs
    //! The sequence from which elements are dropped.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the number of elements
    //! to be dropped from the end of the sequence. If `n` is not given, it
    //! defaults to an `IntegralConstant` with a value equal to `1`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/drop_back.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto drop_back = [](auto&& xs[, auto const& n]) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct drop_back_impl : drop_back_impl<S, when<true>> { };

    struct drop_back_t {
        template <typename Xs, typename N>
        constexpr auto operator()(Xs&& xs, N const& n) const;

        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr drop_back_t drop_back{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_DROP_BACK_HPP

/* drop_back.hpp
rA1SZUKK20faOr/SH17VxwHp1ppXWR2Qdk36wnEQMfiekZn24/BmhjdL56edjaFPNWwf+4gdw3KKYEZPqR8WglXrVQdPSzAdvg2dJyGNu/OkUk0oUi/eTuo/WtYz+4Gyc7NX9y87l73aaH1tz0dN1azBHi07Oeyjz4EU9iPVqfF/afjoVDXbYz+C8VyJF1whTyJFAai99PBIWwT+xjUlGaQLp8pmF7AGukN3dimNJjnjCbb5XqU6DJz2D7/n90Df/b7lEAxkB3r+83oK7LL9G9EqJf3nOYHSsGrs/DTUqJEgULqHmmkIRGbOg7isZNwQiMtSmjILASSa0pZoyiylKbOoKRspJbQHpjkcO3yMmvI4NOVpasoh1JRZiabMVJrSJpoyCxpwCDUlNWreetNlrXl3UA0rLFqOTdPSKzE00b/QjKxZBptugznUajhuGbmYtjj3toWa245Fj08fic1t3b5gpNn6/mnr4CPFm87Js1YNC0fXT4bXobNXDynuPFa8qWrm/8feu8BFWW1/488wg6KiMyoaXvJgYnnBmvv9AgqGhYqKiuUNZRAUgWDGS2liYKmjZWXlOVlZWVl5OlamaFbcVDQrvJxC08KyYsIMLykqOv/v2vsZGAT1vO/v/37+v/f9v/hZ7v3sy9prrb3W2ms/zzP7iT7acKLqcI2mdHDpvjLKa4r3lc3vvOzQwo42uontbkOF+8qq7iza
*/