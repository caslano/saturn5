
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_STACK_TRAITS_H
#define BOOST_CONTEXT_STACK_TRAITS_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {

struct BOOST_CONTEXT_DECL stack_traits
{
    static bool is_unbounded() BOOST_NOEXCEPT_OR_NOTHROW;

    static std::size_t page_size() BOOST_NOEXCEPT_OR_NOTHROW;

    static std::size_t default_size() BOOST_NOEXCEPT_OR_NOTHROW;

    static std::size_t minimum_size() BOOST_NOEXCEPT_OR_NOTHROW;

    static std::size_t maximum_size() BOOST_NOEXCEPT_OR_NOTHROW;
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_STACK_TRAITS_H

/* stack_traits.hpp
Hy8huADHX/Z4154/RW4w9FoD3VY1lRhFDaysCkazPec/dNINO76CySKcBfM4cabT0I2iJMLEXTgB83gMfzZck/uLCWbBVrr7cGqfnNpHKNCnhBL5mEiqdJ/xRUpJRI2uwHduXONt6LvP2FoFEpuK1ctgjal6880vQLJMp05lixAt/WAeeZHxE+Np0WQUzrTLjoP5N6NFTwXKDyMZ6C/wKUd2FEiSN6OwoBD8vgti+LV1OHWjSejNYy/wjTnBFpBep6IpUpbhVvPiOe4NKRrasxs5RznSlHO8AFtNcZCT3fu4cBaz2DhqT/MwiINJMIsMpyisDqOR2lzbtiruX87NfOYaNl8bXVptF35/lTTjTA0wB7YeaOEQ/jEAnotTU/UVz20mJVZIR5+wTMv+VzcteKkXLhaYu9GnW4J0pHYqypE51Oav0DAetk44KRGH4ThtByZV+VGn946bg7a8Qm2tMf69bHHOkTBll+o+fFpQwptq9+lfw16ztojOd8ebOefezIuXhpNl3X16ah+P7a4RoRsvQh++O7OFa4RU4S0h2wDdJLjG1NrGd/zW8y6bqhI1Tnt3A3WKC//aD279JGgZpI24UPYB2rkzTS4W/kSrJE54ubhx/Vjr6olAzhDg9J4ovLg7enWsMSPXBWcW
*/