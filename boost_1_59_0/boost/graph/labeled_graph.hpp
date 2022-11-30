// Copyright (C) 2009 Andrew Sutton

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_LABELED_GRAPH_HPP
#define BOOST_GRAPH_LABELED_GRAPH_HPP

#include <boost/config.hpp>
#include <vector>
#include <map>

#include <boost/static_assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/unordered_map.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/pending/container_traits.hpp>
#include <boost/graph/graph_traits.hpp>

// This file implements a utility for creating mappings from arbitrary
// identifiers to the vertices of a graph.

namespace boost
{

// A type selector that denotes the use of some default value.
struct defaultS
{
};

/** @internal */
namespace graph_detail
{
    /** Returns true if the selector is the default selector. */
    template < typename Selector >
    struct is_default : mpl::bool_< is_same< Selector, defaultS >::value >
    {
    };

    /**
     * Choose the default map instance. If Label is an unsigned integral type
     * the we can use a vector to store the information.
     */
    template < typename Label, typename Vertex > struct choose_default_map
    {
        typedef typename mpl::if_< is_unsigned< Label >, std::vector< Vertex >,
            std::map< Label, Vertex > // TODO: Should use unordered_map?
            >::type type;
    };

    /**
     * @name Generate Label Map
     * These type generators are responsible for instantiating an associative
     * container for the the labeled graph. Note that the Selector must be
     * select a pair associative container or a vecS, which is only valid if
     * Label is an integral type.
     */
    //@{
    template < typename Selector, typename Label, typename Vertex >
    struct generate_label_map
    {
    };

    template < typename Label, typename Vertex >
    struct generate_label_map< vecS, Label, Vertex >
    {
        typedef std::vector< Vertex > type;
    };

    template < typename Label, typename Vertex >
    struct generate_label_map< mapS, Label, Vertex >
    {
        typedef std::map< Label, Vertex > type;
    };

    template < typename Label, typename Vertex >
    struct generate_label_map< multimapS, Label, Vertex >
    {
        typedef std::multimap< Label, Vertex > type;
    };

    template < typename Label, typename Vertex >
    struct generate_label_map< hash_mapS, Label, Vertex >
    {
        typedef boost::unordered_map< Label, Vertex > type;
    };

    template < typename Label, typename Vertex >
    struct generate_label_map< hash_multimapS, Label, Vertex >
    {
        typedef boost::unordered_multimap< Label, Vertex > type;
    };

    template < typename Selector, typename Label, typename Vertex >
    struct choose_custom_map
    {
        typedef
            typename generate_label_map< Selector, Label, Vertex >::type type;
    };
    //@}

    /**
     * Choose and instantiate an "associative" container. Note that this can
     * also choose vector.
     */
    template < typename Selector, typename Label, typename Vertex >
    struct choose_map
    {
        typedef typename mpl::eval_if< is_default< Selector >,
            choose_default_map< Label, Vertex >,
            choose_custom_map< Selector, Label, Vertex > >::type type;
    };

    /** @name Insert Labeled Vertex */
    //@{
    // Tag dispatch on random access containers (i.e., vectors). This function
    // basically requires a) that Container is vector<Label> and that Label
    // is an unsigned integral value. Note that this will resize the vector
    // to accommodate indices.
    template < typename Container, typename Graph, typename Label,
        typename Prop >
    std::pair< typename graph_traits< Graph >::vertex_descriptor, bool >
    insert_labeled_vertex(Container& c, Graph& g, Label const& l, Prop const& p,
        random_access_container_tag)
    {
        typedef typename graph_traits< Graph >::vertex_descriptor Vertex;

        // If the label is out of bounds, resize the vector to accommodate.
        // Resize by 2x the index so we don't cause quadratic insertions over
        // time.
        if (l >= c.size())
        {
            c.resize((l + 1) * 2);
        }
        Vertex v = add_vertex(p, g);
        c[l] = v;
        return std::make_pair(c[l], true);
    }

