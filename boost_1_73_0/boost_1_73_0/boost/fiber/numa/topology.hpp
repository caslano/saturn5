
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
RPURq4zwZX8niF83jLW5bHN/KPiLmf1a64FDE/aOEnp+OglJURi9UYAMgfnTm7E6qRcaDiSvIpTQLG7mG1N1h1klSEGBImvYyYJcMJV9RViqLz90yENcrYVidRPLZXj1jTSvGigh41V0nV7YD98MudfzXWgn2jhPt7Sv4x1NBfAwamN52NwXOsF/dkqeTRHCB6CR98LGGyVywoNycA6L37VwQ/IFTooGkeR8meCVd7xUhq8ncd8NG9qGV6pTtWo=
*/