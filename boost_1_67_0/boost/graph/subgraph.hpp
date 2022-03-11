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