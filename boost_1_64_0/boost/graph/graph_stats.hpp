// Copyright 2005 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Alex Breuer
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_GRAPH_STATS_HPP
#define BOOST_GRAPH_GRAPH_STATS_HPP

#include <map>
#include <list>
#include <boost/graph/iteration_macros.hpp>
#include <boost/assert.hpp>

namespace boost
{
namespace graph
{

    template < typename Graph > struct sort_edge_by_origin
    {
    public:
        typedef typename graph_traits< Graph >::edge_descriptor edge_type;

        explicit sort_edge_by_origin(Graph& g) : g(g) {}

        inline bool operator()(edge_type a, edge_type b)
        {
            return source(a, g) == source(b, g) ? target(a, g) < target(b, g)
                                                : source(a, g) < source(b, g);
        }

    private:
        Graph& g;
    };

    template < typename Graph > struct equal_edge
    {
    public:
        typedef typename graph_traits< Graph >::edge_descriptor edge_type;

        explicit equal_edge(Graph& g) : g(g) {}

        inline bool operator()(edge_type a, edge_type b)
        {
            return source(a, g) == source(b, g) && target(a, g) == target(b, g);
        }

    private:
        Graph& g;
    };

    template < typename Graph > unsigned long num_dup_edges(Graph& g)
    {
        typedef typename graph_traits< Graph >::edge_iterator e_iterator_type;
        typedef typename graph_traits< Graph >::edge_descriptor edge_type;

        std::list< edge_type > all_edges;

        BGL_FORALL_EDGES_T(e, g, Graph) { all_edges.push_back(e); }

        sort_edge_by_origin< Graph > cmp1(g);
        all_edges.sort(cmp1);
        equal_edge< Graph > cmp2(g);
        all_edges.unique(cmp2);

        return num_edges(g) - all_edges.size();
    }

    template < typename Graph >
    std::map< unsigned long, unsigned long > dup_edge_dist(Graph& g)
    {
        std::map< unsigned long, unsigned long > dist;
        typedef
            typename graph_traits< Graph >::adjacency_iterator a_iterator_type;
        typedef typename graph_traits< Graph >::vertex_descriptor vertex_type;

        BGL_FORALL_VERTICES_T(v, g, Graph)
        {
            std::list< vertex_type > front_neighbors;
            a_iterator_type a_iter, a_end;
            for (boost::tie(a_iter, a_end) = adjacent_vertices(v, g);
                 a_iter != a_end; ++a_iter)
            {
                front_neighbors.push_back(*a_iter);
            }

            front_neighbors.sort();
            front_neighbors.unique();
            dist[out_degree(v, g) - front_neighbors.size()] += 1;
        }
        return dist;
    }

    template < typename Graph >
    std::map< unsigned long, unsigned long > degree_dist(Graph& g)
    {
        std::map< unsigned long, unsigned long > dist;
        typedef
            typename graph_traits< Graph >::adjacency_iterator a_iterator_type;
        typedef typename graph_traits< Graph >::vertex_descriptor vertex_type;

        BGL_FORALL_VERTICES_T(v, g, Graph) { dist[out_degree(v, g)] += 1; }

        return dist;
    }

    template < typename Graph >
    std::map< unsigned long, double > weight_degree_dist(Graph& g)
    {
        std::map< unsigned long, double > dist, n;
        typedef
            typename graph_traits< Graph >::adjacency_iterator a_iterator_type;
        typedef typename graph_traits< Graph >::vertex_descriptor vertex_type;
        typedef typename property_map< Graph, edge_weight_t >::const_type
            edge_map_type;
        typedef typename property_traits< edge_map_type >::value_type
            edge_weight_type;

        typename property_map< Graph, edge_weight_t >::type em
            = get(edge_weight, g);

        BGL_FORALL_VERTICES_T(v, g, Graph)
        {
            edge_weight_type tmp = 0;
            BGL_FORALL_OUTEDGES_T(v, e, g, Graph) { tmp += em[e]; }
            n[out_degree(v, g)] += 1.;
            dist[out_degree(v, g)] += tmp;
        }

        for (std::map< unsigned long, double >::iterator iter = dist.begin();
             iter != dist.end(); ++iter)
        {
            BOOST_ASSERT(n[iter->first] != 0);
            dist[iter->first] /= n[iter->first];
        }

        return dist;
    }

}
}

#endif

