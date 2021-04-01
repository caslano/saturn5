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
VgmTDiWvyUnOnPKlKxPEaK6y5UHVWkM3AIKmohMceoSluW5eXXco/+drW7CDVm0tND5v6BEo3gmBvAcAVBbdQka8downYmPmKO5cuMo8rexHUq7D1SYi2y4rhYHfPaaQ2PVWCHZ802AFLAEdvAG/cTfCEDCVFFZwnus2tDhywvn7CRjmg5XgHlaOLpFZKNWMkes5+1d628h2hVgGIBDDKgGGNJuiBkPL1yGvKpVQZcwUK+6OIepT5f013utunaQuhvJoUw5EErKm1k+tvhueMQRJEkenpftHTSD9WB5BYvB0x7AKyVV1jF7GDcplxfqyfX1b9f4kwgTnjwRIs1q+k1wIQ/J0nHdaO3hPy6mAR8nvKcwPJlxVy1eWoiDT/KI/Nx0Ad9SbCpkG8+pV8fKZg/xahtX14HgdB34bv5WVv3BUHA5dE1AqE8M9wEwfIcXrx3STW8IN8YnLZCRdzDNngyA6S4hc0ijFqEjqGPvZwxRlnhw1lBf0Um9bcRTkRjFwa1K0jTy/ei1Pmltgo9bAY0aYUMX1Fw9Af09pabYKQI8powF0NKztDAAC4Q==
*/