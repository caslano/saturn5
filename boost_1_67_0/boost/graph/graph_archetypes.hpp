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