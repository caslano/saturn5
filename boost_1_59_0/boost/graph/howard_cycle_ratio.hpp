// Copyright (C) 2006-2009 Dmitry Bufistov and Andrey Parfenov

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_CYCLE_RATIO_HOWARD_HPP
#define BOOST_GRAPH_CYCLE_RATIO_HOWARD_HPP

#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <limits>

#include <boost/bind/bind.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/concept_check.hpp>
#include <boost/pending/queue.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/concept/assert.hpp>
#include <boost/algorithm/minmax_element.hpp>

/** @file howard_cycle_ratio.hpp
 * @brief The implementation of the maximum/minimum cycle ratio/mean algorithm.
 * @author Dmitry Bufistov
 * @author Andrey Parfenov
 */

namespace boost
{

/**
 * The mcr_float is like numeric_limits, but only for floating point types
 * and only defines infinity() and epsilon(). This class is primarily used
 * to encapsulate a less-precise epsilon than natively supported by the
 * floating point type.
 */
template < typename Float = double > struct mcr_float
{
    typedef Float value_type;

    static Float infinity()
    {
        return std::numeric_limits< value_type >::infinity();
    }

    static Float epsilon() { return Float(-0.005); }
};

namespace detail
{

    template < typename FloatTraits > struct min_comparator_props
    {
        typedef std::greater< typename FloatTraits::value_type > comparator;
        static const int multiplier = 1;
    };

    template < typename FloatTraits > struct max_comparator_props
    {
        typedef std::less< typename FloatTraits::value_type > comparator;
        static const int multiplier = -1;
    };

    template < typename FloatTraits, typename ComparatorProps >
    struct float_wrapper
    {
        typedef typename FloatTraits::value_type value_type;
        typedef ComparatorProps comparator_props_t;
        typedef typename ComparatorProps::comparator comparator;

        static value_type infinity()
        {
            return FloatTraits::infinity() * ComparatorProps::multiplier;
        }

        static value_type epsilon()
        {
            return FloatTraits::epsilon() * ComparatorProps::multiplier;
        }
    };

    /*! @class mcr_howard
     * @brief Calculates optimum (maximum/minimum) cycle ratio of a directed
     * graph. Uses  Howard's iteration policy algorithm. </br>(It is described
     * in the paper "Experimental Analysis of the Fastest Optimum Cycle Ratio
     * and Mean Algorithm" by Ali Dasdan).
     */
    template < typename FloatTraits, typename Graph, typename VertexIndexMap,
        typename EdgeWeight1, typename EdgeWeight2 >
    class mcr_howard
    {
    public:
        typedef typename FloatTraits::value_type float_t;
        typedef typename FloatTraits::comparator_props_t cmp_props_t;
        typedef typename FloatTraits::comparator comparator_t;
        typedef enum
        {
            my_white = 0,
            my_black
        } my_color_type;
        typedef typename graph_traits< Graph >::vertex_descriptor vertex_t;
        typedef typename graph_traits< Graph >::edge_descriptor edge_t;
        typedef typename graph_traits< Graph >::vertices_size_type vn_t;
        typedef std::vector< float_t > vp_t;
        typedef typename boost::iterator_property_map< typename vp_t::iterator,
            VertexIndexMap >
            distance_map_t; // V -> float_t

        typedef typename std::vector< edge_t > ve_t;
        typedef std::vector< my_color_type > vcol_t;
        typedef
            typename ::boost::iterator_property_map< typename ve_t::iterator,
                VertexIndexMap >
                policy_t; // Vertex -> Edge
        typedef
            typename ::boost::iterator_property_map< typename vcol_t::iterator,
                VertexIndexMap >
                color_map_t;

        typedef typename std::list< vertex_t >
            pinel_t; // The in_edges list of the policy graph
        typedef typename std::vector< pinel_t > inedges1_t;
        typedef typename ::boost::iterator_property_map<
            typename inedges1_t::iterator, VertexIndexMap >
            inedges_t;
        typedef typename std::vector< edge_t > critical_cycle_t;

