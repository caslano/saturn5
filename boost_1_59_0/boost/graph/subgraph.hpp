//=======================================================================
// Copyright 2001 University of Notre Dame.
// Authors: Jeremy G. Siek and Lie-Quan Lee
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_SUBGRAPH_HPP
#define BOOST_SUBGRAPH_HPP

// UNDER CONSTRUCTION

#include <boost/config.hpp>
#include <list>
#include <vector>
#include <map>
#include <boost/assert.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_mutability_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/iterator/indirect_iterator.hpp>

#include <boost/static_assert.hpp>
#include <boost/assert.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>

namespace boost
{

struct subgraph_tag
{
};

/** @name Property Lookup
 * The local_property and global_property functions are used to create
 * structures that determine the lookup strategy for properties in subgraphs.
 * Note that the nested kind member is used to help interoperate with actual
 * Property types.
 */
//@{
template < typename T > struct local_property
{
    typedef T kind;
    local_property(T x) : value(x) {}
    T value;
};

template < typename T > inline local_property< T > local(T x)
{
    return local_property< T >(x);
}

template < typename T > struct global_property
{
    typedef T kind;
    global_property(T x) : value(x) {}
    T value;
};

template < typename T > inline global_property< T > global(T x)
{
    return global_property< T >(x);
}
//@}

// Invariants of an induced subgraph:
//   - If vertex u is in subgraph g, then u must be in g.parent().
//   - If edge e is in subgraph g, then e must be in g.parent().
//   - If edge e=(u,v) is in the root graph, then edge e
//     is also in any subgraph that contains both vertex u and v.

// The Graph template parameter must have a vertex_index and edge_index
// internal property. It is assumed that the vertex indices are assigned
// automatically by the graph during a call to add_vertex(). It is not
// assumed that the edge vertices are assigned automatically, they are
// explicitly assigned here.

template < typename Graph > class subgraph
{
    typedef graph_traits< Graph > Traits;
    typedef std::list< subgraph< Graph >* > ChildrenList;

public:
    // Graph requirements
    typedef typename Traits::vertex_descriptor vertex_descriptor;
    typedef typename Traits::edge_descriptor edge_descriptor;
    typedef typename Traits::directed_category directed_category;
    typedef typename Traits::edge_parallel_category edge_parallel_category;
    typedef typename Traits::traversal_category traversal_category;

    // IncidenceGraph requirements
    typedef typename Traits::out_edge_iterator out_edge_iterator;
    typedef typename Traits::degree_size_type degree_size_type;

    // AdjacencyGraph requirements
    typedef typename Traits::adjacency_iterator adjacency_iterator;

    // VertexListGraph requirements
    typedef typename Traits::vertex_iterator vertex_iterator;
    typedef typename Traits::vertices_size_type vertices_size_type;

    // EdgeListGraph requirements
    typedef typename Traits::edge_iterator edge_iterator;
    typedef typename Traits::edges_size_type edges_size_type;

    typedef typename Traits::in_edge_iterator in_edge_iterator;

    typedef typename edge_property_type< Graph >::type edge_property_type;
    typedef typename vertex_property_type< Graph >::type vertex_property_type;
    typedef subgraph_tag graph_tag;
    typedef Graph graph_type;
    typedef typename graph_property_type< Graph >::type graph_property_type;

    // Create the main graph, the root of the subgraph tree
    subgraph() : m_parent(0), m_edge_counter(0) {}

    subgraph(const graph_property_type& p)
    : m_graph(p), m_parent(0), m_edge_counter(0)
    {
    }

    subgraph(vertices_size_type n,
        const graph_property_type& p = graph_property_type())
    : m_graph(n, p), m_parent(0), m_edge_counter(0), m_global_vertex(n)
    {
        typename Graph::vertex_iterator v, v_end;
        vertices_size_type i = 0;
        for (boost::tie(v, v_end) = vertices(m_graph); v != v_end; ++v)
            m_global_vertex[i++] = *v;
    }

    // copy constructor
    subgraph(const subgraph& x) : m_parent(x.m_parent), m_edge_counter(0)
    {
        if (x.is_root())
        {
            m_graph = x.m_graph;
            m_edge_counter = x.m_edge_counter;
            m_global_vertex = x.m_global_vertex;
            m_global_edge = x.m_global_edge;
        }
        else
        {
            get_property(*this) = get_property(x);
            typename subgraph< Graph >::vertex_iterator vi, vi_end;
            boost::tie(vi, vi_end) = vertices(x);
            for (; vi != vi_end; ++vi)
            {
                add_vertex(x.local_to_global(*vi), *this);
            }
        }
        // Do a deep copy (recursive).
        // Only the root graph is copied, the subgraphs contain
        // only references to the global vertices they own.
        typename subgraph< Graph >::children_iterator i, i_end;
        boost::tie(i, i_end) = x.children();
        for (; i != i_end; ++i)
        {
            m_children.push_back(new subgraph< Graph >(*i));
            m_children.back()->m_parent = this;
        }
    }

    ~subgraph()
    {
        for (typename ChildrenList::iterator i = m_children.begin();
             i != m_children.end(); ++i)
        {
            delete *i;
        }
    }

    // Return a null vertex descriptor for the graph.
    static vertex_descriptor null_vertex() { return Traits::null_vertex(); }

    // Create a subgraph
    subgraph< Graph >& create_subgraph()
    {
        m_children.push_back(new subgraph< Graph >());
        m_children.back()->m_parent = this;
        return *m_children.back();
    }

    // Create a subgraph with the specified vertex set.
    template < typename VertexIterator >
    subgraph< Graph >& create_subgraph(
        VertexIterator first, VertexIterator last)
    {
        m_children.push_back(new subgraph< Graph >());
        m_children.back()->m_parent = this;
        for (; first != last; ++first)
        {
            add_vertex(*first, *m_children.back());
        }
        return *m_children.back();
    }

    // local <-> global descriptor conversion functions
    vertex_descriptor local_to_global(vertex_descriptor u_local) const
    {
        return is_root() ? u_local : m_global_vertex[u_local];
    }

    vertex_descriptor global_to_local(vertex_descriptor u_global) const
    {
        vertex_descriptor u_local;
        bool in_subgraph;
        if (is_root())
            return u_global;
        boost::tie(u_local, in_subgraph) = this->find_vertex(u_global);
        BOOST_ASSERT(in_subgraph == true);
        return u_local;
    }

    edge_descriptor local_to_global(edge_descriptor e_local) const
    {
        return is_root()
            ? e_local
            : m_global_edge[get(get(edge_index, m_graph), e_local)];
    }

    edge_descriptor global_to_local(edge_descriptor e_global) const
    {
        return is_root() ? e_global
                         : (*m_local_edge.find(
                                get(get(edge_index, root().m_graph), e_global)))
                               .second;
    }

    // Is vertex u (of the root graph) contained in this subgraph?
    // If so, return the matching local vertex.
    std::pair< vertex_descriptor, bool > find_vertex(
        vertex_descriptor u_global) const
    {
        if (is_root())
            return std::make_pair(u_global, true);
        typename LocalVertexMap::const_iterator i
            = m_local_vertex.find(u_global);
        bool valid = i != m_local_vertex.end();
        return std::make_pair((valid ? (*i).second : null_vertex()), valid);
    }

    // Is edge e (of the root graph) contained in this subgraph?
    // If so, return the matching local edge.
    std::pair< edge_descriptor, bool > find_edge(edge_descriptor e_global) const
    {
        if (is_root())
            return std::make_pair(e_global, true);
        typename LocalEdgeMap::const_iterator i
            = m_local_edge.find(get(get(edge_index, root().m_graph), e_global));
        bool valid = i != m_local_edge.end();
        return std::make_pair((valid ? (*i).second : edge_descriptor()), valid);
    }

    // Return the parent graph.
    subgraph& parent() { return *m_parent; }
    const subgraph& parent() const { return *m_parent; }

    // Return true if this is the root subgraph
    bool is_root() const { return m_parent == 0; }

    // Return the root graph of the subgraph tree.
    subgraph& root() { return is_root() ? *this : m_parent->root(); }

    const subgraph& root() const
    {
        return is_root() ? *this : m_parent->root();
    }

    // Return the children subgraphs of this graph/subgraph.
    // Use a list of pointers because the VC++ std::list doesn't like
    // storing incomplete type.
    typedef indirect_iterator< typename ChildrenList::const_iterator,
        subgraph< Graph >, std::bidirectional_iterator_tag >
        children_iterator;

    typedef indirect_iterator< typename ChildrenList::const_iterator,
        subgraph< Graph > const, std::bidirectional_iterator_tag >
        const_children_iterator;

    std::pair< const_children_iterator, const_children_iterator >
    children() const
    {
        return std::make_pair(const_children_iterator(m_children.begin()),
            const_children_iterator(m_children.end()));
    }

    std::pair< children_iterator, children_iterator > children()
    {
        return std::make_pair(children_iterator(m_children.begin()),
            children_iterator(m_children.end()));
    }

    std::size_t num_children() const { return m_children.size(); }

#ifndef BOOST_GRAPH_NO_BUNDLED_PROPERTIES
    // Defualt property access delegates the lookup to global properties.
    template < typename Descriptor >
    typename graph::detail::bundled_result< Graph, Descriptor >::type&
    operator[](Descriptor x)
    {
        return is_root() ? m_graph[x] : root().m_graph[local_to_global(x)];
    }

    template < typename Descriptor >
    typename graph::detail::bundled_result< Graph, Descriptor >::type const&
    operator[](Descriptor x) const
    {
        return is_root() ? m_graph[x] : root().m_graph[local_to_global(x)];
    }

    // Local property access returns the local property of the given descripor.
    template < typename Descriptor >
    typename graph::detail::bundled_result< Graph, Descriptor >::type&
    operator[](local_property< Descriptor > x)
    {
        return m_graph[x.value];
    }

    template < typename Descriptor >
    typename graph::detail::bundled_result< Graph, Descriptor >::type const&
    operator[](local_property< Descriptor > x) const
    {
        return m_graph[x.value];
    }

    // Global property access returns the global property associated with the
    // given descriptor. This is an alias for the default bundled property
    // access operations.
    template < typename Descriptor >
    typename graph::detail::bundled_result< Graph, Descriptor >::type&
    operator[](global_property< Descriptor > x)
    {
        return (*this)[x.value];
    }

    template < typename Descriptor >
    typename graph::detail::bundled_result< Graph, Descriptor >::type const&
    operator[](global_property< Descriptor > x) const
    {
        return (*this)[x.value];
    }

#endif // BOOST_GRAPH_NO_BUNDLED_PROPERTIES

    //  private:
    typedef typename property_map< Graph, edge_index_t >::type EdgeIndexMap;
    typedef
        typename property_traits< EdgeIndexMap >::value_type edge_index_type;
    BOOST_STATIC_ASSERT((!is_same< edge_index_type,
                         boost::detail::error_property_not_found >::value));

private:
    typedef std::vector< vertex_descriptor > GlobalVertexList;
    typedef std::vector< edge_descriptor > GlobalEdgeList;
    typedef std::map< vertex_descriptor, vertex_descriptor > LocalVertexMap;
    typedef std::map< edge_index_type, edge_descriptor > LocalEdgeMap;
    // TODO: Should the LocalVertexMap be: map<index_type, descriptor>?
    // TODO: Can we relax the indexing requirement if both descriptors are
    // LessThanComparable?
    // TODO: Should we really be using unorderd_map for improved lookup times?

public: // Probably shouldn't be public....
    Graph m_graph;
    subgraph< Graph >* m_parent;
    edge_index_type m_edge_counter; // for generating unique edge indices
    ChildrenList m_children;
    GlobalVertexList m_global_vertex; // local -> global
    LocalVertexMap m_local_vertex; // global -> local
    GlobalEdgeList m_global_edge; // local -> global
    LocalEdgeMap m_local_edge; // global -> local

    edge_descriptor local_add_edge(vertex_descriptor u_local,
        vertex_descriptor v_local, edge_descriptor e_global)
    {
        edge_descriptor e_local;
        bool inserted;
        boost::tie(e_local, inserted) = add_edge(u_local, v_local, m_graph);
        put(edge_index, m_graph, e_local, m_edge_counter++);
        m_global_edge.push_back(e_global);
        m_local_edge[get(get(edge_index, this->root()), e_global)] = e_local;
        return e_local;
    }
};

template < typename Graph >
struct vertex_bundle_type< subgraph< Graph > > : vertex_bundle_type< Graph >
{
};

template < typename Graph >
struct edge_bundle_type< subgraph< Graph > > : edge_bundle_type< Graph >
{
};

template < typename Graph >
struct graph_bundle_type< subgraph< Graph > > : graph_bundle_type< Graph >
{
};

//===========================================================================
// Functions special to the Subgraph Class

template < typename G >
typename subgraph< G >::vertex_descriptor add_vertex(
    typename subgraph< G >::vertex_descriptor u_global, subgraph< G >& g)
{
    BOOST_ASSERT(!g.is_root());
    typename subgraph< G >::vertex_descriptor u_local;
    bool exists_local;
    boost::tie(u_local, exists_local) = g.find_vertex(u_global);

    if (!exists_local)
    {
        typename subgraph< G >::vertex_descriptor v_global;
        typename subgraph< G >::edge_descriptor e_global;
        // call recursion for parent subgraph
        if (!g.parent().is_root())
            add_vertex(u_global, g.parent());

        u_local = add_vertex(g.m_graph);
        g.m_global_vertex.push_back(u_global);
        g.m_local_vertex[u_global] = u_local;

        subgraph< G >& r = g.root();

        // remember edge global and local maps
        {
            typename subgraph< G >::out_edge_iterator ei, ei_end;
            for (boost::tie(ei, ei_end) = out_edges(u_global, r); ei != ei_end;
                 ++ei)
            {
                e_global = *ei;
                v_global = target(e_global, r);
                if (g.find_vertex(v_global).second == true)
                    g.local_add_edge(
                        u_local, g.global_to_local(v_global), e_global);
            }
        }
        if (is_directed(g))
        { // not necessary for undirected graph
            typename subgraph< G >::vertex_iterator vi, vi_end;
            typename subgraph< G >::out_edge_iterator ei, ei_end;
            for (boost::tie(vi, vi_end) = vertices(r); vi != vi_end; ++vi)
            {
                v_global = *vi;
                if (v_global == u_global)
                    continue; // don't insert self loops twice!
                if (!g.find_vertex(v_global).second)
                    continue; // not a subgraph vertex => try next one
                for (boost::tie(ei, ei_end) = out_edges(*vi, r); ei != ei_end;
                     ++ei)
                {
                    e_global = *ei;
                    if (target(e_global, r) == u_global)
                    {
                        g.local_add_edge(
                            g.global_to_local(v_global), u_local, e_global);
                    }
                }
            }
        }
    }
    return u_local;
}

// NOTE: Descriptors are local unless otherwise noted.

//===========================================================================
// Functions required by the IncidenceGraph concept

template < typename G >
std::pair< typename graph_traits< G >::out_edge_iterator,
    typename graph_traits< G >::out_edge_iterator >
out_edges(
    typename graph_traits< G >::vertex_descriptor v, const subgraph< G >& g)
{
    return out_edges(v, g.m_graph);
}

template < typename G >
typename graph_traits< G >::degree_size_type out_degree(
    typename graph_traits< G >::vertex_descriptor v, const subgraph< G >& g)
{
    return out_degree(v, g.m_graph);
}

template < typename G >
typename graph_traits< G >::vertex_descriptor source(
    typename graph_traits< G >::edge_descriptor e, const subgraph< G >& g)
{
    return source(e, g.m_graph);
}

template < typename G >
typename graph_traits< G >::vertex_descriptor target(
    typename graph_traits< G >::edge_descriptor e, const subgraph< G >& g)
{
    return target(e, g.m_graph);
}

//===========================================================================
// Functions required by the BidirectionalGraph concept

template < typename G >
std::pair< typename graph_traits< G >::in_edge_iterator,
    typename graph_traits< G >::in_edge_iterator >
in_edges(
    typename graph_traits< G >::vertex_descriptor v, const subgraph< G >& g)
{
    return in_edges(v, g.m_graph);
}

template < typename G >
typename graph_traits< G >::degree_size_type in_degree(
    typename graph_traits< G >::vertex_descriptor v, const subgraph< G >& g)
{
    return in_degree(v, g.m_graph);
}

template < typename G >
typename graph_traits< G >::degree_size_type degree(
    typename graph_traits< G >::vertex_descriptor v, const subgraph< G >& g)
{
    return degree(v, g.m_graph);
}

//===========================================================================
// Functions required by the AdjacencyGraph concept

template < typename G >
std::pair< typename subgraph< G >::adjacency_iterator,
    typename subgraph< G >::adjacency_iterator >
adjacent_vertices(
    typename subgraph< G >::vertex_descriptor v, const subgraph< G >& g)
{
    return adjacent_vertices(v, g.m_graph);
}

//===========================================================================
// Functions required by the VertexListGraph concept

template < typename G >
std::pair< typename subgraph< G >::vertex_iterator,
    typename subgraph< G >::vertex_iterator >
vertices(const subgraph< G >& g)
{
    return vertices(g.m_graph);
}

template < typename G >
typename subgraph< G >::vertices_size_type num_vertices(const subgraph< G >& g)
{
    return num_vertices(g.m_graph);
}

//===========================================================================
// Functions required by the EdgeListGraph concept

template < typename G >
std::pair< typename subgraph< G >::edge_iterator,
    typename subgraph< G >::edge_iterator >
edges(const subgraph< G >& g)
{
    return edges(g.m_graph);
}

template < typename G >
typename subgraph< G >::edges_size_type num_edges(const subgraph< G >& g)
{
    return num_edges(g.m_graph);
}

//===========================================================================
// Functions required by the AdjacencyMatrix concept

template < typename G >
std::pair< typename subgraph< G >::edge_descriptor, bool > edge(
    typename subgraph< G >::vertex_descriptor u,
    typename subgraph< G >::vertex_descriptor v, const subgraph< G >& g)
{
    return edge(u, v, g.m_graph);
}

//===========================================================================
// Functions required by the MutableGraph concept

namespace detail
{

