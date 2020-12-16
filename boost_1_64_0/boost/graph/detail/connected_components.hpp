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
6pRstxemFOWRd629aTdA37Ue8pwVpEn+ZOe7aKfcZ3PygEv8xGK0Ez+Lkh17yOq67WPJh9Gi29D33KI7lvBlvgFXaBP4h+yNxipuzhSd6+OHk3YllPW/Ut72Vp9rFsS3+pe+d3xlnkeW38vyHK2oehKpxVviL9eqlPmYhG+J21u9G4wi3uMXxtUwbo7bLuV+Bv52wN/B+Lsef0Pshaufv6+q253j8nHxdp3hrJPXH1LjkqpO/lrsV5nJnKq2i/zzI2/qcxjplvYV+vdIPB1R5cP+nrLK0ErfvAbRecbRpqadzMLs0qllFYajHfbBZ/JONZ8yBumx9ackjhq4ysxH8M+ZLz/Bjo62J0p4m31PJeFlJIfas9c+szh4D96Lsf1F3L7nqBP4Rigpmm49zzq4WXTecOiUWwfw6u/46M/lXSbhjQu5d6/dnn1A2sEDo12UvXdp1Up7Vn/zvOn9ifas7d45/7unyF6X+3ml6j37qwd9PzMlDK+yU/eIPVLPJXtI/DiIH3q/59KivILSqY5xyvMlfepI3M0SHSk01rhtSPka5I5vJFoA0ojRftY75K+3Uqu0u1d73+dbqDXfQj0pU8Hu7fq/QNxXug/Rdu/mpj6o0tb9yOGWMh4wN+5nSaMYndciv8COP3FGm6A2e6J+NvJunv18+9Tz7bf6d6W6tsOoPCLPp9s4DeW7yxXWv9quKv7RCVLVv/u+ljpZt1GeEnuMrsP/IHa3Du857Hr+n36entRZfWsEh2PXsaul7dOBWiPBOJbe0G9lHQFPFK3TtEhkNys7f0mYb1fZFzpVviHsPoFPjYyEzMTahvQD0Ke68jTGx3qyp6lvTqF34Q6rT/WZeOe8pfIqff+bP5U8Ln2ulh85+HG7z4+YhZssP57GD6fOcjucB08knFtDhLPBDueGwHDSlM6hntacyqu+YTqlN6KZNzoyzBqcFOUmuZc1r/Jqt9cdH9DfbYffBb2VEv78v1k6mwJ0xtk6HwXqpLjHJryAfXxi4N7W9lzNmzHWOdYvI9+G7jgfsX8NN2Na+/SVDBN0JneF77rIT96UKxY5ZC8kCS0j+2xvgaskHPv8b+e+2ksxtzrmOi3G3K/O6J5jy/HH+vv43Ibu25h3MC863CU4/h6Fcf497h/s3Qd8FFUewPHZ3TQgICkU6V0ExNBCkE4I0kIChF5CCyQCIYQWBKVKlaLAgRTpHRRE6R2U3lQEFRQFARVOBLGg6P32n7dvNrvZ87jDu/Nu98Pjm/nPmzezs7Nl3rx5j3SW+TfMunfncoibbWWd77+cEcIxSzoTTLIvg5102Wb+pZls52yWuxlq/j1D5Z1K+msoyWl99/j7utq2UNaRj/QN0x8TL0v6mZSLWJL6Oy9/f4uPovPzKMw0265jt1SZV1A9J1k+jnSJmNO0lHdbH4N6W4mbsXUsk9++bjzltOxdtfy10PR0m3SHtJbnbSM54t+R7pK+V+uuQFkHpHzV1s36+32ez/nBovs8v3fN0T93uO7H+xszVsERu2LGwhyxj3Ssiu57/JQZi3DE3jZjVR2xBWassh5T3YxVcsSeM2N6+1LMmN6+djpWWW9LTTOm11vJjIU7YqXMWBVH7FEzprcvuxnT22cxY3r7vruqY3r7rpsxvf8+1LFKepvXmrEqeh+YMV1eLzOmy2unYxV1eU3MWITeL2ZM75cwM6b3SzEzprcl1Izp/WIxY+Y++MK9//oUM5/e5mtfuPdf/6EZ09u8zIzp7XvRjJn7yozp16jjFR3T2/L0dR3T2xJ0Kz3Wp1+/FEdsmFrWuX/66Vb3/unnWN37p0/RbTv1NR2Jr7Lqa3K6Tl+uJXroz36R67j6Kv9eD/0=
*/