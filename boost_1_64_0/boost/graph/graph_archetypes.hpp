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
LksHr3BP2+tQJpH427kGS9BDmKoTXb/L0cuDfwV/gG5p443L6aWQLppAr7INeqSGOulXr9Fp8c9gX/QRnBvf4h8SGL9SxNVtF713leJS+73ZYb0ikbbRFnezaZJTRJIkS0mPVu7akDpsjcBrBU1oGa+MZAcd+Dz6FWLhs6DYbW2Df3Zy+fqzJg2ex36s3ah+EQ7OB2dsm12B+IZRLnBbHwXFatKDc17bBIXj8Egcd+1qOsiJp7IZpmLC8oYI1gawuI6Q2rwTajjjwp7gyYLp+sn3uL44f9Or4qo9PuD/7RrAHW+Vt0L8HvOdiUiIzgIUF4ogduU6+6r6pkyY6Pe3HVF+/4A+sfO7Q9aGvT6UC+BKWXy44hnzcX7h0u4n9E12YqnW3PtwtDOvKNBaqqrsiVHJmDyhb24U12TAWpaL9pWulw1NwNdQfcHQWh+ky4ax5Vt+Kj1qpDmmJqhsukTHfWkxTBRVWfjt1wEo3LAr0VfR4lU28jbArR61/QX0+rt0fW6hMHb8RM2R9s7/MyXU0eHJJIyGejkz1a1MIl0eirn2XoHGLN5KJlbEc29zCoYA9IJTaBN35Z4DnB28lkCMt+qfnMOSdG/sKWrM8f8x5mJWlVSmWj36C+lFlLiarjUzE/pwMnwHo7l2fnkaPY+n+4sa3ulRVjV5xPyiXCiVD/sSty+I3yAz4WuWsS25QvNXCnO4RqZrshynr3pQYHY7G+2x4Cqvu06KEhSq0P4/+vH5LiQ+SjlSwT/kZBfkjZPtSy3c0VgChNXUwsHTbfvrDxXndvxC31V6b05W6IqRWYnD4xxdL2OzmmcieoccL1fvIjO6F/ND9NTLzHzW3hXzescEXgcB8OpsfF67OnzpFZPRDgTKhRz4PVqKSnCChbelAtmuokYVzNdjhDCY7vt0wfHn8JgQw3Qc0VjPazLiw1z+lUMiBYdbkubbOM5mb+B03kpM9zFSRbdnujqcJJtZcn3l4JCzZqBurqOVSYW+nv1WEzkKSsmtnY5lZ7YiiM3SkcCAvTwHtQp93fspab+9e7Uh7NsogtZJN2QXwalS9JsUvXZWe/7M+Wux2DdXvgo8yQmDPtX+qmlSvvLMMSlwh2/SKJXcrXuwedPntn2XThO/WFwGTUOzgrsmsqhxmhhosW3rF/s2BOssrq4Wf+4uj6Xwy5vYiPTityMTK/mIPAWDPO2AqcFjnJcMAVRjwlOWUmudqRPE4RsG46URNbgzLqYdXTTShdztvr2mz19JCwGl5lYK8TJyT7UvbtEm0Y82DDaJ5SIkt+PgTLA/07SrwUmLVxkuYsakpWB/+1Ac4DKoETwhZN0BqTcl2CQ9lVnLwvOnfcKivjl/+V450vBdleNO22PKTHF19AybhFP+rgeBD9dROZmCC8nFDc9M/ifIJ+Zlr8jagI8I+YRF6ZsHlkPEe6iUGXkJBAhz98+2JMTvuLR8aY6fpfopnqMNgPTA27YH5VremLBQNfWP+H0WRR9V6NzLj4V23XSSd6fl4JtZI5TuX3pO/VOJIu55bcDYu31j6STw+VXQ8gz7Illbr7vcWOuug5zYY/Kw4t8D19uddnwyGimB9r8EcMu/tWG8DmTlm84eRhmvY/QnjQlikgz1ilBN4c9tAV3cOroIZVHD5buSgaDNZpUMPZzJz6Ws/XbwEZzH+BCZKPSEAgYGo9eTQ1gbIX3mO0Ufb6kjrRcKgnBDPbZc0n4JCrvgc1xd4ZYFN7aoj005NW7Ww70HEl1y6BHlwY81hO9ysqLgK8UMci8GYsmay6syEisf7JCXTS0DHAwdc14dlmy9twX62I6R86oakLRB+3Cmujwx1iMoUc3zy/Hn64T5vdZnk8w=
*/