    template < typename Vertex, typename Edge, typename Graph >
    void add_edge_recur_down(
        Vertex u_global, Vertex v_global, Edge e_global, subgraph< Graph >& g);

    template < typename Vertex, typename Edge, typename Children, typename G >
    void children_add_edge(Vertex u_global, Vertex v_global, Edge e_global,
        Children& c, subgraph< G >* orig)
    {
        for (typename Children::iterator i = c.begin(); i != c.end(); ++i)
        {
            if ((*i)->find_vertex(u_global).second
                && (*i)->find_vertex(v_global).second)
            {
                add_edge_recur_down(u_global, v_global, e_global, **i, orig);
            }
        }
    }

    template < typename Vertex, typename Edge, typename Graph >
    void add_edge_recur_down(Vertex u_global, Vertex v_global, Edge e_global,
        subgraph< Graph >& g, subgraph< Graph >* orig)
    {
        if (&g != orig)
        {
            // add local edge only if u_global and v_global are in subgraph g
            Vertex u_local, v_local;
            bool u_in_subgraph, v_in_subgraph;
            boost::tie(u_local, u_in_subgraph) = g.find_vertex(u_global);
            boost::tie(v_local, v_in_subgraph) = g.find_vertex(v_global);
            if (u_in_subgraph && v_in_subgraph)
            {
                g.local_add_edge(u_local, v_local, e_global);
            }
        }
        children_add_edge(u_global, v_global, e_global, g.m_children, orig);
    }

