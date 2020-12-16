//=======================================================================
// Copyright 2013 University of Warsaw.
// Authors: Piotr Wygocki
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
// This algorithm is described in "Network Flows: Theory, Algorithms, and
// Applications"
// by Ahuja, Magnanti, Orlin.

#ifndef BOOST_GRAPH_SUCCESSIVE_SHORTEST_PATH_HPP
#define BOOST_GRAPH_SUCCESSIVE_SHORTEST_PATH_HPP

#include <numeric>

#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/detail/augment.hpp>

namespace boost
{

namespace detail
{

    template < class Graph, class Weight, class Distance, class Reversed >
    class MapReducedWeight
    : public put_get_helper< typename property_traits< Weight >::value_type,
          MapReducedWeight< Graph, Weight, Distance, Reversed > >
    {
        typedef graph_traits< Graph > gtraits;

    public:
        typedef boost::readable_property_map_tag category;
        typedef typename property_traits< Weight >::value_type value_type;
        typedef value_type reference;
        typedef typename gtraits::edge_descriptor key_type;
        MapReducedWeight(const Graph& g, Weight w, Distance d, Reversed r)
        : g_(g), weight_(w), distance_(d), rev_(r)
        {
        }

        reference operator[](key_type v) const
        {
            return get(distance_, source(v, g_)) - get(distance_, target(v, g_))
                + get(weight_, v);
        }

    private:
        const Graph& g_;
        Weight weight_;
        Distance distance_;
        Reversed rev_;
    };

    template < class Graph, class Weight, class Distance, class Reversed >
    MapReducedWeight< Graph, Weight, Distance, Reversed > make_mapReducedWeight(
        const Graph& g, Weight w, Distance d, Reversed r)
    {
        return MapReducedWeight< Graph, Weight, Distance, Reversed >(
            g, w, d, r);
    }

} // detail

template < class Graph, class Capacity, class ResidualCapacity, class Reversed,
    class Pred, class Weight, class Distance, class Distance2,
    class VertexIndex >
void successive_shortest_path_nonnegative_weights(const Graph& g,
    typename graph_traits< Graph >::vertex_descriptor s,
    typename graph_traits< Graph >::vertex_descriptor t, Capacity capacity,
    ResidualCapacity residual_capacity, Weight weight, Reversed rev,
    VertexIndex index, Pred pred, Distance distance, Distance2 distance_prev)
{
    filtered_graph< const Graph, is_residual_edge< ResidualCapacity > > gres
        = detail::residual_graph(g, residual_capacity);
    typedef typename graph_traits< Graph >::edge_descriptor edge_descriptor;

    BGL_FORALL_EDGES_T(e, g, Graph)
    {
        put(residual_capacity, e, get(capacity, e));
    }

    BGL_FORALL_VERTICES_T(v, g, Graph) { put(distance_prev, v, 0); }

    while (true)
    {
        BGL_FORALL_VERTICES_T(v, g, Graph) { put(pred, v, edge_descriptor()); }
        dijkstra_shortest_paths(gres, s,
            weight_map(
                detail::make_mapReducedWeight(gres, weight, distance_prev, rev))
                .distance_map(distance)
                .vertex_index_map(index)
                .visitor(make_dijkstra_visitor(
                    record_edge_predecessors(pred, on_edge_relaxed()))));

        if (get(pred, t) == edge_descriptor())
        {
            break;
        }

        BGL_FORALL_VERTICES_T(v, g, Graph)
        {
            put(distance_prev, v, get(distance_prev, v) + get(distance, v));
        }

        detail::augment(g, s, t, pred, residual_capacity, rev);
    }
}

// in this namespace argument dispatching tak place
namespace detail
{

    template < class Graph, class Capacity, class ResidualCapacity,
        class Weight, class Reversed, class Pred, class Distance,
        class Distance2, class VertexIndex >
    void successive_shortest_path_nonnegative_weights_dispatch3(const Graph& g,
        typename graph_traits< Graph >::vertex_descriptor s,
        typename graph_traits< Graph >::vertex_descriptor t, Capacity capacity,
        ResidualCapacity residual_capacity, Weight weight, Reversed rev,
        VertexIndex index, Pred pred, Distance dist, Distance2 dist_pred)
    {
        successive_shortest_path_nonnegative_weights(g, s, t, capacity,
            residual_capacity, weight, rev, index, pred, dist, dist_pred);
    }

    // setting default distance map
    template < class Graph, class Capacity, class ResidualCapacity,
        class Weight, class Reversed, class Pred, class Distance,
        class VertexIndex >
    void successive_shortest_path_nonnegative_weights_dispatch3(Graph& g,
        typename graph_traits< Graph >::vertex_descriptor s,
        typename graph_traits< Graph >::vertex_descriptor t, Capacity capacity,
        ResidualCapacity residual_capacity, Weight weight, Reversed rev,
        VertexIndex index, Pred pred, Distance dist, param_not_found)
    {
        typedef typename property_traits< Weight >::value_type D;

        std::vector< D > d_map(num_vertices(g));

        successive_shortest_path_nonnegative_weights(g, s, t, capacity,
            residual_capacity, weight, rev, index, pred, dist,
            make_iterator_property_map(d_map.begin(), index));
    }

