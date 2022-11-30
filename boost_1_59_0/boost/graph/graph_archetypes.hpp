//=======================================================================
// Copyright 2002 Indiana University.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_ARCHETYPES_HPP
#define BOOST_GRAPH_ARCHETYPES_HPP

#include <boost/property_map/property_map.hpp>
#include <boost/concept_archetype.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>

namespace boost
{ // should use a different namespace for this

namespace detail
{
    struct null_graph_archetype : public null_archetype<>
    {
        struct traversal_category
        {
        };
    };
}

//===========================================================================
template < typename Vertex, typename Directed, typename ParallelCategory,
    typename Base = detail::null_graph_archetype >
struct incidence_graph_archetype : public Base
{
    typedef typename Base::traversal_category base_trav_cat;
    struct traversal_category : public incidence_graph_tag, public base_trav_cat
    {
    };
#if 0
    typedef immutable_graph_tag mutability_category;
#endif
    typedef Vertex vertex_descriptor;
    typedef unsigned int degree_size_type;
    typedef unsigned int vertices_size_type;
    typedef unsigned int edges_size_type;
    struct edge_descriptor
    {
        edge_descriptor() {}
        edge_descriptor(const detail::dummy_constructor&) {}
        bool operator==(const edge_descriptor&) const { return false; }
        bool operator!=(const edge_descriptor&) const { return false; }
    };
    typedef input_iterator_archetype< edge_descriptor > out_edge_iterator;

    typedef Directed directed_category;
    typedef ParallelCategory edge_parallel_category;

    typedef void adjacency_iterator;
    typedef void in_edge_iterator;
    typedef void vertex_iterator;
    typedef void edge_iterator;

    static vertex_descriptor null_vertex() { return vertex_descriptor(); }
};
template < typename V, typename D, typename P, typename B >
V source(
    const typename incidence_graph_archetype< V, D, P, B >::edge_descriptor&,
    const incidence_graph_archetype< V, D, P, B >&)
{
    return V(static_object< detail::dummy_constructor >::get());
}
template < typename V, typename D, typename P, typename B >
V target(
    const typename incidence_graph_archetype< V, D, P, B >::edge_descriptor&,
    const incidence_graph_archetype< V, D, P, B >&)
{
    return V(static_object< detail::dummy_constructor >::get());
}

template < typename V, typename D, typename P, typename B >
std::pair< typename incidence_graph_archetype< V, D, P, B >::out_edge_iterator,
    typename incidence_graph_archetype< V, D, P, B >::out_edge_iterator >
out_edges(const V&, const incidence_graph_archetype< V, D, P, B >&)
{
    typedef typename incidence_graph_archetype< V, D, P, B >::out_edge_iterator
        Iter;
    return std::make_pair(Iter(), Iter());
}

template < typename V, typename D, typename P, typename B >
typename incidence_graph_archetype< V, D, P, B >::degree_size_type out_degree(
    const V&, const incidence_graph_archetype< V, D, P, B >&)
{
    return 0;
}

//===========================================================================
template < typename Vertex, typename Directed, typename ParallelCategory,
    typename Base = detail::null_graph_archetype >
struct adjacency_graph_archetype : public Base
{
    typedef typename Base::traversal_category base_trav_cat;
    struct traversal_category : public adjacency_graph_tag, public base_trav_cat
    {
    };
    typedef Vertex vertex_descriptor;
    typedef unsigned int degree_size_type;
    typedef unsigned int vertices_size_type;
    typedef unsigned int edges_size_type;
    typedef void edge_descriptor;
    typedef input_iterator_archetype< Vertex > adjacency_iterator;

    typedef Directed directed_category;
    typedef ParallelCategory edge_parallel_category;

    typedef void in_edge_iterator;
    typedef void out_edge_iterator;
    typedef void vertex_iterator;
    typedef void edge_iterator;

    static vertex_descriptor null_vertex() { return vertex_descriptor(); }
};

template < typename V, typename D, typename P, typename B >
std::pair< typename adjacency_graph_archetype< V, D, P, B >::adjacency_iterator,
    typename adjacency_graph_archetype< V, D, P, B >::adjacency_iterator >
adjacent_vertices(const V&, const adjacency_graph_archetype< V, D, P, B >&)
{
    typedef typename adjacency_graph_archetype< V, D, P, B >::adjacency_iterator
        Iter;
    return std::make_pair(Iter(), Iter());
}

template < typename V, typename D, typename P, typename B >
typename adjacency_graph_archetype< V, D, P, B >::degree_size_type out_degree(
    const V&, const adjacency_graph_archetype< V, D, P, B >&)
{
    return 0;
}

//===========================================================================
template < typename Vertex, typename Directed, typename ParallelCategory,
    typename Base = detail::null_graph_archetype >
struct vertex_list_graph_archetype : public Base
{
    typedef incidence_graph_archetype< Vertex, Directed, ParallelCategory >
        Incidence;
    typedef adjacency_graph_archetype< Vertex, Directed, ParallelCategory >
        Adjacency;

