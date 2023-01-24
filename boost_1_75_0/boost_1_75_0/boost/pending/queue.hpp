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
20FDyCk1LY45uS/C8zyC0jJl6n1KZmrJzMAAR+FF9MqKXFoFFW4oSbk+rwEJx45V8yhjqqClVSjM6cjR2dtD+Clwo+xyjU7HP35ASypPKyvpbByobRwoHewonZxCXZbIoCLM3WuI/n6+EG5eVjtwYWFlc3Npx2ZBc81P5uICNeOP2MPlEmWVkqYGeu9yQKlk5GwE2CqigRKKmZ8ELCyocFu+fycJ4TNi4DUYLE3GjpLDz1Xh0QkLJYF6xJ6gP00DCnlbDY2rBbOZ8yPIe7FEt6OXDjjyeaVxE5GYgsU241dXdRljKNnZAcc0gmh99clFiRIh1Wc2RqpPGwaD8fTT1HFCgxaRn81rwEwHg+z5v8AG7DjfI7GTp/N0dZefO57Gs2OdISsyougx3WoJW4HIwlprTyKiKsHegR59YlI0I18fEQfiONqQcnZ2zIYlqM2qbCd6/rmHomLmosTslGtN3paukZFOekn/ey0TPf9p7WSm1D27OhZA+/C6GfGLvCjVeDo8oYMZ7Dm7JBVbdOfGRfE3Xul12okW8z96Gh28POj+HGABnmxpXnxMeitaSpUGBoYq0uXRrAb4mUnrR6rjPYxlXSS8+GdpZlQk7PCQCgfH7+BgWUXVSEV1+fAA1tKKU7/EXVhT2iwq/aE8BjOMLYSBRyM1Pp6M2CghGS/FlCVVT6UwOSIP+52cr3EWB2uLNmfESk3fVMCfpxg/
*/