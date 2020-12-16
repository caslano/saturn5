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
ykQme57Ud8ukzSthWg5vX5ppk4r8kBknZtqfIt8P75RwTVtT5KUmzdKGNN/LO+v38vIzLA7CdJA++DTs2Igff3Vfg7mehXrc3e3jRlXVF2e+fSaJ/nZHY/5mYsyYMpEnEbb03fObwFjRptzuf1CdBuadq4HY72dtGZd1Acbul5N3XLOvSz3Rmy2jCvtjzPgzkdczbZ/lYu9Osk+WNlO6Z/wkJcbeG6XhZnTIqeaE08lqE9i+k28XMyWcPhLG6HjvOAS7TbxG3CNMO+xmsbtohzUKSgt7UNnf+CUc2cTI7EP1sOj9pHavv7Y+34Cm5BdX2N8Z+kv6a5v3yIvF3qiKPHBJvOfVNvFSiuxzuEXPwduXtEXsdc36RMtN3vaLC2tD33U71iyv627TdDVtI9M+U51VXh3XFFnCZ97pv9o+Ez+78LPA04e/PNZVM6jd1R97vPQt2Wahd4yVPv+hGQO6CLfF+pxfonweU1b3+Punuvv3T5n9LSjXyOxyLfWN6Ut0l1nt79PxzEUplhxXYOpg5mCiKWBvyTWbW1ao9ZZ84/K8e2E3/X2q19CUs+/FXsqqUY7APXLMWJdvRafEOlevbR8TToK5Dqlxx58XKbDcU+eZOjbVnLPEXb1Xxu+wV8Z9ss5Oh53nJ0ZM2LOx6b1PP/Tztu53/fHr6fxe6w1V75Xxz++VYTns9Xfm8jvfbfH5HWb/lvffPLgSc6PP7zU+v9f6/L7e5/cuOxy+Bdi/qbPl94X8XmD/5juL0ZGxuUX8/rOFm8/vofZvGfdx2OkZf5Ln83uY/VvGl6WiPwt7qf5+j99kKXsD6PwNnQOCm4yTaKT587PTmhsHw1zsxQAjYAcYBQfCWnAkjINFMB7OhnXgIlgfXg8bwFtgQ7gTJsInYBI8CpvA72FTGOZOA2wIT4HNYCvYGp4GU+DpsANsDdNgG9gHtoNTYQqcAzvAy2FHWAk7wQ2wM/wrPAs+Bc+GL8Au8APYDX4Pz4M/w+7QnV9HzZhzmQ8g+ZVkyV4TcvR3km44GHaAFbAnvBDOhUPhMjgMroDD4Wo4Am6EF8Hb4Ej4MLwYPgFz4T6YB9+E+fAoHA0dpGEMjIBF8Aw4AXZV+7lq7wEvhDmwFA6HZbAElsNFsAIuh5dAWSsJus/7kEPHpuqY41QHht/7oPtYgl4LWAnbwuVwOHwRToAvwQXwEFwJX4Zr4GvwVvgcvBvu1/M9AA/B5yHf60RvNNwBS+FOOB8+CC+HD8PVcBe8CT4CN6q/u+Gj8H74OHwa7oavwCfhZ/Ap+D3cC8OctNVhLfgqrA1fg43hzfB0uBGeC2+B6XATHAxvhblwMxwHt8CZ8Ha4Gm6Fm+GdcDu8Cz6g4T8Jt8E34D3wA3gvrEt+3wcbwu2wCbwGtobXwm5wBcyAq+Bw+Bc4Cl4Hp8M18Gp4PXwE3gCfhq/p9c0z489k7KBc3xowx7unkDs+OAu2U3tHtefB2fBKta+Bl8Gb4Hz4CJyr8WRYOqYJ5ms8EfAcjefP3GduXg2bqb2F2lPgNbAvvBbKWmiROv5HxyMRntyjS5FzyB5BneEM+Cd4GbwWzoc3wIXwVbgIHoGL4edwCfwOXg5/gVdAF2H/CcbCpbA2XAbrwSthIvwzPBMuh1nwajgO3gCL4Y1wErwJToM3w9lwPVwAN8DL4S1wGdwEl8O/whVwM1wNt8Ab4e1wPdwKN8E74RZ4N7wTboP3wnvhA/A++DC8Hz4OH4BPwZ3wWfggfAE+DF+Bu+Cb8FH4HnwMfgR3Q6euWdYKPgXbwL2wPdwHu8JnYDf4HOwJ98MM+DzMgi/AwfBv8GL4IhwND8Gx8GVYDF+F8+DrcBF8E66Fb8MN8F0=
*/