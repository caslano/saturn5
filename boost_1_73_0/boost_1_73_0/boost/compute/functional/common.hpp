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
WOrtWB5BbIQDPGUqpC8bxfrKWnVpifLUXOYvqKIpbXI+swbW+UscZhgWKH3j/UHOs4K8446vjR/p87iFPVSoAe6PtNOFIF3nDoj3mgnV3osp7CKO2di9pvSHQMeJsSTFexwF+jTsLau3xEBWB9Z68+keRpZse5lqTGqvFU+qY0q+XVx/hpLqozvo8BUGQ3d0w5IugdKBTyztVgdCNwJ4pPluR5jn+k+lxHNzRg5maGXZVjsdCZ6wPHYZvSfkOOYEnpgt9XSCxnAnMFfu6fqivUBv7jFLO4UtzSKODMq2fDocKX10zEdBJkj2LGLroJhAng67yHphCpRsbix3rgduz6JZWc3RNR4m0nU/i8r7TnCpZ9USI/ZVQyxo0dxM/8u2Ua3PXO3skGpUAXaHCLHNDSo9mzUJlb3mznzLabDhq9blUX3a7aY2oXQdNvRLAEc6KdNFj43hRrqb+2PhbqfjdWZuj868nvRd1S03sQprIsNXJ3jiuhtRX3i9yWtX5PjhwFGSzrz1NesG5784b7RE+nvz+u3/M633Z5/dj950xFRyOvbM9dTgq6Q7AQrGqt4XgUPulN/9t46E+Bbpv3UkZDOL/2hTixQHagVfrr8fwrmt8WqIfl6fKuvLPOWFVJ0UV4FybBXcEm8kGJ7o
*/