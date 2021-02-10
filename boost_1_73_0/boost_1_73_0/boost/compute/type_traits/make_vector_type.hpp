//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_MAKE_VECTOR_TYPE_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_MAKE_VECTOR_TYPE_HPP

#include <boost/preprocessor/cat.hpp>

#include <boost/compute/types/fundamental.hpp>

namespace boost {
namespace compute {

/// Meta-function which returns a vector type for \p Scalar with \p Size.
///
/// For example,
/// \code
/// make_vector_type<int, 2>::type == int2_
/// make_vector_type<float, 4>::type == float4_
/// \endcode
///
/// \see is_vector_type
template<class Scalar, size_t Size>
struct make_vector_type
{
};

/// \internal_
template<class Scalar>
struct make_vector_type<Scalar, 1>
{
    typedef Scalar type;
};

/// \internal_
#define BOOST_COMPUTE_DECLARE_MAKE_VECTOR_TYPE_FUNCTION(scalar, size) \
    template<> \
    struct make_vector_type<BOOST_PP_CAT(scalar, _), size> \
    { \
        typedef BOOST_PP_CAT(BOOST_PP_CAT(scalar, size), _) type; \
    };

/// \internal_
#define BOOST_COMPUTE_DECLARE_MAKE_VECTOR_TYPE_FUNCTIONS(scalar) \
    BOOST_COMPUTE_DECLARE_MAKE_VECTOR_TYPE_FUNCTION(scalar, 2) \
    BOOST_COMPUTE_DECLARE_MAKE_VECTOR_TYPE_FUNCTION(scalar, 4) \
    BOOST_COMPUTE_DECLARE_MAKE_VECTOR_TYPE_FUNCTION(scalar, 8) \
    BOOST_COMPUTE_DECLARE_MAKE_VECTOR_TYPE_FUNCTION(scalar, 16)

BOOST_COMPUTE_DECLARE_MAKE_VECTOR_TYPE_FUNCTIONS(char)
BOOST_COMPUTE_DECLARE_MAKE_VECTOR_TYPE_FUNCTIONS(uchar)
BOOST_COMPUTE_DECLARE_MAKE_VECTOR_TYPE_FUNCTIONS(short)
BOOST_COMPUTE_DECLARE_MAKE_VECTOR_TYPE_FUNCTIONS(ushort)
BOOST_COMPUTE_DECLARE_MAKE_VECTOR_TYPE_FUNCTIONS(int)
BOOST_COMPUTE_DECLARE_MAKE_VECTOR_TYPE_FUNCTIONS(uint)
BOOST_COMPUTE_DECLARE_MAKE_VECTOR_TYPE_FUNCTIONS(long)
BOOST_COMPUTE_DECLARE_MAKE_VECTOR_TYPE_FUNCTIONS(ulong)
BOOST_COMPUTE_DECLARE_MAKE_VECTOR_TYPE_FUNCTIONS(float)
BOOST_COMPUTE_DECLARE_MAKE_VECTOR_TYPE_FUNCTIONS(double)

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_MAKE_VECTOR_TYPE_HPP

/* make_vector_type.hpp
wAs903OKQUH6N2AWlAfdChhIDNPw7dBw7L+4l2lUoEozq1f6pHM96quTDsPdh6dqz4eheEnCOBjt+Av8wXdouJ3ve4zZuHPF6kIWS7GpoOC4qTFSi4XUY71w/aGMyYBcnC6lxn0RMAQq31EOIZ4PY0E8Rrc65j6eKId74hqVyF1j10MlX+RyR6kvspSxSmnJCOMgF7s/bo4gYNP03Lm9EMuu09aiRezwkJHq1WQyqnJMjPQqbt7VhvDtGwaRLnZoiPnAtoTmLVCficYTboc2tDz0buatICEKP7+jP233lYtq00EhqiTrzjDSO4pYcLTa2K7pRBatktaRkDVCrwSQbmw6ZkBmwsA2XDuE4iDchh4kiGhFZZC7m20ixBfbOOMZYg47eZLEzlpnrVMlLpMC0I0cEDOFTFaBIrHG4vl1axwbWSHABndqcHDDDbm9feqB0wGAb5h3xgI1dGu7ELuSG8sk75ivWKLg9ANM/yDyUloOqOfQ9pDSXMiZiwgrhTUKs3Uo7o2yQMMN2+MpgqPosQC67c5xdyNC77gUZAQ4kPZCewWJsqK2ddijbgb1aVG5AKXAtELS4bilk1lH0/ozZXoZh4S9XXKcEBhBikYZzLvxmxclOJykFKg3ev+yBKg3+vKyHAh+/14CBC/+
*/