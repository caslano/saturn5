/*!
@file
Forward declares `boost::hana::at_key`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_AT_KEY_HPP
#define BOOST_HANA_FWD_AT_KEY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the value associated to the given key in a structure, or fail.
    //! @ingroup group-Searchable
    //!
    //! Given a `key` and a `Searchable` structure, `at_key` returns the first
    //! value whose key is equal to the given `key`, and fails at compile-time
    //! if no such key exists. This requires the `key` to be compile-time
    //! `Comparable`, exactly like for `find`. `at_key` satisfies the following:
    //! @code
    //!     at_key(xs, key) == find(xs, key).value()
    //! @endcode
    //!
    //! If the `Searchable` actually stores the elements it contains, `at_key`
    //! is required to return a lvalue reference, a lvalue reference to const
    //! or a rvalue reference to the found value, where the type of reference
    //! must match that of the structure passed to `at_key`. If the `Searchable`
    //! does not store the elements it contains (i.e. it generates them on
    //! demand), this requirement is dropped.
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
    //! @include example/at_key.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto at_key = [](auto&& xs, auto const& key) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct at_key_impl : at_key_impl<S, when<true>> { };

    struct at_key_t {
        template <typename Xs, typename Key>
        constexpr decltype(auto) operator()(Xs&& xs, Key const& key) const;
    };

    constexpr at_key_t at_key{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_AT_KEY_HPP

/* at_key.hpp
7rTHPfjCprsbqW595OwpfcOhuaWSQ12Y7hKpW8bQKMQT+vrsr5+cQpdM+wDOXbzNbJdA9ea1UhupnMd40Its1hBR9Diix+uIcav9ABGlrMhSxvfCHe3/VfDF3XR9lSwDVFVpefTXiGtxpXXEBe4NhYYAwcnZ5bvB1egj5pT33dP/nChq3igY8xvw6AxbprDhJNDvxlORLpPFhLm49eul7SXRXuYPVa3dvCy+13FtyIoWH4cfR7i0H18df2h1O9synbaD9lKoPRDuHxOvr/bkX4jd/nIOzxp2HPrHHJgbG/O/WpvXDSrse0eBLT5qY+0e33YMEW07fluDe/t/W7JUtWELGNrpdOje25DIrT8WtIGcJkLvSgS+RQDDoW1o4FktP4+wPCBBb2s219L1NgqP/RWW1hrJW6lt+1aRgDBuTIh/QFdFIHd+a9HCypslaW0PNqTKbyRlfdNtOfBExBZJ8Ns2H8xR47h+UwDWLpF24EOvgaitEWAZhd7d0HzLwLr3B9T3+A1GNYN+PDftQXeQb9MXHmU+PANDfDYO9k2f3dp4z+8Wnd/mLt7NjNiKKQ9Ds+Ei35/Pze1vp22R3T9zHHGb7hwGydetWmJLj0ReeVwiI/NuZ/edOMFTkNuNGfL5bPjmgkLs2/dHbwuG
*/