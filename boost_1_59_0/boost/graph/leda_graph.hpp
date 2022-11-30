//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Copyright 2004 The Trustees of Indiana University.
// Copyright 2007 University of Karlsruhe
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek, Douglas Gregor,
//          Jens Mueller
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#ifndef BOOST_GRAPH_LEDA_HPP
#define BOOST_GRAPH_LEDA_HPP

#include <boost/config.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>

#include <LEDA/graph/graph.h>
#include <LEDA/graph/node_array.h>
#include <LEDA/graph/node_map.h>

// The functions and classes in this file allows the user to
// treat a LEDA GRAPH object as a boost graph "as is". No
// wrapper is needed for the GRAPH object.

// Warning: this implementation relies on partial specialization
// for the graph_traits class (so it won't compile with Visual C++)

// Warning: this implementation is in alpha and has not been tested

namespace boost
{

struct leda_graph_traversal_category : public virtual bidirectional_graph_tag,
                                       public virtual adjacency_graph_tag,
                                       public virtual vertex_list_graph_tag
{
};

template < class vtype, class etype >
struct graph_traits< leda::GRAPH< vtype, etype > >
{
    typedef leda::node vertex_descriptor;
    typedef leda::edge edge_descriptor;

    class adjacency_iterator
    : public iterator_facade< adjacency_iterator, leda::node,
          bidirectional_traversal_tag, leda::node, const leda::node* >
    {
    public:
        adjacency_iterator(
            leda::node node = 0, const leda::GRAPH< vtype, etype >* g = 0)
        : base(node), g(g)
        {
        }

    private:
        leda::node dereference() const { return leda::target(base); }

        bool equal(const adjacency_iterator& other) const
        {
            return base == other.base;
        }

        void increment() { base = g->adj_succ(base); }
        void decrement() { base = g->adj_pred(base); }

        leda::edge base;
        const leda::GRAPH< vtype, etype >* g;

        friend class iterator_core_access;
    };

    class out_edge_iterator
    : public iterator_facade< out_edge_iterator, leda::edge,
          bidirectional_traversal_tag, const leda::edge&, const leda::edge* >
    {
    public:
        out_edge_iterator(
            leda::node node = 0, const leda::GRAPH< vtype, etype >* g = 0)
        : base(node), g(g)
        {
        }

    private:
        const leda::edge& dereference() const { return base; }

        bool equal(const out_edge_iterator& other) const
        {
            return base == other.base;
        }

        void increment() { base = g->adj_succ(base); }
        void decrement() { base = g->adj_pred(base); }

        leda::edge base;
        const leda::GRAPH< vtype, etype >* g;

        friend class iterator_core_access;
    };

    class in_edge_iterator
    : public iterator_facade< in_edge_iterator, leda::edge,
          bidirectional_traversal_tag, const leda::edge&, const leda::edge* >
    {
    public:
        in_edge_iterator(
            leda::node node = 0, const leda::GRAPH< vtype, etype >* g = 0)
        : base(node), g(g)
        {
        }

    private:
        const leda::edge& dereference() const { return base; }

        bool equal(const in_edge_iterator& other) const
        {
            return base == other.base;
        }

        void increment() { base = g->in_succ(base); }
        void decrement() { base = g->in_pred(base); }

        leda::edge base;
        const leda::GRAPH< vtype, etype >* g;

        friend class iterator_core_access;
    };

    class vertex_iterator
    : public iterator_facade< vertex_iterator, leda::node,
          bidirectional_traversal_tag, const leda::node&, const leda::node* >
    {
    public:
        vertex_iterator(
            leda::node node = 0, const leda::GRAPH< vtype, etype >* g = 0)
        : base(node), g(g)
        {
        }

    private:
        const leda::node& dereference() const { return base; }

        bool equal(const vertex_iterator& other) const
        {
            return base == other.base;
        }

        void increment() { base = g->succ_node(base); }
        void decrement() { base = g->pred_node(base); }

        leda::node base;
        const leda::GRAPH< vtype, etype >* g;

        friend class iterator_core_access;
    };

