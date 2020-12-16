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
O+MGjMV3cRBuwmT8EEfiZszFLViCW3GCzn8U38encBsuwe34luTb12spcUmv1696vfxxoV6vE/r3AicxFE9jB/wOu+AZZV+vs8q+Xkqv13mm8/ECTsEf8CH8CV/Fy/gmXsE1+AvuxWv4CV7Hz6U+/ZzfXf8/hfL/UtrX81Ul9z/y9xn7uTUexBQ8jqXG+uM0/Bbn4Ul8EU/hCmN78F08hx8a64378QKeNNYbr+GP2NXGeuNAvIJJ+DOm4VUciddwDP6O+ag8aRfogo+jO67EmvgR1sIL6IvBLux7bIoB2BLrYEcMwoEYjPdhPRyL9bEIG+EUDMMnsAnOwWa4AJvjCmyF67A1bsd2+AlG4CGMxG+wI/6MndDHlf2MQXgXhmN3jMNeOBjvxlzsjZOxL87EGHwK++FSTMAKTMOPMRev4Wj0cOP4Rj+ciq1wOrbHh/FOnIkx+CgOwMcxGWfhWJyN03EOzsO5uBDn4fP4JL6AT+EyXX4lLsDXcSFuxOdwPz6PJ3EJnsd1+CeuRw93jlP0xQ3YEN/BJrgFo3Ar9sUPMRb/gfG4F+/HT/AB/BSfxIP4NH6Dr+Jx3IEn8AB+i8fwJP6EZ5BrUvU9NsPz2A8vYgH+hNPwMj6LV/Al/BmX4DVcj79hBfoa3zNibdyPfvgZBuBpDMafsBEG1uC8hQ0wDJthM2yNLTESW2M0tsWR2A5LMQKnYXt8Bjvhu3gnfoid8Rx2Q29P2hkG4d3YFntjd+yDvTEGUzEW87Ef3o/9cSIOwCdwIC7BkbgCl3qyXHwFP8FleByX4xlciRdwEd7AFzCoJve72BBfxF64GGPQh3r7YROMx6Y4EFPxPkzDMkzH6TgUZ+AwfBaH4wEchYcxG89jDl7FXFRenA8xEPOwJ+ZjHxyL6TgOx2EBFuJ4lN8teOj/r0j+vyh7P/qRYv+Rbvx182L/Yjz2wQGYggNxFCag/PYXpxr14TwcjC9iCq7AVHwXh+LnOBx/wXvxhrFsDGTZmdgas7EAx+AEzMOHcRw+iQW4GAvxDSzC9ViCe7AUP8Ny/BIn4Y/4IBq/B5iC/jgDw/ARjMHHMR1n4b34BD6ET+LT+DT+HZ/BnbgAP8WFeAIXYU1X2gEG4WIMwRXYEt/ACRjB902vYRS+gZ1xDXbBHdgVP8XueB774u8421h/oz/DOjgX6+M6jMH1OALfxrH4DpbguzgL38P5uFl/378FN+D7+vv+bbgbd+JH+KGx33AXGv1aJTbGA9gZD2Esfo5peBiz8QhOx6/wGTyKf8MzuA534y78CCuxAg/hCTyK3+I3+A2exmN4Bk/hL7pem9HPYThewDvwIubhL/gA/orT8CrO0NOP6unZeA3n6umn9PQC/A1fwt9xqZ5erqcr8A9jffFPPKXnO4fKm+MSbViH/soFG6ErtkMP7I2eOAJr4n3ohSPRG2ejD87FWvg39MXF6IcrMQDfwTr4AQbjfqyHlzEEf8cG2MKT/hm7YSjGYWO8B8NwLDbBCdgMn8BwXIjNcQm2MJaLbYzlYlvcgq3xI53+uU7/CnvjKYzG77AnXsJ+eAX7G+uHXZBziYrHBpiATXAQRmIi9sEk7I+DcRCmYhKm4X2YjsU4BCfgMHwQh+MTeA++iCNwKY7E1ZiFW3AUfoLZ+E8cjedwDF7FPPQy+lUMwLFYF8djGBZiZyzGvng/5mMpPosT8BU9fVBPf62n3bzt07WwHBviVOyAD+EdOAd74zOYhgswA5/FCbgIZ+HfcDa+iHP1fPN1fct1fStxKW7A13APrsRKXIUndPplnf4r/h1r+tCvYEPcgB1xI3bDd7AXvovhnhyPlTblQwfciuhKxBEjiTJiFrGU2EQ=
*/