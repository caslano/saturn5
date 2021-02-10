
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
NQ4BkFPiBxDuR8CUNBdUDRh4s1dgXLxI2PVQ3X0neU1J07W7V/8adsn6vjmfHc93Pnq+ly4MpyiGP7hho/QKsZvO4wA+O/7cNWKqcG3LPkw3Cy+ADRt6JKNexl3bcoGzZI1K8+AiCK+CLOznVBsgHy1cqsYIMk+z8Cy7dC/DeDHi4S7f4AizRnZlyXKGYwcVJS1OG8npwEkzcV1w/CTE5fYxfqRvYOLEYOWe6M5ObQ/tUZz/RfgPUEsDBAoAAAAIAC1nSlKZ0pJooQQAAPYKAAA6AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9QUk9YWV9UTFNBVVRIX1RZUEUuM1VUBQABtkgkYK1VYW/bNhD9rl9x8L44hSMnbdOuW1ZMdZzGiGsJktzUgAGBlqiIi0wKJJXEWPbfdxQlpPaSORvqwKF84r073r13dJc9ePXDPo5r4GDvJ2m+CX5w7ZwCKf6gqX7aIUkewP6h4xLXF4QawqPXQ3IAL/J6gH7jlbSxTs1zkrwg3NIkaf4NjfMyMY9osZ6t/0hUG8muCw390QEcf/jwMxzC66Pj9wM4I5zREiJN+YrK6wGcZo3l94Lc37uKfhwA1UBKdwswLpgCJXJ9RyQFfC5ZSrmiGRAF
*/