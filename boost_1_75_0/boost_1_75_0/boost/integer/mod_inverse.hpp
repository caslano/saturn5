/*
 *  (C) Copyright Nick Thompson 2018.
 *  Use, modification and distribution are subject to the
 *  Boost Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef BOOST_INTEGER_MOD_INVERSE_HPP
#define BOOST_INTEGER_MOD_INVERSE_HPP
#include <stdexcept>
#include <boost/throw_exception.hpp>
#include <boost/integer/extended_euclidean.hpp>

namespace boost { namespace integer {

// From "The Joy of Factoring", Algorithm 2.7.
// Here's some others names I've found for this function:
// PowerMod[a, -1, m] (Mathematica)
// mpz_invert (gmplib)
// modinv (some dude on stackoverflow)
// Would mod_inverse be sometimes mistaken as the modular *additive* inverse?
// In any case, I think this is the best name we can get for this function without agonizing.
template<class Z>
Z mod_inverse(Z a, Z modulus)
{
    if (modulus < Z(2))
    {
        BOOST_THROW_EXCEPTION(std::domain_error("mod_inverse: modulus must be > 1"));
    }
    // make sure a < modulus:
    a = a % modulus;
    if (a == Z(0))
    {
        // a doesn't have a modular multiplicative inverse:
        return Z(0);
    }
    boost::integer::euclidean_result_t<Z> u = boost::integer::extended_euclidean(a, modulus);
    if (u.gcd > Z(1))
    {
        return Z(0);
    }
    // x might not be in the range 0 < x < m, let's fix that:
    while (u.x <= Z(0))
    {
        u.x += modulus;
    }
    // While indeed this is an inexpensive and comforting check,
    // the multiplication overflows and hence makes the check itself buggy.
    //BOOST_ASSERT(u.x*a % modulus == 1);
    return u.x;
}

}}
#endif

/* mod_inverse.hpp
/Lm2cVk1XFNoHk7NpbblQc9ztqTSacx5sSeu/KOfuHJPh1GP7sEOo47Q3V3Bu6YcscIo18X3CqP0+DOfHlYYNbnPOix8MRY7LFzx3WVGHaYM0Qe/3OsV6eUzLulC28ornjfNqwCLuR44Y/F8PSJ45ZnWh3GOYH/0eaOEalYG01vKe8aV6pszkvLHfHNGUhHesNmLbcArAnplRFvGi/GBLaXLLDLmy0Oaj+fykBbB6aPZKsy8Q7v2GgXadmeUn0e9PjFl5aznlW/FeUG72Cpiu8CVId5zekiYq0JIg1PC3CFfZM4NeQqY/NPnIX3WXXPEsz37LscrjryU2eO06vDestdSudNsVPZrm2fTXwJwImXa1x0qTttp4cf1MT3FO+UvpibzyVqjJvIVipWx0tjDQTzNfLrCiaxkPrsvwxGt9O+L+C7vl79GvXrttynuxpuCPKjudp5ivIczYkbxX78Vv3TyD6m+075MYSjWeu+ZWKsqqkXvirscTHRL78ZtajV0s1Pu+kQPpt9cAnjE2aZL0irtcRkX5ONMfvDkzX8+h+7ucFp2RIwrHjgsOQS3a7WXj6nVbLudx/WBtFuAvszuTGs+XxOlFDPXXdIz83iCrmx8vyD51nHV2/5eWNwvfUJxKvPNO6Ptp71OZt5tYkJyz1mQObbD3yl41qMigdl+t+TltB1+nRUcIWy7eEau+eF3XPF9SvrLYvS63ZDW
*/