    template < typename Vertex, typename Graph >
    std::pair< typename subgraph< Graph >::edge_descriptor, bool >
    add_edge_recur_up(Vertex u_global, Vertex v_global,
        const typename Graph::edge_property_type& ep, subgraph< Graph >& g,
        subgraph< Graph >* orig)
    {
        if (g.is_root())
        {
            typename subgraph< Graph >::edge_descriptor e_global;
            bool inserted;
            boost::tie(e_global, inserted)
                = add_edge(u_global, v_global, ep, g.m_graph);
            put(edge_index, g.m_graph, e_global, g.m_edge_counter++);
            g.m_global_edge.push_back(e_global);
            children_add_edge(u_global, v_global, e_global, g.m_children, orig);
            return std::make_pair(e_global, inserted);
        }
        else
        {
            return add_edge_recur_up(u_global, v_global, ep, *g.m_parent, orig);
        }
    }

} // namespace detail

// Add an edge to the subgraph g, specified by the local vertex descriptors u
// and v. In addition, the edge will be added to any (all) other subgraphs that
// contain vertex descriptors u and v.

template < typename G >
std::pair< typename subgraph< G >::edge_descriptor, bool > add_edge(
    typename subgraph< G >::vertex_descriptor u,
    typename subgraph< G >::vertex_descriptor v,
    const typename G::edge_property_type& ep, subgraph< G >& g)
{
    if (g.is_root())
    {
        // u and v are really global
        return detail::add_edge_recur_up(u, v, ep, g, &g);
    }
    else
    {
        typename subgraph< G >::edge_descriptor e_local, e_global;
        bool inserted;
        boost::tie(e_global, inserted) = detail::add_edge_recur_up(
            g.local_to_global(u), g.local_to_global(v), ep, g, &g);
        e_local = g.local_add_edge(u, v, e_global);
        return std::make_pair(e_local, inserted);
    }
}

template < typename G >
std::pair< typename subgraph< G >::edge_descriptor, bool > add_edge(
    typename subgraph< G >::vertex_descriptor u,
    typename subgraph< G >::vertex_descriptor v, subgraph< G >& g)
{
    return add_edge(u, v, typename G::edge_property_type(), g);
}

namespace detail
{
    //-------------------------------------------------------------------------
    // implementation of remove_edge(u,v,g)
    template < typename Vertex, typename Graph >
    void remove_edge_recur_down(
        Vertex u_global, Vertex v_global, subgraph< Graph >& g);