/* graph_stats.hpp
VdxCpWfnZZTlxT5sHDU4zfdt/uUQ/L8DBvEzP5sZV+eX9ZcbWKfjaahrf31nRktNaXGW8aemBZ+E5bfiyJKfRKlEu801rPlvxozHaRkjcFnIlTNpA1rvZx2jmMi78DP/55XrQqsBHuYhScuxxts9zelOa6Onv3WrO/u9ih0IY9fInaKECiYSfpB/J9amOz7jYatYasJoaKO+9ezSYI9R702Z6rujK/URC9VCrmesZ+KLM78RntXXK2s9LTYbwbHQJcv040jKUE1CmLeJWuJwy0s2ut6Ol9dDAtPu8Vv2fXbqDBE6HXxKo/nEyX1FP7zBsxP7STuz4mrfAwQS8bZpdrqfmXhQrNyO6uYs9Mx4zjJJyGhS4TyeFPoOl72vFCfGMm81KWv84XHl9yd0BO10SQVNnjO+jz43bRntI9RaL4D7AreipMH6Bc/q7Ep6XsbeidpQnyTamQV3AkPG3nvGOroBw7PC/aQj2TMooVYuIfX0NGPDy+0kjnkEHyXnvaVQOXUftnB6BIOuPGNj9E6snZXKPp3tWlDSEdd9rw1VyRrO9XLAXGDtyvad0PwXNqOCYfv+0eyFv7WTD3faWl8jbP+wHtKeeIaANdCqRt+0sGd1v4BYqbXMS99DYWsxz4HkEXvrO1ffpTjl1adHuCZwuYp18X0I4qsSh/o78t7vNkYldZYw8V9Mldf9lHjWh/+Sr2jsm2G6xNGpxeocbprnzYXNT4UyX3Lj0o+OF4RIWG1trb8K07JKJfqoQ1aX8FHL9+b71+gbxaLqqs0S3dXaUiVk5d8E/SKqeuJe4AyYSHy8z3OG+vElMfxyVacS3hkfTzJC21k+vH5ccdqRW2aSWXZZX3M0/NP33jD3v5MVZwgtuy/kw3Y/mLan73eF2SNPLErGWRrls6jOLKpp0OeaUvVdH/IvkX0rFulo2XAt8ur3jauULHVfTK9lF18jDU+c4XCUK+U/N3Rz35VbnKDLWvLzsYv2HS/O6/XGEaA5rJO7aWOjH+zclOUXuiy5fs373NwIiUKwuSpXaj1RlEkDLs+G9rvE1OdJ58jOPBOLd7h+1eNmUs+RWyI/v5C+xElKKv305tyrrvgdH7U33rJFU/r9aqYU15rnTk8F95To1yzsrNCJPhYxe6BzYYt3zJQxGKe5kS9Zn6i8QA8v74e97puS7GTngPuBLNm3cLiUvMRlI1U20yKYzAgG+h8Y++edZXwc9c3++x4Rr3z8xXU51k8aTlmqQ0TRmduf86XTuh52mQhxsr7Gz1teXmUUD32SSHtZ+N0wmVuOpVNKnGH/U4PriUOGnaMhW7EZfYFHL5ZwtZ61GuJrPltL1ChxEZ7EfUIC9ZkLZsfcT+hv4NJ/JAzP+TQVnNDjdpWt/ZqQ413xlpnnDN/e6fl2Ds7qBWtwT7ZUU3hLTZLJWVf+Nj9ZP3ScPsmirO3VnfH9nbWwHZHIkdZo5WDtWTo+VUMVxlZ9KzVcR02rhwpsgs0fXP24qN8F6g4mfXzhf2P03g93cZFWY8vKrndtbjkM1dbv+yhU1teI8ok5l4e6JtMmHxHzf34SrUyj9DQvRMLl8tDXB/Ynml8LNY69FGf7cl0+XlK7sH0rJE6UTC2AayONk+vtmo7RknZmpOb7E2jCuJxLVlVjwwGuee1L/i0n/PnG+CfutL3VJ+3rvVCf+JLL+0bv0aqy4tknl7jtUjN+yokTGnkSpl7/kh6vYLnnEpW3/Jwtfz89hVKicT5xu/d+/kWfEstJ4gvVMkWXXt42pP14ysv/ng6JyTWZI12/ua3DJPe+5bL88z0aOSJJkSsSWh8+fGxn5hs05jTmiHkRnPElw+tjcefI5G1WJ9wlBwn3t+g=
*/