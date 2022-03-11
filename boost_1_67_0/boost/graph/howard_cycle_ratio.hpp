// Copyright (C) 2006-2009 Dmitry Bufistov and Andrey Parfenov

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_CYCLE_RATIO_HOWARD_HPP
#define BOOST_GRAPH_CYCLE_RATIO_HOWARD_HPP

#include <vector>
#include <list>
#include <algorithm>
#include <limits>

#include <boost/bind.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/concept_check.hpp>
#include <boost/pending/queue.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/concept/assert.hpp>

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
                boost::tie(oei, oeie) = out_edges(*vi, m_g);
                typename graph_traits< Graph >::out_edge_iterator mei
                    = std::max_element(oei, oeie,
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