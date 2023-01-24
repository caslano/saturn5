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
WKAU0EFF5d954Z1IZWg11bJDuUtFCc7BNiFRpnoLP0N7hasc737XY1UTrXdTnuOVYa13Ub4BMq0Zna19+aGotRLF8v1mSGD7H572lKjMffwzpzlHqP7M6THjRusxQHJuRCdeCopS3o0AvaGWnaR9cltXteFyRvwM17JzWIogbIp5pO1i7WDLUSGvJYavkmhdgupdg+ZSjfrN3MArHh//O6/lLxzP6Cp5HfDfy20/gyw/cXqtqiRvPWZFvz4m5McePKSuWB6mS2VYmuLlILfmNwmgMgm8VsYrP6xCGuZSKBYrw+judd2TO+pQjpvRFC341w53Hm2T7f9wPySVo+jeGfRQEudoeZzmNKD9hGl3LjeiBDrnRF/T/YW5AuFzUc4Lwzvqyr37Kxo7qoZxk5uoQecU1+nOgTnaDJqdTMeXy1vDZjFIZGal8pIl+ZaTQWDUKBDXNY4LmG9MF+Bmstj/sPM5bmMuxmrHN22k5I80pl68IDNGYCs1En2xAdCxBvDJOqHxKW5ZZiG4X26voWFuNYG9y7wqPPbPvnShDS7WMvjB64ODF9Ivp/MMe7cu/JKLSTv+Ew/AjlSM1RYij6WczxUf4aE3TS4akLzqBrXPQszlgsSuOkmv+JV3vXhP1ZuLx0JS5Ox/7e1U9rZq0zQaG+mkT1jyGwBsHUoKg+CEcGVz2TqbNMmI81fc4/j5NIeuj7R956tDI961TEfs
*/