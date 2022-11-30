//            Copyright Daniel Trebbien 2010.
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE_1_0.txt or the copy at
//         http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_STOER_WAGNER_MIN_CUT_HPP
#define BOOST_GRAPH_STOER_WAGNER_MIN_CUT_HPP 1

#include <boost/assert.hpp>
#include <set>
#include <vector>
#include <boost/concept_check.hpp>
#include <boost/concept/assert.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/buffer_concepts.hpp>
#include <boost/graph/exception.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/maximum_adjacency_search.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/one_bit_color_map.hpp>
#include <boost/graph/detail/d_ary_heap.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/graph/iteration_macros.hpp>

namespace boost
{

namespace detail
{
    template < typename ParityMap, typename WeightMap, typename IndexMap >
    class mas_min_cut_visitor : public boost::default_mas_visitor
    {
        typedef one_bit_color_map< IndexMap > InternalParityMap;
        typedef typename boost::property_traits< WeightMap >::value_type
            weight_type;

    public:
        template < typename Graph >
        mas_min_cut_visitor(const Graph& g, ParityMap parity,
            weight_type& cutweight, const WeightMap& weight_map,
            IndexMap index_map)
        : m_bestParity(parity)
        , m_parity(make_one_bit_color_map(num_vertices(g), index_map))
        , m_bestWeight(cutweight)
        , m_cutweight(0)
        , m_visited(0)
        , m_weightMap(weight_map)
        {
            // set here since the init list sets the reference
            m_bestWeight = (std::numeric_limits< weight_type >::max)();
        }

        template < typename Vertex, typename Graph >
        void initialize_vertex(Vertex u, const Graph& g)
        {
            typedef typename boost::property_traits< ParityMap >::value_type
                parity_type;
            typedef
                typename boost::property_traits< InternalParityMap >::value_type
                    internal_parity_type;

            put(m_parity, u, internal_parity_type(0));
            put(m_bestParity, u, parity_type(0));
        }

        template < typename Edge, typename Graph >
        void examine_edge(Edge e, const Graph& g)
        {
            weight_type w = get(m_weightMap, e);

            // if the target of e is already marked then decrease cutweight
            // otherwise, increase it
            if (get(m_parity, boost::target(e, g)))
            {
                m_cutweight -= w;
            }
            else
            {
                m_cutweight += w;
            }
        }

        template < typename Vertex, typename Graph >
        void finish_vertex(Vertex u, const Graph& g)
        {
            typedef
                typename boost::property_traits< InternalParityMap >::value_type
                    internal_parity_type;

            ++m_visited;
            put(m_parity, u, internal_parity_type(1));

            if (m_cutweight < m_bestWeight && m_visited < num_vertices(g))
            {
                m_bestWeight = m_cutweight;
                BGL_FORALL_VERTICES_T(i, g, Graph)
                {
                    put(m_bestParity, i, get(m_parity, i));
                }
            }
        }

        inline void clear()
        {
            m_bestWeight = (std::numeric_limits< weight_type >::max)();
            m_visited = 0;
            m_cutweight = 0;
        }

    private:
        ParityMap m_bestParity;
        InternalParityMap m_parity;
        weight_type& m_bestWeight;
        weight_type m_cutweight;
        unsigned m_visited;
        const WeightMap& m_weightMap;
    };

