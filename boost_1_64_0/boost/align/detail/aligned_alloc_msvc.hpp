/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_MSVC_HPP
#define BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_MSVC_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>
#include <malloc.h>

namespace boost {
namespace alignment {

inline void*
aligned_alloc(std::size_t alignment, std::size_t size) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return ::_aligned_malloc(size, alignment);
}

inline void
aligned_free(void* ptr) BOOST_NOEXCEPT
{
    ::_aligned_free(ptr);
}

} /* alignment */
} /* boost */

#endif

/* aligned_alloc_msvc.hpp
gwf7ajTE1XnXtJUiHPiFGWLnnaSYI/AB4VLFnDlQcTyjJp0J1vIWIhEP666f58t+gg3vUBa0rAPCHDRiV24XLYoHAYjn6dl5HHliU6nXxlVn5hXxCeyk387nfZSQz4bXeX4F8Xu3boCN/u+Pr4+wHibniYPuJG8BcPsubOC5n725GB/WslIehjeuX20BTZbTJvo4PYXiktZy6C8QhSFm1Uis/zXTzJY4pPXsN5nbKnpKjedxZzOgdwxA9To6ug8XLS77uMRO7yEbQHf7zaczwFy9yBh8mVbkGwzwlb/RDv01HGDpr6010ET19tOqAb954nJHEiaZJCo9O4zv/hmsviCwwnNHFqEKYxpVZ4UlqJNGZQkuho7LWZl3DAC/TvnBKx+rSqNr5RpfvsLi9TokybrVzfcfOkUxgWkULe9jxEUueYx0/gjYM3esGWc+c4b1hqoMN/8Du26T/ylXQsD95Ocf+FSCSGoyL6c4EJPTfwrB7l11Mtefd7w3fOuKyXyRVjog3AReyADvOjeyrFgAPrM/Mudg9dTb8amxHy3TheYc3ie0/B4gqiIPsg==
*/