    // Tag dispatch on multi associative containers (i.e. multimaps).
    template < typename Container, typename Graph, typename Label,
        typename Prop >
    std::pair< typename graph_traits< Graph >::vertex_descriptor, bool >
    insert_labeled_vertex(Container& c, Graph& g, Label const& l, Prop const& p,
        multiple_associative_container_tag const&)
    {
        // Note that insertion always succeeds so we can add the vertex first
        // and then the mapping to the label.
        typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
        Vertex v = add_vertex(p, g);
        c.insert(std::make_pair(l, v));
        return std::make_pair(v, true);
    }

    // Tag dispatch on unique associative containers (i.e. maps).
    template < typename Container, typename Graph, typename Label,
        typename Prop >
    std::pair< typename graph_traits< Graph >::vertex_descriptor, bool >
    insert_labeled_vertex(Container& c, Graph& g, Label const& l, Prop const& p,
        unique_associative_container_tag)
    {
        // Here, we actually have to try the insertion first, and only add
        // the vertex if we get a new element.
        typedef typename graph_traits< Graph >::vertex_descriptor Vertex;
        typedef typename Container::iterator Iterator;
        std::pair< Iterator, bool > x = c.insert(std::make_pair(l, Vertex()));
        if (x.second)
        {
            x.first->second = add_vertex(g);
            put(boost::vertex_all, g, x.first->second, p);
        }
        return std::make_pair(x.first->second, x.second);
    }

    // Dispatcher
    template < typename Container, typename Graph, typename Label,
        typename Prop >
    std::pair< typename graph_traits< Graph >::vertex_descriptor, bool >
    insert_labeled_vertex(Container& c, Graph& g, Label const& l, Prop const& p)
    {
        return insert_labeled_vertex(c, g, l, p, container_category(c));
    }
    //@}

    /** @name Find Labeled Vertex */
    //@{
    // Tag dispatch for sequential maps (i.e., vectors).
    template < typename Container, typename Graph, typename Label >
    typename graph_traits< Graph >::vertex_descriptor find_labeled_vertex(
        Container const& c, Graph const&, Label const& l,
        random_access_container_tag)
    {
        return l < c.size() ? c[l] : graph_traits< Graph >::null_vertex();
    }

    // Tag dispatch for pair associative maps (more or less).
    template < typename Container, typename Graph, typename Label >
    typename graph_traits< Graph >::vertex_descriptor find_labeled_vertex(
        Container const& c, Graph const&, Label const& l,
        associative_container_tag)
    {
        typename Container::const_iterator i = c.find(l);
        return i != c.end() ? i->second : graph_traits< Graph >::null_vertex();
    }

    // Dispatcher
    template < typename Container, typename Graph, typename Label >
    typename graph_traits< Graph >::vertex_descriptor find_labeled_vertex(
        Container const& c, Graph const& g, Label const& l)
    {
        return find_labeled_vertex(c, g, l, container_category(c));
    }
    //@}

    /** @name Put Vertex Label */
    //@{
    // Tag dispatch on vectors.
    template < typename Container, typename Label, typename Graph,
        typename Vertex >
    bool put_vertex_label(Container& c, Graph const&, Label const& l, Vertex v,
        random_access_container_tag)
    {
        // If the element is already occupied, then we probably don't want to
        // overwrite it.
        if (c[l] == graph_traits< Graph >::null_vertex())
            return false;
        c[l] = v;
        return true;
    }

    // Attempt the insertion and return its result.
    template < typename Container, typename Label, typename Graph,
        typename Vertex >
    bool put_vertex_label(Container& c, Graph const&, Label const& l, Vertex v,
        unique_associative_container_tag)
    {
        return c.insert(std::make_pair(l, v)).second;
    }

    // Insert the pair and return true.
    template < typename Container, typename Label, typename Graph,
        typename Vertex >
    bool put_vertex_label(Container& c, Graph const&, Label const& l, Vertex v,
        multiple_associative_container_tag)
    {
        c.insert(std::make_pair(l, v));
        return true;
    }

