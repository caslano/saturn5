//=======================================================================
// Copyright 1997-2001 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#ifndef BOOST_GRAPH_SGB_GRAPH_HPP
#define BOOST_GRAPH_SGB_GRAPH_HPP

#include <boost/config.hpp>
#include <boost/operators.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>

// Thanks to Andreas Scherer for numerous suggestions and fixes!

// This file adapts a Stanford GraphBase (SGB) Graph pointer into a
// VertexListGraph. Note that a graph adaptor class is not needed,
// SGB's Graph* is used as is. The VertexListGraph concept is fulfilled by
// defining the appropriate non-member functions for Graph*.
//
// The PROTOTYPES change file extensions to SGB must be applied so
// that the SGB functions have real prototypes which are necessary for
// the C++ compiler. To apply the PROTOTYPES extensions, before you do
// "make tests install" for SGB do "ln -s PROTOTYPES/* ." to the SGB
// root directory (or just copy all the files from the PROTOTYPES
// directory to the SGB root directory).
//
extern "C"
{
    // We include all global definitions for the general stuff
    // of The Stanford GraphBase and its various graph generator
    // functions by reading all SGB headerfiles as in section 2 of
    // the "test_sample" program.
#include <gb_graph.h> /* SGB data structures */
#include <gb_io.h> /* SGB input/output routines */
#include <gb_flip.h> /* random number generator */
#include <gb_dijk.h> /* routines for shortest paths */
#include <gb_basic.h> /* the basic graph operations */
#undef empty /* avoid name clash with C++ standard library */
    inline Graph* empty(long n) /* and provide workaround */
    {
        return board(n, 0L, 0L, 0L, 2L, 0L, 0L);
    }
#include <gb_books.h> /* graphs based on literature */
#include <gb_econ.h> /* graphs based on economic data */
#include <gb_games.h> /* graphs based on football scores */
#undef ap /* avoid name clash with BGL parameter */
    // ap ==> Vertex::u.I
#include <gb_gates.h> /* graphs based on logic circuits */
#undef val /* avoid name clash with g++ headerfile stl_tempbuf.h */
    // val ==> Vertex::x.I
#include <gb_lisa.h> /* graphs based on Mona Lisa */
#include <gb_miles.h> /* graphs based on mileage data */
#include <gb_plane.h> /* planar graphs */
#include <gb_raman.h> /* Ramanujan graphs */
#include <gb_rand.h> /* random graphs */
#include <gb_roget.h> /* graphs based on Roget's Thesaurus */
#include <gb_save.h> /* we save results in ASCII format */
#include <gb_words.h> /* five-letter-word graphs */
#undef weight /* avoid name clash with BGL parameter */
    // weight ==> Vertex::u.I
}

namespace boost
{
class sgb_edge;
}

class sgb_out_edge_iterator;
class sgb_adj_iterator;
class sgb_vertex_iterator;

namespace boost
{
typedef Graph* sgb_graph_ptr;
typedef const Graph* sgb_const_graph_ptr;

struct sgb_traversal_tag : public virtual vertex_list_graph_tag,
                           public virtual incidence_graph_tag,
                           public virtual adjacency_graph_tag
{
};

template <> struct graph_traits< sgb_graph_ptr >
{
    typedef Vertex* vertex_descriptor;
    typedef boost::sgb_edge edge_descriptor;
    typedef sgb_out_edge_iterator out_edge_iterator;
    typedef void in_edge_iterator;
    typedef sgb_adj_iterator adjacency_iterator;
    typedef sgb_vertex_iterator vertex_iterator;
    typedef void edge_iterator;
    typedef long vertices_size_type;
    typedef long edge_size_type;
    typedef long degree_size_type;
    typedef directed_tag directed_category;
    typedef sgb_traversal_tag traversal_category;
    typedef allow_parallel_edge_tag edge_parallel_category;
    /** Return a null descriptor */
    static vertex_descriptor null_vertex() { return NULL; }
};
template <> struct graph_traits< sgb_const_graph_ptr >
{
    typedef Vertex* vertex_descriptor;
    typedef boost::sgb_edge edge_descriptor;
    typedef sgb_out_edge_iterator out_edge_iterator;
    typedef void in_edge_iterator;
    typedef sgb_adj_iterator adjacency_iterator;
    typedef sgb_vertex_iterator vertex_iterator;
    typedef void edge_iterator;
    typedef long vertices_size_type;
    typedef long edge_size_type;
    typedef long degree_size_type;
    typedef directed_tag directed_category;
    typedef sgb_traversal_tag traversal_category;
    typedef allow_parallel_edge_tag edge_parallel_category;
    /** Return a null descriptor */
    static vertex_descriptor null_vertex() { return NULL; }
};
}