    class edge_iterator
    : public iterator_facade< edge_iterator, leda::edge,
          bidirectional_traversal_tag, const leda::edge&, const leda::edge* >
    {
    public:
        edge_iterator(
            leda::edge edge = 0, const leda::GRAPH< vtype, etype >* g = 0)
        : base(edge), g(g)
        {
        }

    private:
        const leda::edge& dereference() const { return base; }

        bool equal(const edge_iterator& other) const
        {
            return base == other.base;
        }

        void increment() { base = g->succ_edge(base); }
        void decrement() { base = g->pred_edge(base); }

        leda::node base;
        const leda::GRAPH< vtype, etype >* g;

        friend class iterator_core_access;
    };

    typedef directed_tag directed_category;
    typedef allow_parallel_edge_tag edge_parallel_category; // not sure here
    typedef leda_graph_traversal_category traversal_category;
    typedef int vertices_size_type;
    typedef int edges_size_type;
    typedef int degree_size_type;
};

template <> struct graph_traits< leda::graph >
{
    typedef leda::node vertex_descriptor;
    typedef leda::edge edge_descriptor;

    class adjacency_iterator
    : public iterator_facade< adjacency_iterator, leda::node,
          bidirectional_traversal_tag, leda::node, const leda::node* >
    {
    public:
        adjacency_iterator(leda::edge edge = 0, const leda::graph* g = 0)
        : base(edge), g(g)
        {
        }

    private:
        leda::node dereference() const { return leda::target(base); }

        bool equal(const adjacency_iterator& other) const
        {
            return base == other.base;
        }

        void increment() { base = g->adj_succ(base); }
        void decrement() { base = g->adj_pred(base); }

        leda::edge base;
        const leda::graph* g;

        friend class iterator_core_access;
    };

    class out_edge_iterator
    : public iterator_facade< out_edge_iterator, leda::edge,
          bidirectional_traversal_tag, const leda::edge&, const leda::edge* >
    {
    public:
        out_edge_iterator(leda::edge edge = 0, const leda::graph* g = 0)
        : base(edge), g(g)
        {
        }

    private:
        const leda::edge& dereference() const { return base; }

        bool equal(const out_edge_iterator& other) const
        {
            return base == other.base;
        }

        void increment() { base = g->adj_succ(base); }
        void decrement() { base = g->adj_pred(base); }

        leda::edge base;
        const leda::graph* g;

        friend class iterator_core_access;
    };

    class in_edge_iterator
    : public iterator_facade< in_edge_iterator, leda::edge,
          bidirectional_traversal_tag, const leda::edge&, const leda::edge* >
    {
    public:
        in_edge_iterator(leda::edge edge = 0, const leda::graph* g = 0)
        : base(edge), g(g)
        {
        }

    private:
        const leda::edge& dereference() const { return base; }

        bool equal(const in_edge_iterator& other) const
        {
            return base == other.base;
        }

        void increment() { base = g->in_succ(base); }
        void decrement() { base = g->in_pred(base); }

        leda::edge base;
        const leda::graph* g;

        friend class iterator_core_access;
    };

    class vertex_iterator
    : public iterator_facade< vertex_iterator, leda::node,
          bidirectional_traversal_tag, const leda::node&, const leda::node* >
    {
    public:
        vertex_iterator(leda::node node = 0, const leda::graph* g = 0)
        : base(node), g(g)
        {
        }

    private:
        const leda::node& dereference() const { return base; }

        bool equal(const vertex_iterator& other) const
        {
            return base == other.base;
        }

        void increment() { base = g->succ_node(base); }
        void decrement() { base = g->pred_node(base); }

        leda::node base;
        const leda::graph* g;

        friend class iterator_core_access;
    };

    class edge_iterator
    : public iterator_facade< edge_iterator, leda::edge,
          bidirectional_traversal_tag, const leda::edge&, const leda::edge* >
    {
    public:
        edge_iterator(leda::edge edge = 0, const leda::graph* g = 0)
        : base(edge), g(g)
        {
        }

    private:
        const leda::edge& dereference() const { return base; }

        bool equal(const edge_iterator& other) const
        {
            return base == other.base;
        }

        void increment() { base = g->succ_edge(base); }
        void decrement() { base = g->pred_edge(base); }

        leda::edge base;
        const leda::graph* g;

        friend class iterator_core_access;
    };

    typedef directed_tag directed_category;
    typedef allow_parallel_edge_tag edge_parallel_category; // not sure here
    typedef leda_graph_traversal_category traversal_category;
    typedef int vertices_size_type;
    typedef int edges_size_type;
    typedef int degree_size_type;
};

} // namespace boost