    // Dispatcher
    template < typename Container, typename Label, typename Graph,
        typename Vertex >
    bool put_vertex_label(
        Container& c, Graph const& g, Label const& l, Vertex v)
    {
        return put_vertex_label(c, g, l, v, container_category(c));
    }
    //@}

} // namespace detail

struct labeled_graph_class_tag
{
};

/** @internal
 * This class is responsible for the deduction and declaration of type names
 * for the labeled_graph class template.
 */
template < typename Graph, typename Label, typename Selector >
struct labeled_graph_types
{
    typedef Graph graph_type;

    // Label and maps
    typedef Label label_type;
    typedef typename graph_detail::choose_map< Selector, Label,
        typename graph_traits< Graph >::vertex_descriptor >::type map_type;
};

/**
 * The labeled_graph class is a graph adaptor that maintains a mapping between
 * vertex labels and vertex descriptors.
 *
 * @todo This class is somewhat redundant for adjacency_list<*, vecS>  if
 * the intended label is an unsigned int (and perhaps some other cases), but
 * it does avoid some weird ambiguities (i.e. adding a vertex with a label that
 * does not match its target index).
 *
 * @todo This needs to be reconciled with the named_graph, but since there is
 * no documentation or examples, its not going to happen.
 */
template < typename Graph, typename Label, typename Selector = defaultS >
class labeled_graph : protected labeled_graph_types< Graph, Label, Selector >
{
    typedef labeled_graph_types< Graph, Label, Selector > Base;

public:
    typedef labeled_graph_class_tag graph_tag;

    typedef typename Base::graph_type graph_type;
    typedef typename graph_traits< graph_type >::vertex_descriptor
        vertex_descriptor;
    typedef
        typename graph_traits< graph_type >::edge_descriptor edge_descriptor;
    typedef typename graph_traits< graph_type >::directed_category
        directed_category;
    typedef typename graph_traits< graph_type >::edge_parallel_category
        edge_parallel_category;
    typedef typename graph_traits< graph_type >::traversal_category
        traversal_category;

    typedef typename graph_traits< graph_type >::out_edge_iterator
        out_edge_iterator;
    typedef
        typename graph_traits< graph_type >::in_edge_iterator in_edge_iterator;
    typedef typename graph_traits< graph_type >::adjacency_iterator
        adjacency_iterator;
    typedef
        typename graph_traits< graph_type >::degree_size_type degree_size_type;

    typedef
        typename graph_traits< graph_type >::vertex_iterator vertex_iterator;
    typedef typename graph_traits< graph_type >::vertices_size_type
        vertices_size_type;
    typedef typename graph_traits< graph_type >::edge_iterator edge_iterator;
    typedef
        typename graph_traits< graph_type >::edges_size_type edges_size_type;

    typedef typename graph_type::graph_property_type graph_property_type;
    typedef typename graph_type::graph_bundled graph_bundled;

    typedef typename graph_type::vertex_property_type vertex_property_type;
    typedef typename graph_type::vertex_bundled vertex_bundled;

    typedef typename graph_type::edge_property_type edge_property_type;
    typedef typename graph_type::edge_bundled edge_bundled;

    typedef typename Base::label_type label_type;
    typedef typename Base::map_type map_type;

public:
    labeled_graph(graph_property_type const& gp = graph_property_type())
    : _graph(gp), _map()
    {
    }

    labeled_graph(labeled_graph const& x) : _graph(x._graph), _map(x._map) {}

    // This constructor can only be used if map_type supports positional
    // range insertion (i.e. its a vector). This is the only case where we can
    // try to guess the intended labels for graph.
    labeled_graph(vertices_size_type n,
        graph_property_type const& gp = graph_property_type())
    : _graph(n, gp), _map()
    {
        std::pair< vertex_iterator, vertex_iterator > rng = vertices(_graph);
        _map.insert(_map.end(), rng.first, rng.second);
    }

