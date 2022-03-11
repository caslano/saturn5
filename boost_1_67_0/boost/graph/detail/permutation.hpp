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