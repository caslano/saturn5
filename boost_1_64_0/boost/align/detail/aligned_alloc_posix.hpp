/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_POSIX_HPP
#define BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_POSIX_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>
#include <stdlib.h>

namespace boost {
namespace alignment {

inline void*
aligned_alloc(std::size_t alignment, std::size_t size) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    if (alignment < sizeof(void*)) {
        alignment = sizeof(void*);
    }
    void* p;
    if (::posix_memalign(&p, alignment, size) != 0) {
        p = 0;
    }
    return p;
}

inline void
aligned_free(void* ptr) BOOST_NOEXCEPT
{
    ::free(ptr);
}

} /* alignment */
} /* boost */

#endif

/* aligned_alloc_posix.hpp
A6fl4HnK2PRguYcMbYYXBgyi2p7tdELCiH8ZRZkw13tD96jfC0mFZhbrFrLKkd7aWVf4MQFNlQ53k29gYd0aPVNkOJh+EQKs4jDaJfMB5DnClsTkIxouQdUXCJ5TESAITjDqubGpUzcUfm7Q4tTI+jLKjrBgVkW3nNCf17YS1Uz6rrUQ3d00oLoh/7Pl1TYpfmwP80Hnam0rPQcl2uis84cPqlVuT8/1BLXY6QzFsC0MKFRtCX6yJeQpJyqm6ibvtKDJZHbIBGn8RmqPopfrHhLVZBGtFkd4qH/obDEdnqIvIK0R8cM641gSuS4oYmGFOBEawzJGk8y0NpGYunrYaA9Bb2M9GnDeahwW7w+mOk7xnuw/RXMT/bcizZyUS/uYf2bBuMqhScxdji8Hia/XAXxwSakBmOKBMOGJZbzaju5uAc7s2/2qYiso05v5ikeF2N0+UWCbwMaWqLbc3dYxw9LGi8WH3aynON6xbHX8gKPD3W6ftV0/yxwkIWjzGaOAzEqujYtnycnnYBT2on9mtRSu0hyzgYFTLF80Pym7EBJb3QXgzpN5JzfHyQ==
*/