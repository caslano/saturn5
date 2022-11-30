//  (C) Copyright David Abrahams 2000.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef REVERSE_GRAPH_DWA092300_H_
#define REVERSE_GRAPH_DWA092300_H_

#include <boost/graph/adjacency_iterator.hpp>
#include <boost/graph/properties.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/if.hpp>

namespace boost
{

struct reverse_graph_tag
{
};

namespace detail
{

    template < typename EdgeDesc > class reverse_graph_edge_descriptor
    {
    public:
        EdgeDesc
            underlying_descx; // Odd name is because this needs to be public but
                              // shouldn't be exposed to users anymore

    private:
        typedef EdgeDesc base_descriptor_type;

    public:
        explicit reverse_graph_edge_descriptor(
            const EdgeDesc& underlying_descx = EdgeDesc())
        : underlying_descx(underlying_descx)
        {
        }

        friend bool operator==(const reverse_graph_edge_descriptor& a,
            const reverse_graph_edge_descriptor& b)
        {
            return a.underlying_descx == b.underlying_descx;
        }
        friend bool operator!=(const reverse_graph_edge_descriptor& a,
            const reverse_graph_edge_descriptor& b)
        {
            return a.underlying_descx != b.underlying_descx;
        }
        friend bool operator<(const reverse_graph_edge_descriptor& a,
            const reverse_graph_edge_descriptor& b)
        {
            return a.underlying_descx < b.underlying_descx;
        }
        friend bool operator>(const reverse_graph_edge_descriptor& a,
            const reverse_graph_edge_descriptor& b)
        {
            return a.underlying_descx > b.underlying_descx;
        }
        friend bool operator<=(const reverse_graph_edge_descriptor& a,
            const reverse_graph_edge_descriptor& b)
        {
            return a.underlying_descx <= b.underlying_descx;
        }
        friend bool operator>=(const reverse_graph_edge_descriptor& a,
            const reverse_graph_edge_descriptor& b)
        {
            return a.underlying_descx >= b.underlying_descx;
        }
    };

    template < typename EdgeDesc > struct reverse_graph_edge_descriptor_maker
    {
        typedef reverse_graph_edge_descriptor< EdgeDesc > result_type;

        reverse_graph_edge_descriptor< EdgeDesc > operator()(
            const EdgeDesc& ed) const
        {
            return reverse_graph_edge_descriptor< EdgeDesc >(ed);
        }
    };

    template < typename EdgeDesc, typename Iter >
    std::pair< transform_iterator<
                   reverse_graph_edge_descriptor_maker< EdgeDesc >, Iter >,
        transform_iterator< reverse_graph_edge_descriptor_maker< EdgeDesc >,
            Iter > >
    reverse_edge_iter_pair(const std::pair< Iter, Iter >& ip)
    {
        return std::make_pair(
            make_transform_iterator(
                ip.first, reverse_graph_edge_descriptor_maker< EdgeDesc >()),
            make_transform_iterator(
                ip.second, reverse_graph_edge_descriptor_maker< EdgeDesc >()));
    }

    // Get the underlying descriptor from a vertex or edge descriptor
    template < typename Desc >
    struct get_underlying_descriptor_from_reverse_descriptor
    {
        typedef Desc type;
        static Desc convert(const Desc& d) { return d; }
    };
    template < typename Desc >
    struct get_underlying_descriptor_from_reverse_descriptor<
        reverse_graph_edge_descriptor< Desc > >
    {
        typedef Desc type;
        static Desc convert(const reverse_graph_edge_descriptor< Desc >& d)
        {
            return d.underlying_descx;
        }
    };

    template < bool isEdgeList > struct choose_rev_edge_iter
    {
    };
    template <> struct choose_rev_edge_iter< true >
    {
        template < class G > struct bind_
        {
            typedef transform_iterator<
                reverse_graph_edge_descriptor_maker<
                    typename graph_traits< G >::edge_descriptor >,
                typename graph_traits< G >::edge_iterator >
                type;
        };
    };
    template <> struct choose_rev_edge_iter< false >
    {
        template < class G > struct bind_
        {
            typedef void type;
        };
    };

} // namespace detail

template < class BidirectionalGraph,
    class GraphRef = const BidirectionalGraph& >
class reverse_graph
{
    typedef reverse_graph< BidirectionalGraph, GraphRef > Self;
    typedef graph_traits< BidirectionalGraph > Traits;

public:
    typedef BidirectionalGraph base_type;
    typedef GraphRef base_ref_type;

