
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_NUMA_TOPOLOGY_H
#define BOOST_FIBERS_NUMA_TOPOLOGY_H

#include <cstdint>
#include <set>
#include <vector>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace numa {

struct node {
    std::uint32_t                   id;
    std::set< std::uint32_t >       logical_cpus;
    std::vector< std::uint32_t >    distance;
};

inline
bool operator<( node const& lhs, node const& rhs) noexcept {
    return lhs.id < rhs.id;
}

BOOST_FIBERS_DECL
std::vector< node > topology();

}}}

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_NUMA_TOPOLOGY_H

/* topology.hpp
Lld3q2EOvBnmwsdhHnxS3e1Td6/ARvBVtX9f7T+E2516E8d8KmwFH4I94G9gL/gIPAk+DofCPbAC/glWwWfhZXAvXAOfhxvga/CXcBh8FJ4F/wSnw4OwAL4FZ8MPYBH8BM6EvNIS+1RYBLPgacS3GxwMZ8BhsALanL8E+uA66IcboFNuN8DPnf5CzffDHpx/UM2PwR9i3qPm/RruATgCfgRHQn8CfSfMgmNgHhwLm8PxsBc8
*/