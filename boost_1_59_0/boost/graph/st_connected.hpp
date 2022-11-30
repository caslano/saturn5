// Copyright (C) 2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_DISTRIBUTED_ST_CONNECTED_HPP
#define BOOST_GRAPH_DISTRIBUTED_ST_CONNECTED_HPP

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/two_bit_color_map.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/pending/queue.hpp>

namespace boost
{
namespace graph
{

    template < typename Graph, typename ColorMap >
    bool st_connected(const Graph& g,
        typename graph_traits< Graph >::vertex_descriptor s,
        typename graph_traits< Graph >::vertex_descriptor t, ColorMap color)
    {
        typedef typename property_traits< ColorMap >::value_type Color;
        typedef color_traits< Color > ColorTraits;
        typedef typename graph_traits< Graph >::vertex_descriptor Vertex;

        // Set all vertices to white (unvisited)
        BGL_FORALL_VERTICES_T(v, g, Graph)
        put(color, v, ColorTraits::white());

        // Vertices found from the source are grey
        put(color, s, ColorTraits::gray());

        // Vertices found from the target are greeen
        put(color, t, ColorTraits::green());
        queue< Vertex > Q;
        Q.push(s);
        Q.push(t);

        while (!Q.empty())
        {
            Vertex u = Q.top();
            Q.pop();
            Color u_color = get(color, u);

            BGL_FORALL_OUTEDGES_T(u, e, g, Graph)
            {
                Vertex v = target(e, g);
                Color v_color = get(color, v);
                if (v_color == ColorTraits::white())
                {
                    // We have not seen "v" before; mark it with the same color
                    // as u
                    Color u_color = get(color, u);
                    put(color, v, u_color);

                    // Push it on the queue
                    Q.push(v);
                }
                else if (v_color != ColorTraits::black() && u_color != v_color)
                {
                    // Colors have collided. We're done!
                    return true;
                }
            }
            // u is done, so mark it black
            put(color, u, ColorTraits::black());
        }

        return false;
    }

    template < typename Graph >
    inline bool st_connected(const Graph& g,
        typename graph_traits< Graph >::vertex_descriptor s,
        typename graph_traits< Graph >::vertex_descriptor t)
    {
        return st_connected(g, s, t,
            make_two_bit_color_map(num_vertices(g), get(vertex_index, g)));
    }

}
} // end namespace boost::graph

#endif // BOOST_GRAPH_DISTRIBUTED_ST_CONNECTED_HPP

/* st_connected.hpp
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
*/