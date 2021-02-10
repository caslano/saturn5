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
75LyVyuYeWaWlxoyLKg3tbq0zm4qRtQvQ5AgCqLL+TuKDmGT050i+gw+txGPy2cdCsUFXQ10ss4NAiPkWCSTR3+lre6j9NWqGyy6ectq9svj2S/d3cYawTe8OfdhFlvZJGyjdAvI/8IX8pa/cHfjCRYNceOZ3Wn5jNUddY/6Zt8NSLBASGv83hnsGaMTVXGMRsXifdNLgzcnvK3M40c0dTej4O/qpcabUzadg6nwqGDKTvaOHulXQVUy861oMypT8PdML3Ymnyi0YzgSXXVHpzq/EoPB58msjydKcJVSq/K2SwVyE+GGbs3Mc7HBZIEUkGw0GVSSwHfy2mj9TgBK40fN4U2HVFnnpNfq04qvUI5tNke6MF3oX6kb11ZorhKCrxkIGJHFL3X72MY6VbbYEcXESnrKFki0EQskTtEJ3QQW6DNeXhyF8sIrdcRN1oKfeJ08oVF2NU9CGcxUdUWlLHi0/zTZabJe90Rlkf/WGdK7q8SLDgW/1NtQA4KXOAuMi1Wb1rOQLVq6KuTTxXqNHOeaSpiS1OMxwLTToZtErUYymGV4xqvvCLU1a9N1THeYa6BRzwqXCw33vXpXL25uPBkmcYA7938AUEsDBAoAAAAIAC1nSlJzOZ77EAIAAJIEAAAeAAkAY3VybC1t
*/