    template < typename Vertex, typename Children >
    void children_remove_edge(Vertex u_global, Vertex v_global, Children& c)
    {
        for (typename Children::iterator i = c.begin(); i != c.end(); ++i)
        {
            if ((*i)->find_vertex(u_global).second
                && (*i)->find_vertex(v_global).second)
            {
                remove_edge_recur_down(u_global, v_global, **i);
            }
        }
    }

    template < typename Vertex, typename Graph >
    void remove_edge_recur_down(
        Vertex u_global, Vertex v_global, subgraph< Graph >& g)
    {
        Vertex u_local, v_local;
        u_local = g.m_local_vertex[u_global];
        v_local = g.m_local_vertex[v_global];
        remove_edge(u_local, v_local, g.m_graph);
        children_remove_edge(u_global, v_global, g.m_children);
    }

    template < typename Vertex, typename Graph >
    void remove_edge_recur_up(
        Vertex u_global, Vertex v_global, subgraph< Graph >& g)
    {
        if (g.is_root())
        {
            remove_edge(u_global, v_global, g.m_graph);
            children_remove_edge(u_global, v_global, g.m_children);
        }
        else
        {
            remove_edge_recur_up(u_global, v_global, *g.m_parent);
        }
    }

    //-------------------------------------------------------------------------
    // implementation of remove_edge(e,g)

