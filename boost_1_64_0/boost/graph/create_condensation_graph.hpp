//=======================================================================
// Copyright 2002 Indiana University.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_CREATE_CONDENSATION_GRAPH_HPP
#define BOOST_CREATE_CONDENSATION_GRAPH_HPP

#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>

namespace boost
{

template < typename Graph, typename ComponentLists, typename ComponentNumberMap,
    typename CondensationGraph, typename EdgeMultiplicityMap >
void create_condensation_graph(const Graph& g, const ComponentLists& components,
    ComponentNumberMap component_number, CondensationGraph& cg,
    EdgeMultiplicityMap edge_mult_map)
{
    typedef typename graph_traits< Graph >::vertex_descriptor vertex;
    typedef typename graph_traits< Graph >::vertices_size_type size_type;
    typedef
        typename graph_traits< CondensationGraph >::vertex_descriptor cg_vertex;
    std::vector< cg_vertex > to_cg_vertex(components.size());
    for (size_type s = 0; s < components.size(); ++s)
        to_cg_vertex[s] = add_vertex(cg);

    for (size_type si = 0; si < components.size(); ++si)
    {
        cg_vertex s = to_cg_vertex[si];
        std::vector< cg_vertex > adj;
        for (size_type i = 0; i < components[si].size(); ++i)
        {
            vertex u = components[s][i];
            typename graph_traits< Graph >::adjacency_iterator v, v_end;
            for (boost::tie(v, v_end) = adjacent_vertices(u, g); v != v_end;
                 ++v)
            {
                cg_vertex t = to_cg_vertex[component_number[*v]];
                if (s != t) // Avoid loops in the condensation graph
                    adj.push_back(t);
            }
        }
        std::sort(adj.begin(), adj.end());
        if (!adj.empty())
        {
            size_type i = 0;
            cg_vertex t = adj[i];
            typename graph_traits< CondensationGraph >::edge_descriptor e;
            bool inserted;
            boost::tie(e, inserted) = add_edge(s, t, cg);
            put(edge_mult_map, e, 1);
            ++i;
            while (i < adj.size())
            {
                if (adj[i] == t)
                    put(edge_mult_map, e, get(edge_mult_map, e) + 1);
                else
                {
                    t = adj[i];
                    boost::tie(e, inserted) = add_edge(s, t, cg);
                    put(edge_mult_map, e, 1);
                }
                ++i;
            }
        }
    }
}

template < typename Graph, typename ComponentLists, typename ComponentNumberMap,
    typename CondensationGraph >
void create_condensation_graph(const Graph& g, const ComponentLists& components,
    ComponentNumberMap component_number, CondensationGraph& cg)
{
    create_condensation_graph(
        g, components, component_number, cg, dummy_property_map());
}

} // namespace boost

#endif // BOOST_CREATE_CONDENSATION_GRAPH_HPP

/* create_condensation_graph.hpp
0d6NoqfM3gvTwXedFSppJ6t6fTGzt9gcDBvvh1rmXT3nI8wzvqVn3GzveYYvJUILXVjx1R8IdaZ2eE4PddpL8Rw/r40XSDlh1R7RlnddN9PeDdaZvZLX897ZelWuT9I99pmgcOO2ZfZ7mINNY7qv5e6BieCtQ/2xZuopB1avXhOOYC2mVu/GwfvxY1DPCMTYF3tsuNidwQyA41SRCjloxGXP3kwey7Q7sr/cLd7F87gCxh5TlbN89FIU9NFjzxu+13J2f73B2/bcSRPs5tktI5ljKgAaI7o3fc6AMTftnCcAmlNbLslLn++XlI1vQdmDH4va78VXsu81usnyJPasWTJtEYnmmG2EJZ2K0f5We1micoUseDVu3Pi8F4SZ5LwRQpYmWIRoHu3nEfxUS2fM3C8Dqy/UTqxlKEww6RGNvJNTP2DOScevbOHKMknAvlfM451HX9SyriZJoxfX9GvTfcY6mOjb63AsNJxMDljxClZyU5mtts+xci4bmvgz4vSM3ZOGNY2rXpTtPC6a2/1fT6NozoXi9n4utFU0bcTcI92tD69b02yv/TRhR1+4eWNko9aCWtaOTImt7IkGXOUKjakpW/InM3C6vyKuqeY3J261jqpVjuz6yWKUpXxVzMdaUwpDUzFm+XSuMlN4mO5R4ObHE92prb3p4cTydZFbG1csr9/Y8KJg/XNXb2zc2PzsmbO65G/mioBeX48Bam5v6lna/twtJHYWPsuce+JYBZPNDq3patjThyZL5GNldTWyo7JmSdKsy9GtfGyoN5HEUq+IxfpkM5xUQAxW+KFvncn3vqxrke4z/uW9FulXWrF8kbyfflvmBc2llZVjks1FrV09PMcAdsVcZITejIiD36vmBc1XUDT3uJfZLxh5/LePdRAzyUfZl6TzUduynKxd37gmXb6rdAZpxrvjVJt59oRnId2I/O2mXHrr79pV6xtf0Cyr49nlBqufWJDKLvt3zHqQ+57E/qhDkAac9kwEMu5B4n45SAH3DJ2+l8gc+5r2xgTCfZMBcw8QLWjfYD3TM3k/TEFsi6et1tktiphmNWeTFbjxOFRknX12WvbzlSq62rf29L5Sn7G0am3rC5pawjhLcteuoK2t9xKtamiQXcWtlnZFe8/8+cG5c4MVup5qSyHtRhQeFxINbSBudBz+H/GBWPnPIySOjNzL2IMj7Zn3gJv2pO4mp+q09HAtecot+Xq5lEuf8kd5Yz7KSsZiwXnMrbTQn5deT7iZg2TkHAcZ76A3K5acawzuM2A62/nDzFv1bJWOv2dhMhGTiUKPPdtOMG3hZs/H0e/JQ6i0G+2de90taaVorx7Uyr7cheYlFofE3lo9b+I8Hqh9Czc6Sd/XHHTnTnVrHJtlj7TWl6ElV7adgyJz7p7V1ppzRiyl53yy1RJpadTsBJLJcb1a3WnNudnbqMSN8y8QgKEj+eW8vaqaruSzBE6jRTKvCo8WchcJd5VEnZ5m+KYtaJu96SgsFB2HD5iJdvUVGa+m/lfojNdvJuXL7ntK/nNu5AWucz693vC8FNkj+2/rFc9jyHq1pHsltqmlZb59fkSy1xkv3kBt/HM3stnvh+XdrK6jKOx51Kx7CiTfLYW70Hj7695+eub98dxlFPDelyCz/i1rWvSnGoGR7vMJZNyf5HYWv+MZ/dsy7+Of5bxruzkGqZN1i7mUXPu0ctN/cc8vJGOWp89obdq4et2q9U3BpOsNk+lOiPSsJEn51Zv5cEY6rO1JdLXtQ5Nd9xjeajZlVMqxeYn0gTqVPX3pE13r27X/pggJ+LbyNp5xEgq+ZJAnPYw1773I2W0yXCTyDQP+N+3y1vQ9iVujNaobZx5XbI0=
*/