/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNMENT_OF_CODEGEAR_HPP
#define BOOST_ALIGN_DETAIL_ALIGNMENT_OF_CODEGEAR_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct alignment_of
    : integral_constant<std::size_t, alignof(T)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* alignment_of_codegear.hpp
zmis6ulyKNLbjSh1mr4EmuRHLavobW9kAUBpXXdrJhbIYD2Vlfk9p56Zo2cMM6S84YkvBIeOZM2c7GH7plt2fTSlBJsH5kGfQPGJfImRz2Ee3gLjrfFuYOzgoIJj1CZy2pleiBBI/xPaNiJMQ5152bRsRIDXJBKBq7xlQdhIHkQes9b7pcai4k1UNNwz2YtNSg67zddakEQLgmoflYU2LCSZDT5OF98Sjm3uzhjwawExJCU8l9JvK1gaVAfNErsHmu1gIMd83xxfhrEs0Bzh+K98F/oY/CdsRoLwWnymty9nM0F10F/qF174O0fLEo+wv2KPGdFtPrEkGxUtc92oqrJcrgM3b4tYnYSpAm30d5gZJpaVdctPotLCMtiHLiPzjIMwa+E7Gecv374+vDz+0/H538zXC8rjw6W2P5N7rVMiFEuGIW8bWsECrV/R1a14p7WIWO6JWYLEdJVn/T0BvL0BNMZfIQwTyEW+sZY1jbxeDs3In4rSc0Z+aGD18Q+1zSc2qssajaIoDleQ0sqrlRlxrMpL1kBxcvBptBqzMnKqfPx4iFBqRTcs2x9W/2QvcCCuCQ9uLqlPfeQhp+PBOGeR1VaAItRxz9lDiaSRvbtMogXIVIZAjQ/4vpL6krbKQUhJIgeL8R/yxvW1
*/