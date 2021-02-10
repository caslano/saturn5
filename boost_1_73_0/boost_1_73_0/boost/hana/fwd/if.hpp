/*!
@file
Forward declares `boost::hana::if_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_IF_HPP
#define BOOST_HANA_FWD_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Conditionally return one of two values based on a condition.
    //! @ingroup group-Logical
    //!
    //! Specifically, `then` is returned iff `cond` is true-valued, and
    //! `else_` is returned otherwise. Note that some `Logical` models may
    //! allow `then` and `else_` to have different types, while others may
    //! require both values to have the same type.
    //!
    //!
    //! @param cond
    //! The condition determining which of the two values is returned.
    //!
    //! @param then
    //! The value returned when `cond` is true-valued.
    //!
    //! @param else_
    //! The value returned when `cond` is false-valued.
    //!
    //!
    //! Example
    //! -------
    //! @include example/if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto if_ = [](auto&& cond, auto&& then, auto&& else_) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename L, typename = void>
    struct if_impl : if_impl<L, when<true>> { };

    struct if_t {
        template <typename Cond, typename Then, typename Else>
        constexpr decltype(auto) operator()(Cond&& cond, Then&& then, Else&& else_) const;
    };

    constexpr if_t if_{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_IF_HPP

/* if.hpp
GgI6QKFJDGSui0U08edUmHqumpA0JQKXsibDdyLiCJARlcOB6A0q4txLgqQufuwNv3t3NhQ/Hp6eHvaHP4t3x+Kw/zMC+77Xfw2sD6CxufBvZnM/gcbnIpjOwsCfyDb/vM/2xsbfgmgcLia+qCD3RomfLmbNqwo+uADRuggif1I9G3RHbwbf94agTL9bd/uDQeHem/7Z8IRvf9hAPTEf/vju5HgwOClUGhx9d9jvd09qBkrPESWWqquXBqZwY+KlHqKZ3QSqj73Et29exUk6vvLHH+3bn9Iw2cavHAg/mlzYtwC/dDRLQRGs20Qr4Ke/v2s/uNlrPfWSqE0k3N4i7Qm9JBU7QhdC8UmUKp77rLYBMhqlDpiSa2c2D6L0woHA1J/G81v7Adyb+OeLS4XA4aDfbIt3vddJE0EnqZcGY1CdCHAaX3lzacrGERT557/EC1HpNPeau82dygHZUrRj0ykIcuRN/aUgEs+G0XnabH8DUADEYHFO9t0LQZ8iqA7mR8OzAQIbF1DyCPsH4BDzFO0Mwf03iNO/RaXd7DSf7Laa7VYLvneb7UpdmeTKJPEq4q7uLrhjF2x8Bk1rJFde210F+mDB9sfv0SqNv/dvyyrsNFtZlcq4M4vO2/s7n0ob2M01oLEafHdYUmk/
*/