namespace boost
{

struct edge_length_t
{
    typedef edge_property_tag kind;
};

// We could just use Arc* as the edge descriptor type, but
// we want to add the source(e,g) function which requires
// that we carry along a pointer to the source vertex.
class sgb_edge
{
    typedef sgb_edge self;

public:
    sgb_edge() : _arc(0), _src(0) {}
    sgb_edge(Arc* a, Vertex* s) : _arc(a), _src(s) {}
    friend Vertex* source(self e, sgb_const_graph_ptr) { return e._src; }
    friend Vertex* target(self e, sgb_const_graph_ptr) { return e._arc->tip; }
    friend bool operator==(const self& a, const self& b)
    {
        return a._arc == b._arc;
    }
    friend bool operator!=(const self& a, const self& b)
    {
        return a._arc != b._arc;
    }
#if !defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)
    template < class Ref > friend class sgb_edge_length_map;
    template < class Tag, class Ref > friend class sgb_edge_util_map;
    friend long get(edge_length_t, const sgb_graph_ptr&, const sgb_edge& key);
    friend long get(
        edge_length_t, const sgb_const_graph_ptr&, const sgb_edge& key);
    friend void put(
        edge_length_t, sgb_graph_ptr&, const sgb_edge& key, long value);

protected:
#endif
    Arc* _arc;
    Vertex* _src;
};
} // namespace boost

class sgb_out_edge_iterator
: public boost::forward_iterator_helper< sgb_out_edge_iterator, boost::sgb_edge,
      std::ptrdiff_t, boost::sgb_edge*, boost::sgb_edge >
{
    typedef sgb_out_edge_iterator self;

public:
    sgb_out_edge_iterator() : _src(0), _arc(0) {}
    sgb_out_edge_iterator(Vertex* s, Arc* d) : _src(s), _arc(d) {}
    boost::sgb_edge operator*() { return boost::sgb_edge(_arc, _src); }
    self& operator++()
    {
        _arc = _arc->next;
        return *this;
    }
    friend bool operator==(const self& x, const self& y)
    {
        return x._arc == y._arc;
    }

protected:
    Vertex* _src;
    Arc* _arc;
};

class sgb_adj_iterator
: public boost::forward_iterator_helper< sgb_adj_iterator, Vertex*,
      std::ptrdiff_t, Vertex**, Vertex* >
{
    typedef sgb_adj_iterator self;

public:
    sgb_adj_iterator() : _arc(0) {}
    sgb_adj_iterator(Arc* d) : _arc(d) {}
    Vertex* operator*() { return _arc->tip; }
    self& operator++()
    {
        _arc = _arc->next;
        return *this;
    }
    friend bool operator==(const self& x, const self& y)
    {
        return x._arc == y._arc;
    }

protected:
    Arc* _arc;
};

// The reason we have this instead of just using Vertex* is that we
// want to use Vertex* as the vertex_descriptor instead of just
// Vertex, which avoids problems with boost passing vertex descriptors
// by value and how that interacts with the sgb_vertex_id_map.
class sgb_vertex_iterator
: public boost::forward_iterator_helper< sgb_vertex_iterator, Vertex*,
      std::ptrdiff_t, Vertex**, Vertex* >
{
    typedef sgb_vertex_iterator self;

public:
    sgb_vertex_iterator() : _v(0) {}
    sgb_vertex_iterator(Vertex* v) : _v(v) {}
    Vertex* operator*() { return _v; }
    self& operator++()
    {
        ++_v;
        return *this;
    }
    friend bool operator==(const self& x, const self& y)
    {
        return x._v == y._v;
    }

protected:
    Vertex* _v;
};