        // Bad  vertex flag. If true, then the vertex is "bad".
        // Vertex is "bad" if its out_degree is equal to zero.
        typedef
            typename boost::iterator_property_map< std::vector< int >::iterator,
                VertexIndexMap >
                badv_t;

        /*!
         * Constructor
         * \param g = (V, E) - a directed multigraph.
         * \param vim  Vertex Index Map. Read property Map: V -> [0,
         * num_vertices(g)). \param ewm  edge weight map. Read property map: E
         * -> R \param ew2m  edge weight map. Read property map: E -> R+ \param
         * infty A big enough value to guaranty that there exist a cycle with
         *  better ratio.
         * \param cmp The compare operator for float_ts.
         */
        mcr_howard(const Graph& g, VertexIndexMap vim, EdgeWeight1 ewm,
            EdgeWeight2 ew2m)
        : m_g(g)
        , m_vim(vim)
        , m_ew1m(ewm)
        , m_ew2m(ew2m)
        , m_bound(mcr_bound())
        , m_cr(m_bound)
        , m_V(num_vertices(m_g))
        , m_dis(m_V, 0)
        , m_dm(m_dis.begin(), m_vim)
        , m_policyc(m_V)
        , m_policy(m_policyc.begin(), m_vim)
        , m_inelc(m_V)
        , m_inel(m_inelc.begin(), m_vim)
        , m_badvc(m_V, false)
        , m_badv(m_badvc.begin(), m_vim)
        , m_colcv(m_V)
        , m_col_bfs(m_V)
        {
        }

        /*!
         * \return maximum/minimum_{for all cycles C}
         *         [sum_{e in C} w1(e)] / [sum_{e in C} w2(e)],
         * or FloatTraits::infinity() if graph has no cycles.
         */
        float_t ocr_howard()
        {
            construct_policy_graph();
            int k = 0;
            float_t mcr = 0;
            do
            {
                mcr = policy_mcr();
                ++k;
            } while (
                try_improve_policy(mcr) && k < 100); // To avoid infinite loop

            const float_t eps_ = -0.00000001 * cmp_props_t::multiplier;
            if (m_cmp(mcr, m_bound + eps_))
            {
                return FloatTraits::infinity();
            }
            else
            {
                return mcr;
            }
        }
        virtual ~mcr_howard() {}

    protected:
        virtual void store_critical_edge(edge_t, critical_cycle_t&) {}
        virtual void store_critical_cycle(critical_cycle_t&) {}

    private:
        /*!
         * \return lower/upper bound for the maximal/minimal cycle ratio
         */
        float_t mcr_bound()
        {
            typename graph_traits< Graph >::vertex_iterator vi, vie;
            typename graph_traits< Graph >::out_edge_iterator oei, oeie;
            float_t cz = (std::numeric_limits< float_t >::max)(); // Closest to
                                                                  // zero value
            float_t s = 0;
            const float_t eps_ = std::numeric_limits< float_t >::epsilon();
            for (boost::tie(vi, vie) = vertices(m_g); vi != vie; ++vi)
            {
                for (boost::tie(oei, oeie) = out_edges(*vi, m_g); oei != oeie;
                     ++oei)
                {
                    s += std::abs(m_ew1m[*oei]);
                    float_t a = std::abs(m_ew2m[*oei]);
                    if (a > eps_ && a < cz)
                    {
                        cz = a;
                    }
                }
            }
            return cmp_props_t::multiplier * (s / cz);
        }

