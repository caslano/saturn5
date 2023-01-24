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
ML9LnOo9eJ9FrYwAAlqSep8BcLGfEX753xHq7kFLVvh/8FD9qJ5Hb8STsUVXsmPWvdZFeMe7JkXh9/RRAzDk7/cl/neukic+C6pUpdt71t6lOKwut5ppUE4qw/av183UTOp1nFKW6Y69ppQp77Z4/RuMShjymoL2r9f2QXklqByynxGnoVJR/pkmo3qjoWnZxEjjEvh3fYT6aoDskDG/G6Dbe9Y9vSr60E3ZHxl7cw5+wCVTRfYQ82AFnMfk/JCK94Nck0UtMjTdlBxpXAb/nAw8Oq9ILF9/POccc1aLsjzdpyKbgNPFh+rI1O7WtxNVlICvzIOhySV73w1HNZZNENTxJH96lqEJp8ojgEx3mzeEUi887J02Cr8YBwvseuGV9ytMB3ybLKh602w7mB8YGlJXGOQzlnUTgI/divHlpJbZjw68AYv6gCa8ctTUU1GudPqeCuLyiBqN0162uisiWxFj+poCcpYUhtLJYkdnztJr0EtsG12i4lzILKGC/JLlU7w0X0ihpZVN2Cc+73EIP2L/cO1VppO+rch42b9eM0NRsesqolNiE36xAgz2IfuH6xbp8HZioumkPbhuKnBL8acn49lZxg2HlZ3HqTQQa1Ho4MAaoOPNMueftp9ZO6nCnWBYj8U3HmPJCi3oo0Ds4dUrfZsI/e4PU9Vvm/Kh8r6yFePyj+rzczzMz/Hx+clqpqOgg6SY2Y8K3tMY
*/