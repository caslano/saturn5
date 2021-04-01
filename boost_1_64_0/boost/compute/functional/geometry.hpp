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
AE4KVglAXWeHsWbzmdfQ5UxM/WBV+cqOtO+roa0oHEei5966NQJ3hPNdhYuh4uh9Hg3wwP6kHK8JZYxt7a5l4FfQXzbjz+TRQsinrQd9UVqmzkdyBhTSpDBFk9QnUFove2T6Y79n+4DhOO1e2vS1eP/WV7NKB5fazHVeJ9Rcdi16kn40APHRIf9aHZG973X7hEVnNn/GozmPKAD+6tKFzJPMvPiJUtjt1Owh4myBPzU9qVhnTwr7kCJJaQFmCf8ZIFr3TIuM1wQcKbBMO01NoPzqwCBiCKBn0UhIV4wDjUeQNdoovM/IjjFlG8F7VWxpqikhDlLBo/GgRBIKvuoda6XwSs+sPpdlrbHKfTP6H379UDTITMvKnGkQ8SQ8Bz//VAvVwnfAjwaumNGo7qUIEE7802YEiHuxxcSnwhRwOf2K3d6bLXHZQxIuzEXg5J53xCW/JErjdaKzl4hMDPJ/L3BJn6sz6PtkFjoNgTR2bb+0Urv65vYiUWQX3sU/W+HTbsAjyTit4fJ8e1Q8COB3hlMufJAe0znn6vHERN+GzF4BANBJtlzFEGItng==
*/