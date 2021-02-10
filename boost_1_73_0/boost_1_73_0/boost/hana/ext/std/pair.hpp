/*!
@file
Adapts `std::pair` for use with Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_STD_PAIR_HPP
#define BOOST_HANA_EXT_STD_PAIR_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/first.hpp>
#include <boost/hana/fwd/second.hpp>

#include <utility>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace std {
    //! @ingroup group-ext-std
    //! Adaptation of `std::pair` for Hana.
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! A `std::pair` models exactly the same concepts as a `hana::pair`.
    //! Please refer to the documentation of `hana::pair` for details.
    //!
    //! @include example/ext/std/pair.cpp
    template <typename First, typename Second>
    struct pair { };
}
#endif


BOOST_HANA_NAMESPACE_BEGIN
    namespace ext { namespace std { struct pair_tag; }}

    template <typename First, typename Second>
    struct tag_of<std::pair<First, Second>> {
        using type = ext::std::pair_tag;
    };

    //////////////////////////////////////////////////////////////////////////
    // Product
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct make_impl<ext::std::pair_tag> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return std::make_pair(static_cast<X&&>(x),
                                  static_cast<Y&&>(y));
        }
    };

    template <>
    struct first_impl<ext::std::pair_tag> {
        template <typename T, typename U>
        static constexpr T const& apply(std::pair<T, U> const& p)
        {  return p.first; }

        template <typename T, typename U>
        static constexpr T& apply(std::pair<T, U>& p)
        {  return p.first; }

        template <typename T, typename U>
        static constexpr T&& apply(std::pair<T, U>&& p)
        {  return static_cast<T&&>(p.first); }
    };

    template <>
    struct second_impl<ext::std::pair_tag> {
        template <typename T, typename U>
        static constexpr U const& apply(std::pair<T, U> const& p)
        {  return p.second; }

        template <typename T, typename U>
        static constexpr U& apply(std::pair<T, U>& p)
        {  return p.second; }

        template <typename T, typename U>
        static constexpr U&& apply(std::pair<T, U>&& p)
        {  return static_cast<U&&>(p.second); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_STD_PAIR_HPP

/* pair.hpp
hV7J4th7xA7UQC+iucqLDt+1wOMhdSo7ZzYbEbNkCD1Gw8ZNNwJHaWLL4RkWJtkJXkkU7wJHr11fWzqbrx2VgVQgStl/ABahTMiE7lKXzAzkWftSGEsugTKIFdPlHUGH7pGoSIiUMjZ1G/ZiuXSw4K/w0Fg9SGnwm+nDkYQHT6TinXF1k7RdCmrBzqOwW7p48XLtjC35fU3Sw4TijePQakFYIqngF15C+PoAeiKvJ8uZoofiAurN8HDATjxRfMCWTYFQ7oLAauEysVXdwwmWDVV51c6LDkTUbfIfMv1s26QooD+WO90u3+oWcMwCWb5xRIodHWpIYujGHdOcIYYbazZ4EQbf7BCHVGiEhHLHYvqj27YEDnxxqUap8HXXwF3LRXDhxpJXslQgKhQvs/t2xfuE1Ze19/N8oHqsZrs6VUhAhRuApbkHjbvoYqqLoWzwgcRMkSLk46Icb8rcav2Iy2yF7VJYQJx1mAt6AHJmBaL/9HO2pYr9M55iz0nwBzxYhGzsD7GBTdAINJFcMCbAakx/o/kc49PIhC+kfKvdXwzhkQL2SDAVfX+rWiEIi+4YhkS2JcuiAaEIVZcVxyF3x8HLc+jD5foh67+UjgLjnhSFZ4eHcnvtT6/RJAx6BQPbQoMniI6B5xyMzvUq
*/