    // Construct a graph over n vertices, each of which receives a label from
    // the range [l, l + n). Note that the graph is not directly constructed
    // over the n vertices, but added sequentially. This constructor is
    // necessarily slower than the underlying counterpart.
    template < typename LabelIter >
    labeled_graph(vertices_size_type n, LabelIter l,
        graph_property_type const& gp = graph_property_type())
    : _graph(gp)
    {
        while (n-- > 0)
            add_vertex(*l++);
    }

    // Construct the graph over n vertices each of which has a label in the
    // range [l, l + n) and a property in the range [p, p + n).
    template < typename LabelIter, typename PropIter >
    labeled_graph(vertices_size_type n, LabelIter l, PropIter p,
        graph_property_type const& gp = graph_property_type())
    : _graph(gp)
    {
        while (n-- > 0)
            add_vertex(*l++, *p++);
    }

    labeled_graph& operator=(labeled_graph const& x)
    {
        _graph = x._graph;
        _map = x._map;
        return *this;
    }

    /** @name Graph Accessors */
    //@{
    graph_type& graph() { return _graph; }
    graph_type const& graph() const { return _graph; }
    //@}

    /**
     * Create a new label for the given vertex, returning false, if the label
     * cannot be created.
     */
    bool label_vertex(vertex_descriptor v, Label const& l)
    {
        return graph_detail::put_vertex_label(_map, _graph, l, v);
    }

    /** @name Add Vertex
     * Add a vertex to the graph, returning the descriptor. If the vertices
     * are uniquely labeled and the label already exists within the graph,
     * then no vertex is added, and the returned descriptor refers to the
     * existing vertex. A vertex property can be given as a parameter, if
     * needed.
     */
    //@{
    vertex_descriptor add_vertex(Label const& l)
    {
        return graph_detail::insert_labeled_vertex(
            _map, _graph, l, vertex_property_type())
            .first;
    }

    vertex_descriptor add_vertex(Label const& l, vertex_property_type const& p)
    {
        return graph_detail::insert_labeled_vertex(_map, _graph, l, p).first;
    }
    //@}

    /** @name Insert Vertex
     * Insert a vertex into the graph, returning a pair containing the
     * descriptor of a vertex and a boolean value that describes whether or not
     * a new vertex was inserted. If vertices are not uniquely labeled, then
     * insertion will always succeed.
     */
    //@{
    std::pair< vertex_descriptor, bool > insert_vertex(Label const& l)
    {
        return graph_detail::insert_labeled_vertex(
            _map, _graph, l, vertex_property_type());
    }

    std::pair< vertex_descriptor, bool > insert_vertex(
        Label const& l, vertex_property_type const& p)
    {
        return graph_detail::insert_labeled_vertex(_map, _graph, l, p);
    }
    //@}

    /** Remove the vertex with the given label. */
    void remove_vertex(Label const& l)
    {
        return boost::remove_vertex(vertex(l), _graph);
    }

    /** Return a descriptor for the given label. */
    vertex_descriptor vertex(Label const& l) const
    {
        return graph_detail::find_labeled_vertex(_map, _graph, l);
    }

#ifndef BOOST_GRAPH_NO_BUNDLED_PROPERTIES
    /** @name Bundled Properties */
    //@{
    // Lookup the requested vertex and return the bundle.
    vertex_bundled& operator[](Label const& l) { return _graph[vertex(l)]; }

    vertex_bundled const& operator[](Label const& l) const
    {
        return _graph[vertex(l)];
    }

    // Delegate edge lookup to the underlying graph.
    edge_bundled& operator[](edge_descriptor e) { return _graph[e]; }

    edge_bundled const& operator[](edge_descriptor e) const
    {
        return _graph[e];
    }
    //@}
#endif

