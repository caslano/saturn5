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
WIbiN3rjX8bdvpQiPi2QGpNq+FZ/qAXi98jATd7oS97obTaexTUF91ZVrgLmlUveV+rmeWfI/NBUUaijCyFsZiCL5aQTh8elFfrl561hUzfwMEDVkSib9LJwGVc6jzBqDmZA6CZ7e7C+2agp5/2mtdz4pT6JaQGpkkMqxUsZzL1hq931I4hym2vrqXIK6567lmvdQzdZa90kKYLYBbwkoFg4Z+IWlpZhcWc6KAf3PvQuxkPH
*/