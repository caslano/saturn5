
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
HFdgGFgk0Pw+n3nTVNebNcadiZKxmPAfcm4cQTqtx9AGLVqpDZHKxoGaSry9qh29WJf9wFoG2yGYhicerDA/meFd3qTfc0/uUOkkXmKNP1Z+pN8A5fwIG637uXaWX3yc/ah58dGASC8DqRhmDYkeUwLie0XhUdp8BbTBjxsB1vtC3zk1SYXhVEd0oM9FF+6cPTrvYGwsnH/CKEeuRqzRwYfBJBMEr5IdLf6KDGOu2RicimiVxooo5ordJKvIsQrINJv3UweT10FikxlP6Aw82mCqPR9S9Eq9yl7W+bhuUskVcHEeOKXupXsF9z372HgX3v0lN0yg5MI90gxoLTfljkZGSa/dEMlThrGyyaoL7FcP0Jh/DqIjT1wVh9E5FiuApgscwGxArDruzIES1rYM9Y1T7OoFryXV7bs+b3WfI/eDjY/R/SHm5XDNceL+eHMRXvGGSuPSVfkAcwRfEvWDiXnygWik24+iJWn9+JLQXffxHbgCnnJImE1p5YvR3DFFX5fUijxukTAZeuBo4sRjk6tb7xkNJHL7oOs3i8hzf5EGBC5Aj7JzwAVZQw==
*/