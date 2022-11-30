/*
 *  (C) Copyright Nick Thompson 2018.
 *  Use, modification and distribution are subject to the
 *  Boost Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef BOOST_INTEGER_EXTENDED_EUCLIDEAN_HPP
#define BOOST_INTEGER_EXTENDED_EUCLIDEAN_HPP
#include <limits>
#include <stdexcept>
#include <boost/throw_exception.hpp>
#include <boost/core/swap.hpp>
#include <boost/core/enable_if.hpp>

namespace boost { namespace integer {

// From "The Joy of Factoring", Algorithm 2.7, with a small optimization to remove tmps from Wikipedia.
// Solves mx + ny = gcd(m,n). Returns tuple with (gcd(m,n), x, y).

template<class Z>
struct euclidean_result_t
{
    Z gcd;
    Z x;
    Z y;
};

template<class Z>
typename boost::enable_if_c< std::numeric_limits< Z >::is_signed, euclidean_result_t< Z > >::type
extended_euclidean(Z m, Z n)
{
    if (m < 1 || n < 1)
    {
        BOOST_THROW_EXCEPTION(std::domain_error("extended_euclidean: arguments must be strictly positive"));
    }

    bool swapped = false;
    if (m < n)
    {
        swapped = true;
        boost::swap(m, n);
    }
    Z u0 = m;
    Z u1 = 1;
    Z u2 = 0;
    Z v0 = n;
    Z v1 = 0;
    Z v2 = 1;
    Z w0;
    Z w1;
    Z w2;
    while(v0 > 0)
    {
        Z q = u0/v0;
        w0 = u0 - q*v0;
        w1 = u1 - q*v1;
        w2 = u2 - q*v2;
        u0 = v0;
        u1 = v1;
        u2 = v2;
        v0 = w0;
        v1 = w1;
        v2 = w2;
    }

    euclidean_result_t< Z > result;
    result.gcd = u0;
    if (!swapped)
    {
        result.x = u1;
        result.y = u2;
    }
    else
    {
        result.x = u2;
        result.y = u1;
    }

    return result;
}

}}
#endif

/* extended_euclidean.hpp
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
*/