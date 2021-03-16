/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_MIN_SIZE_HPP
#define BOOST_ALIGN_DETAIL_MIN_SIZE_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<std::size_t A, std::size_t B>
struct min_size
    : integral_constant<std::size_t, (A < B) ? A : B> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* min_size.hpp
/hXNbjNWZJyy4r4stgpvF2rftpBOItRt9HUV3kF/TdBBhhhbngBpY8zRTVTNl/rUKMMvXG+5TJ/3aYKvS8AhQoB0T0iUv3uZl/X5SPvhgwbqiKna+Bg3zKCDGd9RHCKqpPktetRSihMqlS+MpMXweqR0fYNZg4N8BTdQLbOSm6coll1uykveWcd6vyTrbdmj1OV/TiiTQn3hPCmFigWkdwsqg52713RUa8obhx5t0Eru5HtD72tVBd5AhuaNpdY=
*/