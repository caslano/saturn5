/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNMENT_OF_CLANG_HPP
#define BOOST_ALIGN_DETAIL_ALIGNMENT_OF_CLANG_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct alignment_of
    : integral_constant<std::size_t, __alignof(T)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* alignment_of_clang.hpp
ThxdDMBHywn0tAIqMYFKFJARsOVJ9CfRD1R7jLmnP6lX4wpCfDqPjWDM3FRiPHnKGoy6SGJlkoK5UIKT60EOq4ORjMdVJs/JKH23o4dMrbCJoXfu5LiDAIvOvZcZgVoXdHQrEDSTbNg1CUVWEKf5VPNR/KnQWX1FfXITt5RgQo4qy9hV2j5rlIyhDm7mbxgtCWnMWf0sD/5MmFzCSImMmQnL86Qs5nptP4tKrK6Y0fOA03Xc
*/