namespace boost
{

//===========================================================================
// functions for GRAPH<vtype,etype>

template < class vtype, class etype >
typename graph_traits< leda::GRAPH< vtype, etype > >::vertex_descriptor source(
    typename graph_traits< leda::GRAPH< vtype, etype > >::edge_descriptor e,
    const leda::GRAPH< vtype, etype >& g)
{
    return source(e);
}

template < class vtype, class etype >
typename graph_traits< leda::GRAPH< vtype, etype > >::vertex_descriptor target(
    typename graph_traits< leda::GRAPH< vtype, etype > >::edge_descriptor e,
    const leda::GRAPH< vtype, etype >& g)
{
    return target(e);
}

template < class vtype, class etype >
inline std::pair<
    typename graph_traits< leda::GRAPH< vtype, etype > >::vertex_iterator,
    typename graph_traits< leda::GRAPH< vtype, etype > >::vertex_iterator >
vertices(const leda::GRAPH< vtype, etype >& g)
{
    typedef
        typename graph_traits< leda::GRAPH< vtype, etype > >::vertex_iterator
            Iter;
    return std::make_pair(Iter(g.first_node(), &g), Iter(0, &g));
}

template < class vtype, class etype >
inline std::pair<
    typename graph_traits< leda::GRAPH< vtype, etype > >::edge_iterator,
    typename graph_traits< leda::GRAPH< vtype, etype > >::edge_iterator >
edges(const leda::GRAPH< vtype, etype >& g)
{
    typedef typename graph_traits< leda::GRAPH< vtype, etype > >::edge_iterator
        Iter;
    return std::make_pair(Iter(g.first_edge(), &g), Iter(0, &g));
}

template < class vtype, class etype >
inline std::pair<
    typename graph_traits< leda::GRAPH< vtype, etype > >::out_edge_iterator,
    typename graph_traits< leda::GRAPH< vtype, etype > >::out_edge_iterator >
out_edges(
    typename graph_traits< leda::GRAPH< vtype, etype > >::vertex_descriptor u,
    const leda::GRAPH< vtype, etype >& g)
{
    typedef
        typename graph_traits< leda::GRAPH< vtype, etype > >::out_edge_iterator
            Iter;
    return std::make_pair(Iter(g.first_adj_edge(u, 0), &g), Iter(0, &g));
}

template < class vtype, class etype >
inline std::pair<
    typename graph_traits< leda::GRAPH< vtype, etype > >::in_edge_iterator,
    typename graph_traits< leda::GRAPH< vtype, etype > >::in_edge_iterator >
in_edges(
    typename graph_traits< leda::GRAPH< vtype, etype > >::vertex_descriptor u,
    const leda::GRAPH< vtype, etype >& g)
{
    typedef
        typename graph_traits< leda::GRAPH< vtype, etype > >::in_edge_iterator
            Iter;
    return std::make_pair(Iter(g.first_adj_edge(u, 1), &g), Iter(0, &g));
}

template < class vtype, class etype >
inline std::pair<
    typename graph_traits< leda::GRAPH< vtype, etype > >::adjacency_iterator,
    typename graph_traits< leda::GRAPH< vtype, etype > >::adjacency_iterator >
adjacent_vertices(
    typename graph_traits< leda::GRAPH< vtype, etype > >::vertex_descriptor u,
    const leda::GRAPH< vtype, etype >& g)
{
    typedef
        typename graph_traits< leda::GRAPH< vtype, etype > >::adjacency_iterator
            Iter;
    return std::make_pair(Iter(g.first_adj_edge(u, 0), &g), Iter(0, &g));
}

template < class vtype, class etype >
typename graph_traits< leda::GRAPH< vtype, etype > >::vertices_size_type
num_vertices(const leda::GRAPH< vtype, etype >& g)
{
    return g.number_of_nodes();
}

template < class vtype, class etype >
typename graph_traits< leda::GRAPH< vtype, etype > >::edges_size_type num_edges(
    const leda::GRAPH< vtype, etype >& g)
{
    return g.number_of_edges();
}

template < class vtype, class etype >
typename graph_traits< leda::GRAPH< vtype, etype > >::degree_size_type
out_degree(
    typename graph_traits< leda::GRAPH< vtype, etype > >::vertex_descriptor u,
    const leda::GRAPH< vtype, etype >& g)
{
    return g.outdeg(u);
}

template < class vtype, class etype >
typename graph_traits< leda::GRAPH< vtype, etype > >::degree_size_type
in_degree(
    typename graph_traits< leda::GRAPH< vtype, etype > >::vertex_descriptor u,
    const leda::GRAPH< vtype, etype >& g)
{
    return g.indeg(u);
}

template < class vtype, class etype >
typename graph_traits< leda::GRAPH< vtype, etype > >::degree_size_type degree(
    typename graph_traits< leda::GRAPH< vtype, etype > >::vertex_descriptor u,
    const leda::GRAPH< vtype, etype >& g)
{
    return g.outdeg(u) + g.indeg(u);
}

template < class vtype, class etype >
typename graph_traits< leda::GRAPH< vtype, etype > >::vertex_descriptor
add_vertex(leda::GRAPH< vtype, etype >& g)
{
    return g.new_node();
}

template < class vtype, class etype >
typename graph_traits< leda::GRAPH< vtype, etype > >::vertex_descriptor
add_vertex(const vtype& vp, leda::GRAPH< vtype, etype >& g)
{
    return g.new_node(vp);
}

template < class vtype, class etype >
void clear_vertex(
    typename graph_traits< leda::GRAPH< vtype, etype > >::vertex_descriptor u,
    leda::GRAPH< vtype, etype >& g)
{
    typename graph_traits< leda::GRAPH< vtype, etype > >::out_edge_iterator ei,
        ei_end;
    for (boost::tie(ei, ei_end) = out_edges(u, g); ei != ei_end; ei++)
        remove_edge(*ei);

    typename graph_traits< leda::GRAPH< vtype, etype > >::in_edge_iterator iei,
        iei_end;
    for (boost::tie(iei, iei_end) = in_edges(u, g); iei != iei_end; iei++)
        remove_edge(*iei);
}

template < class vtype, class etype >
void remove_vertex(
    typename graph_traits< leda::GRAPH< vtype, etype > >::vertex_descriptor u,
    leda::GRAPH< vtype, etype >& g)
{
    g.del_node(u);
}

template < class vtype, class etype >
std::pair<
    typename graph_traits< leda::GRAPH< vtype, etype > >::edge_descriptor,
    bool >
add_edge(
    typename graph_traits< leda::GRAPH< vtype, etype > >::vertex_descriptor u,
    typename graph_traits< leda::GRAPH< vtype, etype > >::vertex_descriptor v,
    leda::GRAPH< vtype, etype >& g)
{
    return std::make_pair(g.new_edge(u, v), true);
}

template < class vtype, class etype >
std::pair<
    typename graph_traits< leda::GRAPH< vtype, etype > >::edge_descriptor,
    bool >
add_edge(
    typename graph_traits< leda::GRAPH< vtype, etype > >::vertex_descriptor u,
    typename graph_traits< leda::GRAPH< vtype, etype > >::vertex_descriptor v,
    const etype& et, leda::GRAPH< vtype, etype >& g)
{
    return std::make_pair(g.new_edge(u, v, et), true);
}

template < class vtype, class etype >
void remove_edge(
    typename graph_traits< leda::GRAPH< vtype, etype > >::vertex_descriptor u,
    typename graph_traits< leda::GRAPH< vtype, etype > >::vertex_descriptor v,
    leda::GRAPH< vtype, etype >& g)
{
    typename graph_traits< leda::GRAPH< vtype, etype > >::out_edge_iterator i,
        iend;
    for (boost::tie(i, iend) = out_edges(u, g); i != iend; ++i)
        if (target(*i, g) == v)
            g.del_edge(*i);
}

template < class vtype, class etype >
void remove_edge(
    typename graph_traits< leda::GRAPH< vtype, etype > >::edge_descriptor e,
    leda::GRAPH< vtype, etype >& g)
{
    g.del_edge(e);
}

//===========================================================================
// functions for graph (non-templated version)

graph_traits< leda::graph >::vertex_descriptor source(
    graph_traits< leda::graph >::edge_descriptor e, const leda::graph& g)
{
    return source(e);
}

graph_traits< leda::graph >::vertex_descriptor target(
    graph_traits< leda::graph >::edge_descriptor e, const leda::graph& g)
{
    return target(e);
}

inline std::pair< graph_traits< leda::graph >::vertex_iterator,
    graph_traits< leda::graph >::vertex_iterator >
vertices(const leda::graph& g)
{
    typedef graph_traits< leda::graph >::vertex_iterator Iter;
    return std::make_pair(Iter(g.first_node(), &g), Iter(0, &g));
}

inline std::pair< graph_traits< leda::graph >::edge_iterator,
    graph_traits< leda::graph >::edge_iterator >
edges(const leda::graph& g)
{
    typedef graph_traits< leda::graph >::edge_iterator Iter;
    return std::make_pair(Iter(g.first_edge(), &g), Iter(0, &g));
}

inline std::pair< graph_traits< leda::graph >::out_edge_iterator,
    graph_traits< leda::graph >::out_edge_iterator >
out_edges(
    graph_traits< leda::graph >::vertex_descriptor u, const leda::graph& g)
{
    typedef graph_traits< leda::graph >::out_edge_iterator Iter;
    return std::make_pair(Iter(g.first_adj_edge(u), &g), Iter(0, &g));
}

inline std::pair< graph_traits< leda::graph >::in_edge_iterator,
    graph_traits< leda::graph >::in_edge_iterator >
in_edges(graph_traits< leda::graph >::vertex_descriptor u, const leda::graph& g)
{
    typedef graph_traits< leda::graph >::in_edge_iterator Iter;
    return std::make_pair(Iter(g.first_in_edge(u), &g), Iter(0, &g));
}

inline std::pair< graph_traits< leda::graph >::adjacency_iterator,
    graph_traits< leda::graph >::adjacency_iterator >
adjacent_vertices(
    graph_traits< leda::graph >::vertex_descriptor u, const leda::graph& g)
{
    typedef graph_traits< leda::graph >::adjacency_iterator Iter;
    return std::make_pair(Iter(g.first_adj_edge(u), &g), Iter(0, &g));
}

graph_traits< leda::graph >::vertices_size_type num_vertices(
    const leda::graph& g)
{
    return g.number_of_nodes();
}

graph_traits< leda::graph >::edges_size_type num_edges(const leda::graph& g)
{
    return g.number_of_edges();
}

graph_traits< leda::graph >::degree_size_type out_degree(
    graph_traits< leda::graph >::vertex_descriptor u, const leda::graph& g)
{
    return g.outdeg(u);
}

graph_traits< leda::graph >::degree_size_type in_degree(
    graph_traits< leda::graph >::vertex_descriptor u, const leda::graph& g)
{
    return g.indeg(u);
}

graph_traits< leda::graph >::degree_size_type degree(
    graph_traits< leda::graph >::vertex_descriptor u, const leda::graph& g)
{
    return g.outdeg(u) + g.indeg(u);
}

graph_traits< leda::graph >::vertex_descriptor add_vertex(leda::graph& g)
{
    return g.new_node();
}

void remove_edge(graph_traits< leda::graph >::vertex_descriptor u,
    graph_traits< leda::graph >::vertex_descriptor v, leda::graph& g)
{
    graph_traits< leda::graph >::out_edge_iterator i, iend;
    for (boost::tie(i, iend) = out_edges(u, g); i != iend; ++i)
        if (target(*i, g) == v)
            g.del_edge(*i);
}

void remove_edge(graph_traits< leda::graph >::edge_descriptor e, leda::graph& g)
{
    g.del_edge(e);
}

void clear_vertex(
    graph_traits< leda::graph >::vertex_descriptor u, leda::graph& g)
{
    graph_traits< leda::graph >::out_edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = out_edges(u, g); ei != ei_end; ei++)
        remove_edge(*ei, g);

