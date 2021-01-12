/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_IS_ALIGNMENT_HPP
#define BOOST_ALIGN_DETAIL_IS_ALIGNMENT_HPP

#include <boost/config.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

BOOST_CONSTEXPR inline bool
is_alignment(std::size_t value) BOOST_NOEXCEPT
{
    return (value > 0) && ((value & (value - 1)) == 0);
}

} /* detail */
} /* alignment */
} /* boost */

#endif

/* is_alignment.hpp
P/cDc9ZnONVSjMho0t3oy/088osQ7miQYxk2ghlVMlxY2zd4wNrGK3F+xAzO1Kd2nuZWKTyRLl8ca9ZF9smQVfYaqh1Mp4j5ByQAUC5qhbz7as3CNslAnkC5TeTsK8NU+GspHgZ1bWFJFg4JG23rF5CBYsVj5NLAo0Q5vSGzhRF0VSb9uFfTRtZ5lUhps4h2ak/IiRcjRge2oPwkGBQyj0/VLG9c2WW9tCDJBVB4yMyXUQlj
*/