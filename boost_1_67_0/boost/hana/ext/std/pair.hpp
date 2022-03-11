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
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
*/