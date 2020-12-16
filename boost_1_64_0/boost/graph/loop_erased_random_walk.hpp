// Copyright 2010 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Jeremiah Willcock
//           Andrew Lumsdaine

#ifndef BOOST_GRAPH_LOOP_ERASED_RANDOM_WALK_HPP
#define BOOST_GRAPH_LOOP_ERASED_RANDOM_WALK_HPP

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/random.hpp>
#include <boost/next_prior.hpp>
#include <vector>
#include <boost/assert.hpp>

namespace boost
{

struct BOOST_SYMBOL_VISIBLE loop_erased_random_walk_stuck
: public std::exception
{
    virtual ~loop_erased_random_walk_stuck() throw() {}
    inline virtual const char* what() const throw()
    {
        return "Loop-erased random walk found a vertex with no out-edges";
    }
};

// Do a loop-erased random walk from vertex s to any vertex colored black (or
// actually any color other than white or gray) in the color map.  The color
// white is for vertices that are not part of the path, while gray is for
// those that are on the path (for cycle detection).  The vector path is used
// for temporary storage and as the result of the algorithm; while all
// elements of the path except the last have their colors set to gray upon
// return.  Vertex s must start off colored white.
//
// Useful references:
// http://everything2.com/title/loop-erased+random+walk
// Wikipedia page on "Loop-Erased Random Walk"

template < typename Graph, typename ColorMap, typename NextEdge >
void loop_erased_random_walk(const Graph& g,
    typename boost::graph_traits< Graph >::vertex_descriptor s,
    NextEdge next_edge, ColorMap color,
    std::vector< typename boost::graph_traits< Graph >::vertex_descriptor >&
        path)
{
    typedef typename boost::graph_traits< Graph >::vertex_descriptor
        vertex_descriptor;
    typedef
        typename boost::graph_traits< Graph >::edge_descriptor edge_descriptor;
    typedef typename boost::property_traits< ColorMap >::value_type color_t;
    typedef boost::color_traits< color_t > color_gen;

    BOOST_ASSERT(get(color, s) == color_gen::white());
    path.clear();
    path.push_back(s);
    put(color, s, color_gen::gray());
    while (true)
    {
        edge_descriptor e = next_edge(s, g);
        vertex_descriptor t = target(e, g);
        color_t t_color = get(color, t);
        if (t_color == color_gen::white())
        {
            path.push_back(t);
            put(color, t, color_gen::gray());
            s = t;
        }
        else if (t_color == color_gen::gray())
        {
            // Found a loop; delete from path from the first occurrence of t to
            // the end, coloring vertices white.
            typename std::vector< vertex_descriptor >::iterator it
                = std::find(path.begin(), path.end(), t);
            BOOST_ASSERT(it != path.end());
            ++it;
            for (typename std::vector< vertex_descriptor >::iterator j = it;
                 j != path.end(); ++j)
            {
                put(color, *j, color_gen::white());
            }
            path.erase(it, path.end());
            s = t;
        }
        else
        {
            // Done
            path.push_back(t);
            break;
        }
    }
}

template < typename Graph, typename Gen > class unweighted_random_out_edge_gen
{
    Gen& gen;

    typedef boost::graph_traits< Graph > gt;

public:
    unweighted_random_out_edge_gen(Gen& gen) : gen(gen) {}

    typename gt::edge_descriptor operator()(
        typename gt::vertex_descriptor src, const Graph& g) const
    {
        if (out_degree(src, g) == 0)
            throw loop_erased_random_walk_stuck();
        return boost::random_out_edge(g, src, gen);
    }
};

template < typename Graph, typename WeightMap, typename Gen >
class weighted_random_out_edge_gen
{
    WeightMap weight;
    Gen& gen;

    typedef boost::graph_traits< Graph > gt;

public:
    weighted_random_out_edge_gen(const WeightMap& weight, Gen& gen)
    : weight(weight), gen(gen)
    {
    }

    typename gt::edge_descriptor operator()(
        typename gt::vertex_descriptor src, const Graph& g) const
    {
        if (out_degree(src, g) == 0)
            throw loop_erased_random_walk_stuck();
        return boost::weighted_random_out_edge(g, src, weight, gen);
    }
};
}

#endif // BOOST_GRAPH_LOOP_ERASED_RANDOM_WALK_HPP

