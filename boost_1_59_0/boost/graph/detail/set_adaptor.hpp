// (C) Copyright Jeremy Siek 2001.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SET_ADAPTOR_HPP
#define BOOST_SET_ADAPTOR_HPP

#include <set>
#include <boost/unordered_set.hpp>

namespace boost
{

template < class K, class C, class A, class T >
bool set_contains(const std::set< K, C, A >& s, const T& x)
{
    return s.find(x) != s.end();
}

template < class K, class H, class C, class A, class T >
bool set_contains(const boost::unordered_set< K, H, C, A >& s, const T& x)
{
    return s.find(x) != s.end();
}

template < class K, class C, class A >
bool set_equal(const std::set< K, C, A >& x, const std::set< K, C, A >& y)
{
    return x == y;
}

// Not the same as lexicographical_compare_3way applied to std::set.
// this is equivalent semantically to bitset::operator<()
template < class K, class C, class A >
int set_lex_order(const std::set< K, C, A >& x, const std::set< K, C, A >& y)
{
    typename std::set< K, C, A >::iterator xi = x.begin(), yi = y.begin(),
                                           xend = x.end(), yend = y.end();
    for (; xi != xend && yi != yend; ++xi, ++yi)
    {
        if (*xi < *yi)
            return 1;
        else if (*yi < *xi)
            return -1;
    }
    if (xi == xend)
        return (yi == yend) ? 0 : -1;
    else
        return 1;
}

template < class K, class C, class A > void set_clear(std::set< K, C, A >& x)
{
    x.clear();
}

template < class K, class C, class A >
bool set_empty(const std::set< K, C, A >& x)
{
    return x.empty();
}

template < class K, class C, class A, class T >
void set_insert(std::set< K, C, A >& x, const T& a)
{
    x.insert(a);
}

template < class K, class C, class A, class T >
void set_remove(std::set< K, C, A >& x, const T& a)
{
    x.erase(a);
}

template < class K, class C, class A >
void set_intersect(const std::set< K, C, A >& x, const std::set< K, C, A >& y,
    std::set< K, C, A >& z)
{
    z.clear();
    std::set_intersection(
        x.begin(), x.end(), y.begin(), y.end(), std::inserter(z));
}

template < class K, class C, class A >
void set_union(const std::set< K, C, A >& x, const std::set< K, C, A >& y,
    std::set< K, C, A >& z)
{
    z.clear();
    std::set_union(x.begin(), x.end(), y.begin(), y.end(), std::inserter(z));
}

template < class K, class C, class A >
void set_difference(const std::set< K, C, A >& x, const std::set< K, C, A >& y,
    std::set< K, C, A >& z)
{
    z.clear();
    std::set_difference(
        x.begin(), x.end(), y.begin(), y.end(), std::inserter(z, z.begin()));
}

template < class K, class C, class A >
bool set_subset(const std::set< K, C, A >& x, const std::set< K, C, A >& y)
{
    return std::includes(x.begin(), x.end(), y.begin(), y.end());
}

// Shit, can't implement this without knowing the size of the
// universe.
template < class K, class C, class A >
void set_compliment(const std::set< K, C, A >& /*x*/, std::set< K, C, A >& z)
{
    z.clear();
}

} // namespace boost

#endif // BOOST_SET_ADAPTOR_HPP

/* set_adaptor.hpp
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
*/