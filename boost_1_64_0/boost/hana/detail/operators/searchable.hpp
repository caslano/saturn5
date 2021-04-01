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
rwTOBH3HXbwXhwzBBUZTFcQnXnCSlebiNWqEv5hxvreFl7zGHAIkAi+4Sjv4GdQd0Cr9toRNsNGYJyEy2vPlnsXEYOT+JepG9MaP8rzvODJ28JHd0zy6pSSifDbDcKcyrA6dx9PernApl0JUuPcetGvhKqkSWG3/m09c8K7v7ap7p1+rEuQ3wy9npIC8jgk506Pc4cVEluVY5Gl46FqtwpcNTOsA2TRpzR/IZ98raXG8JHIpD9bWWAUGM5y4gYy4JDd+4DcbW7Hr4iNx1vcMGbkBZk51pD5xG2yIB4aBQAD0GYfEgdUWCDKHb6pvGEOyNn9btMalHxX/li2eyMW6ht4kClWz3GkTJs3nwvLRryXmihkRdiegQ5i5TsdAnwq08zCFaD8zOxzo0EdZVkRRqzoxs9wAxL58gaH3BVwU7a+08eblJ0OrSExtofW2ejluKRPGEfrK40wEDLqTsvtqm4Z0w6dimdDVBz7HLQ4TskEAiYBROyzU2jquGjPMb1zXVnXU/UhhzLxqm3GX/MXOs+TsJoAb6NpP3Nnqg82oh7UpY/y+wVL2ArQKFQ==
*/