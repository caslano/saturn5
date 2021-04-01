/*!
@file
Forward declares `boost::hana::contains` and `boost::hana::in`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONTAINS_HPP
#define BOOST_HANA_FWD_CONTAINS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/functional/flip.hpp>
#include <boost/hana/functional/infix.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether the key occurs in the structure.
    //! @ingroup group-Searchable
    //!
    //! Given a `Searchable` structure `xs` and a `key`, `contains` returns
    //! whether any of the keys of the structure is equal to the given `key`.
    //! If the structure is not finite, an equal key has to appear at a finite
    //! position in the structure for this method to finish. For convenience,
    //! `contains` can also be applied in infix notation.
    //!
    //!
    //! @param xs
    //! The structure to search.
    //!
    //! @param key
    //! A key to be searched for in the structure. The key has to be
    //! `Comparable` with the other keys of the structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/contains.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto contains = [](auto&& xs, auto&& key) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct contains_impl : contains_impl<S, when<true>> { };

    struct contains_t {
        template <typename Xs, typename Key>
        constexpr auto operator()(Xs&& xs, Key&& key) const;
    };

    constexpr auto contains = hana::infix(contains_t{});
#endif

    //! Return whether the key occurs in the structure.
    //! @ingroup group-Searchable
    //!
    //! Specifically, this is equivalent to `contains`, except `in` takes its
    //! arguments in reverse order. Like `contains`, `in` can also be applied
    //! in infix notation for increased expressiveness. This function is not a
    //! method that can be overriden; it is just a convenience function
    //! provided with the concept.
    //!
    //!
    //! Example
    //! -------
    //! @include example/in.cpp
    constexpr auto in = hana::infix(hana::flip(hana::contains));
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONTAINS_HPP

/* contains.hpp
BCxtrwN6JE4ARDOjRqE5DjJFAlZAT9ca/RlEq3OUf0/ik9Ih9FViQI8uvqtKg5mFcK48XdpgRwFrTYhxAOL+tJv5ED4xMJsCeXReRgRum1ib1DXd/kDPt2vuD52ZhVFZkafYFlR3G0N1KTr5VI+ifblCakMdnPvgmRRj45REfPPJ/Dr1vdhAfSrd8c1Vkq+VyZ6nyU4uZWYwhTLPw+YPEVD5OSPMXN0iyoaMmD4SNWnOBNX2QWc1QLehRpSHh7CIq8lPQh64O8Ie8kSyLYIe3PRpYtDeXcxJaBpA7rShS9PrjXq//xTOZ/vLoiWPU9WUE767EWCA94kWVR1bQPeCEV5zrVQOpATUngsPXN1/TlFMcPFkVN+m+vHZGyGBQUXpQjOxEcvsMB6tUo7NHXr7CGg7TUmTPdm5Cf3uTqHyJXTrtDighwPWXr3Exgpd2PzyY+k9en6g02hOyLy3ml8VP1i8TK5Vyr2H6MurbxD2w7Yyr6flJ1lug1EfDiwIaePsr7g7f3JDFN4YZzuJYvhBjgXOfK+R4zndh5+/Bg56aSDCDM0VlshPi9X2Zw==
*/