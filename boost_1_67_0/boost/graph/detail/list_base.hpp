//=======================================================================
// Copyright 2002 Indiana University.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_LIST_BASE_HPP
#define BOOST_LIST_BASE_HPP

#include <boost/iterator_adaptors.hpp>

// Perhaps this should go through formal review, and move to <boost/>.

/*
  An alternate interface idea:
    Extend the std::list functionality by creating remove/insert
    functions that do not require the container object!
 */

namespace boost
{
namespace detail
{

    //=========================================================================
    // Linked-List Generic Implementation Functions

    template < class Node, class Next >
    inline Node slist_insert_after(Node pos, Node x, Next next)
    {
        next(x) = next(pos);
        next(pos) = x;
        return x;
    }

    // return next(pos) or next(next(pos)) ?
    template < class Node, class Next >
    inline Node slist_remove_after(Node pos, Next next)
    {
        Node n = next(pos);
        next(pos) = next(n);
        return n;
    }

    template < class Node, class Next >
    inline Node slist_remove_range(Node before_first, Node last, Next next)
    {
        next(before_first) = last;
        return last;
    }

    template < class Node, class Next >
    inline Node slist_previous(Node head, Node x, Node empty, Next next)
    {
        while (head != empty && next(head) != x)
            head = next(head);
        return head;
    }

    template < class Node, class Next >
    inline void slist_splice_after(
        Node pos, Node before_first, Node before_last, Next next)
    {
        if (pos != before_first && pos != before_last)
        {
            Node first = next(before_first);
            Node after = next(pos);
            next(before_first) = next(before_last);
            next(pos) = first;
            next(before_last) = after;
        }
    }

    template < class Node, class Next >
    inline Node slist_reverse(Node node, Node empty, Next next)
    {
        Node result = node;
        node = next(node);
        next(result) = empty;
        while (node)
        {
            Node next = next(node);
            next(node) = result;
            result = node;
            node = next;
        }
        return result;
    }

    template < class Node, class Next >
    inline std::size_t slist_size(Node head, Node empty, Next next)
    {
        std::size_t s = 0;
        for (; head != empty; head = next(head))
            ++s;
        return s;
    }

    template < class Next, class Data > class slist_iterator_policies
    {
    public:
        explicit slist_iterator_policies(const Next& n, const Data& d)
        : m_next(n), m_data(d)
        {
        }

        template < class Reference, class Node >
        Reference dereference(type< Reference >, const Node& x) const
        {
            return m_data(x);
        }

        template < class Node > void increment(Node& x) const { x = m_next(x); }

        template < class Node > bool equal(Node& x, Node& y) const
        {
            return x == y;
        }

    protected:
        Next m_next;
        Data m_data;
    };

    //===========================================================================
    // Doubly-Linked List Generic Implementation Functions

    template < class Node, class Next, class Prev >
    inline void dlist_insert_before(Node pos, Node x, Next next, Prev prev)
    {
        next(x) = pos;
        prev(x) = prev(pos);
        next(prev(pos)) = x;
        prev(pos) = x;
    }

    template < class Node, class Next, class Prev >
    void dlist_remove(Node pos, Next next, Prev prev)
    {
        Node next_node = next(pos);
        Node prev_node = prev(pos);
        next(prev_node) = next_node;
        prev(next_node) = prev_node;
    }

    // This deletes every node in the list except the
    // sentinel node.
    template < class Node, class Delete >
    inline void dlist_clear(Node sentinel, Delete del)
    {
        Node i, tmp;
        i = next(sentinel);
        while (i != sentinel)
        {
            tmp = i;
            i = next(i);
            del(tmp);
        }
    }

    template < class Node > inline bool dlist_empty(Node dummy)
    {
        return next(dummy) == dummy;
    }

    template < class Node, class Next, class Prev >
    void dlist_transfer(Node pos, Node first, Node last, Next next, Prev prev)
    {
        if (pos != last)
        {
            // Remove [first,last) from its old position
            next(prev(last)) = pos;
            next(prev(first)) = last;
            next(prev(pos)) = first;

            // Splice [first,last) into its new position
            Node tmp = prev(pos);
            prev(pos) = prev(last);
            prev(last) = prev(first);
            prev(first) = tmp;
        }
    }

    template < class Next, class Prev, class Data >
    class dlist_iterator_policies : public slist_iterator_policies< Next, Data >
    {
        typedef slist_iterator_policies< Next, Data > Base;

    public:
        template < class Node > void decrement(Node& x) const { x = m_prev(x); }

        dlist_iterator_policies(Next n, Prev p, Data d) : Base(n, d), m_prev(p)
        {
        }

    protected:
        Prev m_prev;
    };

} // namespace detail
} // namespace boost

#endif // BOOST_LIST_BASE_HPP

/* list_base.hpp
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
*/