//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_SCALAR_TYPE_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_SCALAR_TYPE_HPP

#include <boost/preprocessor/cat.hpp>

#include <boost/compute/types/fundamental.hpp>

namespace boost {
namespace compute {

/// Meta-function returning the scalar type for a vector type.
///
/// For example,
/// \code
/// scalar_type<float4_>::type == float
/// \endcode
template<class Vector>
struct scalar_type
{
    /// \internal_
    typedef void type;
};

/// \internal_
#define BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTION(scalar) \
    template<> \
    struct scalar_type<BOOST_PP_CAT(scalar, _)> \
    { \
        typedef BOOST_PP_CAT(scalar, _) type; \
    };

/// \internal_
#define BOOST_COMPUTE_DECLARE_VECTOR_SCALAR_TYPE_FUNCTION(scalar, size) \
    template<> \
    struct scalar_type<BOOST_PP_CAT(BOOST_PP_CAT(scalar, size), _)> \
    { \
        typedef BOOST_PP_CAT(scalar, _) type; \
    };

/// \internal_
#define BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(scalar) \
    BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTION(scalar) \
    BOOST_COMPUTE_DECLARE_VECTOR_SCALAR_TYPE_FUNCTION(scalar, 2) \
    BOOST_COMPUTE_DECLARE_VECTOR_SCALAR_TYPE_FUNCTION(scalar, 4) \
    BOOST_COMPUTE_DECLARE_VECTOR_SCALAR_TYPE_FUNCTION(scalar, 8) \
    BOOST_COMPUTE_DECLARE_VECTOR_SCALAR_TYPE_FUNCTION(scalar, 16)

BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(char)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(uchar)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(short)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(ushort)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(int)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(uint)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(long)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(ulong)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(float)
BOOST_COMPUTE_DECLARE_SCALAR_TYPE_FUNCTIONS(double)

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_SCALAR_TYPE_HPP

/* scalar_type.hpp
8ZOin5Y253odfmttTN9tov9c2/OJyab98aaVYzsF9an1YqNaI4u2rLf8+m1P323J67UZf39b1Xeb9Pe3PX9vG9Ns66x3/U7kurIZiUBeRgxpmznhMZgHfgzzwU9gK3gCtoefwi7wJOwFP4N94N/hAHgRJsDT0nb8Ak6AZ+BUeBbOlnhPw/NwgejL4AW4Fn4DXxN7mLSBjDTmm0Dqpd3aGiBNkf6IjzaOz/aNZ9vm2jaNtGdu
*/