    // Constructor
    reverse_graph(GraphRef g) : m_g(g) {}
    // Conversion from reverse_graph on non-const reference to one on const
    // reference
    reverse_graph(
        const reverse_graph< BidirectionalGraph, BidirectionalGraph& >& o)
    : m_g(o.m_g)
    {
    }

    // Graph requirements
    typedef typename Traits::vertex_descriptor vertex_descriptor;
    typedef detail::reverse_graph_edge_descriptor<
        typename Traits::edge_descriptor >
        edge_descriptor;
    typedef typename Traits::directed_category directed_category;
    typedef typename Traits::edge_parallel_category edge_parallel_category;
    typedef typename Traits::traversal_category traversal_category;

    // IncidenceGraph requirements
    typedef transform_iterator< detail::reverse_graph_edge_descriptor_maker<
                                    typename Traits::edge_descriptor >,
        typename Traits::in_edge_iterator >
        out_edge_iterator;
    typedef typename Traits::degree_size_type degree_size_type;

    // BidirectionalGraph requirements
    typedef transform_iterator< detail::reverse_graph_edge_descriptor_maker<
                                    typename Traits::edge_descriptor >,
        typename Traits::out_edge_iterator >
        in_edge_iterator;

    // AdjacencyGraph requirements
    typedef typename adjacency_iterator_generator< Self, vertex_descriptor,
        out_edge_iterator >::type adjacency_iterator;

    // VertexListGraph requirements
    typedef typename Traits::vertex_iterator vertex_iterator;

    // EdgeListGraph requirements
    enum
    {
        is_edge_list
        = is_convertible< traversal_category, edge_list_graph_tag >::value
    };
    typedef detail::choose_rev_edge_iter< is_edge_list > ChooseEdgeIter;
    typedef typename ChooseEdgeIter::template bind_< BidirectionalGraph >::type
        edge_iterator;
    typedef typename Traits::vertices_size_type vertices_size_type;
    typedef typename Traits::edges_size_type edges_size_type;

    typedef reverse_graph_tag graph_tag;

#ifndef BOOST_GRAPH_NO_BUNDLED_PROPERTIES
    // Bundled properties support
    template < typename Descriptor >
    typename graph::detail::bundled_result< BidirectionalGraph,
        typename detail::get_underlying_descriptor_from_reverse_descriptor<
            Descriptor >::type >::type&
    operator[](Descriptor x)
    {
        return m_g[detail::get_underlying_descriptor_from_reverse_descriptor<
            Descriptor >::convert(x)];
    }

    template < typename Descriptor >
    typename graph::detail::bundled_result< BidirectionalGraph,
        typename detail::get_underlying_descriptor_from_reverse_descriptor<
            Descriptor >::type >::type const&
    operator[](Descriptor x) const
    {
        return m_g[detail::get_underlying_descriptor_from_reverse_descriptor<
            Descriptor >::convert(x)];
    }
#endif // BOOST_GRAPH_NO_BUNDLED_PROPERTIES

    static vertex_descriptor null_vertex() { return Traits::null_vertex(); }

