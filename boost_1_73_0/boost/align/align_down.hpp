/*
Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ALIGN_DOWN_HPP
#define BOOST_ALIGN_ALIGN_DOWN_HPP

#include <boost/align/detail/align_down.hpp>
#include <boost/align/detail/not_pointer.hpp>

namespace boost {
namespace alignment {

template<class T>
BOOST_CONSTEXPR inline typename detail::not_pointer<T, T>::type
align_down(T value, std::size_t alignment) BOOST_NOEXCEPT
{
    return T(value & ~T(alignment - 1));
}

} /* alignment */
} /* boost */

#endif

/* align_down.hpp
kpPvTfY/kHyn3ocWKUrh+D+/RTbW/KE4PsdHrJYD4CJj6ivpA6DJGHkP+yGFtZP+0gRTh3rQxwJCc6Z46Yu8xe/oM326Y9yTUsQcFPHQ4o+T5Cz7bQCEXfmu6F+ElBjqWYVu/wwUdTmxxLz5fdIuIAQWccGeG659jJPjnPcw8Mb4sW4x3eGMDElEAjk+3hqi/9JwcHwIn5a/uQdHZDp5+6XrbhcZCK/E4bhG3yy3XrwBw1Hx
*/