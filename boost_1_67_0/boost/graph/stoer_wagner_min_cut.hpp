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