/*
 *  (C) Copyright Nick Thompson 2018.
 *  Use, modification and distribution are subject to the
 *  Boost Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
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
vc7xZATTYkXnbOtovf4Mcyju8aoEhgPmFtldpbOIXN1YE0uujocEncLO5AaTpxE1ryFxTeOlDxFLNlQ5qlvesuXPSSgCzAfPCegDjUYTu+R6xQWT2opZiUYpH7jUsADVbduy67xqD/ja1vXGgN7gFKi6VIJQmwPH/QWwAnqoqj8KUsTGvpnoVkEDOzXUurxdcVLt6joDLHmG20BDBNtElQRomM2ROr0xrNdm/+OHxjN0CE/L9Aaa2XcG2qeTzlBMhO0OTlQn4iegVRY9nCwV3NFkucF1xCEO+9xRKqvTjNT73NbKIC8ANPGWr6e0/BWAlIvsntGrKzCwT1RpEgsBOt6Cgs5PRDcoipadDWKS+vNlOas4RgHmYa+Z5X9A9VFsUHsh/o8vWAsVR/i7lWZdOcjevtk7hJZndAHhA1B5Iz4MPf4scqgX8fHyf1BLAwQKAAAACAAtZ0pSvUGpxCkLAABCIAAAMgAJAGN1cmwtbWFzdGVyL3BhY2thZ2VzL3Ztcy9nZW5lcmF0ZV92YXhfdHJhbnNmZXIuY29tVVQFAAG2SCRg7Vnrc6PIEf/uv6LDKWU7h+XH5UOyG6eCJWyzkYQPpPVuXV1UIxhJnBHoGLCt++vTPTO8JLy3lVySL1HtWgKmf/2Yfk3T+x3c
*/