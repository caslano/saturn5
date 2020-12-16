// Boost.Geometry Index
//
// R-tree scoped deallocator
//
// Copyright (c) 2011-2018 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_SCOPED_DEALLOCATOR_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_SCOPED_DEALLOCATOR_HPP

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

template <typename Alloc>
class scoped_deallocator
{
    typedef boost::container::allocator_traits<Alloc> alloc_traits;

    scoped_deallocator(scoped_deallocator const&);
    scoped_deallocator & operator=(scoped_deallocator const&);
public:
    typedef typename alloc_traits::pointer pointer;

    inline scoped_deallocator(pointer p, Alloc & a)
        : m_ptr(p), m_alloc(a)
    {}
    inline ~scoped_deallocator()
    {
        if ( m_ptr )
        {
            alloc_traits::deallocate(m_alloc, m_ptr, 1);
        }
    }
    inline void release()
    {
        m_ptr = 0;
    }
private:
    pointer m_ptr;
    Alloc & m_alloc;
};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_SCOPED_DEALLOCATOR_HPP

/* scoped_deallocator.hpp
aZhmRj9Hq9F3Be+9iS8sf8M1f/s1f7UdkBZ/9amLiPyV0aZcK1Dzu1l0aDuWaX41DmJOUX9WyhRPyFEZHbe+E5nYaut5s+hZ4gjbp3NFHfezT5LKiL+aZ58ge9yzT1LK/r2zT/prXmfoDf100mwIc6EPnWc5eeWAz/zJOWXTi8oLxuvdsHwILfn6NimoZ5NvDdfK7Ic9UeyDPXqGiRlnRhjZ5ubMgnyxn+tJqdwTY9p0HqCRa7OPc67IDPGYvRXK9PtpoyfNLO1jfGdLnzngKnJ9PVXk9OvcVjq+LBa5tp5Y7re745qHWcy192dG06PoTds7fXH1z5X6VnSvetJ+FV2YOUu22RPDlFfmn1eUhe+LsS7C/lqE/cdKe1h7TNKPuJvrdZ+BmUZhm0x36tjOmW5CpONg+PhJvapsc1P+ldU4czJ4vZdGjCEDNV/Z6Y7w43rNb8YsTsXdydfxHkITt4zzZq8ufph2VCzh10SO6aYNPS7+fdA935Sjm62YfyKXmNg0sUZty5TxhxQdz1VuH+ZHkatYHpT5SWWCcSWm65gfX1GRyN1z5Lgf3Pv7Zx33v9Kx/6htr8b5CU5/qfswpYfv6W1bV6K/rCtOqD/nIb6lZYX/qEb/Hbp3QgsakWhf6+4yTHx96tpJ+zKzb0JesXnKnWL6OnFhiDFzXA1XX2QeTdbzPgumXib1SvLZcMkVurez2WdAY1aZoXClyJwpdZ9YX54t2g3E9PG/E/+mZm68Q+zx5tmfF/35MH7Mca5v+tbIffZMmcw1TTlwN+WI2EdE8x55FtUp+p2DA+ssO5xdjitFr8XFOXmlxDchp5D7d71e60hf6TioPlV+pPh/6Izf06dNM/fDxt+EZ35XVOz4Zxv/umpnjRB2/lV7/w7ipIySJ7OHJPnATfIhbulGTtIO00PXBu56yI3UgwSNqgeVr2uenWzQckTTS+4J9KL+/3E9BPvI9aqHznqNd9Q+cqvqIWoHyZ+5dz3+tT088toe2rDq/nX17DY4I7h/XejrGXY2U/3vqVtl7zoNk2byEpta/X3piE/3pQvP336X/GXUJ7RL/kLHtaVJVfPXJCJ/gZPYN4/4NH/h91RjG1XN3yn2PZVb/syGgye/32BQHx0aV03vXXSX65Ze6fSywuj60DBp4r+k6nN242/GtWrk1UVf5pn7EvPMPbzdJzWpWqaG6LDCrUxl9oSOWbBsVRi9bIQ1z54fSwrOaXi7bspnZEz55qf8svKlafkeEzdNJ6LeNjZxb8drXctYMq08etkIE57vn35hvkP74IqmVfN3xJ4vhuePKZm8vNG5V5W8qXya3o9VaVPG3zxHOYk2RXpV2hRpaJsKL0+LZlXLE0Dfe6uWh6vScu4xU8PbiXl2F5HnH6qh7zTNM3FGtgmTx60ueWxan/9mVs3j9ClOe2hcv4rOkQ/PX9xJ6JT4XPvdNc2r5q05sk2q5M1saxq1TRDGXItlKa57miLzy/c0Jc0q1yLpRO5pavRe3MK9rWe5lI0eNEq5VD56W8f/l/efJ9PWY1tWLU+sff9UpTzSs0QrD/K/vF8hPtd2tMclby3tvr1q3nTHrajtXMOkhT0vnqH+qbAiIv81T0LfpFdF3/qMlDTC59iLW4U8s9IyDSQDa02Z5Dkto5TzzD1L+pU8LUdQLi7Eb7zTZoxfrRM+lwo+jye8/f5T7EnGPj7s2WQHVcAMTKrO41pT3q2a37LiLpJjfS0frX2ofLrZP+5tsedYo2RWZfay1PoIytcV+TTsb4j9EtZhxITO18vRk5mzxV+lczSx4yD29rjwz8wFi3RtCu8ZZur7UuM31ezhnQ6PiH8Hmf8vbUWeWuNH5hID7RM=
*/