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