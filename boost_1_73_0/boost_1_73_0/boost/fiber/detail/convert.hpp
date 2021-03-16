
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_CONVERT_H
#define BOOST_FIBERS_DETAIL_CONVERT_H

#include <chrono>
#include <memory>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

inline
std::chrono::steady_clock::time_point convert(
        std::chrono::steady_clock::time_point const& timeout_time) noexcept {
    return timeout_time;
}

template< typename Clock, typename Duration >
std::chrono::steady_clock::time_point convert(
        std::chrono::time_point< Clock, Duration > const& timeout_time) {
    return std::chrono::steady_clock::now() + ( timeout_time - Clock::now() );
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_CONVERT_H

/* convert.hpp
jMN8fnQ9XQrG66jNeZt8iENH5fHIQ3wBbqH9Z0+M14PU/8fyZF8B4jS4Tcd4H60Hpcdk32HERXBbjvM++trbi8Tk1/azOx/dho0Gk3KC7z+6XxLxlZwfLRQx4GIK+PF9FpEF5rcazrSe0ucX2pzEOlTI++gPGXwM5sDXNmfaj+jvEoaewvX5aZvzN/heRTQvcljvFPH5ZeH3bgPzdLHNuQw+ur68BuaVs7yP7k8uAvPMN/x4nEHcfR7XeTVfP2g=
*/