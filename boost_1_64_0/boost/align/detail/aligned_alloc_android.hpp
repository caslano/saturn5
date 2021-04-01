/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_ANDROID_HPP
#define BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_ANDROID_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>
#include <malloc.h>

namespace boost {
namespace alignment {

inline void*
aligned_alloc(std::size_t alignment, std::size_t size) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return ::memalign(alignment, size);
}

inline void
aligned_free(void* ptr) BOOST_NOEXCEPT
{
    ::free(ptr);
}

} /* alignment */
} /* boost */

#endif

/* aligned_alloc_android.hpp
/B38ZJKecJCJtVr5hf2oTbzcN5030CVw4Bujk3iV/HgWAmEs2JAr6+UXjfvrdyAtz1l9r6MoxxjfHzyzTPBNFlAboDNMrcOS/L48DjEbxi4agDfZGritcqHD+O7VUJgYQEne9wpsHIVZytFZulubiDsztqpA7U39+boQqXzIc3v5S6ytCrZDyekNo5cIQjz5zf6nr1SkMeRVwm+VpYFg5k6TzYX0qNoWNyQp4xURIfHAnLAW2Y6GOUVjkqDjwU3Xffu7torLYTIVOPZIfcdoQUJvcFH6WeeVVXVXL8ahBSYSVuTY6HfpTGcy9Xq2ue4+91CNwQKmljxs6Nui+LZG1DfffORbO8njNnQxq831Zr0LOorW4dGaH+JBsqRSye2ZYbyQrN5d2Fmrr4Bz6+fTwLWH5/A7W0fOSi359R1TzjtSXqmr0VptKUw6Ha2UNsRygIQ/6baPqioCPj+JLOW4l+Dd5U9diejNDu2KTahnltmAvUfTuQGpom26my4QUi5bcZMN59axRwsiA6tLlerJ3dnIBypxFdto4w12Ye7EjUqET71qli4oCA99/A==
*/