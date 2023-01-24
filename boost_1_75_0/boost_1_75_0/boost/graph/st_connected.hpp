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
+1F3FTxNwSu6c1X4KMRPbVPd1fzuLftrCur6OHlI/keEoJOaCdP2cfIL/gYV72D0X7SC25ofHaucY9BFV/G/G5VIURMnQ5cQCActG1DcA4oLyJxVxYrhFFEG3tengBkH4NvxB3aje5i0+PUsKJ4NZB0ICVrBC/MnfEnPZjZbFYBz//vUi80Zo+cG1NQmlw3anl9gIv3wp/M+sFhg8DxPYoR0AKJPxnxrylTSU941RYUTg4dogNwVyt0ZFdX8Q3KIaABPu1z5BdNw6BPwOkj5hRXlTmj/pzLYnBT3uHOiSjSgszzAO/DMyshb9sOSlo3OOZqUX25hWzsPodSvDw0m9JCNsJ4qYozhZM2BU3kqv/54gnpkStDnst+l79ImQXmBfr2qty/dkjxuht7r0WulE6qo6tHxPUdnmJQ9kQK02JadOETu6sAKcGNgQxtuw45mTlOA750QDBoVbd4lkG/L7Vq5MlJhSVmWFTdYsc9ngfw0rTX5NCXI7E0cX6Y183ihrg+GP3XFjl9hxHVRBIy7K0qQ3JzelFU3zqQr8pX17+sceE/wZwuidNeOFvCcsC2/MpO2PrRgC6QlpCQ8qvoVi3SnMZBdlb1UFGL5DQiw/3FZhoewXyycqpt8vQV8f5JKdR2v+unE4ieLu18FmSMOT8y7BsMMU/pzxoYhTROv8uFzZaQL7oEc7DZDWPO37hm4NHitGPb2WlpDEQPo
*/