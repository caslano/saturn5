//=======================================================================
// Copyright (c) Aaron Windsor 2007
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef __FACE_ITERATORS_HPP__
#define __FACE_ITERATORS_HPP__

#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/graph/graph_traits.hpp>

namespace boost
{

// tags for defining traversal properties

// VisitorType
struct lead_visitor
{
};
struct follow_visitor
{
};

// TraversalType
struct single_side
{
};
struct both_sides
{
};

// TraversalSubType
struct first_side
{
}; // for single_side
struct second_side
{
}; // for single_side
struct alternating
{
}; // for both_sides

// Time
struct current_iteration
{
};
struct previous_iteration
{
};

// Why TraversalType AND TraversalSubType? TraversalSubType is a function
// template parameter passed in to the constructor of the face iterator,
// whereas TraversalType is a class template parameter. This lets us decide
// at runtime whether to move along the first or second side of a bicomp (by
// assigning a face_iterator that has been constructed with TraversalSubType
// = first_side or second_side to a face_iterator variable) without any of
// the virtual function overhead that comes with implementing this
// functionality as a more structured form of type erasure. It also allows
// a single face_iterator to be the end iterator of two iterators traversing
// both sides of a bicomp.

// ValueType is either graph_traits<Graph>::vertex_descriptor
// or graph_traits<Graph>::edge_descriptor

// forward declaration (defining defaults)
template < typename Graph, typename FaceHandlesMap, typename ValueType,
    typename BicompSideToTraverse = single_side,
    typename VisitorType = lead_visitor, typename Time = current_iteration >
class face_iterator;

template < typename Graph, bool StoreEdge > struct edge_storage
{
};

template < typename Graph > struct edge_storage< Graph, true >
{
    typename graph_traits< Graph >::edge_descriptor value;
};

// specialization for TraversalType = traverse_vertices
template < typename Graph, typename FaceHandlesMap, typename ValueType,
    typename TraversalType, typename VisitorType, typename Time >

class face_iterator : public boost::iterator_facade<
                          face_iterator< Graph, FaceHandlesMap, ValueType,
                              TraversalType, VisitorType, Time >,
                          ValueType, boost::forward_traversal_tag, ValueType >
{
public:
    typedef typename graph_traits< Graph >::vertex_descriptor vertex_t;
    typedef typename graph_traits< Graph >::edge_descriptor edge_t;
    typedef face_iterator< Graph, FaceHandlesMap, ValueType, TraversalType,
        VisitorType, Time >
        self;
    typedef typename FaceHandlesMap::value_type face_handle_t;

    face_iterator()
    : m_lead(graph_traits< Graph >::null_vertex())
    , m_follow(graph_traits< Graph >::null_vertex())
    {
    }

    template < typename TraversalSubType >
    face_iterator(face_handle_t anchor_handle, FaceHandlesMap face_handles,
        TraversalSubType traversal_type)
    : m_follow(anchor_handle.get_anchor()), m_face_handles(face_handles)
    {
        set_lead_dispatch(anchor_handle, traversal_type);
    }

    template < typename TraversalSubType >
    face_iterator(vertex_t anchor, FaceHandlesMap face_handles,
        TraversalSubType traversal_type)
    : m_follow(anchor), m_face_handles(face_handles)
    {
        set_lead_dispatch(m_face_handles[anchor], traversal_type);
    }

private:
    friend class boost::iterator_core_access;

    inline vertex_t get_first_vertex(
        face_handle_t anchor_handle, current_iteration)
    {
        return anchor_handle.first_vertex();
    }

    inline vertex_t get_second_vertex(
        face_handle_t anchor_handle, current_iteration)
    {
        return anchor_handle.second_vertex();
    }

    inline vertex_t get_first_vertex(
        face_handle_t anchor_handle, previous_iteration)
    {
        return anchor_handle.old_first_vertex();
    }

    inline vertex_t get_second_vertex(
        face_handle_t anchor_handle, previous_iteration)
    {
        return anchor_handle.old_second_vertex();
    }

    inline void set_lead_dispatch(face_handle_t anchor_handle, first_side)
    {
        m_lead = get_first_vertex(anchor_handle, Time());
        set_edge_to_first_dispatch(anchor_handle, ValueType(), Time());
    }

    inline void set_lead_dispatch(face_handle_t anchor_handle, second_side)
    {
        m_lead = get_second_vertex(anchor_handle, Time());
        set_edge_to_second_dispatch(anchor_handle, ValueType(), Time());
    }

    inline void set_edge_to_first_dispatch(
        face_handle_t anchor_handle, edge_t, current_iteration)
    {
        m_edge.value = anchor_handle.first_edge();
    }

    inline void set_edge_to_second_dispatch(
        face_handle_t anchor_handle, edge_t, current_iteration)
    {
        m_edge.value = anchor_handle.second_edge();
    }

    inline void set_edge_to_first_dispatch(
        face_handle_t anchor_handle, edge_t, previous_iteration)
    {
        m_edge.value = anchor_handle.old_first_edge();
    }

    inline void set_edge_to_second_dispatch(
        face_handle_t anchor_handle, edge_t, previous_iteration)
    {
        m_edge.value = anchor_handle.old_second_edge();
    }

    template < typename T >
    inline void set_edge_to_first_dispatch(face_handle_t, vertex_t, T)
    {
    }

    template < typename T >
    inline void set_edge_to_second_dispatch(face_handle_t, vertex_t, T)
    {
    }

    void increment()
    {
        face_handle_t curr_face_handle(m_face_handles[m_lead]);
        vertex_t first = get_first_vertex(curr_face_handle, Time());
        vertex_t second = get_second_vertex(curr_face_handle, Time());
        if (first == m_follow)
        {
            m_follow = m_lead;
            set_edge_to_second_dispatch(curr_face_handle, ValueType(), Time());
            m_lead = second;
        }
        else if (second == m_follow)
        {
            m_follow = m_lead;
            set_edge_to_first_dispatch(curr_face_handle, ValueType(), Time());
            m_lead = first;
        }
        else
            m_lead = m_follow = graph_traits< Graph >::null_vertex();
    }

    bool equal(self const& other) const
    {
        return m_lead == other.m_lead && m_follow == other.m_follow;
    }

    ValueType dereference() const
    {
        return dereference_dispatch(VisitorType(), ValueType());
    }

    inline ValueType dereference_dispatch(lead_visitor, vertex_t) const
    {
        return m_lead;
    }

    inline ValueType dereference_dispatch(follow_visitor, vertex_t) const
    {
        return m_follow;
    }

    inline ValueType dereference_dispatch(lead_visitor, edge_t) const
    {
        return m_edge.value;
    }

    inline ValueType dereference_dispatch(follow_visitor, edge_t) const
    {
        return m_edge.value;
    }

    vertex_t m_lead;
    vertex_t m_follow;
    edge_storage< Graph, boost::is_same< ValueType, edge_t >::value > m_edge;
    FaceHandlesMap m_face_handles;
};

template < typename Graph, typename FaceHandlesMap, typename ValueType,
    typename VisitorType, typename Time >
class face_iterator< Graph, FaceHandlesMap, ValueType, both_sides, VisitorType,
    Time >
: public boost::iterator_facade< face_iterator< Graph, FaceHandlesMap,
                                     ValueType, both_sides, VisitorType, Time >,
      ValueType, boost::forward_traversal_tag, ValueType >
{
public:
    typedef face_iterator< Graph, FaceHandlesMap, ValueType, both_sides,
        VisitorType, Time >
        self;
    typedef typename graph_traits< Graph >::vertex_descriptor vertex_t;
    typedef typename FaceHandlesMap::value_type face_handle_t;

    face_iterator() {}

    face_iterator(face_handle_t anchor_handle, FaceHandlesMap face_handles)
    : first_itr(anchor_handle, face_handles, first_side())
    , second_itr(anchor_handle, face_handles, second_side())
    , first_is_active(true)
    , first_increment(true)
    {
    }

    face_iterator(vertex_t anchor, FaceHandlesMap face_handles)
    : first_itr(face_handles[anchor], face_handles, first_side())
    , second_itr(face_handles[anchor], face_handles, second_side())
    , first_is_active(true)
    , first_increment(true)
    {
    }

private:
    friend class boost::iterator_core_access;

    typedef face_iterator< Graph, FaceHandlesMap, ValueType, single_side,
        follow_visitor, Time >
        inner_itr_t;

    void increment()
    {
        if (first_increment)
        {
            ++first_itr;
            ++second_itr;
            first_increment = false;
        }
        else if (first_is_active)
            ++first_itr;
        else
            ++second_itr;
        first_is_active = !first_is_active;
    }

    bool equal(self const& other) const
    {
        // Want this iterator to be equal to the "end" iterator when at least
        // one of the iterators has reached the root of the current bicomp.
        // This isn't ideal, but it works.

        return (first_itr == other.first_itr || second_itr == other.second_itr);
    }

    ValueType dereference() const
    {
        return first_is_active ? *first_itr : *second_itr;
    }

    inner_itr_t first_itr;
    inner_itr_t second_itr;
    inner_itr_t face_end;
    bool first_is_active;
    bool first_increment;
};

} /* namespace boost */

#endif //__FACE_ITERATORS_HPP__

/* face_iterators.hpp
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
*/