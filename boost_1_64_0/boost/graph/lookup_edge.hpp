//=======================================================================
// Copyright 2009 Trustees of Indiana University
// Author: Jeremiah Willcock
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_LOOKUP_EDGE_HPP
#define BOOST_GRAPH_LOOKUP_EDGE_HPP

#include <utility>
#include <boost/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/graph/graph_traits.hpp>

// lookup_edge: a function that acts like edge() but falls back to out_edges()
// and a search when edge() is not provided.

namespace boost
{

template < typename Graph >
std::pair< typename boost::graph_traits< Graph >::edge_descriptor, bool >
lookup_edge(typename boost::graph_traits< Graph >::vertex_descriptor src,
    typename boost::graph_traits< Graph >::vertex_descriptor tgt,
    const Graph& g,
    typename boost::enable_if< is_adjacency_matrix< Graph >, int >::type = 0)
{
    return edge(src, tgt, g);
}

template < typename Graph >
std::pair< typename boost::graph_traits< Graph >::edge_descriptor, bool >
lookup_edge(typename boost::graph_traits< Graph >::vertex_descriptor src,
    typename boost::graph_traits< Graph >::vertex_descriptor tgt,
    const Graph& g,
    typename boost::disable_if< is_adjacency_matrix< Graph >, int >::type = 0)
{
    typedef typename boost::graph_traits< Graph >::out_edge_iterator it;
    typedef typename boost::graph_traits< Graph >::edge_descriptor edesc;
    std::pair< it, it > oe = out_edges(src, g);
    for (; oe.first != oe.second; ++oe.first)
    {
        edesc e = *oe.first;
        if (target(e, g) == tgt)
            return std::make_pair(e, true);
    }
    return std::make_pair(edesc(), false);
}

}

#endif // BOOST_GRAPH_LOOKUP_EDGE_HPP

/* lookup_edge.hpp
DgfCM+EgOBkmwQVwsM43OEz/PhwON8KR8FGYBrfDdLgDjoa7YAbcA8fofIKZOp9gFlQ8C4yD9eB42ARq/7bwbNgNToSD4CQ4Ak6G44z/dDgd5sOZ8Fw4C5bDc+BlcLZOL2yg7ydgAe6H4By4GxbCt2ERdLi/nwvrwhIYD0thJ1gGT4fz4BA4X58veC7MhgvhVLgIlsHzdX7BJXAFLIdXw6VwLbwQ3gEv0vkHl+lyBa/S5xH+HL4Fr4F/gtfCOg15lwBj4PWwM1yt8wneqM8jvEmnE66BZ8CbYTK8BY6ClXA0vA2Og7fDSXAdzIF3wlx4tz4OeA+8CN6rjwNugLfD++GD8Be6fsAH4TPwEfgqfFSnHz4Gf4Bb4PExtEuwDdwKu8Df6HyET8EJZv9s+Ft4nnFfCZ+Fq+DzutzDHTr/4Mv6fMJX4JPwdV3e4BvwS/gWbBhL+wHbw3d1fsH3dD7B9/X5gx/AOfAjeDHcB2+En8B74H4dPzwAX4efwnfgZ/Ab+Dn8Dh6E0fq9EGwFv4SnwT/CfvAQTIFfwQz4NRwLv4ET4WFd7+F3MBd+r9MFVZB2E0bADTASPmrcO2FdqN/f1INRsAFsDo+HXWFD2AfGwGkwDs6GCXA9PAE+ApvBZ2FzuAu2gBGNue+ADWBbeA3sCG+Fp8BNsAvcBhPhftgDHoK9Yd0mtDswHvaD7WF/2AsOhD+DZ8BhcBAcAwfDCXAInASHwnPgCl0u4XK4GF4OLzDuC427Aq6EG4z7V/BKXS7hbPgBTCW+z+EI+D1Mgy3ieQ6E3WG6Th/MhP3hLwmXBB+Cw+ALcBR8EY6FDnZnwgCcDE+FubCrTjfMgPPhGHiBiXc5HA/vg9lwM5wEt8LJ8HmYA1+BU+BuOBV+BKfDAzAPHoT58Bs4Gx6BuTCY4KajYYJ7fUuARbhPhMWwC5wL+8ISOAiWwjRYBrPhPDgFzocF8Fy4AC6Ay+BCWAHPgzfARfAOuBjeD8+Hv4ZL9HHAC+AeWA4/gEvhYXihPg/woqB73zclmTjQKrQRbUO70QEUMYxyiXqiFDQFLUAVaB3agl5BB1HEcO7BUCIairJRMVqJ1qOtaDc6iKJSuA6jRDQUTURlqAKtR1vRbnQAqVTSgHqiNJSHFqNVaAPahvagQyhmBPUFDUBZqAAtQ6vRZrQT7UNRI7FDg1AWKkDLUCXajr5FXdJIF6pAW9Ah1HgU6UAZqBgtRxvQdrQHRaQTL0pBBWgV2oJ2o4MoajTxogEoGy1GlWgreh9FZLAfpaApqBytR8+hA+gIajGGfEND0QxUjtajregVdBCpsaQVDUBT0DK0Hm1BO9EBdAS1yMQGzUBlaDXagt5HUVmcIzQIzUDL0Dq0Fe1Fapy7fmk72BNNROWoEm1Ge9BBFDOe/WgomogWo3VoG9qH1AR+ByWibFSGlqPVaCPajvYilU160QCUgdbw28VwJdqEnkP70Lco5kziRIkoDZWhlWgj2o52o4Mo5izShtLQDLQMrUPb0V6kzsYGJaIUVIBWokq0He1GB1DERPIb9URD0Qy0AK1Bm9EepCYRF+qCNgQ5BliMKtBmtBMdQtGTyVPUE6WhArQSbUSvoG9R0xzKGRqKpqAFaDXagnaiI6jdFOJAaWgiWoxWofVoM3oO7UFHUPRUjhGloGyUhxagiqnYo+1oH1LT+F00FGWjBagSbUE70V4UMZ3zhAahKWgZqkTb0F4UNYM4UArKRgVoMVqFNqLt6AA6gtrl8lsoOxcbtAZtRDvRXhQxk99Cg1A2Kkdr0Aa0VSvIMcJDKHoWeY8yUB5ahtaj59AedBBF5HEe0QA0EZWjNWgL2otUPvtROzQUZaEyVIE25hM=
*/