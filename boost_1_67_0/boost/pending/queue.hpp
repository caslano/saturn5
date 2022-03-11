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