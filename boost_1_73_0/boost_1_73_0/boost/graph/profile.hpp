//
//=======================================================================
// Copyright 2002 Marc Wintermantel (wintermantel@even-ag.ch)
// ETH Zurich, Center of Structure Technologies
// (https://web.archive.org/web/20050307090307/http://www.structures.ethz.ch/)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_PROFILE_HPP
#define BOOST_GRAPH_PROFILE_HPP

#include <boost/graph/graph_traits.hpp>
#include <boost/detail/numeric_traits.hpp>
#include <boost/graph/bandwidth.hpp>

namespace boost
{

template < typename Graph, typename VertexIndexMap >
typename graph_traits< Graph >::vertices_size_type profile(
    const Graph& g, VertexIndexMap index)
{
    typename graph_traits< Graph >::vertices_size_type b = 0;
    typename graph_traits< Graph >::vertex_iterator i, end;
    for (boost::tie(i, end) = vertices(g); i != end; ++i)
    {
        b += ith_bandwidth(*i, g, index) + 1;
    }

    return b;
}

template < typename Graph >
typename graph_traits< Graph >::vertices_size_type profile(const Graph& g)
{
    return profile(g, get(vertex_index, g));
}

} // namespace boost

#endif // BOOST_GRAPH_PROFILE_HPP

/* profile.hpp
Z43wZj6LFld++LHRSJstr7GEf3BBPvqrf2bxKmrA5s7CBTyHF6KFsk8jwxbm8I9cqOHh6NQfdNrHp+3RUZN28TgeBzMgxIsxshzpc5w8rlM0Bhq/gN0dXwawc8YM5VFoGOjJg2fNF7Ky7LJ9fNzf9w/PevuN+Y1qYR7MZvG4WBrH5iqPa+qscDjodAqlp0kYQlFZFmnrOAYIgpc+nKFx6F8t4usFYj//Krzxs5tliAu7AjaYzlcYpDfeI0SheY9GKwJDlFRqeedxPIPv8SIsaYAOIwFkOA/Gl7dvaBLfsu546eOr0tqq5Fi0BBzRPMhWSXlr0eJi7WCWl4CF/apBRema1a0AefqIaqIVrOI9wh9iEJMwmMgNBJB3DQOBvdbi1Fkabuzua0Pt3Hlx6qxOWe/A0cPxma+Zh2g5nKwZS9WsgSoQdAN5R1pX2mPpZMq6HkvyCWQ7A7QG30oOFvHaGpzcesErVx3R1GMSZob7xCdl8RiW5RJI1Ay4rS2SAhgR6/2L98YPH06P99L7XxjQDjS201o3JsD+KbBUc2IfPOeki21gJatQXn0Sr+sUqk9iH6RDriOQUHUtqrMQo/zvzqAPhP74uLIOdwMshDY3MeCKeo8fyQ3KR1jE1Y4G8opwzPWpwc/148zr5BBf
*/