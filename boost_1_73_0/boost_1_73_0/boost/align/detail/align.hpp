/*
Copyright 2014-2016 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGN_HPP
#define BOOST_ALIGN_DETAIL_ALIGN_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace alignment {

inline void*
align(std::size_t alignment, std::size_t size, void*& ptr,
    std::size_t& space)
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    if (size <= space) {
        char* p = reinterpret_cast<char*>(~(alignment - 1) &
            (reinterpret_cast<std::size_t>(ptr) + alignment - 1));
        std::size_t n = space - (p - static_cast<char*>(ptr));
        if (size <= n) {
            ptr = p;
            space = n;
            return p;
        }
    }
    return 0;
}

} /* alignment */
} /* boost */

#endif

/* align.hpp
6FT6jMuQOzFVU0PwitiFRiDz5qYYyQRKf5O7ez9e9NKERLN5LtSnqjqMhp+o5decBoWHi5QdpcGFCMSqpkHdxrJU3zB3b38PancQ0i6HtMvZaXGapakK5hRyEGbbhOC2IpmG2c8ySxfWcNm9NDiRGgCTiGDMrmhWAAaasa2IkYKgYzIJT/MTQ6+YTAg3p05PHllZSLgaGjePqKw+IWWIgYaCtnUVHGRAINqzNMUFIv4tNKl7QSM8wFd1SGPEKQ6So2aKEnclMkUHmqA6YavqWLeiNdMehuxMX5EaxYBkqmbLVPks8iC12Mnpnp68UHpw+vLV6eE3F1Dw6mamZoBb1aExCjb6sYjLGpi/sARJNsSwg41HbnTG5OQo+FzN8+s2KBQjvaabpRV+pKiC23OChRxiFDR1s22LEFhUhQi5fNFTl7J5vi4ajW5g3sLAnJsEfPokA7bIhTqmoRV+U0nZgETmQyeLizlMMga0OviQBK+io9HUSUQVBfs7R1Ek0uoCDOmWRaSWogOGU8unA7tKAsD5IHvBWDF8nH1TrS5PRfO9redX/ODthfwl0s+MH78p2hxpdYPsAmZCHMMlQunIuHZ1lqx8dzFGbJHIlBeu3fh3FpEkX31z8YcyvnPy4g3E+D3EKOUNZxYUPhdi
*/