        /*!
         *  Constructs an arbitrary policy graph.
         */
        void construct_policy_graph()
        {
            m_sink = graph_traits< Graph >().null_vertex();
            typename graph_traits< Graph >::vertex_iterator vi, vie;
            typename graph_traits< Graph >::out_edge_iterator oei, oeie;
            for (boost::tie(vi, vie) = vertices(m_g); vi != vie; ++vi)
            {
                using namespace boost::placeholders;

                boost::tie(oei, oeie) = out_edges(*vi, m_g);
                typename graph_traits< Graph >::out_edge_iterator mei
                    = boost::first_max_element(oei, oeie,
                        boost::bind(m_cmp,
                            boost::bind(&EdgeWeight1::operator[], m_ew1m, _1),
                            boost::bind(&EdgeWeight1::operator[], m_ew1m, _2)));
                if (mei == oeie)
                {
                    if (m_sink == graph_traits< Graph >().null_vertex())
                    {
                        m_sink = *vi;
                    }
                    m_badv[*vi] = true;
                    m_inel[m_sink].push_back(*vi);
                }
                else
                {
                    m_inel[target(*mei, m_g)].push_back(*vi);
                    m_policy[*vi] = *mei;
                }
            }
        }
        /*! Sets the distance value for all vertices "v" such that there is
         * a path from "v" to "sv". It does "inverse" breadth first visit of the
         * policy graph, starting from the vertex "sv".
         */
        void mcr_bfv(vertex_t sv, float_t cr, color_map_t c)
        {
            boost::queue< vertex_t > Q;
            c[sv] = my_black;
            Q.push(sv);
            while (!Q.empty())
            {
                vertex_t v = Q.top();
                Q.pop();
                for (typename pinel_t::const_iterator itr = m_inel[v].begin();
                     itr != m_inel[v].end(); ++itr)
                // For all in_edges of the policy graph
                {
                    if (*itr != sv)
                    {
                        if (m_badv[*itr])
                        {
                            m_dm[*itr] = m_dm[v] + m_bound - cr;
                        }
                        else
                        {
                            m_dm[*itr] = m_dm[v] + m_ew1m[m_policy[*itr]]
                                - m_ew2m[m_policy[*itr]] * cr;
                        }
                        c[*itr] = my_black;
                        Q.push(*itr);
                    }
                }
            }
        }

        /*!
         * \param sv an arbitrary (undiscovered) vertex of the policy graph.
         * \return a vertex in the policy graph that belongs to a cycle.
         * Performs a depth first visit until a cycle edge is found.
         */
        vertex_t find_cycle_vertex(vertex_t sv)
        {
            vertex_t gv = sv;
            std::fill(m_colcv.begin(), m_colcv.end(), my_white);
            color_map_t cm(m_colcv.begin(), m_vim);
            do
            {
                cm[gv] = my_black;
                if (!m_badv[gv])
                {
                    gv = target(m_policy[gv], m_g);
                }
                else
                {
                    gv = m_sink;
                }
            } while (cm[gv] != my_black);
            return gv;
        }

        /*!
         * \param sv - vertex that belongs to a cycle in the policy graph.
         */
        float_t cycle_ratio(vertex_t sv)
        {
            if (sv == m_sink)
                return m_bound;
            std::pair< float_t, float_t > sums_(float_t(0), float_t(0));
            vertex_t v = sv;
            critical_cycle_t cc;
            do
            {
                store_critical_edge(m_policy[v], cc);
                sums_.first += m_ew1m[m_policy[v]];
                sums_.second += m_ew2m[m_policy[v]];
                v = target(m_policy[v], m_g);
            } while (v != sv);
            float_t cr = sums_.first / sums_.second;
            if (m_cmp(m_cr, cr))
            {
                m_cr = cr;
                store_critical_cycle(cc);
            }
            return cr;
        }