    /** Return a null descriptor */
    static vertex_descriptor null_vertex()
    {
        return graph_traits< graph_type >::null_vertex();
    }

private:
    graph_type _graph;
    map_type _map;
};

/**
 * The partial specialization over graph pointers allows the construction
 * of temporary labeled graph objects. In this case, the labels are destructed
 * when the wrapper goes out of scope.
 */
template < typename Graph, typename Label, typename Selector >
class labeled_graph< Graph*, Label, Selector >
: protected labeled_graph_types< Graph, Label, Selector >
{
    typedef labeled_graph_types< Graph, Label, Selector > Base;

public:
    typedef labeled_graph_class_tag graph_tag;

    typedef typename Base::graph_type graph_type;
    typedef typename graph_traits< graph_type >::vertex_descriptor
        vertex_descriptor;
    typedef
        typename graph_traits< graph_type >::edge_descriptor edge_descriptor;
    typedef typename graph_traits< graph_type >::directed_category
        directed_category;
    typedef typename graph_traits< graph_type >::edge_parallel_category
        edge_parallel_category;
    typedef typename graph_traits< graph_type >::traversal_category
        traversal_category;

    typedef typename graph_traits< graph_type >::out_edge_iterator
        out_edge_iterator;
    typedef
        typename graph_traits< graph_type >::in_edge_iterator in_edge_iterator;
    typedef typename graph_traits< graph_type >::adjacency_iterator
        adjacency_iterator;
    typedef
        typename graph_traits< graph_type >::degree_size_type degree_size_type;

    typedef
        typename graph_traits< graph_type >::vertex_iterator vertex_iterator;
    typedef typename graph_traits< graph_type >::vertices_size_type
        vertices_size_type;
    typedef typename graph_traits< graph_type >::edge_iterator edge_iterator;
    typedef
        typename graph_traits< graph_type >::edges_size_type edges_size_type;

    typedef typename graph_type::vertex_property_type vertex_property_type;
    typedef typename graph_type::edge_property_type edge_property_type;
    typedef typename graph_type::graph_property_type graph_property_type;
    typedef typename graph_type::vertex_bundled vertex_bundled;
    typedef typename graph_type::edge_bundled edge_bundled;

    typedef typename Base::label_type label_type;
    typedef typename Base::map_type map_type;

    labeled_graph(graph_type* g) : _graph(g) {}

    /** @name Graph Access */
    //@{
    graph_type& graph() { return *_graph; }
    graph_type const& graph() const { return *_graph; }
    //@}

    /**
     * Create a new label for the given vertex, returning false, if the label
     * cannot be created.
     */
    bool label_vertex(vertex_descriptor v, Label const& l)
    {
        return graph_detail::put_vertex_label(_map, *_graph, l, v);
    }

    /** @name Add Vertex */
    //@{
    vertex_descriptor add_vertex(Label const& l)
    {
        return graph_detail::insert_labeled_vertex(
            _map, *_graph, l, vertex_property_type())
            .first;
    }

    vertex_descriptor add_vertex(Label const& l, vertex_property_type const& p)
    {
        return graph_detail::insert_labeled_vertex(_map, *_graph, l, p).first;
    }

    std::pair< vertex_descriptor, bool > insert_vertex(Label const& l)
    {
        return graph_detail::insert_labeled_vertex(
            _map, *_graph, l, vertex_property_type());
    }
    //@}

    /** Try to insert a vertex with the given label. */
    std::pair< vertex_descriptor, bool > insert_vertex(
        Label const& l, vertex_property_type const& p)
    {
        return graph_detail::insert_labeled_vertex(_map, *_graph, l, p);
    }

    /** Remove the vertex with the given label. */
    void remove_vertex(Label const& l)
    {
        return boost::remove_vertex(vertex(l), *_graph);
    }

    /** Return a descriptor for the given label. */
    vertex_descriptor vertex(Label const& l) const
    {
        return graph_detail::find_labeled_vertex(_map, *_graph, l);
    }

#ifndef BOOST_GRAPH_NO_BUNDLED_PROPERTIES
    /** @name Bundled Properties */
    //@{
    // Lookup the requested vertex and return the bundle.
    vertex_bundled& operator[](Label const& l) { return (*_graph)[vertex(l)]; }

    vertex_bundled const& operator[](Label const& l) const
    {
        return (*_graph)[vertex(l)];
    }

    // Delegate edge lookup to the underlying graph.
    edge_bundled& operator[](edge_descriptor e) { return (*_graph)[e]; }

    edge_bundled const& operator[](edge_descriptor e) const
    {
        return (*_graph)[e];
    }
    //@}
#endif

    static vertex_descriptor null_vertex()
    {
        return graph_traits< graph_type >::null_vertex();
    }

private:
    graph_type* _graph;
    map_type _map;
};

#define LABELED_GRAPH_PARAMS typename G, typename L, typename S
#define LABELED_GRAPH labeled_graph< G, L, S >

/** @name Labeled Graph */
//@{
template < LABELED_GRAPH_PARAMS >
inline bool label_vertex(typename LABELED_GRAPH::vertex_descriptor v,
    typename LABELED_GRAPH::label_type const l, LABELED_GRAPH& g)
{
    return g.label_vertex(v, l);
}

template < LABELED_GRAPH_PARAMS >
inline typename LABELED_GRAPH::vertex_descriptor vertex_by_label(
    typename LABELED_GRAPH::label_type const l, LABELED_GRAPH& g)
{
    return g.vertex(l);
}
//@}

/** @name Graph */
//@{
template < LABELED_GRAPH_PARAMS >
inline std::pair< typename LABELED_GRAPH::edge_descriptor, bool > edge(
    typename LABELED_GRAPH::vertex_descriptor const& u,
    typename LABELED_GRAPH::vertex_descriptor const& v, LABELED_GRAPH const& g)
{
    return edge(u, v, g.graph());
}

// Labeled Extensions
template < LABELED_GRAPH_PARAMS >
inline std::pair< typename LABELED_GRAPH::edge_descriptor, bool > edge_by_label(
    typename LABELED_GRAPH::label_type const& u,
    typename LABELED_GRAPH::label_type const& v, LABELED_GRAPH const& g)
{
    return edge(g.vertex(u), g.vertex(v), g);
}
//@}

/** @name Incidence Graph */
//@{
template < LABELED_GRAPH_PARAMS >
inline std::pair< typename LABELED_GRAPH::out_edge_iterator,
    typename LABELED_GRAPH::out_edge_iterator >
out_edges(typename LABELED_GRAPH::vertex_descriptor v, LABELED_GRAPH const& g)
{
    return out_edges(v, g.graph());
}

template < LABELED_GRAPH_PARAMS >
inline typename LABELED_GRAPH::degree_size_type out_degree(
    typename LABELED_GRAPH::vertex_descriptor v, LABELED_GRAPH const& g)
{
    return out_degree(v, g.graph());
}

template < LABELED_GRAPH_PARAMS >
inline typename LABELED_GRAPH::vertex_descriptor source(
    typename LABELED_GRAPH::edge_descriptor e, LABELED_GRAPH const& g)
{
    return source(e, g.graph());
}

template < LABELED_GRAPH_PARAMS >
inline typename LABELED_GRAPH::vertex_descriptor target(
    typename LABELED_GRAPH::edge_descriptor e, LABELED_GRAPH const& g)
{
    return target(e, g.graph());
}
//@}

/** @name Bidirectional Graph */
//@{
template < LABELED_GRAPH_PARAMS >
inline std::pair< typename LABELED_GRAPH::in_edge_iterator,
    typename LABELED_GRAPH::in_edge_iterator >
in_edges(typename LABELED_GRAPH::vertex_descriptor v, LABELED_GRAPH const& g)
{
    return in_edges(v, g.graph());
}

template < LABELED_GRAPH_PARAMS >
inline typename LABELED_GRAPH::degree_size_type in_degree(
    typename LABELED_GRAPH::vertex_descriptor v, LABELED_GRAPH const& g)
{
    return in_degree(v, g.graph());
}

template < LABELED_GRAPH_PARAMS >
inline typename LABELED_GRAPH::degree_size_type degree(
    typename LABELED_GRAPH::vertex_descriptor v, LABELED_GRAPH const& g)
{
    return degree(v, g.graph());
}
//@}

/** @name Adjacency Graph */
//@{
template < LABELED_GRAPH_PARAMS >
inline std::pair< typename LABELED_GRAPH::adjacency_iterator,
    typename LABELED_GRAPH::adjacency_iterator >
adjacenct_vertices(
    typename LABELED_GRAPH::vertex_descriptor v, LABELED_GRAPH const& g)
{
    return adjacent_vertices(v, g.graph());
}
//@}

/** @name VertexListGraph */
//@{
template < LABELED_GRAPH_PARAMS >
inline std::pair< typename LABELED_GRAPH::vertex_iterator,
    typename LABELED_GRAPH::vertex_iterator >
vertices(LABELED_GRAPH const& g)
{
    return vertices(g.graph());
}

template < LABELED_GRAPH_PARAMS >
inline typename LABELED_GRAPH::vertices_size_type num_vertices(
    LABELED_GRAPH const& g)
{
    return num_vertices(g.graph());
}
//@}

/** @name EdgeListGraph */
//@{
template < LABELED_GRAPH_PARAMS >
inline std::pair< typename LABELED_GRAPH::edge_iterator,
    typename LABELED_GRAPH::edge_iterator >
edges(LABELED_GRAPH const& g)
{
    return edges(g.graph());
}

template < LABELED_GRAPH_PARAMS >
inline typename LABELED_GRAPH::edges_size_type num_edges(LABELED_GRAPH const& g)
{
    return num_edges(g.graph());
}
//@}

/** @internal @name Property Lookup */
//@{
namespace graph_detail
{
    struct labeled_graph_vertex_property_selector
    {
        template < class LabeledGraph, class Property, class Tag > struct bind_
        {
            typedef typename LabeledGraph::graph_type Graph;
            typedef property_map< Graph, Tag > PropertyMap;
            typedef typename PropertyMap::type type;
            typedef typename PropertyMap::const_type const_type;
        };
    };