    // would be private, but template friends aren't portable enough.
    // private:
    GraphRef m_g;
};

// These are separate so they are not instantiated unless used (see bug 1021)
template < class BidirectionalGraph, class GraphRef >
struct vertex_property_type< reverse_graph< BidirectionalGraph, GraphRef > >
{
    typedef
        typename boost::vertex_property_type< BidirectionalGraph >::type type;
};

template < class BidirectionalGraph, class GraphRef >
struct edge_property_type< reverse_graph< BidirectionalGraph, GraphRef > >
{
    typedef typename boost::edge_property_type< BidirectionalGraph >::type type;
};

template < class BidirectionalGraph, class GraphRef >
struct graph_property_type< reverse_graph< BidirectionalGraph, GraphRef > >
{
    typedef
        typename boost::graph_property_type< BidirectionalGraph >::type type;
};

#ifndef BOOST_GRAPH_NO_BUNDLED_PROPERTIES
template < typename Graph, typename GraphRef >
struct vertex_bundle_type< reverse_graph< Graph, GraphRef > >
: vertex_bundle_type< Graph >
{
};

template < typename Graph, typename GraphRef >
struct edge_bundle_type< reverse_graph< Graph, GraphRef > >
: edge_bundle_type< Graph >
{
};

template < typename Graph, typename GraphRef >
struct graph_bundle_type< reverse_graph< Graph, GraphRef > >
: graph_bundle_type< Graph >
{
};
#endif // BOOST_GRAPH_NO_BUNDLED_PROPERTIES

template < class BidirectionalGraph >
inline reverse_graph< BidirectionalGraph > make_reverse_graph(
    const BidirectionalGraph& g)
{
    return reverse_graph< BidirectionalGraph >(g);
}

template < class BidirectionalGraph >
inline reverse_graph< BidirectionalGraph, BidirectionalGraph& >
make_reverse_graph(BidirectionalGraph& g)
{
    return reverse_graph< BidirectionalGraph, BidirectionalGraph& >(g);
}

template < class BidirectionalGraph, class GRef >
std::pair< typename reverse_graph< BidirectionalGraph >::vertex_iterator,
    typename reverse_graph< BidirectionalGraph >::vertex_iterator >
vertices(const reverse_graph< BidirectionalGraph, GRef >& g)
{
    return vertices(g.m_g);
}

template < class BidirectionalGraph, class GRef >
std::pair< typename reverse_graph< BidirectionalGraph >::edge_iterator,
    typename reverse_graph< BidirectionalGraph >::edge_iterator >
edges(const reverse_graph< BidirectionalGraph, GRef >& g)
{
    return detail::reverse_edge_iter_pair<
        typename graph_traits< BidirectionalGraph >::edge_descriptor >(
        edges(g.m_g));
}

template < class BidirectionalGraph, class GRef >
inline std::pair<
    typename reverse_graph< BidirectionalGraph >::out_edge_iterator,
    typename reverse_graph< BidirectionalGraph >::out_edge_iterator >
out_edges(
    const typename graph_traits< BidirectionalGraph >::vertex_descriptor u,
    const reverse_graph< BidirectionalGraph, GRef >& g)
{
    return detail::reverse_edge_iter_pair<
        typename graph_traits< BidirectionalGraph >::edge_descriptor >(
        in_edges(u, g.m_g));
}

template < class BidirectionalGraph, class GRef >
inline typename graph_traits< BidirectionalGraph >::vertices_size_type
num_vertices(const reverse_graph< BidirectionalGraph, GRef >& g)
{
    return num_vertices(g.m_g);
}

template < class BidirectionalGraph, class GRef >
inline typename reverse_graph< BidirectionalGraph >::edges_size_type num_edges(
    const reverse_graph< BidirectionalGraph, GRef >& g)
{
    return num_edges(g.m_g);
}

template < class BidirectionalGraph, class GRef >
inline typename graph_traits< BidirectionalGraph >::degree_size_type out_degree(
    const typename graph_traits< BidirectionalGraph >::vertex_descriptor u,
    const reverse_graph< BidirectionalGraph, GRef >& g)
{
    return in_degree(u, g.m_g);
}

template < class BidirectionalGraph, class GRef >
inline typename graph_traits< BidirectionalGraph >::vertex_descriptor vertex(
    const typename graph_traits< BidirectionalGraph >::vertices_size_type v,
    const reverse_graph< BidirectionalGraph, GRef >& g)
{
    return vertex(v, g.m_g);
}

template < class BidirectionalGraph, class GRef >
inline std::pair< typename graph_traits< reverse_graph< BidirectionalGraph,
                      GRef > >::edge_descriptor,
    bool >
edge(const typename graph_traits< BidirectionalGraph >::vertex_descriptor u,
    const typename graph_traits< BidirectionalGraph >::vertex_descriptor v,
    const reverse_graph< BidirectionalGraph, GRef >& g)
{
    typedef typename graph_traits< BidirectionalGraph >::edge_descriptor
        underlying_edge_descriptor;
    std::pair< underlying_edge_descriptor, bool > e = edge(v, u, g.m_g);
    return std::make_pair(
        detail::reverse_graph_edge_descriptor< underlying_edge_descriptor >(
            e.first),
        e.second);
}

template < class BidirectionalGraph, class GRef >
inline std::pair<
    typename reverse_graph< BidirectionalGraph >::in_edge_iterator,
    typename reverse_graph< BidirectionalGraph >::in_edge_iterator >
in_edges(const typename graph_traits< BidirectionalGraph >::vertex_descriptor u,
    const reverse_graph< BidirectionalGraph, GRef >& g)
{
    return detail::reverse_edge_iter_pair<
        typename graph_traits< BidirectionalGraph >::edge_descriptor >(
        out_edges(u, g.m_g));
}

template < class BidirectionalGraph, class GRef >
inline std::pair<
    typename reverse_graph< BidirectionalGraph, GRef >::adjacency_iterator,
    typename reverse_graph< BidirectionalGraph, GRef >::adjacency_iterator >
adjacent_vertices(
    typename graph_traits< BidirectionalGraph >::vertex_descriptor u,
    const reverse_graph< BidirectionalGraph, GRef >& g)
{
    typedef reverse_graph< BidirectionalGraph, GRef > Graph;
    typename graph_traits< Graph >::out_edge_iterator first, last;
    boost::tie(first, last) = out_edges(u, g);
    typedef
        typename graph_traits< Graph >::adjacency_iterator adjacency_iterator;
    return std::make_pair(adjacency_iterator(first, const_cast< Graph* >(&g)),
        adjacency_iterator(last, const_cast< Graph* >(&g)));
}

template < class BidirectionalGraph, class GRef >
inline typename graph_traits< BidirectionalGraph >::degree_size_type in_degree(
    const typename graph_traits< BidirectionalGraph >::vertex_descriptor u,
    const reverse_graph< BidirectionalGraph, GRef >& g)
{
    return out_degree(u, g.m_g);
}

template < class Edge, class BidirectionalGraph, class GRef >
inline typename graph_traits< BidirectionalGraph >::vertex_descriptor source(
    const detail::reverse_graph_edge_descriptor< Edge >& e,
    const reverse_graph< BidirectionalGraph, GRef >& g)
{
    return target(e.underlying_descx, g.m_g);
}

template < class Edge, class BidirectionalGraph, class GRef >
inline typename graph_traits< BidirectionalGraph >::vertex_descriptor target(
    const detail::reverse_graph_edge_descriptor< Edge >& e,
    const reverse_graph< BidirectionalGraph, GRef >& g)
{
    return source(e.underlying_descx, g.m_g);
}

template < class BidirectionalGraph, class GRef >
inline typename graph_traits< BidirectionalGraph >::degree_size_type degree(
    const typename graph_traits< BidirectionalGraph >::vertex_descriptor u,
    const reverse_graph< BidirectionalGraph, GRef >& g)
{
    return degree(u, g.m_g);
}

namespace detail
{

