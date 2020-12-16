//
// detail/array.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_ARRAY_HPP
#define BOOST_ASIO_DETAIL_ARRAY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_ARRAY)
# include <array>
#else // defined(BOOST_ASIO_HAS_STD_ARRAY)
# include <boost/array.hpp>
#endif // defined(BOOST_ASIO_HAS_STD_ARRAY)

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_STD_ARRAY)
using std::array;
#else // defined(BOOST_ASIO_HAS_STD_ARRAY)
using boost::array;
#endif // defined(BOOST_ASIO_HAS_STD_ARRAY)

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_ARRAY_HPP

/* array.hpp
eV9EeOC5yKwIzYJXl9+bRbb2BociGh3aeFEgtoPzAvdCLNwLieVeCPdEFofcC+nym9KxzE8xzE/RgT02IXIf7VsI7jqHmoH34oBsgbxvuU78f09DYyj4P0jbO0f9zvcCmf3SMYz5/nGA92Q79AbYfknADyF5nc92+TfTwbnSPOPfx1y0sw97EC300Vj//4vWtji0FyR/P/ged4REPVFP1FMX9cJcveRqJX7bg74Ja55x7IyVkzVXHDL7v7/ZzvtZwLmH6Csorxv/ZfZfO8dy7RzDtXM0185Rne+12dytvtDd/8b9v6TB925Yv9zzXYd2gopLO+9jfvP8TiFlIf8H7aJMh+V1657tP95fw70dh94Fm4N4hOaFnRmhM71mz2Pne/G68U7Y4O/KdK7RtvalX0QemrtKL3VoEai8LMA7OC8wVkYxVvrfT3L4d8Mv5rrmEua3QPugvG7cMzrqPuTgmO/mPXY/rVhoxSh+w3/5vwX+tVNUYO0U9D2JuisdugnceXnItyNCygLfWrLLFmY99I67Zf+pdy/9q2l3rhlC/vPWcb1Dsasd2npF0PVUl/kKzeuk1X7oepuyD4HlyiBa3yL/qPr9l9Nv3vOQopQwa+h7HgJx0DmPrgv5f11GBO+PYw3bZiUO4/zfB25f49CTIP6q4P/SRUrUEXV0WJ3/kk0OxkNnevT/7fr/43GE/dDGXiH/d03sqURvhP97tJ6fOnQ1SL46EFOhef75d2s0czBp22H3rrdL/4H3/nQxXwfe3xXHdaOl83vPm4+6h8KfduNdtF3wDOypsci50twbC35vTqz/OzIrNjr0CfCtCNgvJC/0nRTdf1/EkcblI7c98jfiHnLoWmD5QVB//1b5Cs3r/Jbot1vfHtGHne/tjgrr6r3ddRH/pfG98zr/5EidzLw+j3l9pnkvG9fX9sXhu7olw39qPjX3Zi7o2dFjV+fzgwi5mBesxGH0weuCtTsc+sBgZfB4Bqgj6ii0Tud82pbOfJp8aD7dftj7H1JV+oJDJ4GR1wTiIZD3LcfF3Aj6YR/6ISnXxew3Oew7prtecSj8Va51A7yC8rp5/Xuk9Y+91zf3gDcHff/SPMfiWmX4zhied0XRr6O17DWHHgKl1wbZkTqijigX9QJ1uvlu5X/X/qgj0A0dZ4JlCn1Pzrf5vuQ973Hv4X2ecVwXPEaE5gfkOGranf1o3+YdPQf3i/nHZfN9L3yza79DPT53qOeq4H1f4f686w44FLUq9Btf4X/fBgTyvmWMH833we8Vaj1sD7UvuC94/uLQbWBbQKaQvJD3AnXOT53vBdrH/V3Q8/pA+5C8Lv8DEfjGmFU9AmvsoDHBro6vHRosp1oCtLvI6yF1s+5RbfjvSg+fl47+P7OjfDewvZdTPXs71bY6oFsgL8gO3azbrX0nXY9voe8/D8TDweusjh5OjTvOKcsNAf4heSH8unnfuLup/340tMsO2jCup+IO/lfVF+3UpeCegGyheYH3WoXWDzy76Di03s+JUs5u1kfcx0rG9q6gZxe+GKfuBFE/DHp2QV3tDH12EVr3H61Pe/JeWf97lv+5Zwz/rjQwtgSNj53XEZFcf3fj/7YhNI80Pm13OPUVWPCjoDjvIj8sp6dylkT4r2cCMR6p0L3uywY7FTnEqU3B9ELzQ+kFvjVz2H9Auv3MLmT8C9WxLsOpG8D4NYG4DM77p/4f+s243/lN8fbOPSd1gb0oyBLrn6878wPv7rUhv1XxO/p+867Fw75DHidftlO3gY6AvKF5gWsSr/8dwIHnNru/GSd8VqdWg8obg/odZTqsrJvvgavDhvTZmrbObxR3zut9v931z8E4Tkj17xP2Bew=
*/