    template < typename G, typename Edge, typename Children >
    void children_remove_edge(Edge e_global, Children& c)
    {
        for (typename Children::iterator i = c.begin(); i != c.end(); ++i)
        {
            std::pair< typename subgraph< G >::edge_descriptor, bool > found
                = (*i)->find_edge(e_global);
            if (!found.second)
            {
                continue;
            }
            children_remove_edge< G >(e_global, (*i)->m_children);
            remove_edge(found.first, (*i)->m_graph);
        }
    }

} // namespace detail

template < typename G >
void remove_edge(typename subgraph< G >::vertex_descriptor u,
    typename subgraph< G >::vertex_descriptor v, subgraph< G >& g)
{
    if (g.is_root())
    {
        detail::remove_edge_recur_up(u, v, g);
    }
    else
    {
        detail::remove_edge_recur_up(
            g.local_to_global(u), g.local_to_global(v), g);
    }
}

template < typename G >
void remove_edge(typename subgraph< G >::edge_descriptor e, subgraph< G >& g)
{
    typename subgraph< G >::edge_descriptor e_global = g.local_to_global(e);
#ifndef NDEBUG
    std::pair< typename subgraph< G >::edge_descriptor, bool > fe
        = g.find_edge(e_global);
    BOOST_ASSERT(fe.second && fe.first == e);
#endif // NDEBUG
    subgraph< G >& root = g.root(); // chase to root
    detail::children_remove_edge< G >(e_global, root.m_children);
    remove_edge(e_global, root.m_graph); // kick edge from root
}

// This is slow, but there may not be a good way to do it safely otherwise
template < typename Predicate, typename G >
void remove_edge_if(Predicate p, subgraph< G >& g)
{
    while (true)
    {
        bool any_removed = false;
        typedef typename subgraph< G >::edge_iterator ei_type;
        for (std::pair< ei_type, ei_type > ep = edges(g); ep.first != ep.second;
             ++ep.first)
        {
            if (p(*ep.first))
            {
                any_removed = true;
                remove_edge(*ep.first, g);
                break; /* Since iterators may be invalidated */
            }
        }
        if (!any_removed)
            break;
    }
}

template < typename G >
void clear_vertex(typename subgraph< G >::vertex_descriptor v, subgraph< G >& g)
{
    while (true)
    {
        typedef typename subgraph< G >::out_edge_iterator oei_type;
        std::pair< oei_type, oei_type > p = out_edges(v, g);
        if (p.first == p.second)
            break;
        remove_edge(*p.first, g);
    }
}

namespace detail
{
    template < typename G >
    typename subgraph< G >::vertex_descriptor add_vertex_recur_up(
        subgraph< G >& g)
    {
        typename subgraph< G >::vertex_descriptor u_local, u_global;
        if (g.is_root())
        {
            u_global = add_vertex(g.m_graph);
            g.m_global_vertex.push_back(u_global);
        }
        else
        {
            u_global = add_vertex_recur_up(*g.m_parent);
            u_local = add_vertex(g.m_graph);
            g.m_global_vertex.push_back(u_global);
            g.m_local_vertex[u_global] = u_local;
        }
        return u_global;
    }
} // namespace detail

template < typename G >
typename subgraph< G >::vertex_descriptor add_vertex(subgraph< G >& g)
{
    typename subgraph< G >::vertex_descriptor u_local, u_global;
    if (g.is_root())
    {
        u_global = add_vertex(g.m_graph);
        g.m_global_vertex.push_back(u_global);
        u_local = u_global;
    }
    else
    {
        u_global = detail::add_vertex_recur_up(g.parent());
        u_local = add_vertex(g.m_graph);
        g.m_global_vertex.push_back(u_global);
        g.m_local_vertex[u_global] = u_local;
    }
    return u_local;
}

#if 0
// TODO: Under Construction
template <typename G>
void remove_vertex(typename subgraph<G>::vertex_descriptor u, subgraph<G>& g)
{ BOOST_ASSERT(false); }
#endif

//===========================================================================
// Functions required by the PropertyGraph concept

/**
 * The global property map returns the global properties associated with local
 * descriptors.
 */
template < typename GraphPtr, typename PropertyMap, typename Tag >
class subgraph_global_property_map
: public put_get_helper< typename property_traits< PropertyMap >::reference,
      subgraph_global_property_map< GraphPtr, PropertyMap, Tag > >
{
    typedef property_traits< PropertyMap > Traits;

public:
    typedef typename mpl::if_<
        is_const< typename remove_pointer< GraphPtr >::type >,
        readable_property_map_tag, typename Traits::category >::type category;
    typedef typename Traits::value_type value_type;
    typedef typename Traits::key_type key_type;
    typedef typename Traits::reference reference;

    subgraph_global_property_map() {}

    subgraph_global_property_map(GraphPtr g, Tag tag) : m_g(g), m_tag(tag) {}

    reference operator[](key_type e) const
    {
        PropertyMap pmap = get(m_tag, m_g->root().m_graph);
        return m_g->is_root() ? pmap[e] : pmap[m_g->local_to_global(e)];
    }

    GraphPtr m_g;
    Tag m_tag;
};

/**
 * The local property map returns the local property associated with the local
 * descriptors.
 */
template < typename GraphPtr, typename PropertyMap, typename Tag >
class subgraph_local_property_map
: public put_get_helper< typename property_traits< PropertyMap >::reference,
      subgraph_local_property_map< GraphPtr, PropertyMap, Tag > >
{
    typedef property_traits< PropertyMap > Traits;

public:
    typedef typename mpl::if_<
        is_const< typename remove_pointer< GraphPtr >::type >,
        readable_property_map_tag, typename Traits::category >::type category;
    typedef typename Traits::value_type value_type;
    typedef typename Traits::key_type key_type;
    typedef typename Traits::reference reference;

    typedef Tag tag;
    typedef PropertyMap pmap;

    subgraph_local_property_map() {}

    subgraph_local_property_map(GraphPtr g, Tag tag) : m_g(g), m_tag(tag) {}

    reference operator[](key_type e) const
    {
        // Get property map on the underlying graph.
        PropertyMap pmap = get(m_tag, m_g->m_graph);
        return pmap[e];
    }

    GraphPtr m_g;
    Tag m_tag;
};

namespace detail
{
    // Extract the actual tags from local or global property maps so we don't
    // try to find non-properties.
    template < typename P > struct extract_lg_tag
    {
        typedef P type;
    };
    template < typename P > struct extract_lg_tag< local_property< P > >
    {
        typedef P type;
    };
    template < typename P > struct extract_lg_tag< global_property< P > >
    {
        typedef P type;
    };

