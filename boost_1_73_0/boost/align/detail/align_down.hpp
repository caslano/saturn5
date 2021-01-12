/*
Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGN_DOWN_HPP
#define BOOST_ALIGN_DETAIL_ALIGN_DOWN_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace alignment {

inline void*
align_down(void* ptr, std::size_t alignment) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return reinterpret_cast<void*>(~(alignment - 1) &
        reinterpret_cast<std::size_t>(ptr));
}

} /* alignment */
} /* boost */

#endif

/* align_down.hpp
z7Xb/u73BNV7Wp1x70TbWfT19kmkVDCmv+NMjYqD134C71afZKGB18OvDVlyQ7+1y16HZMtJJIl8ognUPDh4+2PcQRgfNqPcgU1IWqabv12Ws6bQrLVc4jbI7ofkJDyhLHEFyfdlZDJyHnXTvIsxs4Y3BOn3R6U9xU+m5ef6TZByMeNVrmL3IK283S+wvDHQ2p1UtIc0B7N1pkoUh7Bz2C9rUrAZAnvdu2pk5lbYF9kDYtBF
*/