    template < class Graph, class P, class T, class R, class Capacity,
        class ResidualCapacity, class Weight, class Reversed, class Pred,
        class Distance, class VertexIndex >
    void successive_shortest_path_nonnegative_weights_dispatch2(Graph& g,
        typename graph_traits< Graph >::vertex_descriptor s,
        typename graph_traits< Graph >::vertex_descriptor t, Capacity capacity,
        ResidualCapacity residual_capacity, Weight weight, Reversed rev,
        VertexIndex index, Pred pred, Distance dist,
        const bgl_named_params< P, T, R >& params)
    {
        successive_shortest_path_nonnegative_weights_dispatch3(g, s, t,
            capacity, residual_capacity, weight, rev, index, pred, dist,
            get_param(params, vertex_distance2));
    }

    // setting default distance map
    template < class Graph, class P, class T, class R, class Capacity,
        class ResidualCapacity, class Weight, class Reversed, class Pred,
        class VertexIndex >
    void successive_shortest_path_nonnegative_weights_dispatch2(Graph& g,
        typename graph_traits< Graph >::vertex_descriptor s,
        typename graph_traits< Graph >::vertex_descriptor t, Capacity capacity,
        ResidualCapacity residual_capacity, Weight weight, Reversed rev,
        VertexIndex index, Pred pred, param_not_found,
        const bgl_named_params< P, T, R >& params)
    {
        typedef typename property_traits< Weight >::value_type D;

        std::vector< D > d_map(num_vertices(g));

        successive_shortest_path_nonnegative_weights_dispatch3(g, s, t,
            capacity, residual_capacity, weight, rev, index, pred,
            make_iterator_property_map(d_map.begin(), index),
            get_param(params, vertex_distance2));
    }

    template < class Graph, class P, class T, class R, class Capacity,
        class ResidualCapacity, class Weight, class Reversed, class Pred,
        class VertexIndex >
    void successive_shortest_path_nonnegative_weights_dispatch1(Graph& g,
        typename graph_traits< Graph >::vertex_descriptor s,
        typename graph_traits< Graph >::vertex_descriptor t, Capacity capacity,
        ResidualCapacity residual_capacity, Weight weight, Reversed rev,
        VertexIndex index, Pred pred, const bgl_named_params< P, T, R >& params)
    {
        successive_shortest_path_nonnegative_weights_dispatch2(g, s, t,
            capacity, residual_capacity, weight, rev, index, pred,
            get_param(params, vertex_distance), params);
    }

    // setting default predecessors map
    template < class Graph, class P, class T, class R, class Capacity,
        class ResidualCapacity, class Weight, class Reversed,
        class VertexIndex >
    void successive_shortest_path_nonnegative_weights_dispatch1(Graph& g,
        typename graph_traits< Graph >::vertex_descriptor s,
        typename graph_traits< Graph >::vertex_descriptor t, Capacity capacity,
        ResidualCapacity residual_capacity, Weight weight, Reversed rev,
        VertexIndex index, param_not_found,
        const bgl_named_params< P, T, R >& params)
    {
        typedef typename graph_traits< Graph >::edge_descriptor edge_descriptor;
        std::vector< edge_descriptor > pred_vec(num_vertices(g));

        successive_shortest_path_nonnegative_weights_dispatch2(g, s, t,
            capacity, residual_capacity, weight, rev, index,
            make_iterator_property_map(pred_vec.begin(), index),
            get_param(params, vertex_distance), params);
    }

} // detail

template < class Graph, class P, class T, class R >
void successive_shortest_path_nonnegative_weights(Graph& g,
    typename graph_traits< Graph >::vertex_descriptor s,
    typename graph_traits< Graph >::vertex_descriptor t,
    const bgl_named_params< P, T, R >& params)
{

    return detail::successive_shortest_path_nonnegative_weights_dispatch1(g, s,
        t,
        choose_const_pmap(get_param(params, edge_capacity), g, edge_capacity),
        choose_pmap(get_param(params, edge_residual_capacity), g,
            edge_residual_capacity),
        choose_const_pmap(get_param(params, edge_weight), g, edge_weight),
        choose_const_pmap(get_param(params, edge_reverse), g, edge_reverse),
        choose_const_pmap(get_param(params, vertex_index), g, vertex_index),
        get_param(params, vertex_predecessor), params);
}

template < class Graph >
void successive_shortest_path_nonnegative_weights(Graph& g,
    typename graph_traits< Graph >::vertex_descriptor s,
    typename graph_traits< Graph >::vertex_descriptor t)
{
    bgl_named_params< int, buffer_param_t > params(0);
    successive_shortest_path_nonnegative_weights(g, s, t, params);
}

} // boost
#endif /* BOOST_GRAPH_SUCCESSIVE_SHORTEST_PATH_HPP */