    // NOTE: Mysterious Property template parameter unused in both metafunction
    // classes.
    struct subgraph_global_pmap
    {
        template < class Tag, class SubGraph, class Property > struct bind_
        {
            typedef typename SubGraph::graph_type Graph;
            typedef SubGraph* SubGraphPtr;
            typedef const SubGraph* const_SubGraphPtr;
            typedef typename extract_lg_tag< Tag >::type TagType;
            typedef typename property_map< Graph, TagType >::type PMap;
            typedef
                typename property_map< Graph, TagType >::const_type const_PMap;

        public:
            typedef subgraph_global_property_map< SubGraphPtr, PMap, TagType >
                type;
            typedef subgraph_global_property_map< const_SubGraphPtr, const_PMap,
                TagType >
                const_type;
        };
    };

    struct subgraph_local_pmap
    {
        template < class Tag, class SubGraph, class Property > struct bind_
        {
            typedef typename SubGraph::graph_type Graph;
            typedef SubGraph* SubGraphPtr;
            typedef const SubGraph* const_SubGraphPtr;
            typedef typename extract_lg_tag< Tag >::type TagType;
            typedef typename property_map< Graph, TagType >::type PMap;
            typedef
                typename property_map< Graph, TagType >::const_type const_PMap;

        public:
            typedef subgraph_local_property_map< SubGraphPtr, PMap, TagType >
                type;
            typedef subgraph_local_property_map< const_SubGraphPtr, const_PMap,
                TagType >
                const_type;
        };
    };

