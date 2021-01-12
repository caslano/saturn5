//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_GEOMETRY_HPP
#define BOOST_COMPUTE_FUNCTIONAL_GEOMETRY_HPP

#include <boost/compute/type_traits.hpp>
#include <boost/compute/functional/detail/macros.hpp>

namespace boost {
namespace compute {

BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(cross, T (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(dot, typename scalar_type<T>::type (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(distance, typename scalar_type<T>::type (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(fast_distance, typename scalar_type<T>::type (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(length, typename scalar_type<T>::type (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(fast_length, typename scalar_type<T>::type (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(normalize, T (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(fast_normalize, T (T), class T)

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_GEOMETRY_HPP

/* geometry.hpp
qQfo/OmO/W11c9cUJH+eZK895/K4xeOOlOkBCtUD1A+xtP6thwW6X289vBm5Xf8+ZFM/9e99bpk3yd+xLuqsht2O/VHY2+zxlj3o4uZF2mtao/Uc6VhYEY6HTeEEeL6aL4RTQ86TTtP46hY/T6rnSB1uhz74MkyDr8Dq8FVYC+6CdUL1vrh0r67uUV4PeyAtXXqelPTT4VpYDT4Cm8GtsDt8GmbDZ+F0+BxcAnfAG+Hz8Fb4
*/