    /**
     * \brief Computes a min-cut of the input graph
     *
     * Computes a min-cut of the input graph using the Stoer-Wagner algorithm.
     *
     * \pre \p g is a connected, undirected graph
     * \pre <code>pq.empty()</code>
     * \param[in] g the input graph
     * \param[in] weights a readable property map from each edge to its weight
     * (a non-negative value) \param[out] parities a writable property map from
     * each vertex to a bool type object for distinguishing the two vertex sets
     * of the min-cut \param[out] assignments a read/write property map from
     * each vertex to a \c vertex_descriptor object. This map serves as work
     * space, and no particular meaning should be derived from property values
     *     after completion of the algorithm.
     * \param[out] pq a keyed, updatable max-priority queue
     * \returns the cut weight of the min-cut
     * \see
     * http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.114.6687&rep=rep1&type=pdf
     * \see
     * http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.31.614&rep=rep1&type=pdf
     *
     * \author Daniel Trebbien
     * \date 2010-09-11
     */
    template < class UndirectedGraph, class WeightMap, class ParityMap,
        class VertexAssignmentMap, class KeyedUpdatablePriorityQueue,
        class IndexMap >
    typename boost::property_traits< WeightMap >::value_type
    stoer_wagner_min_cut(const UndirectedGraph& g, WeightMap weights,
        ParityMap parities, VertexAssignmentMap assignments,
        KeyedUpdatablePriorityQueue& pq, IndexMap index_map)
    {
        typedef
            typename boost::graph_traits< UndirectedGraph >::vertex_descriptor
                vertex_descriptor;
        typedef typename boost::property_traits< WeightMap >::value_type
            weight_type;

        typename graph_traits< UndirectedGraph >::vertex_iterator u_iter, u_end;

        weight_type bestW = (std::numeric_limits< weight_type >::max)();
        weight_type bestThisTime = (std::numeric_limits< weight_type >::max)();
        vertex_descriptor bestStart
            = boost::graph_traits< UndirectedGraph >::null_vertex();

        detail::mas_min_cut_visitor< ParityMap, WeightMap, IndexMap > vis(
            g, parities, bestThisTime, weights, index_map);

        // for each node in the graph,
        for (boost::tie(u_iter, u_end) = vertices(g); u_iter != u_end; ++u_iter)
        {
            // run the MAS and find the min cut
            vis.clear();
            boost::maximum_adjacency_search(g,
                boost::weight_map(weights)
                    .visitor(vis)
                    .root_vertex(*u_iter)
                    .vertex_assignment_map(assignments)
                    .max_priority_queue(pq));
            if (bestThisTime < bestW)
            {
                bestW = bestThisTime;
                bestStart = *u_iter;
            }
        }

        // Run one more time, starting from the best start location, to
        // ensure the visitor has the best values.
        vis.clear();
        boost::maximum_adjacency_search(g,
            boost::vertex_assignment_map(assignments)
                .weight_map(weights)
                .visitor(vis)
                .root_vertex(bestStart)
                .max_priority_queue(pq));

        return bestW;
    }
} // end `namespace detail` within `namespace boost`

template < class UndirectedGraph, class WeightMap, class ParityMap,
    class VertexAssignmentMap, class KeyedUpdatablePriorityQueue,
    class IndexMap >
typename boost::property_traits< WeightMap >::value_type stoer_wagner_min_cut(
    const UndirectedGraph& g, WeightMap weights, ParityMap parities,
    VertexAssignmentMap assignments, KeyedUpdatablePriorityQueue& pq,
    IndexMap index_map)
{
    BOOST_CONCEPT_ASSERT((boost::IncidenceGraphConcept< UndirectedGraph >));
    BOOST_CONCEPT_ASSERT((boost::VertexListGraphConcept< UndirectedGraph >));
    typedef typename boost::graph_traits< UndirectedGraph >::vertex_descriptor
        vertex_descriptor;
    typedef typename boost::graph_traits< UndirectedGraph >::vertices_size_type
        vertices_size_type;
    typedef typename boost::graph_traits< UndirectedGraph >::edge_descriptor
        edge_descriptor;
    BOOST_CONCEPT_ASSERT((boost::Convertible<
        typename boost::graph_traits< UndirectedGraph >::directed_category,
        boost::undirected_tag >));
    BOOST_CONCEPT_ASSERT(
        (boost::ReadablePropertyMapConcept< WeightMap, edge_descriptor >));
    // typedef typename boost::property_traits<WeightMap>::value_type
    // weight_type;
    BOOST_CONCEPT_ASSERT(
        (boost::WritablePropertyMapConcept< ParityMap, vertex_descriptor >));
    // typedef typename boost::property_traits<ParityMap>::value_type
    // parity_type;
    BOOST_CONCEPT_ASSERT(
        (boost::ReadWritePropertyMapConcept< VertexAssignmentMap,
            vertex_descriptor >));
    BOOST_CONCEPT_ASSERT((boost::Convertible< vertex_descriptor,
        typename boost::property_traits< VertexAssignmentMap >::value_type >));
    BOOST_CONCEPT_ASSERT(
        (boost::KeyedUpdatableQueueConcept< KeyedUpdatablePriorityQueue >));

    vertices_size_type n = num_vertices(g);
    if (n < 2)
        throw boost::bad_graph(
            "the input graph must have at least two vertices.");
    else if (!pq.empty())
        throw std::invalid_argument(
            "the max-priority queue must be empty initially.");

    return detail::stoer_wagner_min_cut(
        g, weights, parities, assignments, pq, index_map);
}

namespace graph
{
    namespace detail
    {
        template < class UndirectedGraph, class WeightMap >
        struct stoer_wagner_min_cut_impl
        {
            typedef typename boost::property_traits< WeightMap >::value_type
                result_type;
            template < typename ArgPack >
            result_type operator()(const UndirectedGraph& g, WeightMap weights,
                const ArgPack& arg_pack) const
            {
                using namespace boost::graph::keywords;
                typedef typename boost::graph_traits<
                    UndirectedGraph >::vertex_descriptor vertex_descriptor;
                typedef typename boost::property_traits< WeightMap >::value_type
                    weight_type;

                typedef boost::detail::make_priority_queue_from_arg_pack_gen<
                    boost::graph::keywords::tag::max_priority_queue,
                    weight_type, vertex_descriptor,
                    std::greater< weight_type > >
                    gen_type;

                gen_type gen(
                    choose_param(get_param(arg_pack, boost::distance_zero_t()),
                        weight_type(0)));

                typename boost::result_of< gen_type(
                    const UndirectedGraph&, const ArgPack&) >::type pq
                    = gen(g, arg_pack);

                boost::dummy_property_map dummy_prop;
                return boost::stoer_wagner_min_cut(g, weights,
                    arg_pack[_parity_map | dummy_prop],
                    boost::detail::make_property_map_from_arg_pack_gen<
                        tag::vertex_assignment_map, vertex_descriptor >(
                        vertex_descriptor())(g, arg_pack),
                    pq,
                    boost::detail::override_const_property(
                        arg_pack, _vertex_index_map, g, vertex_index));
            }
        };
    }
    BOOST_GRAPH_MAKE_FORWARDING_FUNCTION(stoer_wagner_min_cut, 2, 4)
}

// Named parameter interface
BOOST_GRAPH_MAKE_OLD_STYLE_PARAMETER_FUNCTION(stoer_wagner_min_cut, 2)
namespace graph
{
    // version without IndexMap kept for backwards compatibility
    // (but requires vertex_index_t to be defined in the graph)
    // Place after the macro to avoid compilation errors
    template < class UndirectedGraph, class WeightMap, class ParityMap,
        class VertexAssignmentMap, class KeyedUpdatablePriorityQueue >
    typename boost::property_traits< WeightMap >::value_type
    stoer_wagner_min_cut(const UndirectedGraph& g, WeightMap weights,
        ParityMap parities, VertexAssignmentMap assignments,
        KeyedUpdatablePriorityQueue& pq)
    {

        return stoer_wagner_min_cut(
            g, weights, parities, assignments, pq, get(vertex_index, g));
    }
} // end `namespace graph`
} // end `namespace boost`

#include <boost/graph/iteration_macros_undef.hpp>

#endif // !BOOST_GRAPH_STOER_WAGNER_MIN_CUT_HPP

/* stoer_wagner_min_cut.hpp
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
*/