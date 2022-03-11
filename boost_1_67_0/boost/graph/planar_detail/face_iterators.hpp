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