    template < typename PM > struct reverse_graph_edge_property_map
    {
    private:
        PM underlying_pm;

    public:
        typedef reverse_graph_edge_descriptor<
            typename property_traits< PM >::key_type >
            key_type;
        typedef typename property_traits< PM >::value_type value_type;
        typedef typename property_traits< PM >::reference reference;
        typedef typename property_traits< PM >::category category;

        explicit reverse_graph_edge_property_map(const PM& pm)
        : underlying_pm(pm)
        {
        }

        friend reference get(
            const reverse_graph_edge_property_map& m, const key_type& e)
        {
            return get(m.underlying_pm, e.underlying_descx);
        }

        friend void put(const reverse_graph_edge_property_map& m,
            const key_type& e, const value_type& v)
        {
            put(m.underlying_pm, e.underlying_descx, v);
        }

        reference operator[](const key_type& k) const
        {
            return (this->underlying_pm)[k.underlying_descx];
        }
    };

} // namespace detail

template < class BidirGraph, class GRef, class Property >
struct property_map< reverse_graph< BidirGraph, GRef >, Property >
{
    typedef boost::is_same<
        typename detail::property_kind_from_graph< BidirGraph, Property >::type,
        edge_property_tag >
        is_edge_prop;
    typedef boost::is_const< typename boost::remove_reference< GRef >::type >
        is_ref_const;
    typedef typename boost::mpl::if_< is_ref_const,
        typename property_map< BidirGraph, Property >::const_type,
        typename property_map< BidirGraph, Property >::type >::type orig_type;
    typedef typename property_map< BidirGraph, Property >::const_type
        orig_const_type;
    typedef typename boost::mpl::if_< is_edge_prop,
        detail::reverse_graph_edge_property_map< orig_type >, orig_type >::type
        type;
    typedef typename boost::mpl::if_< is_edge_prop,
        detail::reverse_graph_edge_property_map< orig_const_type >,
        orig_const_type >::type const_type;
};

template < class BidirGraph, class GRef, class Property >
struct property_map< const reverse_graph< BidirGraph, GRef >, Property >
{
    typedef boost::is_same<
        typename detail::property_kind_from_graph< BidirGraph, Property >::type,
        edge_property_tag >
        is_edge_prop;
    typedef typename property_map< BidirGraph, Property >::const_type
        orig_const_type;
    typedef typename boost::mpl::if_< is_edge_prop,
        detail::reverse_graph_edge_property_map< orig_const_type >,
        orig_const_type >::type const_type;
    typedef const_type type;
};

template < class BidirGraph, class GRef, class Property >
typename disable_if< is_same< Property, edge_underlying_t >,
    typename property_map< reverse_graph< BidirGraph, GRef >,
        Property >::type >::type
get(Property p, reverse_graph< BidirGraph, GRef >& g)
{
    return typename property_map< reverse_graph< BidirGraph, GRef >,
        Property >::type(get(p, g.m_g));
}

template < class BidirGraph, class GRef, class Property >
typename disable_if< is_same< Property, edge_underlying_t >,
    typename property_map< reverse_graph< BidirGraph, GRef >,
        Property >::const_type >::type
get(Property p, const reverse_graph< BidirGraph, GRef >& g)
{
    const BidirGraph& gref = g.m_g; // in case GRef is non-const
    return typename property_map< reverse_graph< BidirGraph, GRef >,
        Property >::const_type(get(p, gref));
}

template < class BidirectionalGraph, class GRef, class Property, class Key >
typename disable_if< is_same< Property, edge_underlying_t >,
    typename property_traits<
        typename property_map< reverse_graph< BidirectionalGraph, GRef >,
            Property >::const_type >::value_type >::type
get(Property p, const reverse_graph< BidirectionalGraph, GRef >& g,
    const Key& k)
{
    return get(get(p, g), k);
}

template < class BidirectionalGraph, class GRef, class Property, class Key,
    class Value >
void put(Property p, reverse_graph< BidirectionalGraph, GRef >& g, const Key& k,
    const Value& val)
{
    put(get(p, g), k, val);
}

// Get the underlying descriptor from a reverse_graph's wrapped edge descriptor

namespace detail
{
    template < class E > struct underlying_edge_desc_map_type
    {
        E operator[](const reverse_graph_edge_descriptor< E >& k) const
        {
            return k.underlying_descx;
        }
    };

