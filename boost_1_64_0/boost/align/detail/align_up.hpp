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
f66lzgjl9U2O3dH9xyCujasy/ZYflcGcKE3shlGZHTx8xzlArxhVizPqStKlguiJEv9/9cfcqZoxrIZ07iHwdV29v4NNWWP7H0m9IuI5ULe1gtFK9nzFsx8ouiZOESeJ34dpNEroehdx3ZHU0Et832onHXpqhCunm37S1SjSXiTpvjxsFZ1SyOTNk/zBmlwBHqUBVaW3sXx7I/cq1ZBqdu5zm4hVYVOjBJpRqik3z+r+Kbtr42Nz3tX8LMW141I9WCUEKK7V9pcTmv09fAGiEx8FUvw5gO5L9W00IxIZj9wkJ5VmDhuEzS1Koy+RVqp/C1Ll2bIaYfjBrX/lCC5M4mgVgljmz0X55J45LnaFWe+Q5ix5eDfTruPsWMQHiM7qfQwTDTsH5abVISOMAtCHonQVBX3/UP8I3W7hZO0q8RNjo1rQSjzQ0rO4g6RaWP+A1gAmHrJzKhs68PX7xeKJTnhw6oIukDRkgvOgV3wsEYJnb7xWQh9/jTeJDZMPzKdWIcW5K3syg2CIhlwHaI6Htk+O7JwJbNt9OSLEHrXre2ve22a9MovavEJzWQ==
*/