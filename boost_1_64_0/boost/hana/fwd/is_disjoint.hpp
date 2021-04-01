/*!
@file
Forward declares `boost::hana::is_disjoint`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_IS_DISJOINT_HPP
#define BOOST_HANA_FWD_IS_DISJOINT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether two `Searchable`s are disjoint.
    //! @ingroup group-Searchable
    //!
    //! Given two `Searchable`s `xs` and `ys`, `is_disjoint` returns a
    //! `Logical` representing whether the keys in `xs` are disjoint from
    //! the keys in `ys`, i.e. whether both structures have no keys in common.
    //!
    //!
    //! @param xs, ys
    //! Two `Searchable`s to test for disjointness.
    //!
    //!
    //! Example
    //! -------
    //! @include example/is_disjoint.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto is_disjoint = [](auto const& xs, auto const& ys) {
        return tag-dispatched;
    };
#else
    template <typename S1, typename S2, typename = void>
    struct is_disjoint_impl : is_disjoint_impl<S1, S2, when<true>> { };

    struct is_disjoint_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&& xs, Ys&& ys) const;
    };

    constexpr is_disjoint_t is_disjoint{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_IS_DISJOINT_HPP

/* is_disjoint.hpp
UV73YV2tjTYYyNdCAeiUmPKQUTkTlGYAPa/NU048eT82NbRk28U0ROLsBUYe/DUrevmwPCPRbgBdLdgUiJ3c+GAOMO+7FIFg1TpL+1k10dRvxMY1vZUfr0mU5YTEqBfRBzT71PydueGczXaVENJkGjbDI9SH8rdVx+udshQ9QS93GqtxInj8t0bTe0MgbSUg9W2x2/EKYOne3er4hDJeUugFTYhsJdmHWRkAT8XCRnp5NRxrKSpBHqPJAkKnVpFI1XUvAuEzuI/V3gxWlcTCzSbEjNAWdWnPP1+sJHgZrPoKsH5ubVcVNSVjfhBYwIstJZw8AmoCgn0QW/IoINGMFK5w77oBq4EqO5fRe4tRvSwxSufkI0vC0gW+5KvTI4VdJTs+V5NRZNfCb815QuI/N0UbUcXrW62483IfQppLTV/P6M086x7Zu0KtPQDeiI9vlbUt6ajvmIYKUFfdh5HUmWIY6oK9d22AQtDjfvzNkudQOdLec4BCw7e9wKr35THXWyPq9ID/o3an6vZ1GzvsBwd7Q0i3cBKiYrYWXqymcfM1lrXHw5yz9lUmGw==
*/