    template < class E >
    E get(underlying_edge_desc_map_type< E > m,
        const reverse_graph_edge_descriptor< E >& k)
    {
        return m[k];
    }
}

template < class E >
struct property_traits< detail::underlying_edge_desc_map_type< E > >
{
    typedef detail::reverse_graph_edge_descriptor< E > key_type;
    typedef E value_type;
    typedef const E& reference;
    typedef readable_property_map_tag category;
};

template < class Graph, class GRef >
struct property_map< reverse_graph< Graph, GRef >, edge_underlying_t >
{
private:
    typedef typename graph_traits< Graph >::edge_descriptor ed;

public:
    typedef detail::underlying_edge_desc_map_type< ed > type;
    typedef detail::underlying_edge_desc_map_type< ed > const_type;
};

template < typename T > struct is_reverse_graph : boost::mpl::false_
{
};
template < typename G, typename R >
struct is_reverse_graph< reverse_graph< G, R > > : boost::mpl::true_
{
};

template < class G >
typename enable_if< is_reverse_graph< G >,
    detail::underlying_edge_desc_map_type< typename graph_traits<
        typename G::base_type >::edge_descriptor > >::type
get(edge_underlying_t, G&)
{
    return detail::underlying_edge_desc_map_type<
        typename graph_traits< typename G::base_type >::edge_descriptor >();
}

template < class G >
typename enable_if< is_reverse_graph< G >,
    typename graph_traits< typename G::base_type >::edge_descriptor >::type
get(edge_underlying_t, G&, const typename graph_traits< G >::edge_descriptor& k)
{
    return k.underlying_descx;
}

template < class G >
typename enable_if< is_reverse_graph< G >,
    detail::underlying_edge_desc_map_type< typename graph_traits<
        typename G::base_type >::edge_descriptor > >::type
get(edge_underlying_t, const G&)
{
    return detail::underlying_edge_desc_map_type<
        typename graph_traits< typename G::base_type >::edge_descriptor >();
}

template < class G >
typename enable_if< is_reverse_graph< G >,
    typename graph_traits< typename G::base_type >::edge_descriptor >::type
get(edge_underlying_t, const G&,
    const typename graph_traits< G >::edge_descriptor& k)
{
    return k.underlying_descx;
}

// Access to wrapped graph's graph properties

template < typename BidirectionalGraph, typename GRef, typename Tag,
    typename Value >
inline void set_property(const reverse_graph< BidirectionalGraph, GRef >& g,
    Tag tag, const Value& value)
{
    set_property(g.m_g, tag, value);
}

template < typename BidirectionalGraph, typename GRef, typename Tag >
inline typename boost::mpl::if_<
    boost::is_const< typename boost::remove_reference< GRef >::type >,
    const typename graph_property< BidirectionalGraph, Tag >::type&,
    typename graph_property< BidirectionalGraph, Tag >::type& >::type
get_property(const reverse_graph< BidirectionalGraph, GRef >& g, Tag tag)
{
    return get_property(g.m_g, tag);
}

} // namespace boost

#endif

/* reverse_graph.hpp
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
*/