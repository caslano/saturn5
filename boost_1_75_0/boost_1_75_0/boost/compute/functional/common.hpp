//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_COMMON_HPP
#define BOOST_COMPUTE_FUNCTIONAL_COMMON_HPP

#include <boost/compute/functional/detail/macros.hpp>

namespace boost {
namespace compute {

BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(clamp, T (T, T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(degrees, T (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(radians, T (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(sign, T (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(smoothstep, T (T, T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(step, T (T, T), class T)

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_COMMON_HPP

/* common.hpp
mZ99B/N313m754c2VEx0W2uXIqdGtvH4py763j3W2JIPIGuGl1/hk17u2KPvIjd3FVfFCvZgv2DxSyzMj5wJluJC9kPdY7fZWocUxrsg71/13VbCFe9MxCH2w8TMXtyjlqgXhO2n63znficDrVDzrgGjGqIcwSHyo8PZhIbLRiLH/95Y+HztPA9lfHXtEdpVhJd0NyJ+sQXwfhdow5co3PgHR1YiQGZh/qpHYnGpmEJfFAr+k62quyNTLbK0/Cv//amJhWuiua+4cTofThaDziVQ4/5y8bXLvpDrWJD7898iWrHnhWbx4p6WZn94lP63X0NnooX/6L9oH8C/4jAG/O5WQG4C9lLRDNZVqECA5MkUyWMyP7FaGhUfNYx26/46w12vUJXh640vo46v3f7+ySqOZIBGR+fnG+mKL69K/fxIu0r6a6/G9oVt7ZrtNzXS5UsHfvetfD1magA/fGS/nlQpPOuZTI1UP1roE2o5TdXNM0EJG6tvg5AHifaHhmNyqxEnBrG8Tw+TsrWEiq274QoZFXSIRarwXOvu7oR+0RPYOCvVgq9BlJNh6cYTM/fUFpTOSfVADB4Pd7sADxJJoeBSZC3wcTXSj33qqF9hh0MpiQlIbWbr9fNN4lu/d7+Dm+EFB36h20vFpzdEf+bqWE/g0o6e+yu0/YLiFM4GF4A+yGm8hr/oZ2xpJUZfPcX4aCG5fvab/IHiC1EP
*/