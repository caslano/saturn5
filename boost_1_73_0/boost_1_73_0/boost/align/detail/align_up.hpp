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
waDjKIyrFmIaJRmYr1XNv7Ku0ioSK17trLgxpNfBKly3dDn0PZFXupEL4cCOmay1gGb+4aPFJKSZPxVnEZAkWzr4ooGFXax1mq+2dsnSOqtTcd4UuswbRYC1gcoyWCYWBeqg+qjJjtY4qmaOgoS9os/UkQhC/8DRQq7YEcWx/C7b6gMxE/24eFk9gevHTBDdaCcJ1OPm9LWrgEwhn0tVVRF5R2ovnLfUGmsoAuWkeE5DALWXr7K0BjpnUX3t0jo=
*/