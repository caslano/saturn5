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
Y/H4UqF5c2kMoq4cYMbgB3OZ/3R1vD+hm39zP0Vdf9H7pDEevqWjR/Qia9IVJ9zV9yE8W1OM+fDFVMlRWRUry4djPtvkQMzj3Pr/IqwetJvv1UusZcSRNNtbaBsut79jNmNKL6OZX+rR7OAcXh/z0amv0s19MeCx/bEg7f+pc0CvYxliBjg/9sN5kW7eZji/qoDzPsFZQ0PQPDOcplofnMV0s7wWcLprg3CeJZnG355MnYq94Y3jOP38UoP/qPKXVO6udXkvrJ+lwHYrn6Tls9en768iRBKOfK02iO2+N7vtx9a0XmKf76zTCZJrJ/WW8DYSTi5XK92ZpAVSr818+vS/Ls15iQCN/cqFtlY1VOiDjf43Tn+fTRd9oWpYOJtk7xYVlEqwF1L0k9+6fTmdKlup/Ld4xV7Ynd6yiTbBXr+GCn1M3OFuDtNH4PIvxoNo6pzGzrusC+0va6euWi93fqLt3eFsJBddGIqfacUeiD4UOUSEppE6uYxQeiwWiS+ptEv8gEAau8QzVLGvsgZcHxKf3O7pqIPjY82Lqk01dDF6x+izrlrAD7eN/tTeRZd+Klb0AVrmnannqYdWvfqKVfbxGDG23j0+2zPb1TbRa2U/iK10k7hEDei0RdOctY8TSu60mggvKsiXdUSbiK86EpQv753HMtS3qPIElZ/NK+/HnZCIzX6cmhfc7q9X17+vM9YWe5PeTAOyRa01
*/