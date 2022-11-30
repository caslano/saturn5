//  (C) Copyright Jeremy Siek 2004
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_QUEUE_HPP
#define BOOST_QUEUE_HPP

#include <deque>
#include <algorithm>

namespace boost
{

template < class _Tp, class _Sequence = std::deque< _Tp > > class queue;

template < class _Tp, class _Seq >
inline bool operator==(const queue< _Tp, _Seq >&, const queue< _Tp, _Seq >&);

template < class _Tp, class _Seq >
inline bool operator<(const queue< _Tp, _Seq >&, const queue< _Tp, _Seq >&);

template < class _Tp, class _Sequence > class queue
{

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    template < class _Tp1, class _Seq1 >
    friend bool operator==(
        const queue< _Tp1, _Seq1 >&, const queue< _Tp1, _Seq1 >&);
    template < class _Tp1, class _Seq1 >
    friend bool operator<(
        const queue< _Tp1, _Seq1 >&, const queue< _Tp1, _Seq1 >&);
#endif
public:
    typedef typename _Sequence::value_type value_type;
    typedef typename _Sequence::size_type size_type;
    typedef _Sequence container_type;

    typedef typename _Sequence::reference reference;
    typedef typename _Sequence::const_reference const_reference;
#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
protected:
#endif
    _Sequence c;

public:
    queue() : c() {}
    explicit queue(const _Sequence& __c) : c(__c) {}

    bool empty() const { return c.empty(); }
    size_type size() const { return c.size(); }
    reference front() { return c.front(); }
    const_reference front() const { return c.front(); }
    reference top() { return c.front(); }
    const_reference top() const { return c.front(); }
    reference back() { return c.back(); }
    const_reference back() const { return c.back(); }
    void push(const value_type& __x) { c.push_back(__x); }
    void pop() { c.pop_front(); }

    void swap(queue& other)
    {
        using std::swap;
        swap(c, other.c);
    }
};

template < class _Tp, class _Sequence >
bool operator==(
    const queue< _Tp, _Sequence >& __x, const queue< _Tp, _Sequence >& __y)
{
    return __x.c == __y.c;
}

template < class _Tp, class _Sequence >
bool operator<(
    const queue< _Tp, _Sequence >& __x, const queue< _Tp, _Sequence >& __y)
{
    return __x.c < __y.c;
}

template < class _Tp, class _Sequence >
bool operator!=(
    const queue< _Tp, _Sequence >& __x, const queue< _Tp, _Sequence >& __y)
{
    return !(__x == __y);
}

template < class _Tp, class _Sequence >
bool operator>(
    const queue< _Tp, _Sequence >& __x, const queue< _Tp, _Sequence >& __y)
{
    return __y < __x;
}

template < class _Tp, class _Sequence >
bool operator<=(
    const queue< _Tp, _Sequence >& __x, const queue< _Tp, _Sequence >& __y)
{
    return !(__y < __x);
}

template < class _Tp, class _Sequence >
bool operator>=(
    const queue< _Tp, _Sequence >& __x, const queue< _Tp, _Sequence >& __y)
{
    return !(__x < __y);
}

template < class _Tp, class _Sequence >
inline void swap(queue< _Tp, _Sequence >& __x, queue< _Tp, _Sequence >& __y)
{
    __x.swap(__y);
}

} /* namespace boost */

#endif /* BOOST_QUEUE_HPP */

/* queue.hpp
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
*/