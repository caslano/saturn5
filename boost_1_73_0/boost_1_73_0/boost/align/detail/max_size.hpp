/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_MAX_SIZE_HPP
#define BOOST_ALIGN_DETAIL_MAX_SIZE_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<std::size_t A, std::size_t B>
struct max_size
    : integral_constant<std::size_t, (A > B) ? A : B> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* max_size.hpp
b6ztHjv7adxjVI+1HH3rVXBZheJSswvld0tDDE42TXl+8vzZV6G86Beo9cxFc2H3mhp16hD0em6h/hYxJ43HJaao0//0BGnOWqTWFsxumwj41iKWG4WWYGifl+r/MLR+exrHiHHInyBOg2XY7iqrB0cRTnOCQw4Vfbte1NdcSvHorT3cyHIg6WDCus29xOk73rFahXm0sRD6tUZXbdaENn/orobxxzT9cKnqDqQwaS7a1j0ZA21YCKphvt2TWGoKfp3Xxj+2qkND7SRJl49vpFQtHb0Zr9ib8aqM6MYTZXkD+fpj0VSiVYgg2C9NkXkN+rY3yni5mozRZ4WD/Cv7q9NoNrMezoUd74iYUzH8oh3vfn3wX//6zR6O5Xeytt/85b+yv/062x39eu8/xv+xP955YKa4IM41h01urB+O//2E/zX7y7C5vfvbP7/6XubOfs0J9/75xfcbkxq1dJgrHUgRNLY0o5RHFZ75dypPkxbxLcohMW8Fhek9zLEZrZcibaNFJh9lbGOW/clLvdATE6x+TDn6YvR4f/RIyWisBIi45ZIdxbu0jZ2Qh9kUhQYYoh7SSDdChihiYQ893uHi0HPhLdbbIqolsBAOBRBUzi7dXKh2Q5ZWXrEsCrRYxEcRyZ3cX568OX6nrT1T
*/