    // These metafunctions select the corresponding metafunctions above, and
    // are used by the choose_pmap metafunction below to specialize the choice
    // of local/global property map. By default, we defer to the global
    // property.
    template < class Tag > struct subgraph_choose_pmap_helper
    {
        typedef subgraph_global_pmap type;
    };
    template < class Tag >
    struct subgraph_choose_pmap_helper< local_property< Tag > >
    {
        typedef subgraph_local_pmap type;
    };
    template < class Tag >
    struct subgraph_choose_pmap_helper< global_property< Tag > >
    {
        typedef subgraph_global_pmap type;
    };

    // As above, unless we're requesting vertex_index_t. Then it's always a
    // local property map. This enables the correct translation of descriptors
    // between local and global layers.
    template <> struct subgraph_choose_pmap_helper< vertex_index_t >
    {
        typedef subgraph_local_pmap type;
    };
    template <>
    struct subgraph_choose_pmap_helper< local_property< vertex_index_t > >
    {
        typedef subgraph_local_pmap type;
    };
    template <>
    struct subgraph_choose_pmap_helper< global_property< vertex_index_t > >
    {
        typedef subgraph_local_pmap type;
    };

    // Determine the kind of property. If SameType<Tag, vertex_index_t>, then
    // the property lookup is always local. Otherwise, the lookup is global.
    // NOTE: Property parameter is basically unused.
    template < class Tag, class Graph, class Property >
    struct subgraph_choose_pmap
    {
        typedef typename subgraph_choose_pmap_helper< Tag >::type Helper;
        typedef typename Helper::template bind_< Tag, Graph, Property > Bind;
        typedef typename Bind::type type;
        typedef typename Bind::const_type const_type;
    };

