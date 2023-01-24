/*!
@file
Forward declares `boost::hana::insert`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_INSERT_HPP
#define BOOST_HANA_FWD_INSERT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename T, typename = void>
    struct insert_impl : insert_impl<T, when<true>> { };
    //! @endcond

    struct insert_t {
        template <typename Set, typename ...Args>
        constexpr decltype(auto) operator()(Set&& set, Args&& ...args) const;
    };

    constexpr insert_t insert{};


    //! Insert a value at a given index in a sequence.
    //! @ingroup group-Sequence
    //!
    //! Given a sequence, an index and an element to insert, `insert` inserts
    //! the element at the given index.
    //!
    //! @param xs
    //! The sequence in which a value should be inserted.
    //!
    //! @param n
    //! The index at which an element should be inserted. This must be a
    //! non-negative `Constant` of an integral type, and it must also be
    //! true that `n < length(xs)` if `xs` is a finite sequence.
    //!
    //! @param element
    //! The element to insert in the sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/insert.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto insert = [](auto&& xs, auto&& n, auto&& element) {
        return tag-dispatched;
    };
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_INSERT_HPP

/* insert.hpp
0ZJkSbZMtky3pFrSLZmWHIvLssCyyJJvKbQst6yyrLGstYAxRL9V0JMclUu1QLUIHJ4Gdw0qGfgKA0+R4EcLXmLBRxJ4SAX9LtBeCNrXgu6NoHkr6C0HrUdA5ynQeAH0yUBbGOiKBE1aaF+sJkGTBP1L1WRqXNC/Qs0qzVro4EbNZs1WzS5NueaA5ojmuOaU5rTmgqZBI9OGasO0vbWR2iitVmvVxmoTtEnaydpUbabWpV2kLdSu0q7Vrtdu1G7WbtXu0pZrD2iPaI9rT2lPay9oG7QyXaguTNdbF6mL0ml1Vl2sLkGXpJusS9Vl6ly6RbpC3SrdWt163UbdZt1W3S5due6A7ojuuO6U7rTugq5BJ9OH6sP0vfWR+ii9Vm/Vx+oT9En6yfpUfabepV+kL9Sv0q/Vr9dv1G/Wb9Xv0pfrD+iP6I/rT+lP6y/oG/QyQ6ghzNDbEGmIMmgNVkOsIcGQZJhsSDVkGlyGRYZCwyrDWsN6w0bDZsNWwy5DueGA4YjhuOGU4bThgqHBIDOGGsOMvY2Rxiij1mg1xhoTjEnGycZUY6bRZVxkLDSuMq41rjduNG42bjXuMpYbDxiPGI8bTxlPGy8YG4wUzFVSmAUtUUBDIqAdSmhGtCZek6hJhh9I1+TAE+RrlmvWaNbBF2zSbNEU/R/vDaIN8YZEQ7JhuiHdkGNYYMg3LDesMawzbDBsMmwxFBmKDRWG
*/