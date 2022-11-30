//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#ifndef BOOST_GRAPH_DETAIL_CONNECTED_COMPONENTS_HPP
#define BOOST_GRAPH_DETAIL_CONNECTED_COMPONENTS_HPP

#if defined(__sgi) && !defined(__GNUC__)
#pragma set woff 1234
#endif

#include <boost/operators.hpp>

namespace boost
{

namespace detail
{

    //=========================================================================
    // Implementation details of connected_components

    // This is used both in the connected_components algorithm and in
    // the kosaraju strong components algorithm during the second DFS
    // traversal.
    template < class ComponentsPA, class DFSVisitor >
    class components_recorder : public DFSVisitor
    {
        typedef typename property_traits< ComponentsPA >::value_type comp_type;

    public:
        components_recorder(ComponentsPA c, comp_type& c_count, DFSVisitor v)
        : DFSVisitor(v), m_component(c), m_count(c_count)
        {
        }

        template < class Vertex, class Graph >
        void start_vertex(Vertex u, Graph& g)
        {
            ++m_count;
            DFSVisitor::start_vertex(u, g);
        }
        template < class Vertex, class Graph >
        void discover_vertex(Vertex u, Graph& g)
        {
            put(m_component, u, m_count);
            DFSVisitor::discover_vertex(u, g);
        }

    protected:
        ComponentsPA m_component;
        comp_type& m_count;
    };

    template < class DiscoverTimeMap, class FinishTimeMap, class TimeT,
        class DFSVisitor >
    class time_recorder : public DFSVisitor
    {
    public:
        time_recorder(
            DiscoverTimeMap d, FinishTimeMap f, TimeT& t, DFSVisitor v)
        : DFSVisitor(v), m_discover_time(d), m_finish_time(f), m_t(t)
        {
        }

        template < class Vertex, class Graph >
        void discover_vertex(Vertex u, Graph& g)
        {
            put(m_discover_time, u, ++m_t);
            DFSVisitor::discover_vertex(u, g);
        }
        template < class Vertex, class Graph >
        void finish_vertex(Vertex u, Graph& g)
        {
            put(m_finish_time, u, ++m_t);
            DFSVisitor::discover_vertex(u, g);
        }

    protected:
        DiscoverTimeMap m_discover_time;
        FinishTimeMap m_finish_time;
        TimeT m_t;
    };
    template < class DiscoverTimeMap, class FinishTimeMap, class TimeT,
        class DFSVisitor >
    time_recorder< DiscoverTimeMap, FinishTimeMap, TimeT, DFSVisitor >
    record_times(DiscoverTimeMap d, FinishTimeMap f, TimeT& t, DFSVisitor vis)
    {
        return time_recorder< DiscoverTimeMap, FinishTimeMap, TimeT,
            DFSVisitor >(d, f, t, vis);
    }

    //=========================================================================
    // Implementation detail of dynamic_components

    //-------------------------------------------------------------------------
    // Helper functions for the component_index class

    // Record the representative vertices in the header array.
    // Representative vertices now point to the component number.

    template < class Parent, class OutputIterator, class Integer >
    inline void build_components_header(
        Parent p, OutputIterator header, Integer num_nodes)
    {
        Parent component = p;
        Integer component_num = 0;
        for (Integer v = 0; v != num_nodes; ++v)
            if (p[v] == v)
            {
                *header++ = v;
                component[v] = component_num++;
            }
    }

    // Pushes x onto the front of the list. The list is represented in
    // an array.
    template < class Next, class T, class V >
    inline void push_front(Next next, T& head, V x)
    {
        T tmp = head;
        head = x;
        next[x] = tmp;
    }

    // Create a linked list of the vertices in each component
    // by reusing the representative array.
    template < class Parent1, class Parent2, class Integer >
    void link_components(Parent1 component, Parent2 header, Integer num_nodes,
        Integer num_components)
    {
        // Make the non-representative vertices point to their component
        Parent1 representative = component;
        for (Integer v = 0; v != num_nodes; ++v)
            if (component[v] >= num_components || header[component[v]] != v)
                component[v] = component[representative[v]];

        // initialize the "head" of the lists to "NULL"
        std::fill_n(header, num_components, num_nodes);

        // Add each vertex to the linked list for its component
        Parent1 next = component;
        for (Integer k = 0; k != num_nodes; ++k)
            push_front(next, header[component[k]], k);
    }

    template < class IndexContainer, class HeaderContainer >
    void construct_component_index(
        IndexContainer& index, HeaderContainer& header)
    {
        build_components_header(index.begin(), std::back_inserter(header),
            index.end() - index.begin());

        link_components(index.begin(), header.begin(),
            index.end() - index.begin(), header.end() - header.begin());
    }

    template < class IndexIterator, class Integer, class Distance >
    class component_iterator
    : boost::forward_iterator_helper<
          component_iterator< IndexIterator, Integer, Distance >, Integer,
          Distance, Integer*, Integer& >
    {
    public:
        typedef component_iterator self;

        IndexIterator next;
        Integer node;

        typedef std::forward_iterator_tag iterator_category;
        typedef Integer value_type;
        typedef Integer& reference;
        typedef Integer* pointer;
        typedef Distance difference_type;

        component_iterator() {}
        component_iterator(IndexIterator x, Integer i) : next(x), node(i) {}
        Integer operator*() const { return node; }
        self& operator++()
        {
            node = next[node];
            return *this;
        }
    };

    template < class IndexIterator, class Integer, class Distance >
    inline bool operator==(
        const component_iterator< IndexIterator, Integer, Distance >& x,
        const component_iterator< IndexIterator, Integer, Distance >& y)
    {
        return x.node == y.node;
    }

} // namespace detail

} // namespace detail

#if defined(__sgi) && !defined(__GNUC__)
#pragma reset woff 1234
#endif

#endif

/* connected_components.hpp
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
*/