namespace boost
{

inline std::pair< sgb_vertex_iterator, sgb_vertex_iterator > vertices(
    sgb_const_graph_ptr g)
{
    return std::make_pair(sgb_vertex_iterator(g->vertices),
        sgb_vertex_iterator(g->vertices + g->n));
}

inline std::pair< sgb_out_edge_iterator, sgb_out_edge_iterator > out_edges(
    Vertex* u, sgb_const_graph_ptr)
{
    return std::make_pair(
        sgb_out_edge_iterator(u, u->arcs), sgb_out_edge_iterator(u, 0));
}

inline boost::graph_traits< sgb_graph_ptr >::degree_size_type out_degree(
    Vertex* u, sgb_const_graph_ptr g)
{
    boost::graph_traits< sgb_graph_ptr >::out_edge_iterator i, i_end;
    boost::tie(i, i_end) = out_edges(u, g);
    return std::distance(i, i_end);
}

// in_edges?

inline std::pair< sgb_adj_iterator, sgb_adj_iterator > adjacent_vertices(
    Vertex* u, sgb_const_graph_ptr)
{
    return std::make_pair(sgb_adj_iterator(u->arcs), sgb_adj_iterator(0));
}

inline long num_vertices(sgb_const_graph_ptr g) { return g->n; }
inline long num_edges(sgb_const_graph_ptr g) { return g->m; }

inline Vertex* vertex(long v, sgb_const_graph_ptr g) { return g->vertices + v; }

// Various Property Maps

// Vertex ID
class sgb_vertex_id_map
: public boost::put_get_helper< long, sgb_vertex_id_map >
{
public:
    typedef boost::readable_property_map_tag category;
    typedef long value_type;
    typedef long reference;
    typedef Vertex* key_type;
    sgb_vertex_id_map() : _g(0) {}
    sgb_vertex_id_map(sgb_graph_ptr g) : _g(g) {}
    long operator[](Vertex* v) const { return v - _g->vertices; }

protected:
    sgb_graph_ptr _g;
};
inline sgb_vertex_id_map get(vertex_index_t, sgb_graph_ptr g)
{
    return sgb_vertex_id_map(g);
}

// Vertex Name
class sgb_vertex_name_map
: public boost::put_get_helper< char*, sgb_vertex_name_map >
{
public:
    typedef boost::readable_property_map_tag category;
    typedef char* value_type;
    typedef char* reference;
    typedef Vertex* key_type;
    char* operator[](Vertex* v) const { return v->name; }
};
inline sgb_vertex_name_map get(vertex_name_t, sgb_graph_ptr)
{
    return sgb_vertex_name_map();
}

// Vertex Property Tags
#define SGB_PROPERTY_TAG(KIND, TAG)            \
    template < class T > struct TAG##_property \
    {                                          \
        typedef KIND##_property_tag kind;      \
        typedef T type;                        \
    };
SGB_PROPERTY_TAG(vertex, u)
SGB_PROPERTY_TAG(vertex, v)
SGB_PROPERTY_TAG(vertex, w)
SGB_PROPERTY_TAG(vertex, x)
SGB_PROPERTY_TAG(vertex, y)
SGB_PROPERTY_TAG(vertex, z)

// Edge Property Tags
SGB_PROPERTY_TAG(edge, a)
SGB_PROPERTY_TAG(edge, b)

// Various Utility Maps

// helpers
inline Vertex*& get_util(util& u, Vertex*) { return u.V; }
inline Arc*& get_util(util& u, Arc*) { return u.A; }
inline sgb_graph_ptr& get_util(util& u, sgb_graph_ptr) { return u.G; }
inline char*& get_util(util& u, char*) { return u.S; }
inline long& get_util(util& u, long) { return u.I; }

#define SGB_GET_UTIL_FIELD(KIND, X)                                           \
    template < class T > inline T& get_util_field(KIND* k, X##_property< T >) \
    {                                                                         \
        return get_util(k->X, T());                                           \
    }

SGB_GET_UTIL_FIELD(Vertex, u)
SGB_GET_UTIL_FIELD(Vertex, v)
SGB_GET_UTIL_FIELD(Vertex, w)
SGB_GET_UTIL_FIELD(Vertex, x)
SGB_GET_UTIL_FIELD(Vertex, y)
SGB_GET_UTIL_FIELD(Vertex, z)

SGB_GET_UTIL_FIELD(Arc, a)
SGB_GET_UTIL_FIELD(Arc, b)

// Vertex Utility Map
template < class Tag, class Ref >
class sgb_vertex_util_map
: public boost::put_get_helper< Ref, sgb_vertex_util_map< Tag, Ref > >
{
    Tag tag;

public:
    explicit sgb_vertex_util_map(Tag tag = Tag()) : tag(tag) {}
    typedef boost::lvalue_property_map_tag category;
    typedef typename Tag::type value_type;
    typedef Vertex* key_type;
    typedef Ref reference;
    reference operator[](Vertex* v) const { return get_util_field(v, tag); }
};

// Edge Utility Map
template < class Tag, class Ref >
class sgb_edge_util_map
: public boost::put_get_helper< Ref, sgb_edge_util_map< Tag, Ref > >
{
    Tag tag;

public:
    explicit sgb_edge_util_map(Tag tag = Tag()) : tag(tag) {}
    typedef boost::lvalue_property_map_tag category;
    typedef typename Tag::type value_type;
    typedef Vertex* key_type;
    typedef Ref reference;
    reference operator[](const sgb_edge& e) const
    {
        return get_util_field(e._arc, tag);
    }
};

template < class Tag >
inline sgb_vertex_util_map< Tag, const typename Tag::type& > get_property_map(
    Tag, const sgb_graph_ptr& g, vertex_property_tag)
{
    return sgb_vertex_util_map< Tag, const typename Tag::type& >();
}
template < class Tag >
inline sgb_vertex_util_map< Tag, typename Tag::type& > get_property_map(
    Tag, sgb_graph_ptr& g, vertex_property_tag)
{
    return sgb_vertex_util_map< Tag, typename Tag::type& >();
}

template < class Tag >
inline sgb_edge_util_map< Tag, const typename Tag::type& > get_property_map(
    Tag, const sgb_graph_ptr& g, edge_property_tag)
{
    return sgb_edge_util_map< Tag, const typename Tag::type& >();
}
template < class Tag >
inline sgb_edge_util_map< Tag, typename Tag::type& > get_property_map(
    Tag, sgb_graph_ptr& g, edge_property_tag)
{
    return sgb_edge_util_map< Tag, typename Tag::type& >();
}

// Edge Length Access
template < class Ref >
class sgb_edge_length_map
: public boost::put_get_helper< Ref, sgb_edge_length_map< Ref > >
{
public:
    typedef boost::lvalue_property_map_tag category;
    typedef long value_type;
    typedef sgb_edge key_type;
    typedef Ref reference;
    reference operator[](const sgb_edge& e) const { return e._arc->len; }
};

inline sgb_edge_length_map< const long& > get(
    edge_length_t, const sgb_graph_ptr&)
{
    return sgb_edge_length_map< const long& >();
}
inline sgb_edge_length_map< const long& > get(
    edge_length_t, const sgb_const_graph_ptr&)
{
    return sgb_edge_length_map< const long& >();
}
inline sgb_edge_length_map< long& > get(edge_length_t, sgb_graph_ptr&)
{
    return sgb_edge_length_map< long& >();
}
inline long get(edge_length_t, const sgb_graph_ptr&, const sgb_edge& key)
{
    return key._arc->len;
}
inline long get(edge_length_t, const sgb_const_graph_ptr&, const sgb_edge& key)
{
    return key._arc->len;
}
inline void put(edge_length_t, sgb_graph_ptr&, const sgb_edge& key, long value)
{
    key._arc->len = value;
}

// Property Map Traits Classes
template <> struct property_map< sgb_graph_ptr, edge_length_t >
{
    typedef sgb_edge_length_map< long& > type;
    typedef sgb_edge_length_map< const long& > const_type;
};
template <> struct property_map< sgb_graph_ptr, vertex_index_t >
{
    typedef sgb_vertex_id_map type;
    typedef sgb_vertex_id_map const_type;
};
template <> struct property_map< sgb_graph_ptr, vertex_name_t >
{
    typedef sgb_vertex_name_map type;
    typedef sgb_vertex_name_map const_type;
};

template <> struct property_map< sgb_const_graph_ptr, edge_length_t >
{
    typedef sgb_edge_length_map< const long& > const_type;
};
template <> struct property_map< sgb_const_graph_ptr, vertex_index_t >
{
    typedef sgb_vertex_id_map const_type;
};
template <> struct property_map< sgb_const_graph_ptr, vertex_name_t >
{
    typedef sgb_vertex_name_map const_type;
};

namespace detail
{
    template < class Kind, class PropertyTag > struct sgb_choose_property_map
    {
    };
    template < class PropertyTag >
    struct sgb_choose_property_map< vertex_property_tag, PropertyTag >
    {
        typedef typename PropertyTag::type value_type;
        typedef sgb_vertex_util_map< PropertyTag, value_type& > type;
        typedef sgb_vertex_util_map< PropertyTag, const value_type& >
            const_type;
    };
    template < class PropertyTag >
    struct sgb_choose_property_map< edge_property_tag, PropertyTag >
    {
        typedef typename PropertyTag::type value_type;
        typedef sgb_edge_util_map< PropertyTag, value_type& > type;
        typedef sgb_edge_util_map< PropertyTag, const value_type& > const_type;
    };
} // namespace detail
template < class PropertyTag > struct property_map< sgb_graph_ptr, PropertyTag >
{
    typedef typename property_kind< PropertyTag >::type Kind;
    typedef detail::sgb_choose_property_map< Kind, PropertyTag > Choice;
    typedef typename Choice::type type;
    typedef typename Choice::const_type const_type;
};
template < class PropertyTag >
struct property_map< sgb_const_graph_ptr, PropertyTag >
{
    typedef typename property_kind< PropertyTag >::type Kind;
    typedef detail::sgb_choose_property_map< Kind, PropertyTag > Choice;
    typedef typename Choice::const_type const_type;
};

#define SGB_UTIL_ACCESSOR(KIND, X)                                             \
    template < class T >                                                       \
    inline sgb_##KIND##_util_map< X##_property< T >, T& > get(                 \
        X##_property< T >, sgb_graph_ptr&)                                     \
    {                                                                          \
        return sgb_##KIND##_util_map< X##_property< T >, T& >();               \
    }                                                                          \
    template < class T >                                                       \
    inline sgb_##KIND##_util_map< X##_property< T >, const T& > get(           \
        X##_property< T >, const sgb_graph_ptr&)                               \
    {                                                                          \
        return sgb_##KIND##_util_map< X##_property< T >, const T& >();         \
    }                                                                          \
    template < class T >                                                       \
    inline sgb_##KIND##_util_map< X##_property< T >, const T& > get(           \
        X##_property< T >, const sgb_const_graph_ptr&)                         \
    {                                                                          \
        return sgb_##KIND##_util_map< X##_property< T >, const T& >();         \
    }                                                                          \
    template < class T, class Key >                                            \
    inline typename sgb_##KIND##_util_map< X##_property< T >,                  \
        const T& >::value_type                                                 \
    get(X##_property< T >, const sgb_graph_ptr&, const Key& key)               \
    {                                                                          \
        return sgb_##KIND##_util_map< X##_property< T >, const T& >()[key];    \
    }                                                                          \
    template < class T, class Key >                                            \
    inline typename sgb_##KIND##_util_map< X##_property< T >,                  \
        const T& >::value_type                                                 \
    get(X##_property< T >, const sgb_const_graph_ptr&, const Key& key)         \
    {                                                                          \
        return sgb_##KIND##_util_map< X##_property< T >, const T& >()[key];    \
    }                                                                          \
    template < class T, class Key, class Value >                               \
    inline void put(                                                           \
        X##_property< T >, sgb_graph_ptr&, const Key& key, const Value& value) \
    {                                                                          \
        sgb_##KIND##_util_map< X##_property< T >, T& >()[key] = value;         \
    }

SGB_UTIL_ACCESSOR(vertex, u)
SGB_UTIL_ACCESSOR(vertex, v)
SGB_UTIL_ACCESSOR(vertex, w)
SGB_UTIL_ACCESSOR(vertex, x)
SGB_UTIL_ACCESSOR(vertex, y)
SGB_UTIL_ACCESSOR(vertex, z)

SGB_UTIL_ACCESSOR(edge, a)
SGB_UTIL_ACCESSOR(edge, b)

} // namespace boost

#endif // BOOST_GRAPH_SGB_GRAPH_HPP

/* stanford_graph.hpp
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
*/