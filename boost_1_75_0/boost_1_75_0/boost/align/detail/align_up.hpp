/*
Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGN_UP_HPP
#define BOOST_ALIGN_DETAIL_ALIGN_UP_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace alignment {

inline void*
align_up(void* ptr, std::size_t alignment) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return reinterpret_cast<void*>(~(alignment - 1) &
        (reinterpret_cast<std::size_t>(ptr) + alignment - 1));
}

} /* alignment */
} /* boost */

#endif

/* align_up.hpp
VLK62eTCFXOEs7cSyICiFOf+ZpRazh1GYBu/ue289UkDY9FKt4EWwxaBLF9poYR6hWTd2EyUUmifyI1i/XzM8BCG8Bj7bult6h402wPvSIUBgGZ7BuvfmiWTKlwaXWIiejUip4Wg+BGDbMl7v9+3qcYTaA6BZ54WX8qYCSkTiPB46mHdDWJttSX+/hqnn8tMK4GcEqe5/8XQRVioNt8G5xqLOhj7dHrglFl/MEq4PzqesNvsu5trLEEVZMWIDq+SPB7WfqU7tp9ps/q9U2KmKsAAAcbxFwR8oJEJIIaK3HARriASR8sQhkUFGR6hKwS4ZhsQDbVCBIJvNl4ERFKyDetIiUKplxXuvFCQeq0W8rALPeZDhJ4FwD2a3CNajSjOAxFv21A+jUhdtRHo+JgoxekY73NwkncFfKHi4J1SDGCS/4kYvSPqU0F+GP0uhhQRoP+DWhb2ovpHcwjRI1TcoXsJM1uQLOLavPJDo4nDzYZKAK+A1kmIPGdGZyqKo3FxJWM9Oj5C3MkXhECCW0aEXfYQyj5TyzaPBOXLZHFhFqrQONqq47l6USJBs4wzVKxNsfY5G3B9uEEV2htaeyvGwN1PVBM5wNjS0cRffymDJcnDl0J4q9ogXopuNnwclqOtiom8q8InqmiW8DHwG9ynRF+q8+os3ep7+zU/bsT4tjzuQf8z9jLe4kuSyo7wNjLRHvRGRSX4E+LZwgIu
*/