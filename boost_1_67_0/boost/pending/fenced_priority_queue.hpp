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