    graph_traits< leda::graph >::in_edge_iterator iei, iei_end;
    for (boost::tie(iei, iei_end) = in_edges(u, g); iei != iei_end; iei++)
        remove_edge(*iei, g);
}

void remove_vertex(
    graph_traits< leda::graph >::vertex_descriptor u, leda::graph& g)
{
    g.del_node(u);
}

std::pair< graph_traits< leda::graph >::edge_descriptor, bool > add_edge(
    graph_traits< leda::graph >::vertex_descriptor u,
    graph_traits< leda::graph >::vertex_descriptor v, leda::graph& g)
{
    return std::make_pair(g.new_edge(u, v), true);
}

//===========================================================================
// property maps for GRAPH<vtype,etype>

class leda_graph_id_map : public put_get_helper< int, leda_graph_id_map >
{
public:
    typedef readable_property_map_tag category;
    typedef int value_type;
    typedef int reference;
    typedef leda::node key_type;
    leda_graph_id_map() {}
    template < class T > long operator[](T x) const { return x->id(); }
};
template < class vtype, class etype >
inline leda_graph_id_map get(
    vertex_index_t, const leda::GRAPH< vtype, etype >& g)
{
    return leda_graph_id_map();
}
template < class vtype, class etype >
inline leda_graph_id_map get(edge_index_t, const leda::GRAPH< vtype, etype >& g)
{
    return leda_graph_id_map();
}