    struct labeled_graph_edge_property_selector
    {
        template < class LabeledGraph, class Property, class Tag > struct bind_
        {
            typedef typename LabeledGraph::graph_type Graph;
            typedef property_map< Graph, Tag > PropertyMap;
            typedef typename PropertyMap::type type;
            typedef typename PropertyMap::const_type const_type;
        };
    };
}

template <> struct vertex_property_selector< labeled_graph_class_tag >
{
    typedef graph_detail::labeled_graph_vertex_property_selector type;
};

template <> struct edge_property_selector< labeled_graph_class_tag >
{
    typedef graph_detail::labeled_graph_edge_property_selector type;
};
//@}

/** @name Property Graph */
//@{
template < LABELED_GRAPH_PARAMS, typename Prop >
inline typename property_map< LABELED_GRAPH, Prop >::type get(
    Prop p, LABELED_GRAPH& g)
{
    return get(p, g.graph());
}

template < LABELED_GRAPH_PARAMS, typename Prop >
inline typename property_map< LABELED_GRAPH, Prop >::const_type get(
    Prop p, LABELED_GRAPH const& g)
{
    return get(p, g.graph());
}

template < LABELED_GRAPH_PARAMS, typename Prop, typename Key >
inline typename property_traits< typename property_map<
    typename LABELED_GRAPH::graph_type, Prop >::const_type >::value_type
get(Prop p, LABELED_GRAPH const& g, const Key& k)
{
    return get(p, g.graph(), k);
}

template < LABELED_GRAPH_PARAMS, typename Prop, typename Key, typename Value >
inline void put(Prop p, LABELED_GRAPH& g, Key const& k, Value const& v)
{
    put(p, g.graph(), k, v);
}
//@}

/** @name Mutable Graph */
//@{
template < LABELED_GRAPH_PARAMS >
inline std::pair< typename LABELED_GRAPH::edge_descriptor, bool > add_edge(
    typename LABELED_GRAPH::vertex_descriptor const& u,
    typename LABELED_GRAPH::vertex_descriptor const& v, LABELED_GRAPH& g)
{
    return add_edge(u, v, g.graph());
}

template < LABELED_GRAPH_PARAMS >
inline std::pair< typename LABELED_GRAPH::edge_descriptor, bool > add_edge(
    typename LABELED_GRAPH::vertex_descriptor const& u,
    typename LABELED_GRAPH::vertex_descriptor const& v,
    typename LABELED_GRAPH::edge_property_type const& p, LABELED_GRAPH& g)
{
    return add_edge(u, v, p, g.graph());
}

template < LABELED_GRAPH_PARAMS >
inline void clear_vertex(
    typename LABELED_GRAPH::vertex_descriptor v, LABELED_GRAPH& g)
{
    return clear_vertex(v, g.graph());
}

template < LABELED_GRAPH_PARAMS >
inline void remove_edge(
    typename LABELED_GRAPH::edge_descriptor e, LABELED_GRAPH& g)
{
    return remove_edge(e, g.graph());
}

template < LABELED_GRAPH_PARAMS >
inline void remove_edge(typename LABELED_GRAPH::vertex_descriptor u,
    typename LABELED_GRAPH::vertex_descriptor v, LABELED_GRAPH& g)
{
    return remove_edge(u, v, g.graph());
}

// Labeled extensions
template < LABELED_GRAPH_PARAMS >
inline std::pair< typename LABELED_GRAPH::edge_descriptor, bool >
add_edge_by_label(typename LABELED_GRAPH::label_type const& u,
    typename LABELED_GRAPH::label_type const& v, LABELED_GRAPH& g)
{
    return add_edge(g.vertex(u), g.vertex(v), g);
}

template < LABELED_GRAPH_PARAMS >
inline std::pair< typename LABELED_GRAPH::edge_descriptor, bool >
add_edge_by_label(typename LABELED_GRAPH::label_type const& u,
    typename LABELED_GRAPH::label_type const& v,
    typename LABELED_GRAPH::edge_property_type const& p, LABELED_GRAPH& g)
{
    return add_edge(g.vertex(u), g.vertex(v), p, g);
}

template < LABELED_GRAPH_PARAMS >
inline void clear_vertex_by_label(
    typename LABELED_GRAPH::label_type const& l, LABELED_GRAPH& g)
{
    clear_vertex(g.vertex(l), g.graph());
}

template < LABELED_GRAPH_PARAMS >
inline void remove_edge_by_label(typename LABELED_GRAPH::label_type const& u,
    typename LABELED_GRAPH::label_type const& v, LABELED_GRAPH& g)
{
    remove_edge(g.vertex(u), g.vertex(v), g.graph());
}
//@}

/** @name Labeled Mutable Graph
 * The labeled mutable graph hides the add_ and remove_ vertex functions from
 * the mutable graph concept. Note that the remove_vertex is hidden because
 * removing the vertex without its key could leave a dangling reference in
 * the map.
 */
//@{
template < LABELED_GRAPH_PARAMS >
inline typename LABELED_GRAPH::vertex_descriptor add_vertex(
    typename LABELED_GRAPH::label_type const& l, LABELED_GRAPH& g)
{
    return g.add_vertex(l);
}

// MutableLabeledPropertyGraph::add_vertex(l, vp, g)
template < LABELED_GRAPH_PARAMS >
inline typename LABELED_GRAPH::vertex_descriptor add_vertex(
    typename LABELED_GRAPH::label_type const& l,
    typename LABELED_GRAPH::vertex_property_type const& p, LABELED_GRAPH& g)
{
    return g.add_vertex(l, p);
}

template < LABELED_GRAPH_PARAMS >
inline void remove_vertex(
    typename LABELED_GRAPH::label_type const& l, LABELED_GRAPH& g)
{
    g.remove_vertex(l);
}
//@}

#undef LABELED_GRAPH_PARAMS
#undef LABELED_GRAPH

} // namespace boost

// Pull the labeled graph traits
#include <boost/graph/detail/labeled_graph_traits.hpp>

#endif // BOOST_GRAPH_LABELED_GRAPH_HPP

/* labeled_graph.hpp
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
*/