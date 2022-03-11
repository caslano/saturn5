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