template < class Tag > struct leda_property_map
{
};

template <> struct leda_property_map< vertex_index_t >
{
    template < class vtype, class etype > struct bind_
    {
        typedef leda_graph_id_map type;
        typedef leda_graph_id_map const_type;
    };
};
template <> struct leda_property_map< edge_index_t >
{
    template < class vtype, class etype > struct bind_
    {
        typedef leda_graph_id_map type;
        typedef leda_graph_id_map const_type;
    };
};

template < class Data, class DataRef, class GraphPtr >
class leda_graph_data_map : public put_get_helper< DataRef,
                                leda_graph_data_map< Data, DataRef, GraphPtr > >
{
public:
    typedef Data value_type;
    typedef DataRef reference;
    typedef void key_type;
    typedef lvalue_property_map_tag category;
    leda_graph_data_map(GraphPtr g) : m_g(g) {}
    template < class NodeOrEdge > DataRef operator[](NodeOrEdge x) const
    {
        return (*m_g)[x];
    }

protected:
    GraphPtr m_g;
};

template <> struct leda_property_map< vertex_all_t >
{
    template < class vtype, class etype > struct bind_
    {
        typedef leda_graph_data_map< vtype, vtype&,
            leda::GRAPH< vtype, etype >* >
            type;
        typedef leda_graph_data_map< vtype, const vtype&,
            const leda::GRAPH< vtype, etype >* >
            const_type;
    };
};
template < class vtype, class etype >
inline typename property_map< leda::GRAPH< vtype, etype >, vertex_all_t >::type
get(vertex_all_t, leda::GRAPH< vtype, etype >& g)
{
    typedef
        typename property_map< leda::GRAPH< vtype, etype >, vertex_all_t >::type
            pmap_type;
    return pmap_type(&g);
}
template < class vtype, class etype >
inline typename property_map< leda::GRAPH< vtype, etype >,
    vertex_all_t >::const_type