        /*!
         *  Finds the optimal cycle ratio of the policy graph
         */
        float_t policy_mcr()
        {
            using namespace boost::placeholders;

            std::fill(m_col_bfs.begin(), m_col_bfs.end(), my_white);
            color_map_t vcm_ = color_map_t(m_col_bfs.begin(), m_vim);
            typename graph_traits< Graph >::vertex_iterator uv_itr, vie;
            boost::tie(uv_itr, vie) = vertices(m_g);
            float_t mcr = m_bound;
            while ((uv_itr = std::find_if(uv_itr, vie,
                        boost::bind(std::equal_to< my_color_type >(), my_white,
                            boost::bind(&color_map_t::operator[], vcm_, _1))))
                != vie)
            /// While there are undiscovered vertices
            {
                vertex_t gv = find_cycle_vertex(*uv_itr);
                float_t cr = cycle_ratio(gv);
                mcr_bfv(gv, cr, vcm_);
                if (m_cmp(mcr, cr))
                    mcr = cr;
                ++uv_itr;
            }
            return mcr;
        }

        /*!
         * Changes the edge m_policy[s] to the new_edge.
         */
        void improve_policy(vertex_t s, edge_t new_edge)
        {
            vertex_t t = target(m_policy[s], m_g);
            typename property_traits< VertexIndexMap >::value_type ti
                = m_vim[t];
            m_inelc[ti].erase(
                std::find(m_inelc[ti].begin(), m_inelc[ti].end(), s));
            m_policy[s] = new_edge;
            t = target(new_edge, m_g);
            m_inel[t].push_back(s); /// Maintain in_edge list
        }

        /*!
         * A negative cycle detector.
         */
        bool try_improve_policy(float_t cr)
        {
            bool improved = false;
            typename graph_traits< Graph >::vertex_iterator vi, vie;
            typename graph_traits< Graph >::out_edge_iterator oei, oeie;
            const float_t eps_ = FloatTraits::epsilon();
            for (boost::tie(vi, vie) = vertices(m_g); vi != vie; ++vi)
            {
                if (!m_badv[*vi])
                {
                    for (boost::tie(oei, oeie) = out_edges(*vi, m_g);
                         oei != oeie; ++oei)
                    {
                        vertex_t t = target(*oei, m_g);
                        // Current distance from *vi to some vertex
                        float_t dis_
                            = m_ew1m[*oei] - m_ew2m[*oei] * cr + m_dm[t];
                        if (m_cmp(m_dm[*vi] + eps_, dis_))
                        {
                            improve_policy(*vi, *oei);
                            m_dm[*vi] = dis_;
                            improved = true;
                        }
                    }
                }
                else
                {
                    float_t dis_ = m_bound - cr + m_dm[m_sink];
                    if (m_cmp(m_dm[*vi] + eps_, dis_))
                    {
                        m_dm[*vi] = dis_;
                    }
                }
            }
            return improved;
        }

    private:
        const Graph& m_g;
        VertexIndexMap m_vim;
        EdgeWeight1 m_ew1m;
        EdgeWeight2 m_ew2m;
        comparator_t m_cmp;
        float_t m_bound; //> The lower/upper bound to the maximal/minimal cycle
                         // ratio
        float_t m_cr; //>The best cycle ratio that has been found so far

        vn_t m_V; //>The number of the vertices in the graph
        vp_t m_dis; //>Container for the distance map
        distance_map_t m_dm; //>Distance map

        ve_t m_policyc; //>Container for the policy graph
        policy_t m_policy; //>The interface for the policy graph

        inedges1_t m_inelc; //>Container fot in edges list
        inedges_t m_inel; //>Policy graph, input edges list

        std::vector< int > m_badvc;
        badv_t m_badv; // Marks "bad" vertices

        vcol_t m_colcv, m_col_bfs; // Color maps
        vertex_t m_sink; // To convert any graph to "good"
    };

