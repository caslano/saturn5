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
8sgtS2V3Z4/lKfWwdrf3AuBeMb/OXHDjl+8ucOh0/Z6E0DRTigRNLNh+xXyYzbGSZJk22MncYBnLpFmgT9OV0xWYbVF9KpuagYMjQBlktM08Msz1wmmrQftKlBYCBQE/TXdBYZCb0copVBqSpXzPzWAzshj6+TxX0Yu5pPNjC+ci5TAGL0ZsW+E3L9VQO8A3/ex6w3hQCniqGJ4gZAoYo8W7pixmfq3+b+uXu9bnxaVZi1yT4OUgrq5MncWuZrAqxLFHD5Vf4Cphy4M0MqT+ljrs8m7A5MAuJGN1zJo2Ns50R6yGNGcrC1Yp7nYkN8t8bpRUwDdEPl0yzAEXplbjPr2jYI/lojAqBfWouc4rqy0Lca+zVJ5wsIHrI1cu1gi6K1Vek3FUU+IygrmM8QwqmqRw7xUngXRqEQoh9sgLIQdOoanqrWHuRvXDu7XFUWoR43qUWovdHHb/+M0Fq9zPv+b6UyxYmftGr73axhiILpirVWQip7DEKr3KEAcYsk6qlew+hseQqL7cDFdJHoVrfF7caU4zrRNC8fr1bGhvnrNOPisNJXUigqGPdcDuiunKYvTtNmrCV3++WWElumLOPQubzWsgPVPO+oOrnhhqJvTOOSG+gxiazUomZIeaz6OxxLQIeax7Moam76Rp
*/