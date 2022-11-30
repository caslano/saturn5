//  (C) Copyright Jeremiah Willcock 2004
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FENCED_PRIORITY_QUEUE_HPP
#define BOOST_FENCED_PRIORITY_QUEUE_HPP

#include <vector>
#include <queue>
#include <functional>
#include <boost/pending/queue.hpp>

// Fenced priority queue
// Jeremiah Willcock

// This class implements a fenced priority queue.  This is similar to
// a normal priority queue (sorts its members, and only returns the
// first), except that members cannot be sorted around a "fence" that
// can be placed into the buffer.  This fence is inserted using the
// fence() member function or (possibly) implicitly by the top() and
// pop() methods, and is removed automatically when the elements
// around it are popped.

// The implementation is as follows:  Q is an unsorted queue that
// contains the already-sorted list data, and PQ is a priority queue
// that contains new elements (since the last fence) that have yet to
// be sorted.  New elements are inserted into PQ, and a fence moves
// all elements in PQ into the back of Q in sorted order.  Elements
// are then popped from the front of Q, and if that is empty the front
// of PQ.

namespace boost
{

template < class T, class Compare = std::less< T >, bool implicit_fence = true,
    class Buffer = boost::queue< T > >
class fenced_priority_queue
{
public:
    typedef T value_type;
    typedef typename Buffer::size_type size_type;

    fenced_priority_queue(const Compare _comp = Compare()) : PQ(_comp) {}

    void push(const T& data);
    void pop(void);
    T& top(void);
    const T& top(void) const;
    size_type size(void) const;
    bool empty(void) const;
    void fence(void);

private:
    void fence(void) const;

    // let them mutable to allow const version of top and the same
    // semantics with non-constant version. Rich Lee
    mutable std::priority_queue< T, std::vector< T >, Compare > PQ;
    mutable Buffer Q;
};

template < class T, class Compare, bool implicit_fence, class Buffer >
inline void fenced_priority_queue< T, Compare, implicit_fence, Buffer >::push(
    const T& t)
{
    // Push a new element after the last fence.  This puts it into the
    // priority queue to be sorted with all other elements in its
    // partition.
    PQ.push(t);
}

template < class T, class Compare, bool implicit_fence, class Buffer >
inline void fenced_priority_queue< T, Compare, implicit_fence, Buffer >::pop(
    void)
{
    // Pop one element from the front of the queue.  Removes from the
    // already-sorted part of the queue if it is non-empty, otherwise
    // removes from the new-element priority queue.  Runs an implicit
    // "fence" operation if the implicit_fence template argument is
    // true.
    if (implicit_fence)
        fence();
    if (!Q.empty())
        Q.pop();
    else
        PQ.pop();
}

template < class T, class Compare, bool implicit_fence, class Buffer >
inline T& fenced_priority_queue< T, Compare, implicit_fence, Buffer >::top(void)
{
    // Get the top element from the queue.  This element comes from Q if
    // possible, otherwise from PQ.  Causes an implicit "fence"
    // operation if the implicit_fence template argument is true.
    if (implicit_fence)
        fence();
    if (!Q.empty())
        return Q.top();
    else
        // std::priority_queue only have const version of top. Rich Lee
        return const_cast< T& >(PQ.top());
}

template < class T, class Compare, bool implicit_fence, class Buffer >
inline const T&
fenced_priority_queue< T, Compare, implicit_fence, Buffer >::top(void) const
{
    if (implicit_fence)
        fence();
    if (!Q.empty())
        return Q.top();
    else
        return PQ.top();
}

template < class T, class Compare, bool implicit_fence, class Buffer >
inline typename fenced_priority_queue< T, Compare, implicit_fence,
    Buffer >::size_type
fenced_priority_queue< T, Compare, implicit_fence, Buffer >::size(void) const
{
    // Returns the size of the queue (both parts together).
    return Q.size() + PQ.size();
}

template < class T, class Compare, bool implicit_fence, class Buffer >
inline bool fenced_priority_queue< T, Compare, implicit_fence, Buffer >::empty(
    void) const
{
    // Returns if the queue is empty, i.e. both parts are empty.
    return Q.empty() && PQ.empty();
}

template < class T, class Compare, bool implicit_fence, class Buffer >
inline void fenced_priority_queue< T, Compare, implicit_fence, Buffer >::fence(
    void)
{
    // Perform a fence operation.  Remove elements from PQ in sorted
    // order and insert them in the back of Q.
    while (!PQ.empty())
    {
        Q.push(PQ.top());
        PQ.pop();
    }
}
template < class T, class Compare, bool implicit_fence, class Buffer >
inline void fenced_priority_queue< T, Compare, implicit_fence, Buffer >::fence(
    void) const
{
    // Perform a fence operation.  Remove elements from PQ in sorted
    // order and insert them in the back of Q.
    while (!PQ.empty())
    {
        Q.push(PQ.top());
        PQ.pop();
    }
}

}
#endif /* BOOST_FENCED_PRIORITY_QUEUE_HPP */

/* fenced_priority_queue.hpp
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
*/