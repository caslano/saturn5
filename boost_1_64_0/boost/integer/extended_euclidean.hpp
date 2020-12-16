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
eyEdiqAm2mEwZmAtDuMm3sG9T92QEjlRHFXRCD0wBBMxH6uxDQdxDvfxAd4D8jBSITfKoi7aoz/GYzaWYzOO4w7ewXrI3B1xkRzpkR1FUAE10QLdMRgTMRcrsB67cAp38RnmEe2GxEiPPCiH6miEtuiBwZiIFdiLy7iL15CPOQeSIiuKoQa6YAzmYA324SY+IHhCTkIGZEVhVERDtENfTMBsLMEG7MFRXMNL/ET4lLEFqZAfVVAXzdAb47AQW3Ect/EB/jOOQ0YURjW0wxDMxiIsw3rswFFcwBXcw3N8gfOccyEm4iMlCqAWOmAIZmIJNuIAzuIGXsB6wX0dEiENcqMkKqM9RmIxtuE4buETor/kmiE3yqAeOmE05mEjDuAMbuE5viPyiuOQHnlRAQ3QHn0xCrOwEGuwD0dxE+8hX5NfERtJkA65UBQVURdt0B2DMR6rcAA38RZR3nAsCqI+BmE+1uMgLuIRPkC/pa8gDQqgAuqhLYZhFtbjAG7gDcJ35F0URX20Qz9MwF9YjxO4iy8I/yV2kRNV0RGTsAa7cRr38A1R3nPfgRwoidroiEGYgdXYg3N4iI/wPjDnRXLkREk0QA+MxhysxQFcxUvIj+QlpEReVERjdMNkrMJh3MB7xPjEcwEURzOMwnLsxBk8g/zMOZEGhVEZTdENozEbq7EPZ3EH72F/4T4DSZEDxVEHnTEaC7ELl/AS1lfyARIjI4qjGlqjL2ZgPQ7jDj4g6jfGbGRAQdRDN4zCLKzCbpzGa4jvlAnJkB3F0QCdMBDTsR6n8ArqB3VHehRAVbRADwzHLKzEDhzDJTzEZ0R+Mq4gE/KjMpqiO6ZgEbbhOO7iDWx+qP4fJEYWlEQNtEFvjMI8rMVuXMJjfEJgx7HiIhVyoRRqoR36YTz+wlrsxnFcxVP8QETEseIgGbKgAMqiHtqiL0ZjLlZjL07hOp7hB2LKOFZq5EN51EErDMIEzMRSbMMZPMAnRFNxrKTIjupohq6YhIXYglN4gM8wbPIbGymRGyVQE+0xCguxHZfwBq6mXZAXFdARQzEXm3EWz6FMHCsWUqEAqqEB2mEgpmINDuAy3sB1aXfkRmnURldMxnocwBW8gevFsX5HKuRFBTRGL4zAQmzCKTzED8Tx41gZURLNMBAzsQfn8QoyiGMlQEE0Rg9MxEqcwQu4IZ9BJpREA3THJCzFVhzGZbyAFSEWkQhZUQJNMQhzsRU38AZ+FGIWeVANHTASC7EDl/AS//8B4C9IgRyogg4YiznYgAO4gHv4CBktjhUDCZEBRVAHLdAJo7AQO3Ea9/ARfnTiEYmRA6XREO3QH+MwH1txEg/xCTJGHCs6EiMLSqMW2mAQJmAJtuAkHuELov5C+yI9CqAymqAbxmIhtuEkbuMdYrCxX1qUQBP0whQsx26cx0N8gIkZx4qHHCiLxuiJCViBfbiKz4gRK46VDiVQB50wAFOwBvtxE68Q/EpMIhmyoziqoTm6YhLmYCW2YD8u4in0b9QZWVECFVEbrTEQ07AM23Ecj/ERgj+6/oY0KITyaIKOGIUF2I6TuI6n+IyYceJYSZATJVED7TEEs7AS23AEN/AK4r/0IaRDUdRAG/TDRPyNU3iBn4gaN471B1IjC/KjFGqiHfpiOGZiCdbhIK7hET7C/E5+QhJkRn5URF00RFv0xGBMxkJswRFcw3N8RyQecY/MKI6aaIv+mIQl2IMzuIpn+AovPnVGCmRCbpRBA3TBEEzFQmzHMVzFI7xH+EccKz6yoiTqoB0GYTrW4B9cxSvYCbg2SIjsKIVG6IaRmI11OIjreAuTkLyJNCiAEqiO5hiEhdiFG/iCXxPxWRRENXTGVGw=
*/