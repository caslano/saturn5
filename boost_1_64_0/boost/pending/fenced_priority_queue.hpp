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
CFn623YZiyELX2jHe0z0p/ZC5dI21d4VEk/J1kg7VB99X+qszg+qxNbUfL4JsmNqrv2J9Jvaxz8r+lNr+RrpD+Wfd0mdn7TjvSJ1uceWvSpp1RjcJ/pTejko+amzh9+ILN1O+3vRqTp/aRa7WqfO/zr6SJ3/Sf3W2vE+8vn6GWi7pFVrqbMiU+uIzyS/39tlfCl1VmtR706w09m2zK8T6qz2Ad0gC1B74isgC59q17k3ZCVqngmUMpRPHAxZndpHXQNZuprfQiFraLJlEVLuEnX+1wk6UOcl35J4v7LTxkg8tVaJF5nyG2Mhq1BnubdKfg12GSmSVp1fTRP9RdiyOyD742m7P2ZL20bbsmxJ+1s7bZ6U8QNbNg8y51V1/ic67WTHK4YsSJ23L4IsX9npo9K/K2zZ41Luzer8T/pIfSdZDVn1Plv2lJTrZ8uegez3aj+4UfJ7yI63RfRSact+BlmL8vfPS1p1tr4TstiL6vxPdLpVnf+Jnaq90C+lfh52/Q6IXtQ+5RBk3/K24/1OdKX2Gm9J2nZb1iLlnrZlJ6Q/fmrLPhT9vWTL/iA6eMCWnZE+f8Ru73nItqq1wBeQOWqv5tUZelFj0BcyR53d+EOWf7U6/5O0yndeCVmF0kF/yBpUuYOkDDV/XA1ZiWrvtZAF/dyWhUtatfYeAVnLK7bsJpGpueI7nb9+rhIHWbjaGyRKXdT6dILEU+vEyZDFbLF1kCo6eNCON0PSqnl6lqSdYaedI/EesGW5kp9q21zI0tX+7T7IAtS52YPSR/52XUqkbSq/JZDVqbl7mchUfzwpup9s62qV9K9Ku1bKUPGehqyqhzr/gyxUjaPN0udf2uVuk3Y8asueEx18387vRbHTRHX+JzqdZMv2iE7VefFr0h/qDO/X0jalqwbJT51JHxZbU7I3IUtWdvWO6PQtW3ZcdKXm35OSnzp/+RiyNOWb/iR1VvPMuc5fXzNcFL2o/YenL/Ssvjd29kX9DtjldvVFWjXvd4esutZuRy/IqlS/9ZO019iyIMiS1RnKEF/pSzveMMgeVGe010kZKl4kZL9WNhTtC51622m/LW1bo87/IAvvacdLEL0E2fHGQ9ai1iCTpC7KT94m7VD73zSpizoPyxDZI3YZd4pelF+7GzJHzVH50g7lOwtFpvZ5D0BWoXznw9IfyoeVSnvVN4elEu+3drlPSP1esnW1ErKA39hpKyU/tc5ZL/VT30h/IPpT30l+LOWqtFulHaqM7VLuflv2gvSRsquXRX8P2vHqJK0aW3ulP9Se81eSn+q3NyB7SK0tGmUsdLXjHZH2ttplvO379T3Oe2J/ar/VKmlVe09JXb5t5/dHkY2z430qadW66YL0W4bdlx5+kKnv550gCzpiyy7z+/p8GQBZlTqH6wlZvlr/9ZX81LeigZCVzLPjBYtsqC0bCplTbMuGQxZwky37JmTV6jwiCrLYM+r8T+L9UJ3/Sf3Uuv0WyOrUmiYJsp9/YqedKGnVWelU0YGaU26XOvvYsnTIwq+wy82S/jhjy+6S/BbZae8VmZqTC6Q/1By1QHSqdP+QtE19M3wEsga1xy6DLP0VW7Zc9HeXOv8THay2Zd+DrF310TrIYu6327FBdKD0/CNpm1oj/VTqUm+nrZZy1Xn2jg4923V+SXSqzqV+DtmVavzWS51nqvM/yDpdsOO9Ljq9zM7vt5JWfRtrgsxRc+1Rv69/S3hXdK/G7wfSR9+zy22DrEKtr05Lf6i17SeQTVX9+zlkf1LtcLqgzurOmA9kJY22rAtk4erb9uWQ5b9n59cDMk+l0z6QJY+z6zwAsgBVv6sgq1NnVSFSP2WTYV2+fu/hesh2fmk=
*/