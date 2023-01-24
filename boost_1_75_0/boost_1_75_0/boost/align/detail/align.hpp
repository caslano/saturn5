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
sbdlxsvwPtz6ikX+4JmhFDMKN4X1hHzy+DSIzk+Os8XJkA5pPQrk/PgaNlXYYqQoGpPYfRrgV9ceCjuk9M3rZjKpE4LXuc8oQizuNg/vh76EAQxs2OW5J3VHC4CE4EIoGDS5kleRO7UpNKXeU17WOFmVgMT/cNYg8LGbqfAnzH2xhJoIcswj5W8XvZB8eYacGDXE4Rh6KdZkOd5WVYSDvTNrH6I2BC/YM2y31Qw7gwsxUQll4P0IlXE+ffZLWBsr3DCSrRUpNsh21rO8m+lepbP6RDpfsFmMg2Ho4jJauG8k+6HbIquDasNKFWY9dotXZT1U2ne9A3yMx9rpmVSXjc/2qlRIQs+byux0eRxZ5pE8GlGOoSWY2lr1LJyMDgYhaT7ZqPBW1CVUKttMRPPcM1wcIIFsKAMvPYWa3CUeU+dyqmyMTy8bqWM8Bp5HDkC+dzbZs03Hn7IIVmyCKCnP0swZ9xBkd86KQvNlOZUSNrDIsLLz9rlD6baEVF3PvPKcTtunN6Y2WQQCA3nGpH/8yENVvYSa3EIW0op/6yMlGL7Gfv78WcLLAGA5kFq6dMR43j5POFR3qdLQRtE8DHMM2Ugm+kEovVQkIbLgUp5n2nwsr4vLNFnvWj22YbNN0nuuimh+U3w1X+or5Chwfayoi3uBzhkTINWApUcV1Kp/P0k41MPkdc8tYJPT7lnOGg06Kzq385gnSR6t9SA/
*/