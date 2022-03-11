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