/* successive_shortest_path_nonnegative_weights.hpp
6/eBzm3eLuXq6mmb+lymPeV67BLtpk4o/aO/Ma7Vgz7u7j6u05eDUuZ191Q/Cfv1lZ6nK/PsMOap9XAtc2yramVGOMp4Td93qzLTnWXm36rMCso8EkQZzxmu1cfbcmzDYUcZ1xlNZSPKbrkN5jw9GtuvQ11nDPFuxgisfjJi2K2vQztH/ecxw7pJfliVdR/JMmYGGds3I+pW2zeTMo8aZbwfqVl9+4J1mdWUeUzqeWTkrcYTk88yTG/TYzOMm1cXbx/w8uQ/bnWrbZd5DholfU+3W15f50j+3bKcsYwdNkzZx7qaFaTHViUq9fhUByz//tDfHAtLT9+irI4ndLlKx/WaTh9JerQeg2sOMVeXm6d9UvuUSOgxZkcZ77bCLDTSev2Hcbx+Nt7zVUePoavTnsEFxEKZdvqs6FzH56zTevnPVx0fDGXajMXE36ql/VNbocenDVWp8qzkmozBddNvEszr8BHy+QyWa6ORLv95LK5kPRZXgB4vy+ZnTOvrF9JWuVS9dnKOtSrXIeaY85xvSON8o6+Fe5vXt2Y/Zj772Bpgpv9fZa33Vj4tlPx9Z5yj8SBGG/2HnMun8yMJ/ZsSubf662cSA2yO8p1UsL6/2iXTCcqPEq1VbXMMU+exkscVn3M87pVSfr1tg/paHz+OOluqAP1sy6Ysv9fQ14CvSJntttMsYajNQz1N6PswPX8Tyjruo8ZnlZu/+ZDdI/UY271Cyn5gO2Oc+Vj/BYRRT77Uo5/7mfd87BalrPdfuozNvEYIrrJMysvimEf3aU/fJfuXu+sU571YtXoy1E3j5pvPBIJk/rttndSPOo0nBJJWhx8XXbc8u6B9W+5P7pEy/+QOxlstIgLkOaAu51hH3f6fk7KTaf8DzHPjNlm/VbbO9JM+qupxRosS0wOsx13VfwfLWHmOY8/8DZE5Xt7LUv99Kow90Ee5/Nf7EmNs467d7WPacbdo/Nbnr55TmfcrteS4tLe94CrPC51tK1SOGcexVL3N6GPVvEe1t4UQ0jLMeap+5sG6vgDJM/ezPg795DhcpAc1mdmR86F2ETnFsm3TSx1H4Xi5dHS0C33/mW2eUyivr7t0u94o0zEdlGvTdqGSxhVhLznf+pyyuarHXL1573EddcTTfm23yE/XOdF5bK6WOgZ1qEkd+tjUy+mhQqSMo852Pi4qnD6kpZevT03LfY5c8Uqb5n9/1sezpJcUZFa9ppo8SNqweU3llmhM+0j7a+XCeaCH9Mntnde92XSWmUXGfWMLfa8Xl2OUmeker9qpp+iBDtGz1bd5q942T7ck97rmuMJPS7kg1VTms6kzsg2X2q6xLQqLa/qBR1DrF20ftXlELWrbRo8rbC3j1yaYdZqrlJm20TYpaFm9Nvp639y+ohJ9byZ9g01Vyzee9RYUZeU47wcyko36LriusWWoYEljSpZxzu8129u+E/mfeI1lz6KG+j2N9OMRIQ2fq31nu38pvV/0+NGZ0viH6PuqnOFG2Tm1a6mPbWdtNW0urtt4d+oN3vt82lbhUYP3p73HO5t+VWN52aHNq4j3qPRUn3mF836LOuqEz12qY602alKtump5rabqZK1Hbe2lXuc+WWab0ySl2Ql1V3iaOhLuq/4Mn+3+Oi+1+6jNU7IPg/X196331/j8wsyJuSVyl8lxqPdHiWzj4xF9bXV9Dvg3Uv0CGqnvAqaFSL7Z9sL8v7Z5ycu36vpMcluj91EM9WyW+e+OuK/ButoL2/5LhZrXY6XFBfk8duCrgszRJVljxucWWp+bT42zX88H62Ppj4HGdKZbnGsjtYWQcqTs72+ku+tyjv1x0W+9bbXvZNbDaLtXmX+frEdEhK/z8zc=
*/