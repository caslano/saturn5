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
9tDjNSw7tZwGSacBx3FSJySk/8V6Lr1d1ZjBJj8mJaj21jt7CjJ864n8ENkIVESk55YB7mMgAUeJg5RMhcEGLS9ex7WX8E4em5AKuri/6sYlGVEE9T9m8fOKMWkfkn7gk1XGMq0oMdWecSaEV6C82G6vIdSvB93jT7lHM8qGa93srHSpN6/ydUh3Q9akVzfYHzISEA+PAHh7AhDBTBjEbGbR2Iys17w1qm5fQ1q5YbOkO85Uhg/MkQfSKeBU4kVgbT97CGns55jPI7+cdmQVDJWOeCwX7NU4W7MZvk/aHtfmytP1n3i5X39Xpgww0nZILu3tOW5r3jeAl194FI+uDKym7OSw0tIr5q17Gj96lzPtj8wTiXsKtNSoRwPLBhu2RoESDJlLcMeg19ROHTJvJ40IxuvvPDZo7xqLxembm576ReWVXPzSpngWe7ZNPgEGjGlmngxhRR2IgqKZu7zkvIovHzrRBHrFkPFfmkHe4x32nPNqsiL4GMIRdIv4h7LKggkBqX4DYqFuDYgJAK1tQGmHxm9C3vVIqE130rUZ+jpOCZA0KPJdEspAkg==
*/