    /*! \class mcr_howard1
     * \brief Finds optimum cycle raio and a critical cycle
     */
    template < typename FloatTraits, typename Graph, typename VertexIndexMap,
        typename EdgeWeight1, typename EdgeWeight2 >
    class mcr_howard1 : public mcr_howard< FloatTraits, Graph, VertexIndexMap,
                            EdgeWeight1, EdgeWeight2 >
    {
    public:
        typedef mcr_howard< FloatTraits, Graph, VertexIndexMap, EdgeWeight1,
            EdgeWeight2 >
            inhr_t;
        mcr_howard1(const Graph& g, VertexIndexMap vim, EdgeWeight1 ewm,
            EdgeWeight2 ew2m)
        : inhr_t(g, vim, ewm, ew2m)
        {
        }

        void get_critical_cycle(typename inhr_t::critical_cycle_t& cc)
        {
            return cc.swap(m_cc);
        }

    protected:
        void store_critical_edge(
            typename inhr_t::edge_t ed, typename inhr_t::critical_cycle_t& cc)
        {
            cc.push_back(ed);
        }

        void store_critical_cycle(typename inhr_t::critical_cycle_t& cc)
        {
            m_cc.swap(cc);
        }

    private:
        typename inhr_t::critical_cycle_t m_cc; // Critical cycle
    };

    /*!
     * \param g a directed multigraph.
     * \param vim Vertex Index Map. A map V->[0, num_vertices(g))
     * \param ewm Edge weight1 map.
     * \param ew2m Edge weight2 map.
     * \param pcc  pointer to the critical edges list.
     * \return Optimum cycle ratio of g or FloatTraits::infinity() if g has no
     * cycles.
     */
    template < typename FT, typename TG, typename TVIM, typename TEW1,
        typename TEW2, typename EV >
    typename FT::value_type optimum_cycle_ratio(
        const TG& g, TVIM vim, TEW1 ewm, TEW2 ew2m, EV* pcc)
    {
        typedef typename graph_traits< TG >::directed_category DirCat;
        BOOST_STATIC_ASSERT(
            (is_convertible< DirCat*, directed_tag* >::value == true));
        BOOST_CONCEPT_ASSERT((IncidenceGraphConcept< TG >));
        BOOST_CONCEPT_ASSERT((VertexListGraphConcept< TG >));
        typedef typename graph_traits< TG >::vertex_descriptor Vertex;
        BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept< TVIM, Vertex >));
        typedef typename graph_traits< TG >::edge_descriptor Edge;
        BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept< TEW1, Edge >));
        BOOST_CONCEPT_ASSERT((ReadablePropertyMapConcept< TEW2, Edge >));

        if (pcc == 0)
        {
            return detail::mcr_howard< FT, TG, TVIM, TEW1, TEW2 >(
                g, vim, ewm, ew2m)
                .ocr_howard();
        }

        detail::mcr_howard1< FT, TG, TVIM, TEW1, TEW2 > obj(g, vim, ewm, ew2m);
        double ocr = obj.ocr_howard();
        obj.get_critical_cycle(*pcc);
        return ocr;
    }
} // namespace detail

// Algorithms
// Maximum Cycle Ratio

template < typename FloatTraits, typename Graph, typename VertexIndexMap,
    typename EdgeWeight1Map, typename EdgeWeight2Map >
inline typename FloatTraits::value_type maximum_cycle_ratio(const Graph& g,
    VertexIndexMap vim, EdgeWeight1Map ew1m, EdgeWeight2Map ew2m,
    std::vector< typename graph_traits< Graph >::edge_descriptor >* pcc = 0,
    FloatTraits = FloatTraits())
{
    typedef detail::float_wrapper< FloatTraits,
        detail::max_comparator_props< FloatTraits > >
        Traits;
    return detail::optimum_cycle_ratio< Traits >(g, vim, ew1m, ew2m, pcc);
}

template < typename Graph, typename VertexIndexMap, typename EdgeWeight1Map,
    typename EdgeWeight2Map >
inline double maximum_cycle_ratio(const Graph& g, VertexIndexMap vim,
    EdgeWeight1Map ew1m, EdgeWeight2Map ew2m,
    std::vector< typename graph_traits< Graph >::edge_descriptor >* pcc = 0)
{
    return maximum_cycle_ratio(g, vim, ew1m, ew2m, pcc, mcr_float<>());
}

