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
skvbZeyydjm7vF3BrmhXsivbVeyqdjW7ul3DrmnXsmvbdey6dj27vt3Abmg3shvbTeymdjO7ud3Cbmm3slvbbey2dju7vd3B7mh3sjvbXeyudje7u93D7mn3snvbfey+dj+7vz3AHmgPsgfbQ+yh9jB7uD3CHmmPskfbY+yx9jh7vD3BnmhPsifbU+yp9jR7uj3DnmnPsmfbc+y59jx7vv2XvcBeaC+yF9tL7KX2Mnu5vcJeaa+yV9tr7LX2Ovtve729wd5ob7I321vsrfY2e7u9w95p77J323vsvfY+e799wP7HPmgfsg/bR+yj9jH7uH3CPmmfsk/bZ+yz9jn7vH3Bvmhfsi/bV+yr9jX7un3Dvmnfsm/bd+y79j37vv3Afmg/sh/bT+yn9jP7uf3Cfmm/sl/bb+y39jv7X/u9/cH+aH+yP9tf7K/2N/u7/cP+See3hRBSKOEILYxwhSd8EYhQREQUEVVEE9FFDPGL+I+IKWKJX8VvIraII/4r4orfRTwRX/whEoiEIpFILJKIpOJPkUwkFylESpFKpBZpRFqRTqQXGURGkUlkFllEVpFNZBc5RE6RS+QWeURekU/kFwVEQVFIFBZFRFFRTBQXJURJUUqUFmVEWVFOlBcVREVRSVQWVURVUU1UFzVETVFL1BZ1RF1RT9QXDURD0Ug0Fk1EU9FMNBctREvRSrQWbURb0U60Fx1ER9FJdBZdRFfRTXQXPURP0Uv0Fn1EX9FP9BcDxEAxSAwWQ8RQMUwMFyPESDFKjBZjxFgxTowXE8REMUlMFlPEVDFNTBczxEwxS8wWc8RcMU/MF3+JBWKhWCQWiyViqVgmlosVYqVYJVaLNWKtWCf+FuvFBrFRbBKbxRaxVWwT28UOsVPsErvFHrFX7BP7xQHxjzgoDonD4og4Ko6J4+KEOClOidPijDgrzonz4oK4KC6Jy+KKuCquievihrgpbonb4o64K+6J++KBeCgeicfiiXgqnonn4oV4KV6J1+KNeCveiX/Fe/FBfBSfxGfxRXwV38R38UP8JPXbUkgplXSklka60pO+DGQoIzKKjCqjyegyhvxF/kfGlLHkr/I3GVvGkf+VceXvMp6ML/+QCWRCmUgmlklkUvmnTCaTyxQypUwlU8s0Mq1MJ9PLDDKjzCQzyywyq8wms8scMqfMJXPLPDKvzCfzywKyoCwkC8sisqgsJovLErKkLCVLyzKyrCwny8sKsqKsJCvLKrKqrCaryxqypqwla8s6sq6sJ+vLBrKhbCQbyyayqWwmm8sWsqVsJVvLNrKtbCfbyw6yo+wkO8susqvsJrvLHrKn7CV7yz6yr+wn+8sBcqAcJAfLIXKoHCaHyxFypBwlR8sxcqwcJ8fLCXKinCQnyylyqpwmp8sZcqacJWfLOXKunCfny7/kArlQLpKL5RK5VC6Ty+UKuVKukqvlGrlWrpN/y/Vyg9woN8nNcovcKrfJ7XKH3Cl3yd1yj9wr98n98oD8Rx6Uh+RheUQelcfkcXlCnpSn5Gl5Rp6V5+R5eUFelJfkZXlFXpXX5HV5Q96Ut+RteUfelffkfflAPpSP5GP5RD6Vz+Rz+UK+lK/ka/lGvpXv5L/yvfwgP8pP8rP8Ir/Kb/K7/CF/MvDbSiiplHKUVka5ylO+ClSoIiqKiqqiqegqhvpF/UfFVLHUr+o3FVvFUf9VcdXvKp6Kr/5QCVRClUglVklUUvWnSqaSqxQqpUqlUqs0Kq1Kp9KrDCqjyqQyqywqq8qmsqscKqfKpXKrPCqvyqfyqwKqoCqkCqsiqqgqpoqrEqqkKqVKqzKqrCqnyqsKqqKqpCqrKqqqqqaqqxqqpqqlaqs6qq6qp+o=
*/