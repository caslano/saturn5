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
WgTDwHJRbEdpQwaTBzpADqzIhFPlFWicbBlQqxri0G7W0kSraULMhILCa1sjx9AxP3r2sysqBfBVOVtI/qppKHHV6cEDy4EoFTov22Ls88K8avAuXFpTzg6DtFZsv3hsXnxSOSCeoMciRgDJlEpGj+NVlNZUws46PatKG2mhtVRDsCse0WQbFomqhSsDdaX1pdVmV4yHWjXUli8praiop4lRuqgysKKOxjcb0tp7unvxbHBHFFagkbroVdX4Kxc=
*/