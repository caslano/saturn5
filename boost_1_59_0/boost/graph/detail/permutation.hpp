// (C) Copyright Jeremy Siek 2001.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PERMUTATION_HPP
#define BOOST_PERMUTATION_HPP

#include <vector>
#include <memory>
#include <functional>
#include <algorithm>
#include <boost/graph/detail/shadow_iterator.hpp>

namespace boost
{

template < class Iter1, class Iter2 >
void permute_serial(Iter1 permuter, Iter1 last, Iter2 result)
{
#ifdef BOOST_NO_STD_ITERATOR_TRAITS
    typedef std::ptrdiff_t D :
#else
    typedef typename std::iterator_traits< Iter1 >::difference_type D;
#endif

        D n
        = 0;
    while (permuter != last)
    {
        std::swap(result[n], result[*permuter]);
        ++n;
        ++permuter;
    }
}

template < class InIter, class RandIterP, class RandIterR >
void permute_copy(InIter first, InIter last, RandIterP p, RandIterR result)
{
#ifdef BOOST_NO_STD_ITERATOR_TRAITS
    typedef std::ptrdiff_t i = 0;
#else
    typename std::iterator_traits< RandIterP >::difference_type i = 0;
#endif
    for (; first != last; ++first, ++i)
        result[p[i]] = *first;
}

namespace detail
{

    template < class RandIter, class RandIterPerm, class D, class T >
    void permute_helper(RandIter first, RandIter last, RandIterPerm p, D, T)
    {
        D i = 0, pi, n = last - first, cycle_start;
        T tmp;
        std::vector< int > visited(n, false);

        while (i != n)
        { // continue until all elements have been processed
            cycle_start = i;
            tmp = first[i];
            do
            { // walk around a cycle
                pi = p[i];
                visited[pi] = true;
                std::swap(tmp, first[pi]);
                i = pi;
            } while (i != cycle_start);

            // find the next cycle
            for (i = 0; i < n; ++i)
                if (visited[i] == false)
                    break;
        }
    }

} // namespace detail

template < class RandIter, class RandIterPerm >
void permute(RandIter first, RandIter last, RandIterPerm p)
{
    detail::permute_helper(first, last, p, last - first, *first);
}

// Knuth 1.3.3, Vol. 1 p 176
// modified for zero-based arrays
// time complexity?
//
// WARNING: T must be a signed integer!
template < class PermIter > void invert_permutation(PermIter X, PermIter Xend)
{
#ifdef BOOST_NO_STD_ITERATOR_TRAITS
    typedef std::ptrdiff_t T :
#else
    typedef typename std::iterator_traits< PermIter >::value_type T;
#endif
        T n
        = Xend - X;
    T m = n;
    T j = -1;

    while (m > 0)
    {
        T i = X[m - 1] + 1;
        if (i > 0)
        {
            do
            {
                X[m - 1] = j - 1;
                j = -m;
                m = i;
                i = X[m - 1] + 1;
            } while (i > 0);
            i = j;
        }
        X[m - 1] = -i - 1;
        --m;
    }
}

// Takes a "normal" permutation array (and its inverse), and turns it
// into a BLAS-style permutation array (which can be thought of as a
// serialized permutation).
template < class Iter1, class Iter2, class Iter3 >
inline void serialize_permutation(Iter1 q, Iter1 q_end, Iter2 q_inv, Iter3 p)
{
#ifdef BOOST_NO_STD_ITERATOR_TRAITS
    typedef std::ptrdiff_t P1;
    typedef std::ptrdiff_t P2;
    typedef std::ptrdiff_t D;
#else
    typedef typename std::iterator_traits< Iter1 >::value_type P1;
    typedef typename std::iterator_traits< Iter2 >::value_type P2;
    typedef typename std::iterator_traits< Iter1 >::difference_type D;
#endif
    D n = q_end - q;
    for (D i = 0; i < n; ++i)
    {
        P1 qi = q[i];
        P2 qii = q_inv[i];
        *p++ = qii;
        std::swap(q[i], q[qii]);
        std::swap(q_inv[i], q_inv[qi]);
    }
}

// Not used anymore, leaving it here for future reference.
template < typename Iter, typename Compare >
void merge_sort(Iter first, Iter last, Compare cmp)
{
    if (first + 1 < last)
    {
        Iter mid = first + (last - first) / 2;
        merge_sort(first, mid, cmp);
        merge_sort(mid, last, cmp);
        std::inplace_merge(first, mid, last, cmp);
    }
}

// time: N log N + 3N + ?
// space: 2N
template < class Iter, class IterP, class Cmp, class Alloc >
inline void sortp(Iter first, Iter last, IterP p, Cmp cmp, Alloc alloc)
{
    typedef typename std::iterator_traits< IterP >::value_type P;
    typedef typename std::iterator_traits< IterP >::difference_type D;
    D n = last - first;
    std::vector< P, Alloc > q(n);
    for (D i = 0; i < n; ++i)
        q[i] = i;
    std::sort(make_shadow_iter(first, q.begin()),
        make_shadow_iter(last, q.end()), shadow_cmp< Cmp >(cmp));
    invert_permutation(q.begin(), q.end());
    std::copy(q.begin(), q.end(), p);
}

template < class Iter, class IterP, class Cmp >
inline void sortp(Iter first, Iter last, IterP p, Cmp cmp)
{
    typedef typename std::iterator_traits< IterP >::value_type P;
    sortp(first, last, p, cmp, std::allocator< P >());
}

template < class Iter, class IterP >
inline void sortp(Iter first, Iter last, IterP p)
{
    typedef typename std::iterator_traits< Iter >::value_type T;
    typedef typename std::iterator_traits< IterP >::value_type P;
    sortp(first, last, p, std::less< T >(), std::allocator< P >());
}

template < class Iter, class IterP, class Cmp, class Alloc >
inline void sortv(Iter first, Iter last, IterP p, Cmp cmp, Alloc alloc)
{
    typedef typename std::iterator_traits< IterP >::value_type P;
    typedef typename std::iterator_traits< IterP >::difference_type D;
    D n = last - first;
    std::vector< P, Alloc > q(n), q_inv(n);
    for (D i = 0; i < n; ++i)
        q_inv[i] = i;
    std::sort(make_shadow_iter(first, q_inv.begin()),
        make_shadow_iter(last, q_inv.end()), shadow_cmp< Cmp >(cmp));
    std::copy(q_inv, q_inv.end(), q.begin());
    invert_permutation(q.begin(), q.end());
    serialize_permutation(q.begin(), q.end(), q_inv.end(), p);
}

} // namespace boost

#endif // BOOST_PERMUTATION_HPP

/* permutation.hpp
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
*/