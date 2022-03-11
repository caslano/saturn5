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