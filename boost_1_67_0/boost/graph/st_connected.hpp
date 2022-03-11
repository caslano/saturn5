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