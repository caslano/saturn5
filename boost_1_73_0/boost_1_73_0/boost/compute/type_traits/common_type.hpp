//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_COMMON_TYPE_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_COMMON_TYPE_HPP

#include <boost/type_traits/common_type.hpp>

#include <boost/compute/types/fundamental.hpp>

namespace boost {

/// \internal_
#define BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPE(scalar, size) \
    template<> \
    struct common_type<BOOST_COMPUTE_MAKE_VECTOR_TYPE(scalar, size), \
                       BOOST_COMPUTE_MAKE_SCALAR_TYPE(scalar)> \
    { \
        typedef BOOST_COMPUTE_MAKE_VECTOR_TYPE(scalar, size) type; \
    }; \
    template<> \
    struct common_type<BOOST_COMPUTE_MAKE_SCALAR_TYPE(scalar), \
                       BOOST_COMPUTE_MAKE_VECTOR_TYPE(scalar, size)> \
    { \
        typedef BOOST_COMPUTE_MAKE_VECTOR_TYPE(scalar, size) type; \
    };

/// \internal_
#define BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(scalar) \
    BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPE(scalar, 2) \
    BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPE(scalar, 4) \
    BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPE(scalar, 8) \
    BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPE(scalar, 16) \

BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(char)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(uchar)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(short)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(ushort)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(int)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(uint)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(long)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(ulong)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(float)
BOOST_COMPUTE_DECLARE_SCALAR_VECTOR_COMMON_TYPES(double)

} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_COMMON_TYPE_HPP

/* common_type.hpp
XPl4Rvv9dMJpJIbfNhMBAdr+2psfJHgNrYXFZFnisgtqyS90TWx9/QyZDrUavR6mJ0/0swWRKXnvGM8ReiVw57XPnTzanB6hRYpwmOhwSK5DkzSMrhPjDhYullJTjGY1+/dN+ocGIOfNr32O+yaBZ+XaEL//TNhXAa49r9e+ZlT40wgCOMZPEFD7ZExYtVGt5Tk6zz26hsl7oDflInGaUyoqdOTFX/6S4z5V8DR2Iqy3ph5GdN/P7/lOlZZYpbwv5DSHUolNt5a+j2GFXT8/afx47St2rYhE6TFEArfgHAxp9MG13EtvmseqdOlkUFeFCKpJb+2IRsNVbLIfX130NJAoegQOeS4glMu36WyVbjLhBRKUn9jpE/DWvNPw8IW+EuMaBFMQpKHDcO8yH+16AncmqJodkl/aeMx7KNVbb/LPpSneYlhMDwKsEaq+AUVk7xGXNPeSThrRRq9zm/zosKShruAksYSTC2COie91ap/lrcbR1wvc/44rZdV6uEL/7pqS3sE+Xl2Nv4sFoFT9NmaQvP5jXX9hWsdP3xLdw7JW52zMpwInSzF+6rjA/B912cmTCVdBVGoZkdA8ga6WEwylQknLp6evtR4MVE3Pn9OhlmKKq+xoyp0LiHorIcZt4SUpm3vFjr9fQjOR
*/