    // Used by the vertex/edge property selectors to determine the kind(s) of
    // property maps used by the property_map type generator.
    struct subgraph_property_generator
    {
        template < class SubGraph, class Property, class Tag > struct bind_
        {
            typedef subgraph_choose_pmap< Tag, SubGraph, Property > Choice;
            typedef typename Choice::type type;
            typedef typename Choice::const_type const_type;
        };
    };

} // namespace detail

template <> struct vertex_property_selector< subgraph_tag >
{
    typedef detail::subgraph_property_generator type;
};

template <> struct edge_property_selector< subgraph_tag >
{
    typedef detail::subgraph_property_generator type;
};

// ==================================================
// get(p, g), get(p, g, k), and put(p, g, k, v)
// ==================================================
template < typename G, typename Property >
typename property_map< subgraph< G >, Property >::type get(
    Property p, subgraph< G >& g)
{
    typedef typename property_map< subgraph< G >, Property >::type PMap;
    return PMap(&g, p);
}

template < typename G, typename Property >
typename property_map< subgraph< G >, Property >::const_type get(
    Property p, const subgraph< G >& g)
{
    typedef typename property_map< subgraph< G >, Property >::const_type PMap;
    return PMap(&g, p);
}

template < typename G, typename Property, typename Key >
typename property_traits<
    typename property_map< subgraph< G >, Property >::const_type >::value_type
get(Property p, const subgraph< G >& g, const Key& k)
{
    typedef typename property_map< subgraph< G >, Property >::const_type PMap;
    PMap pmap(&g, p);
    return pmap[k];
}

template < typename G, typename Property, typename Key, typename Value >
void put(Property p, subgraph< G >& g, const Key& k, const Value& val)
{
    typedef typename property_map< subgraph< G >, Property >::type PMap;
    PMap pmap(&g, p);
    pmap[k] = val;
}

// ==================================================
// get(global(p), g)
// NOTE: get(global(p), g, k) and put(global(p), g, k, v) not supported
// ==================================================
template < typename G, typename Property >
typename property_map< subgraph< G >, global_property< Property > >::type get(
    global_property< Property > p, subgraph< G >& g)
{
    typedef typename property_map< subgraph< G >,
        global_property< Property > >::type Map;
    return Map(&g, p.value);
}

template < typename G, typename Property >
typename property_map< subgraph< G >, global_property< Property > >::const_type
get(global_property< Property > p, const subgraph< G >& g)
{
    typedef typename property_map< subgraph< G >,
        global_property< Property > >::const_type Map;
    return Map(&g, p.value);
}

// ==================================================
// get(local(p), g)
// NOTE: get(local(p), g, k) and put(local(p), g, k, v) not supported
// ==================================================
template < typename G, typename Property >
typename property_map< subgraph< G >, local_property< Property > >::type get(
    local_property< Property > p, subgraph< G >& g)
{
    typedef
        typename property_map< subgraph< G >, local_property< Property > >::type
            Map;
    return Map(&g, p.value);
}

template < typename G, typename Property >
typename property_map< subgraph< G >, local_property< Property > >::const_type
get(local_property< Property > p, const subgraph< G >& g)
{
    typedef typename property_map< subgraph< G >,
        local_property< Property > >::const_type Map;
    return Map(&g, p.value);
}

template < typename G, typename Tag >
inline typename graph_property< G, Tag >::type& get_property(
    subgraph< G >& g, Tag tag)
{
    return get_property(g.m_graph, tag);
}

template < typename G, typename Tag >
inline const typename graph_property< G, Tag >::type& get_property(
    const subgraph< G >& g, Tag tag)
{
    return get_property(g.m_graph, tag);
}

//===========================================================================
// Miscellaneous Functions

template < typename G >
typename subgraph< G >::vertex_descriptor vertex(
    typename subgraph< G >::vertices_size_type n, const subgraph< G >& g)
{
    return vertex(n, g.m_graph);
}

//===========================================================================
// Mutability Traits
// Just pull the mutability traits form the underlying graph. Note that this
// will probably fail (badly) for labeled graphs.
template < typename G > struct graph_mutability_traits< subgraph< G > >
{
    typedef typename graph_mutability_traits< G >::category category;
};

} // namespace boost

#endif // BOOST_SUBGRAPH_HPP

/* subgraph.hpp
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
*/