get(vertex_all_t, const leda::GRAPH< vtype, etype >& g)
{
    typedef typename property_map< leda::GRAPH< vtype, etype >,
        vertex_all_t >::const_type pmap_type;
    return pmap_type(&g);
}

template <> struct leda_property_map< edge_all_t >
{
    template < class vtype, class etype > struct bind_
    {
        typedef leda_graph_data_map< etype, etype&,
            leda::GRAPH< vtype, etype >* >
            type;
        typedef leda_graph_data_map< etype, const etype&,
            const leda::GRAPH< vtype, etype >* >
            const_type;
    };
};
template < class vtype, class etype >
inline typename property_map< leda::GRAPH< vtype, etype >, edge_all_t >::type
get(edge_all_t, leda::GRAPH< vtype, etype >& g)
{
    typedef
        typename property_map< leda::GRAPH< vtype, etype >, edge_all_t >::type
            pmap_type;
    return pmap_type(&g);
}
template < class vtype, class etype >
inline
    typename property_map< leda::GRAPH< vtype, etype >, edge_all_t >::const_type
    get(edge_all_t, const leda::GRAPH< vtype, etype >& g)
{
    typedef typename property_map< leda::GRAPH< vtype, etype >,
        edge_all_t >::const_type pmap_type;
    return pmap_type(&g);
}

// property map interface to the LEDA node_array class

