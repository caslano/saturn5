
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
HVRzbnzJSt9McAsUvi1K3y5wBxS+c0pfGbhKhc9rvs7nAy5wvuyLVPr6g4tR+CYofVPBzVb4spS+reD2Knynlb7z4C4rfA0W6HwucH4LZF93pe8JcIMVvgSlbxK4mQrfWqVvE7hdCl+B0lcErkzhcyzU+TzB+SyUfZ2Vvh7g+it8o5S+RHBTFb6VSl8muK0K33GlrxDcecHni7il9DVPdVoBqbzPheiVqvMNBher8CUrfXPALRN81fuC0ncA3HE=
*/