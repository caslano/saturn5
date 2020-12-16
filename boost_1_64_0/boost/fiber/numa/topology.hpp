
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
GWnZI5oZKTSvuG4oweTMFvb0tQhDwRKcpGqhY+z44rphBBmdJfSsVx108jqc3wOapT99zzacLa9G2HWUNpyEtrJeWc8Dp38UUU5/BmGF9pCTWjGr0AT5DBWFQ4IKkZfmCzS2yoWHrTOUgX9coXOa1ggrAYT+6etwsksW8e9EjaEDv04Cw7fJ8PIju7xoRzP1M5mKQm60TOTgRV+i75f0/Zy+P8o8nbw8TvcpFABAa1HF36hFh/YURD3/N/j4KqER8Y+ZQilH57Pv+bE3eW5BdY8hqIdninFzy/cJeCBY9cfzDLkrlZmrU2hqcd2JtIycwOnXGM8+HFFD6pLj4sk0Jo6cKQfp2ZKDPf7KORid2Bb5wMOa5+TrcBl/d7P7wXkgoVn7P4zX/vG8/eWy/X+0aX8xb3+5bP9cs/2vHFD73bbt73Zw2m9/v4EFvPhA44T+4kMFfeFWeWlPDkH8iTTi04CTkU9kczZupT1Hj76cQaxynay9r0es+hKEdNpjyReOSLcn0jtOItKYbpQQaXGPh0h3JNJ3n2RDegOSTuKkNwjSXYl0NZFm6UbTg0Sa/Lw46e5EutSO9FgkvVF9azI0pbiuN5HuSqRZuvErIi1eNKAL6/lE+vMTbUi/A1pftAyFqQcVYWqjjTBLAwVJkyTLY4yU0+AR4sOdObACnlFcdyRVbumJYl+q3IfuRYMoeS5PLjemseTBlDyVJ1cYo1hyISX7eXKl0WcfH+k/+ScJbOXXSjb+37VdCUqL614iS+jkGWIlaLhfH97M3LSTnJb6zJC9eY7szY4vse16uir8bzAF4yulYEzyMsnGJItyFcBuTajq/MPXhPj8mPZOvJUxSvwYeYLgx4P32ayM/yJ+dDhB8uNcyQ/3i2JlPIkeXeVDvK1scdmxZWanH84Wu/058HZE8887EXgwJVv1Qfy0s/hV25DLpefC+nRE3vwCIEsHw3cfw2k0hfj4+TSxg7+xJ4EdPK597LYI1Y98TkGvqx2TnwQGwXSh7OWRkzmodgce39HiejGQymSG06VsGlxJi1r3afL2+nmy2zOfZ9PgJNMHfl0nBzlsMNz1hBspQ9y5Ou7O5xhuVwqKI/D3Az4qOZPeiSQUjqYl/lW81Zx/jmUd4H/XMoWLuZKLrdDLsqHnUvujoK39kdUckIbmXW/yoTl2S1YWHPNmGHX34JT0/Bl+ghJ8P/yBglqPHzubCMlBjIYw5O/yzXxkxq8fVu8A4z8TvyL/tON/e87/NEoP5Ec9YqfJbZnelQnRy0uAnnAAlb9hvHsdoXSWLjrSBjkefG4b4b1thC9sI3xeG+GzWoKnASWR2ususTCFid9bnj8Q/NwfiO/9gfiFPxA/7wfiZ7WGT9P42l1s6IN1+d4n9ImraPhVu7i+2Y32oXnHgT2jEHPuv0uzZ9B+3oP28wnHyf28Ui7ORVvZFbXHmTfe09LQUVzAFhJ6bmk8E3mJyPfH2hD5FI5IpI/OG8eKTXHbp2zhn8NlC59xwROyAGc0k0qg+x7eOJvvPf9k15K6gUDL/c8l9XmfHiRDSuv3Ex3/YPyWmt86zwisBso9ij0SuvxI+ZNMkBAKbHkXAM8V4EiC2VoecHJbpmJQySYX7XWZF7aDQr8GpVXYVaJp5u1EhsW20DQf24KLlp6q1CILBF8go4BdA2BQH/yVCo0iZx36jb4+ZVm8kuHJ1kqighhdJYjT80DTLU3MRZEPvbZjoVQeUjHaDyl8jxQaiV3BZqQfUDTplluZ3463crksmb1ldJ7eyvva6a0sk62k16PyuF1qDNVzDNy/iuaJekb7QCUfDloqGc0UNWyaAz+V4sGtstDChwLgYnd+Up8B1JZaqeE=
*/