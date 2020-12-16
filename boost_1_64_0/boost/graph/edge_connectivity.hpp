//=======================================================================
// Copyright 2000 University of Notre Dame.
// Authors: Jeremy G. Siek, Andrew Lumsdaine, Lie-Quan Lee
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_EDGE_CONNECTIVITY
#define BOOST_EDGE_CONNECTIVITY

// WARNING: not-yet fully tested!

#include <boost/config.hpp>
#include <vector>
#include <set>
#include <algorithm>
#include <boost/graph/edmonds_karp_max_flow.hpp>

namespace boost
{

namespace detail
{

    template < class Graph >
    inline std::pair< typename graph_traits< Graph >::vertex_descriptor,
        typename graph_traits< Graph >::degree_size_type >
    min_degree_vertex(Graph& g)
    {
        typedef graph_traits< Graph > Traits;
        typename Traits::vertex_descriptor p;
        typedef typename Traits::degree_size_type size_type;
        size_type delta = (std::numeric_limits< size_type >::max)();

        typename Traits::vertex_iterator i, iend;
        for (boost::tie(i, iend) = vertices(g); i != iend; ++i)
            if (degree(*i, g) < delta)
            {
                delta = degree(*i, g);
                p = *i;
            }
        return std::make_pair(p, delta);
    }

    template < class Graph, class OutputIterator >
    void neighbors(const Graph& g,
        typename graph_traits< Graph >::vertex_descriptor u,
        OutputIterator result)
    {
        typename graph_traits< Graph >::adjacency_iterator ai, aend;
        for (boost::tie(ai, aend) = adjacent_vertices(u, g); ai != aend; ++ai)
            *result++ = *ai;
    }

    template < class Graph, class VertexIterator, class OutputIterator >
    void neighbors(const Graph& g, VertexIterator first, VertexIterator last,
        OutputIterator result)
    {
        for (; first != last; ++first)
            neighbors(g, *first, result);
    }

} // namespace detail

// O(m n)
template < class VertexListGraph, class OutputIterator >
typename graph_traits< VertexListGraph >::degree_size_type edge_connectivity(
    VertexListGraph& g, OutputIterator disconnecting_set)
{
    //-------------------------------------------------------------------------
    // Type Definitions
    typedef graph_traits< VertexListGraph > Traits;
    typedef typename Traits::vertex_iterator vertex_iterator;
    typedef typename Traits::edge_iterator edge_iterator;
    typedef typename Traits::out_edge_iterator out_edge_iterator;
    typedef typename Traits::vertex_descriptor vertex_descriptor;
    typedef typename Traits::degree_size_type degree_size_type;
    typedef color_traits< default_color_type > Color;

    typedef adjacency_list_traits< vecS, vecS, directedS > Tr;
    typedef typename Tr::edge_descriptor Tr_edge_desc;
    typedef adjacency_list< vecS, vecS, directedS, no_property,
        property< edge_capacity_t, degree_size_type,
            property< edge_residual_capacity_t, degree_size_type,
                property< edge_reverse_t, Tr_edge_desc > > > >
        FlowGraph;
    typedef typename graph_traits< FlowGraph >::edge_descriptor edge_descriptor;

    //-------------------------------------------------------------------------
    // Variable Declarations
    vertex_descriptor u, v, p, k;
    edge_descriptor e1, e2;
    bool inserted;
    vertex_iterator vi, vi_end;
    edge_iterator ei, ei_end;
    degree_size_type delta, alpha_star, alpha_S_k;
    std::set< vertex_descriptor > S, neighbor_S;
    std::vector< vertex_descriptor > S_star, non_neighbor_S;
    std::vector< default_color_type > color(num_vertices(g));
    std::vector< edge_descriptor > pred(num_vertices(g));

    //-------------------------------------------------------------------------
    // Create a network flow graph out of the undirected graph
    FlowGraph flow_g(num_vertices(g));

    typename property_map< FlowGraph, edge_capacity_t >::type cap
        = get(edge_capacity, flow_g);
    typename property_map< FlowGraph, edge_residual_capacity_t >::type res_cap
        = get(edge_residual_capacity, flow_g);
    typename property_map< FlowGraph, edge_reverse_t >::type rev_edge
        = get(edge_reverse, flow_g);

    for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
    {
        u = source(*ei, g), v = target(*ei, g);
        boost::tie(e1, inserted) = add_edge(u, v, flow_g);
        cap[e1] = 1;
        boost::tie(e2, inserted) = add_edge(v, u, flow_g);
        cap[e2] = 1; // not sure about this
        rev_edge[e1] = e2;
        rev_edge[e2] = e1;
    }

    //-------------------------------------------------------------------------
    // The Algorithm

    boost::tie(p, delta) = detail::min_degree_vertex(g);
    S_star.push_back(p);
    alpha_star = delta;
    S.insert(p);
    neighbor_S.insert(p);
    detail::neighbors(
        g, S.begin(), S.end(), std::inserter(neighbor_S, neighbor_S.begin()));

    boost::tie(vi, vi_end) = vertices(g);
    std::set_difference(vi, vi_end, neighbor_S.begin(), neighbor_S.end(),
        std::back_inserter(non_neighbor_S));

    while (!non_neighbor_S.empty())
    { // at most n - 1 times
        k = non_neighbor_S.front();

        alpha_S_k = edmonds_karp_max_flow(
            flow_g, p, k, cap, res_cap, rev_edge, &color[0], &pred[0]);

        if (alpha_S_k < alpha_star)
        {
            alpha_star = alpha_S_k;
            S_star.clear();
            for (boost::tie(vi, vi_end) = vertices(flow_g); vi != vi_end; ++vi)
                if (color[*vi] != Color::white())
                    S_star.push_back(*vi);
        }
        S.insert(k);
        neighbor_S.insert(k);
        detail::neighbors(g, k, std::inserter(neighbor_S, neighbor_S.begin()));
        non_neighbor_S.clear();
        boost::tie(vi, vi_end) = vertices(g);
        std::set_difference(vi, vi_end, neighbor_S.begin(), neighbor_S.end(),
            std::back_inserter(non_neighbor_S));
    }
    //-------------------------------------------------------------------------
    // Compute edges of the cut [S*, ~S*]
    std::vector< bool > in_S_star(num_vertices(g), false);
    typename std::vector< vertex_descriptor >::iterator si;
    for (si = S_star.begin(); si != S_star.end(); ++si)
        in_S_star[*si] = true;

    degree_size_type c = 0;
    for (si = S_star.begin(); si != S_star.end(); ++si)
    {
        out_edge_iterator ei, ei_end;
        for (boost::tie(ei, ei_end) = out_edges(*si, g); ei != ei_end; ++ei)
            if (!in_S_star[target(*ei, g)])
            {
                *disconnecting_set++ = *ei;
                ++c;
            }
    }
    return c;
}

} // namespace boost