/* loop_erased_random_walk.hpp
DzqIos8hP1EWWoxWoc1oN/oWtZjNfpSFdupyDMvRerQV7UZHUNMC0oImogWoAlWijWgr2oei53CeUTbKQwvQGrQFvYIOoOhCfhMlojRUjFaidWhTIXZoH4oo4jdRT5RVpGq32q12q91qt9qtdqvdarfarXar3Wq32u1/aotAM/9Z6/+fm194Wo+c/ML8Mv0VgL/rGwDxKlrmOa6qr2cQl06dnzsjZ3qxEv8y/FeLf2HuuTLs1/XXY34rff7z8W+pomLXt1QqIysjZ0hSWtrgpCEjc5LTx6eOHZ3ObvnWwHm+bw1sc5Rss1BD6RZz571kMDhGf2uAgy6cV6yqXW/+GrE50bixFnejn7COY7/YXLFV6uSTXPflxl0U47o3WnfVdbHp15ZtbYD3urAcdiSOrW56i0uKpueWlubMKiia5q5bJ3Mgz2UKsF1f09h2tWugfibuOQF3XqrYMzHVtW+kQvan2DWu94v7MuNm9vF6yQfJo6CkL8/OT150p973tGPiZistmFrq7o/H9YXENTvgy1/7uydJ2L7G7f2OF9e8GTqhcWYd5IfE/nInoILY4GfDNJMwSZy0KMWU+KmKMENkLm1X9IKE66bixc8Rv4F3ab9XVF31pMxpHSRljvxUbKHySc3AYcvDZIlnhp1b+xtxz3e6qsaOL80zSbNdS3ah/M7lKk7coTD5ziP4eevbUbiVN4f2Uglzvp2r7v+dk9UoWUNSj8s5X89tjFyaGB0RVT+vfl5kIHhi/fz6XSMD0ccHwtbotMfwrcR1lS3TzST/WqqTQ+mPmDJ/akE+mZibo6tch/79p/Tgv9L883L9a2hFSRobSxrjcH8t8Y7F3Tu0jidbcZV1X9tLmBOwwc1xpYn7RdVKPSDzLeNVpqRh74m6Itu2wJaX78U+0q4L+oW4G0h9XB849tyqioDMrZIx7Dv5m3qDW+qN+O3Gr0yJH6fP+14DZQo/KVNSbwv1ceI/oonrvs+4TzH1vMVdrvtUcU827khKrLu/GLfffolxN23i2i8Js98UZv9+mDt6vetONO4TjTutSdW1mWfUVbItNe3gIrQCmyliX17lnNe8xmvIPs6uqVQi7kLVn/+zlPNXl6Pl66uWowXizlcx6oxqy1EKv3mb2LQ6Vjs8wvu2Zdh8EnO9qZDriqRG8m2NxGnPG27vPJCP9tu17eor2W4PKvyog/CB5vSdi/1S94rJzI2++qBD+Rhp89HWBdd+kLjH4U68W7tzgtr+vubGfr67Xny6uYadKjYzg1L+bRz9JO+ycHeS/XnBd9SR0LWBTdciZdfO/ZPYDAjscY5T8eLnqJ3i91igEyO3jg9MCG+X7Lq0i+/VdrkqC4s4bDrESfzT58woyC/MVbZelkp82cbNlWeDdp/sb9d1HbPtel+J9ym1Vh2nWopfKE0PBe6jfh+gxOY5a5VOWz17XMV2/YKHxfaRwIhAL+NH6ZDfnMwx9vXnhZ5mZK+LX0u4WMe/9mrO3HlFZblu2vKxeUdsfnD6OY8TF342v2YHGqokZ5IT5dSzeTHXrt2XdI+UBzVYdVDNTHsXJX4tnRbcsd2mhqn6ToPw+w7Jj8OSH/2NO5R/Tfn9s2IjlNvuL05wuQTRbko9se2mW3RsWvZJfKerFqatzFDVbc5FcaatlG8WOQHvu0ORuH3zsVLwo4y6fvPd+jPgbvMtTNMOnWPcfYx70r1V261Scdt2T9z+du+uMPuIDVXvn1qFuXsZdz9jP2yDvf+yc41aOzXPUWlyovYva5PdtlfT2D0DF+7JubPgmRdqnpOTJ/bOBy1Ln3n0qoSiA1e93i3z9Zya5sbUNAemprlGNc8p+oX8blLUze89fkmD+08=
*/