// Minimum Cycle Ratio

template < typename FloatTraits, typename Graph, typename VertexIndexMap,
    typename EdgeWeight1Map, typename EdgeWeight2Map >
typename FloatTraits::value_type minimum_cycle_ratio(const Graph& g,
    VertexIndexMap vim, EdgeWeight1Map ew1m, EdgeWeight2Map ew2m,
    std::vector< typename graph_traits< Graph >::edge_descriptor >* pcc = 0,
    FloatTraits = FloatTraits())
{
    typedef detail::float_wrapper< FloatTraits,
        detail::min_comparator_props< FloatTraits > >
        Traits;
    return detail::optimum_cycle_ratio< Traits >(g, vim, ew1m, ew2m, pcc);
}

template < typename Graph, typename VertexIndexMap, typename EdgeWeight1Map,
    typename EdgeWeight2Map >
inline double minimum_cycle_ratio(const Graph& g, VertexIndexMap vim,
    EdgeWeight1Map ew1m, EdgeWeight2Map ew2m,
    std::vector< typename graph_traits< Graph >::edge_descriptor >* pcc = 0)
{
    return minimum_cycle_ratio(g, vim, ew1m, ew2m, pcc, mcr_float<>());
}

// Maximum Cycle Mean

template < typename FloatTraits, typename Graph, typename VertexIndexMap,
    typename EdgeWeightMap, typename EdgeIndexMap >
inline typename FloatTraits::value_type maximum_cycle_mean(const Graph& g,
    VertexIndexMap vim, EdgeWeightMap ewm, EdgeIndexMap eim,
    std::vector< typename graph_traits< Graph >::edge_descriptor >* pcc = 0,
    FloatTraits ft = FloatTraits())
{
    typedef typename remove_const<
        typename property_traits< EdgeWeightMap >::value_type >::type Weight;
    typename std::vector< Weight > ed_w2(boost::num_edges(g), 1);
    return maximum_cycle_ratio(
        g, vim, ewm, make_iterator_property_map(ed_w2.begin(), eim), pcc, ft);
}

template < typename Graph, typename VertexIndexMap, typename EdgeWeightMap,
    typename EdgeIndexMap >
inline double maximum_cycle_mean(const Graph& g, VertexIndexMap vim,
    EdgeWeightMap ewm, EdgeIndexMap eim,
    std::vector< typename graph_traits< Graph >::edge_descriptor >* pcc = 0)
{
    return maximum_cycle_mean(g, vim, ewm, eim, pcc, mcr_float<>());
}

// Minimum Cycle Mean

template < typename FloatTraits, typename Graph, typename VertexIndexMap,
    typename EdgeWeightMap, typename EdgeIndexMap >
inline typename FloatTraits::value_type minimum_cycle_mean(const Graph& g,
    VertexIndexMap vim, EdgeWeightMap ewm, EdgeIndexMap eim,
    std::vector< typename graph_traits< Graph >::edge_descriptor >* pcc = 0,
    FloatTraits ft = FloatTraits())
{
    typedef typename remove_const<
        typename property_traits< EdgeWeightMap >::value_type >::type Weight;
    typename std::vector< Weight > ed_w2(boost::num_edges(g), 1);
    return minimum_cycle_ratio(
        g, vim, ewm, make_iterator_property_map(ed_w2.begin(), eim), pcc, ft);
}

template < typename Graph, typename VertexIndexMap, typename EdgeWeightMap,
    typename EdgeIndexMap >
inline double minimum_cycle_mean(const Graph& g, VertexIndexMap vim,
    EdgeWeightMap ewm, EdgeIndexMap eim,
    std::vector< typename graph_traits< Graph >::edge_descriptor >* pcc = 0)
{
    return minimum_cycle_mean(g, vim, ewm, eim, pcc, mcr_float<>());
}

} // namespace boost

#endif

/* howard_cycle_ratio.hpp
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
*/