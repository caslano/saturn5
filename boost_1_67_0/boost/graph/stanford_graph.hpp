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