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
6X+zjMsHy8jGPGW6YAZ/P7AKgY+KNgqDA8UggdzgLbL8FL/wQ3MMmBspyq1icAhnxQ5OvtHAy5FpLyLlQM/2Mp7dvJe7gcx4LpmnGE//xV5/ZwqXqSNSVkoyCvoVaUGKFTeppaPVxhmL28jMPWjnXwKt8HJXxVyNR36WNmtT0Cp6A1CY5r4JwpKVYnFxE7fvt9D4ghTQmO8+vrEnm82R3PQ621824a1l9G49O2rmb4DyuxYgwe7CHc30ZkjM3KEHhf/adoEcq8X1OwBYIkBpQVHpxOeslBSEGppKdpUao8HRykpJBUcsK2UGPMfowBL4UlLpYzhFmZWSGF75k7Y8JcVn2o9Z6BPQbjD2rXT6R4D/rTl0F64RWpwyiRzO9WX4qV6c6n8sJdkgTjw4FYFbDcDVQJbsHTEIHBmG7dpOz6V3QWJwDDSYvB+TKB5GEhzC72+C+7eGUCdu+5uDrML5OXP1x2h/ASmGXQceQwaZJoW2s/oUvj4lsMPGUJsDM2IDP5uIrtSlCltjzPJs7/ab+Jv9t0DqlOZtl7GurbH78RIc5Y14CXb8GBDRkhfMARolwQDCl5KUSf9yjFmaiTgmX5CSTM5TFjiFd/Tv4BWGIfalqqKGRzpABovHjQjTZw8xk/DGnP5gQ31TwcrZjtPPcPPj35R5oaARqPgjXYiKRQ142vFbNwdnZFddHeKbWHV1mC+h6urN0NdcXS7G
*/