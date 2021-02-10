/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_SUNOS_HPP
#define BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_SUNOS_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>
#include <stdlib.h>

namespace boost {
namespace alignment {

inline void*
aligned_alloc(std::size_t alignment, std::size_t size) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return ::memalign(alignment, size);
}

inline void
aligned_free(void* ptr) BOOST_NOEXCEPT
{
    ::free(ptr);
}

} /* alignment */
} /* boost */

#endif

/* aligned_alloc_sunos.hpp
turbVGW5cWbNgr310vQXKx2jkVR6mgyMS1QRJxE/tTsBbU1e8EgtAIhgqWoFmmnbjVrG4kjB/wdTlMpRROJayGpMgxC0vw3VgkxVYmmRRKjSUjesX7QE/yF4WnedIQasFwCzCxi4hVShi7VrsSJMPbchrHaZS2G3qRGstcS7OvQSUE7MmzMIQWX3a76kYJoincwtxT+zwcNWWlEOpQKLRP+ArEAdKK3O3m7HfBskhGulHGbEAfCiS5uuqqRbZrECX1E13VWRTcCEOpx7SaJWksen8dqnJ8dvL7Oj4/PLk1cnR4eXxx7QZ45cQlXrEjBDxpJh1h4SEWUSy9ZjSKHKOawb4CF/DC1OJBgPHQNcEHXLIZj626Hs6ih4hnUhdHB6vXSfuew7zAD/3A26CUT1vj3wBWP2VNWzfADB4Rv378RUmI/FOuQcUTkPH/MK5Ww2kC1vGhac5UVCVV/Y6Szv6+L4/E/H5z8Xzjq4PZFuKCqquG/0Um9lXtafwE936fWU2lV6XkRI0WfWxCmz32q0YT6nps9pvYlIWIcos6z5oeKN7S/ZWHb4/vL1u/OTyz/3Pt3dPjrkqrb3XNNmmTqjpxB9RN+xZ1rN9LS/HkqOsvOKu34ITjEwpi2vqyR+TjHL0x1KLceoh2upchtO
*/