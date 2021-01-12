
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_IS_ALL_SAME_H
#define BOOST_FIBERS_DETAIL_IS_ALL_SAME_H

#include <type_traits>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

template< typename X, typename ... Y >
struct is_all_same;

template< typename X, typename Y0, typename ... Y >
struct is_all_same< X, Y0, Y ... > {
    static constexpr bool value =
        std::is_same< X, Y0 >::value && is_all_same< X, Y ... >::value;
};

template< typename X, typename Y0 >
struct is_all_same< X, Y0 > {
    static constexpr bool value = std::is_same< X, Y0 >::value;
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_IS_ALL_SAME_H

/* is_all_same.hpp
ar07irkz/EzL4xg8G34NF0ILdyscaH754VoYo/EiHHM/3KzxGe5xP6TtSHxawjjYBmbCtrAlbAfbw26wA+wE+8IusD/sCofpeb2eriGjznpc7xlN/7Oa7udhE/gCbAP3wRPgSzou2Q97wZfhUDWPhfQdev/VdVjwOo/77+9i6R/hUzAe/hGeCZ+FRfB5WAVfgMvgS3A9/Iv2H+MtXasE+2v4cchgDX+bPgdsh+3hfbArfBjm
*/