template < class E, class ERef, class NodeMapPtr >
class leda_node_property_map
: public put_get_helper< ERef, leda_node_property_map< E, ERef, NodeMapPtr > >
{
public:
    typedef E value_type;
    typedef ERef reference;
    typedef leda::node key_type;
    typedef lvalue_property_map_tag category;
    leda_node_property_map(NodeMapPtr a) : m_array(a) {}
    ERef operator[](leda::node n) const { return (*m_array)[n]; }

protected:
    NodeMapPtr m_array;
};
template < class E >
leda_node_property_map< E, const E&, const leda::node_array< E >* >
make_leda_node_property_map(const leda::node_array< E >& a)
{
    typedef leda_node_property_map< E, const E&, const leda::node_array< E >* >
        pmap_type;
    return pmap_type(&a);
}
template < class E >
leda_node_property_map< E, E&, leda::node_array< E >* >
make_leda_node_property_map(leda::node_array< E >& a)
{
    typedef leda_node_property_map< E, E&, leda::node_array< E >* > pmap_type;
    return pmap_type(&a);
}

template < class E >
leda_node_property_map< E, const E&, const leda::node_map< E >* >
make_leda_node_property_map(const leda::node_map< E >& a)
{
    typedef leda_node_property_map< E, const E&, const leda::node_map< E >* >
        pmap_type;
    return pmap_type(&a);
}
template < class E >
leda_node_property_map< E, E&, leda::node_map< E >* >
make_leda_node_property_map(leda::node_map< E >& a)
{
    typedef leda_node_property_map< E, E&, leda::node_map< E >* > pmap_type;
    return pmap_type(&a);
}

// g++ 'enumeral_type' in template unification not implemented workaround
template < class vtype, class etype, class Tag >
struct property_map< leda::GRAPH< vtype, etype >, Tag >
{
    typedef typename leda_property_map< Tag >::template bind_< vtype, etype >
        map_gen;
    typedef typename map_gen::type type;
    typedef typename map_gen::const_type const_type;
};

template < class vtype, class etype, class PropertyTag, class Key >
inline typename boost::property_traits< typename boost::property_map<
    leda::GRAPH< vtype, etype >, PropertyTag >::const_type >::value_type
get(PropertyTag p, const leda::GRAPH< vtype, etype >& g, const Key& key)
{
    return get(get(p, g), key);
}

template < class vtype, class etype, class PropertyTag, class Key, class Value >
inline void put(PropertyTag p, leda::GRAPH< vtype, etype >& g, const Key& key,
    const Value& value)
{
    typedef
        typename property_map< leda::GRAPH< vtype, etype >, PropertyTag >::type
            Map;
    Map pmap = get(p, g);
    put(pmap, key, value);
}

// property map interface to the LEDA edge_array class

template < class E, class ERef, class EdgeMapPtr >
class leda_edge_property_map
: public put_get_helper< ERef, leda_edge_property_map< E, ERef, EdgeMapPtr > >
{
public:
    typedef E value_type;
    typedef ERef reference;
    typedef leda::edge key_type;
    typedef lvalue_property_map_tag category;
    leda_edge_property_map(EdgeMapPtr a) : m_array(a) {}
    ERef operator[](leda::edge n) const { return (*m_array)[n]; }

protected:
    EdgeMapPtr m_array;
};
template < class E >
leda_edge_property_map< E, const E&, const leda::edge_array< E >* >
make_leda_node_property_map(const leda::node_array< E >& a)
{
    typedef leda_edge_property_map< E, const E&, const leda::node_array< E >* >
        pmap_type;
    return pmap_type(&a);
}
template < class E >
leda_edge_property_map< E, E&, leda::edge_array< E >* >
make_leda_edge_property_map(leda::edge_array< E >& a)
{
    typedef leda_edge_property_map< E, E&, leda::edge_array< E >* > pmap_type;
    return pmap_type(&a);
}

template < class E >
leda_edge_property_map< E, const E&, const leda::edge_map< E >* >
make_leda_edge_property_map(const leda::edge_map< E >& a)
{
    typedef leda_edge_property_map< E, const E&, const leda::edge_map< E >* >
        pmap_type;
    return pmap_type(&a);
}
template < class E >
leda_edge_property_map< E, E&, leda::edge_map< E >* >
make_leda_edge_property_map(leda::edge_map< E >& a)
{
    typedef leda_edge_property_map< E, E&, leda::edge_map< E >* > pmap_type;
    return pmap_type(&a);
}

} // namespace boost

#endif // BOOST_GRAPH_LEDA_HPP

/* leda_graph.hpp
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
*/