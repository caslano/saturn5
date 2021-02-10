/*!
@file
Forward declares `boost::hana::find`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FIND_HPP
#define BOOST_HANA_FWD_FIND_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Finds the value associated to the given key in a structure.
    //! @ingroup group-Searchable
    //!
    //! Given a `key` and a `Searchable` structure, `find` returns the `just`
    //! the first value whose key is equal to the given `key`, or `nothing` if
    //! there is no such key. Comparison is done with `equal`. `find` satisfies
    //! the following:
    //! @code
    //!     find(xs, key) == find_if(xs, equal.to(key))
    //! @endcode
    //!
    //!
    //! @param xs
    //! The structure to be searched.
    //!
    //! @param key
    //! A key to be searched for in the structure. The key has to be
    //! `Comparable` with the other keys of the structure. In the current
    //! version of the library, the comparison of `key` with any other key
    //! of the structure must return a compile-time `Logical`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/find.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto find = [](auto&& xs, auto const& key) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct find_impl : find_impl<S, when<true>> { };

    struct find_t {
        template <typename Xs, typename Key>
        constexpr auto operator()(Xs&& xs, Key const& key) const;
    };

    constexpr find_t find{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FIND_HPP

/* find.hpp
B6aF0FLNtCJmLuVEdlAbJAb1jUjzaHJUkmCDWiRkHpptgWcqxW/9rAlAQzxT8y7IYk4Sn9i1SKpXBXNVEVB/Devj6Jer1QYTFIXLu4ZRV3CVzJh47zvOsH8qIj63yckczuWw9+ZRenUIrP0M2tRLvgZNnQXr9Xtj1Ynhi1fiQu/2bNILhgJMnFMJdhrk8zXVgOCg4O3pCWT3fKk5bAoZTww/YBIPWap45u7/+UW8WpQXyieLZYNipGCZd+wquZ+XKUGVu5HU578lW2OE44J3yANvAkiNjN+lKnVu3HNGBE+M3rTh1/ImYxRud8StkE+4Ze2Zblo/MiFcLCdYXJu+bQgiTu0mjCYH+3Wer93lxA/cudkjnVv9nnXiHR69SLjnRxeRAri4dl8SbXNNiyP3+icDqkoTF/2LEXDReXvYflcoB3hIUp3J66uDK2qWuQQpTdZK++tSqqymSk0fRkFk/kHoQgSB97JhXYXavsFLY3kHZEt8VcwKszHuQCucLYO2o4vzc+vMiviS7dHo92rPv0FfB8SnhypIUqc25kZRo4zghJyvBCm3o1PsgLkafmd3UDtipR2s7zZUXx0ZSHUU2LvNddLZIHxjj6E3AgqDYJSl3tk9zE2iRq6H+c7upb/6umwu/K4wFbwfH8Vk
*/