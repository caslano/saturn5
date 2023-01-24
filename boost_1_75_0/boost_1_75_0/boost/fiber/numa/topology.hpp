
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
rJHUfSzcJKIIfyI04dZrUjiR7K1L4Dl7RDjbPRhN47QaDyyK8XUM6kCB6xOBbFHAV4bB59ExfFChcuqbDhAmrmIiapovYAIeUZbUzKX/EWrm38JEalOydyxlXXr2GhGTY3on1WKoCy+FqmULhXsEjRY+lndAcN03eFuZNJ7xHXCAw68Wm+f1QwmUEjrTKUeJqIeuAl28XjbAz5dbMVLv6DA1JrLLKZI0gje5qgdPTAa3890Qn7cpXbio0lgXrrZn51k5E+yUltPdBmMs1iOtH77uTVxgof/+ij99y/B0F3/6tuHperO2OqDoVcPEOrWF79JLzMtTB9m85GsL76CF56EgxcR88m8rhYAsNtM0l3BeqoT8aeC7I/mrdLLUUoOnHgy6ivXNteOFoEvYZirvcIkk4tqWqHYUmnI9ShIJvzhngWMMxOCF7RK1sua1bzDC+NBghKFThLuFIhwwD+7Bg/8CPBOZi7aHwkCNn8o8qJwQjA0rMQjGjIcAECzv0zNhnRlbiUtxw1VJ2ZmAMXXjdidATN09Spud9PrvXSgbPUWX39gF3v6yi95+y38f2qXjmQ24tj61RVzb9l+tw7WPcFy7753W4NrhDzWHa+d8JnDtjM9CcS3pAoYbMe6VqSEY90s8K9su1WPcpNcJ4xYDxq0kjLukJ2JcXxpi3MesBNnFyrw3COMWB62fvm0VaQleeioU4zYsawLjTmMY
*/