/*!
@file
Defines operators for Searchables.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_SEARCHABLE_HPP
#define BOOST_HANA_DETAIL_OPERATORS_SEARCHABLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/at_key.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Derived>
    struct searchable_operators {
        template <typename Key>
        constexpr decltype(auto) operator[](Key&& key) & {
            return hana::at_key(static_cast<Derived&>(*this),
                                static_cast<Key&&>(key));
        }

        template <typename Key>
        constexpr decltype(auto) operator[](Key&& key) && {
            return hana::at_key(static_cast<Derived&&>(*this),
                                static_cast<Key&&>(key));
        }

        template <typename Key>
        constexpr decltype(auto) operator[](Key&& key) const& {
            return hana::at_key(static_cast<Derived const&>(*this),
                                static_cast<Key&&>(key));
        }
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_SEARCHABLE_HPP

/* searchable.hpp
dd4dOxVDhArDM7SNl8Q2XaqhB8ZwS9+uktgh3SQcqHbuR3hi8kyOoxkCFWcjce7xJvRnm4MLlCN3d1zr92vVoWk4bVKyL0nJilrFfK0h1Faw8gjY0twZFiEOG/E0XlPz22tqWgr7qW7J5FNbIsd8tzBGoMDSCiN5PVqwDH2jXs3WFnyYutfmmsUvG2nlIZLqbaSfrZBGiluch6aXH24Yo4f90+9x5IwwahMBLg4mpPx0bmFw
*/