    typedef typename Base::traversal_category base_trav_cat;
    struct traversal_category : public vertex_list_graph_tag,
                                public base_trav_cat
    {
    };
#if 0
    typedef immutable_graph_tag mutability_category;
#endif
    typedef Vertex vertex_descriptor;
    typedef unsigned int degree_size_type;
    typedef typename Incidence::edge_descriptor edge_descriptor;
    typedef typename Incidence::out_edge_iterator out_edge_iterator;
    typedef typename Adjacency::adjacency_iterator adjacency_iterator;

    typedef input_iterator_archetype< Vertex > vertex_iterator;
    typedef unsigned int vertices_size_type;
    typedef unsigned int edges_size_type;

    typedef Directed directed_category;
    typedef ParallelCategory edge_parallel_category;

    typedef void in_edge_iterator;
    typedef void edge_iterator;

    static vertex_descriptor null_vertex() { return vertex_descriptor(); }
};

template < typename V, typename D, typename P, typename B >
std::pair< typename vertex_list_graph_archetype< V, D, P, B >::vertex_iterator,
    typename vertex_list_graph_archetype< V, D, P, B >::vertex_iterator >
vertices(const vertex_list_graph_archetype< V, D, P, B >&)
{
    typedef typename vertex_list_graph_archetype< V, D, P, B >::vertex_iterator
        Iter;
    return std::make_pair(Iter(), Iter());
}

template < typename V, typename D, typename P, typename B >
typename vertex_list_graph_archetype< V, D, P, B >::vertices_size_type
num_vertices(const vertex_list_graph_archetype< V, D, P, B >&)
{
    return 0;
}

// ambiguously inherited from incidence graph and adjacency graph
template < typename V, typename D, typename P, typename B >
typename vertex_list_graph_archetype< V, D, P, B >::degree_size_type out_degree(
    const V&, const vertex_list_graph_archetype< V, D, P, B >&)
{
    return 0;
}

//===========================================================================

struct property_graph_archetype_tag
{
};

template < typename GraphArchetype, typename Property, typename ValueArch >
struct property_graph_archetype : public GraphArchetype
{
    typedef property_graph_archetype_tag graph_tag;
    typedef ValueArch vertex_property_type;
    typedef ValueArch edge_property_type;
};

struct choose_edge_property_map_archetype
{
    template < typename Graph, typename Property, typename Tag > struct bind_
    {
        typedef mutable_lvalue_property_map_archetype<
            typename Graph::edge_descriptor, Property >
            type;
        typedef lvalue_property_map_archetype< typename Graph::edge_descriptor,
            Property >
            const_type;
    };
};
template <> struct edge_property_selector< property_graph_archetype_tag >
{
    typedef choose_edge_property_map_archetype type;
};

struct choose_vertex_property_map_archetype
{
    template < typename Graph, typename Property, typename Tag > struct bind_
    {
        typedef mutable_lvalue_property_map_archetype<
            typename Graph::vertex_descriptor, Property >
            type;
        typedef lvalue_property_map_archetype<
            typename Graph::vertex_descriptor, Property >
            const_type;
    };
};

template <> struct vertex_property_selector< property_graph_archetype_tag >
{
    typedef choose_vertex_property_map_archetype type;
};

template < typename G, typename P, typename V >
typename property_map< property_graph_archetype< G, P, V >, P >::type get(
    P, property_graph_archetype< G, P, V >&)
{
    typename property_map< property_graph_archetype< G, P, V >, P >::type pmap;
    return pmap;
}

template < typename G, typename P, typename V >
typename property_map< property_graph_archetype< G, P, V >, P >::const_type get(
    P, const property_graph_archetype< G, P, V >&)
{
    typename property_map< property_graph_archetype< G, P, V >, P >::const_type
        pmap;
    return pmap;
}

template < typename G, typename P, typename K, typename V >
typename property_traits< typename property_map<
    property_graph_archetype< G, P, V >, P >::const_type >::value_type
get(P p, const property_graph_archetype< G, P, V >& g, K k)
{
    return get(get(p, g), k);
}

template < typename G, typename P, typename V, typename Key >
void put(
    P p, property_graph_archetype< G, P, V >& g, const Key& key, const V& value)
{
    typedef typename boost::property_map< property_graph_archetype< G, P, V >,
        P >::type Map;
    Map pmap = get(p, g);
    put(pmap, key, value);
}

struct color_value_archetype
{
    color_value_archetype() {}
    color_value_archetype(detail::dummy_constructor) {}
    bool operator==(const color_value_archetype&) const { return true; }
    bool operator!=(const color_value_archetype&) const { return true; }
};
template <> struct color_traits< color_value_archetype >
{
    static color_value_archetype white()
    {
        return color_value_archetype(
            static_object< detail::dummy_constructor >::get());
    }
    static color_value_archetype gray()
    {
        return color_value_archetype(
            static_object< detail::dummy_constructor >::get());
    }
    static color_value_archetype black()
    {
        return color_value_archetype(
            static_object< detail::dummy_constructor >::get());
    }
};

template < typename T > class buffer_archetype
{
public:
    void push(const T&) {}
    void pop() {}
    T& top() { return static_object< T >::get(); }
    const T& top() const { return static_object< T >::get(); }
    bool empty() const { return true; }
};

} // namespace boost

#endif // BOOST_GRAPH_ARCHETYPES_HPP

/* graph_archetypes.hpp
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
*/