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
fXwpdH7dt0PHVz9m+78VSi8KqPeztVft6Vn1Nf8M9ednoXTLLO3ndMdtpfrSHUpnzA6lh5q0xx3+Ns56pqaHju/eGUq3X+hvHksdp18oH8d9do/90L7mXRAI1TfRcX6berjf9pxu/nHqyXdD55/u0h70G5OfC13fUaK8CvQvyv/BlcpJOa7+hvr2hP5tq34iTXlVKIdix3Ov7VSOS9X/mXH+xi9crvax+Qeh+9bPdRzD/6+e1KhQ/h/ofx4OpTveoL/9rXasvzz0SOj8lfqxyU/ory623eFyXtbfzg+dn9g7JpRvknK5z3E8EkoXvEE/n6/+ab+bHtY/aNf5pcq7U/2pCp3f2qS/3h5Kx12hvm/QDtS7e7TX+c2h48WfVe+/rD07bhs71PvpY/XL+vFWfws7oFz79Hvj1M/HQuk9+p3pN2jHE0PHe+7Vj2i3d2qvC/aFjnccCYTGRXvde5q/Od3rPPAZ+6s9LfiHeniG7b1XOZWrZ086bhcqb+exR5PUk5RQet2D/lZZf3z7ZfqlmaF059v9jetrx4bkv0q/Waadv+Q8PN/ypo4N1TNR+/+a+SrUjz/YzkdD5Y+L0p9PUw+qQ+ev1272qcdlzcqr3nlCua/4Zuj4rvudT9WL8Z9Vzs6XO53nC3foh3eZRusnpuunv+U4Fjmv6l/KXlbet4TS7c+F8s1/jfNxrH76ScdLuc97s/qm3PJfVE9XKhfT+d9Uj6bb/0f1q5d5vEs9/7Pz3jnqQZn291XzqYczt2o/jaHrd+unbl9rXHD22FB5Zzr/PuT4zFFef9WfGn8dqNX+znceMv9454m5pld+0HnmCuVrvef9xnn5dVGh8rTz/D36uTHOE6frN42btji+Vz+kHp8VSu9+neM9ZmyoXu1k4mF/0/1Nx+l5fxtsnLHofvuRZ7y0xXEocD4Z1s7Vg0LL37Q5dDy+SD+41X7+3Xao53f82XGYo99+1varx9dfqpy0qyP6vcPWc+dC9Xmf5Y7Tz8SrH8+rX5eF9dN4cZ5xcIL9HtCey/VX8c47Y50Pdmnfjxg3fd/6LteOL1ceXwzlW32VfuVdjluK7be83Tc5L6kfi96mHCx3/una42udB87XP6vPO9uch9+k3VeqX/nOu7v1i2eE0unF9q9dvbUfsx9T77r1K+pF2SXa/+nK72/OCw2Of639DPuvxz0uC6UX3WJ9ynev+px7tnHMBMdxm3azynkoXvl/xHl1tnI8TT/bab8tJ+rt2t8K/e5brO/nxudrQuk96x2vfO1zs3ryI/V7pferhxPPUl+/qz3qVwrt99bXadf6wRmJymVIu1UvdtcbHz7s9THqyVkhua3botx+HDq/vkR7vFF5G3egfqH7KtWT1bYv2euO6+KAcZjrvsnel/te9eIh/af9vCPa+ffn6ts/jP/2Ko+VoePd+pPnG/THpvP0e1GroowPtfsttst+rHif9Y933lZvNhY4vvqfsnnm/6X2W2F8N8frpnMd962XKSfH+dlfKodH9I+Ow4wa7d1yp7qumfUa+7/N9cEc+7fP+T9e//oX5a7eXL3R+W2R/brPef4zzjtLtVfj4KWz1TP7ufkr+lfnlb0zQ+dnZbveUb/vOVd56S+vc37cpb/Pv9b41fbccSAqlP9R++26c9ylHs9TL23X3RuVi+vzPZO9f7H2sk0/kqSfrwpdz+9Qbq/XX+ifczvUS9t/5K/Ou9pzYZpxQ5d+xXT7+errA9rP1/W35j/8bfXwH/rR7ytfry+a7zwxoJ14fr5xWNlZtkf53hnjvK9eznQdGhWnP52uvT6nf9QPTwzXd5rlux66rsF5YdDyzbfxZvvfrX+LVW8mWc6d6oXxx9U=
*/