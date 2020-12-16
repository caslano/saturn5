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
OjkpJY39odM8JK1vUmJibF+SzbI1JD09MT7DWbampA2JTYnvN8y6zl72OmKp10zztqelJBj7S6f5ONIyY5KGJiYkRcc4665t1tEvKWWQM93PMY89WYXqdH/LumSmxMoeS0pxLivAmj84PT7Wsm6BktcnJT62n5kWZC7HWS5Y0mRmM62upCX2iU9ylqsvaSnRiZbtCZG0+P6J8rk516uBff4kZ5aznoaSFxPbJ72/Wb6RpKUlpMZmpNlznMsIlbzUtOi09FRrPWGSPijVWraJI61ffEKsJb2pvW0l9o9PjLXW0cy+3JTovrHmPg+3Ly+2b3pKfNowvaL8tdD5zf8i3/gI+iSlUrdzmS3NfZiZFpvq3LetzO2JNdPa2Nts6kDLukXay6Um3OHcrx0daUZb7hff37q8To592DGzkzX9Dmd6R+u2R5npzrQ77Z8Nic60zmZaR7POLjpNL8xM72qvM35QbFK69TjrZv9c0tItZe+StIGxw6TNO8t2t++L6NRU53b3cBw3/CcuOj7Run097XnRydFpcdb0XroN6hyzrrtJ19XoLGdeb8vxpDPN9Yp2rK+lfF/7MZYenxCjV8y5/Bi9Xropmumxer10jllXP+d66SxnXv8q61V1vjh7fRw5ySlJaUmJsf2d6xwvedEJyYnO8gN0+00xqkvsxxHuzEuw5CVGD4q15iU6tn8QLTdD+lfzmEm6KS8hNtHymQ62r0fqsMS+5jwp9mUlJ8QbS0yMyeyXEt3fsrxUe5uJzshMjk+OTeDITTX3YZq9L4qNjmHn91NmemUN2U+Zmf3iUzjkzPTPdHpyUkJ832HO9H860tNTkjl8zWUf0Om6Z5Vd4Vjvg1XyOP6Tq7a7Qzo/Os04Dpz76POq88UlpaZVqfeLqvmxg6LjE6z7/3DV/Phk5az7iM6ju01Kic3sS88U3zc6wcz/0pGfmpoem0Iji+07MNVS91c6nzODPdNS99HqebSnBEv+11X2rTm7mf+NzqddUCA+TRc0l33MsW6JcfF9yI5OdOYdr5pHa0g2807ovIw7I7vRnabE900zl/mtucw0WlZsjD5Fm/Oe1PnpqbF8gAlp0anO9T1VdXuSOUjSrNtzWufLhtIXZ6ZKP2zmf6fz01LSU9NYtG6KZv4ZnZ+aHp8W2yeTgTAzkxITnNt89qZ853qfq5bXrZOz3u8d6x2dkhYfnaD7I2f+eZ2fmMQHqDuaVEv+BTNfb5q9+aqmOv+Hqu0vOj0tLjMhdkhsgqXMRV2GFpI0NJP+KGOY9NqpluPjX45jNCGa/eJMP+tqpGeYx26AY5t1Or2LWfZ7e5rUbT32zut0ve3mfrtgTbf312beDzrPvCqz1HfRuWzJMrdBp1ffhk3e0qfd1P+8Z09n38r53EzfbKbL6dVcpy1munneNvO2Vsmreq5/X+dxSZJqTd9mzsOFwyDnMbTdTKe/GBibZl3ODnuePhskp8T2c+Z9oPMSYvtH9x2WEstJx8zbWSXPuOZ2zvehzktKTIlNTWdFLO1vl7kuzjmt27Bb5+tD3Uzfo9M5DKMT2GxHfR/p9L4J8bGJaTrXUl+FIz+d7bNca/zDni6dfoxkOuf52DFPfHJcbIozfa9Oj4nj6IseZNa1T6fLRWKflKSBlro+0XnygVjW61Od7mxbPv7zSV+rbMpFxl7Lz86VsQY9/ReQrkcULCuXsp5SBzXEJyXS3JPi+8p1BOmPm2ULCbklk5k8VIL/hCCu8/RYEZfkv/SDRAPiM+Kw0R7ayxgH2Xm52eO4TZyQX1hGz6THqqqvyMsvLC4r0ePVOcqHm++8PyXT2y1jn8n4FpI/0CzfRKaHMH1Cpnc43xVP/db37Oc=
*/