#endif // BOOST_EDGE_CONNECTIVITY

/* edge_connectivity.hpp
iNCLzmqdHU7Z7CY/WcdYH0unQ6HUGVoX4HSynW7e4duyjXbszH7QlZp346nT16THqqBGp9wilymTldoVhaWF8tNagFBvpGj9kryy4nyt1nn7UpjV9Ww+5UWI1avK3Ko5z+aw+7brkYqlUct1G2dzf9Hv0bWtuIBnM/DRqXxl5W54IjanHW7jHT4vJ2R4R5A7J2bZcXuVU/1ybfFr4ZsbnCakpalR0/vZoaC+LrBTAHp1MCeYRStlR7huKPQ+niiMbnOFdadqlLo21TrtrCd/m9Q2w65gruBTAYad0EGGXRSXB7nmGumfa86tUQ8Hxjfh0dgsZojC/MbR8y6U+BpbQ1m/nrYssMau03qdpKrUwtErKroRkjyLraHxbY2tldayOSo7s1Q0jr5aWuM61RRbq08gVzZIyjSI1RLbjd5iK3MrMbS6+WOT8Vlx4uXujqyPp2WnZEM8Pbsma2Lo2YatvsKOyjWlJaulKOpMuG4Up+d69Qjy66N10hZlkPv+SGtGkNHlbJyZ2/NndPck+5ye6dOzOrl6ZLyp+nh1TWKBrG+56yDfCMynsjCrCuz5VAmNUoMuJx30JllbiOr5y9dirN7N5xzp28F9G7qwWcNS9Va61uetWLa61E2fp/GteJmLL3B9kMZ/XYtbHB/QjD7jW+0y7+BLuWyBWbKmvJBKoFIm2rz20awep8bSYief6dcf3UCva21t9ha+3xoVJ5ljTC1ZUhhYhOzzsQxD73XQgoBa3QeDA/WA4OUFSy03D8L5rp7Xs9M5zqah07SlGNjpvZQQi36BE26xonDtDFV13HQsWlQbu1v1HKuzFlSj51NgtUtHpco8pixvaeGSvGW+HzKujqkj7WLoXBvyjBgaaZM3utrTY2jnk75rY76vZV2tmHFrYuqiOdJpq9Ni687e0JKj6tH5y3nOcPliWIp3ZfREd71z2yheJri06iJbo1suN2Tlsd5OLrSjc0qwTm51pamD0q4s2NxYr+40jKAFwqq7LGZza22OUqXht+gCUQfrDVMqdF8c3MP8dd1j+2sjj7P24a9J/8MetWu1jFGCq/56E0G+ZqREu9cwqC7jc472+Rz9bh9/G/2osqy1TbiOrf17sMXQMR30WwyNr9DxOL4yur5GLwDs8LFObZmlUJ8Ncy1uO7jM1PsFOgBK/dNOA9jjbEsF+p2Q29FRUOoE/8m4jj4c15KUAzDrquudDULOrQZ/ooZTgNVrYH3XhERN1nxDlj1bg9VWncbBOfET7Xeik/CavSWykm5806NZbOw+m1W/Mpg2EncPhXnVbzEs5DfJT554OJ5eXehrWNh3H7lgFC87kQxHQuH23FG83FYU5CTVawjJ+aN4PcKp0XOkYZ16Wyx1x09nlnC82PCBJZZmGbLofvggztj5zOd9f6Q5PMcgvV3YoVSzz+n1gkvs1TU96bQ+xpyNUkWjz6Opl3U/pvNM1/YHzb4wn1ti1l997jlde41bXXq+p8uTzQ3hf3jf2y/Ne+w9eV2GH93n3hhH19omvavR+TvemmKeK+IB9SU9Pya5d7a3y+hXgR1evMXs8MoL1Qx/x+eSOBqZuFgr+4Ds1RWdOyfquRh/WWOLg7FR2nUalo5alboYPnwebTu8vbbVrOPmb6D6usaYTdbYa1Eo9P4b9KzRaC3vkTfrUOsFUHW+85tmxa9z52mWCUZDfyLo1tS5rUG3hl7JadnwivpBms8rKCjlzIGPdet/iI+b122RbNSbXWZZrHNHjOxBGL2SwNLAK8EVgOoFziqAOiR81lKsUaXm+yxnL/xbyf4Rd1cbpo+609hj/myIOxbaaTTZgTN30ZSilXn5cucaM1r6mLXK16hWTyLpSTE=
*/