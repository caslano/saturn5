
///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_MATH_HYPERGEOMETRIC_1F1_CF_HPP
#define BOOST_MATH_HYPERGEOMETRIC_1F1_CF_HPP

#include <boost/math/tools/fraction.hpp>

//
// Evaluation of 1F1 by continued fraction
// see http://functions.wolfram.com/HypergeometricFunctions/Hypergeometric1F1/10/0002/
//
// This is not terribly useful, as like the series we're adding a something to 1,
// so only really useful when we know that the result will be > 1.
//


  namespace boost { namespace math { namespace detail {

     template <class T>
     struct hypergeometric_1F1_cf_func
     {
        typedef std::pair<T, T>  result_type;
        hypergeometric_1F1_cf_func(T a_, T b_, T z_) : a(a_), b(b_), z(z_), k(0) {}
        std::pair<T, T> operator()()
        {
           ++k;
           return std::make_pair(-(((a + k) * z) / ((k + 1) * (b + k))), 1 + ((a + k) * z) / ((k + 1) * (b + k)));
        }
        T a, b, z;
        unsigned k;
     };

     template <class T, class Policy>
     T hypergeometric_1F1_cf(const T& a, const T& b, const T& z, const Policy& pol, const char* function)
     {
        hypergeometric_1F1_cf_func<T> func(a, b, z);
        boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
        T result = boost::math::tools::continued_fraction_a(func, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
        boost::math::policies::check_series_iterations<T>(function, max_iter, pol);
        return 1 + a * z / (b * (1 + result));
     }

  } } } // namespaces

#endif // BOOST_MATH_HYPERGEOMETRIC_1F1_BESSEL_HPP

/* hypergeometric_1F1_cf.hpp
pJjwnEZ+v0IV5xEncZBXXDvJmrz22hI7UDi8yMpHWxvS/hQwCTHSn/zNMO4a0d+1nu+u26D5jbUNMKN/Goa9iTDn9S/LNFvUlsXpxtrUlk530zXoI+x7LP3b/4avZKXmiO9drUm7Zllqs9ItCQ0KKc439v/jcWjbeNkqquHMg2bVjr8E+1d6hy7rM/UkkacO6KLaxq7eq7hv+Va7Vk/HAEhPw+TxaNTVfcgX9BnZCor99h6DHZ5p8NSbVBcq4Di6hOzivcQilkqNXpe/iOGoHGcrGYiD1Nd7LZ+ozt+rskRVI29qhIkDDDfGiOelLhtgqOpkZ5cwrhwVcjvJlgr7XsBPbmSlLalcPOAWqjTWfYJ+JpOwCbd66TDHYYP9J/7S+yjwT/SeuKOf4FPrhqL7z+/BPtun+Avj3e87dL6nD/O8wH4g/W2uwda5jP52i5uJ7JWrRPoWw5AfyhYqaz3wtqXkT5DDm5Yyp6e58FuWmE82rH3Dcj/I0BFanYchJommpcwYncpAtbHDEz9rYuNc1uO8d09Kvs7NITVMwkx5DKY2YAdRgBRD9UCXh0vq71EepR1w3E90nmOtwDDh+I5czsS3UvJ1G9+BzyC+WONYUAxvZuYThfQ0G9auylcBt1yZPG9HU/aNJs1CZdvoYRMFWZlbx9mUMLdTU21P6aohhiOr+vY9w3l7qa9mdCoAk2dLoobUuTDXSTruXakzlqPCot46MrprT0g7fXXLaZvidpP8vobhiu0KXefNd8ZeaMjcXZDF1CdN0om7Y8uiXyZQtzula4ZZ9M/qPJdhg310TWwcw9t+WuIXZnlyMs1erEEOr3U+tppavliDvbbPy/wqpQZsirLD8bhUXjzB3c5T1A4pjjom9DszjuaV81s77m+5YUb7XrZcp3W6Tk0DmBmfQT3A3JUbFqoDag69pL9Hg+n0Xa4fSVF4Bz6HsIhb0Z00w+tMKm3FzyBn3+UZ3yXAcTJJPynx5xeL023Xnl23H2LYrpM179tc1jK8hUy1sahThbws1jSkTBSy+YycjAFC4fTeW1m9XMgtZK30F0E/kb3OXTLM4hiNGHPYB2QYbdDBphpLHMDp9+77xh0YdmKX/d53w61jQ+vGVnCsaDgx8to3lXOLYQaGHtrnKcMaY68h51cNGzb45A4lw9u3AyUvLKuNP4z/CrlE/B0YxjcC4e/QsjAEVXkfhTiMPdGHBTkYUjrO0e0sq8ahNbFDAxz3A7BDC5hkTZ3psow2WGtih5iymq+3ih1yeeOObodr0iYa/1x7RfrQIBfOr5nbWzaUX4MwZ/MryIXza/UOlg3l1zDA+flVuaNl/PwaBhnkl8R1kTlY2cuw+MANLQcrWnGjACcvH6l4xhXLcRcUS9sYYHgdQJhRgOE52VjK7r0DDMWR93/inqcijuMoZwaLOC5xOt/jIjahrUV11Y9dgjm+gPHkiUU9S9mR9S/hqNkCgP6f/bvfSvXYETbnKM1q9bM42zNcUox3tmx1RWu8OMPfSxg0g/d/anIP1n20TkGoqTPbD1BavkgWiXb8Aql2imZfbs13ZInWg3a723jaqHvZXMNhCqwjPWKinVqZP5kFhtZKVDvzyJDOOwP0e40PnHBU6PP35xhSNuGDFJPb5IyA2X+wy8RdSuFWK60gsPMsIw7JOmpVM+kSUF6axVbWOpuK7IgwPWFo6EBadyMtUa2dWK33RmvMcFniHWeyRtKDThcYqP3G65Pfa3VyunUOW+EiKWtgurGbprABNeOmKeK6oZlwmg5qhjF+zdQV46aZxHcgjHuPZGmTf+cTCNmSgfiAel52uVa3o0Oi9gy5HA0aaJpcuTMM6NodKUsuR3vyhNo=
*/