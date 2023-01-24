//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_VECTOR_SIZE_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_VECTOR_SIZE_HPP

#include <boost/preprocessor/cat.hpp>

#include <boost/compute/types/fundamental.hpp>

namespace boost {
namespace compute {

/// Meta-function returning the size (number of components) of a vector type
/// \p T. For scalar types this function returns \c 1.
///
/// For example,
/// \code
/// vector_size<float>::value == 1
/// vector_size<float4_>::value == 4
/// \endcode
template<class T>
struct vector_size
{
    /// \internal_
    BOOST_STATIC_CONSTANT(size_t, value = 1);
};

/// \internal_
#define BOOST_COMPUTE_DECLARE_VECTOR_SIZE_FUNCTION(scalar, size) \
    template<> \
    struct vector_size<BOOST_PP_CAT(BOOST_PP_CAT(scalar, size), _)> \
    { \
        BOOST_STATIC_CONSTANT(size_t, value = size); \
    };

/// \internal_
#define BOOST_COMPUTE_DECLARE_VECTOR_SIZE_FUNCTIONS(scalar) \
    BOOST_COMPUTE_DECLARE_VECTOR_SIZE_FUNCTION(scalar, 2) \
    BOOST_COMPUTE_DECLARE_VECTOR_SIZE_FUNCTION(scalar, 4) \
    BOOST_COMPUTE_DECLARE_VECTOR_SIZE_FUNCTION(scalar, 8) \
    BOOST_COMPUTE_DECLARE_VECTOR_SIZE_FUNCTION(scalar, 16)

BOOST_COMPUTE_DECLARE_VECTOR_SIZE_FUNCTIONS(char)
BOOST_COMPUTE_DECLARE_VECTOR_SIZE_FUNCTIONS(uchar)
BOOST_COMPUTE_DECLARE_VECTOR_SIZE_FUNCTIONS(short)
BOOST_COMPUTE_DECLARE_VECTOR_SIZE_FUNCTIONS(ushort)
BOOST_COMPUTE_DECLARE_VECTOR_SIZE_FUNCTIONS(int)
BOOST_COMPUTE_DECLARE_VECTOR_SIZE_FUNCTIONS(uint)
BOOST_COMPUTE_DECLARE_VECTOR_SIZE_FUNCTIONS(long)
BOOST_COMPUTE_DECLARE_VECTOR_SIZE_FUNCTIONS(ulong)
BOOST_COMPUTE_DECLARE_VECTOR_SIZE_FUNCTIONS(float)
BOOST_COMPUTE_DECLARE_VECTOR_SIZE_FUNCTIONS(double)

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_VECTOR_SIZE_HPP

/* vector_size.hpp
6Y/ZxtVCH5waumldCDh1C4NwjugfGxittpo3XqfmZRJq3huAUVzIdkMXxll08zmGca4HY+rjXyF6qJ1ztV6jVrmWOpZXH/1wn4rb/G27e6HP/lfRtt9IDA77BR4J6lteop+7gXHt/0oVe1FUiQrXxcATGz13n32J9/V66xL7C9r5orZvIwKzxepwoKs3cVJJddLTJ8ZJFQmkG3rZfiZVtiwSu8BI2lMOTJhv7TTf2pn4hX2+c2H4zmo7YSX0bWp5uMOJhKGDT1bFPV7WF2N2iMBe537jfqo8v0hsimKCcdWnR1n7/sQ/EjoxhqMxYzgaa7mDKNpKu91ZFV6snRWR26KtRF/arctJ4MqEF0VcRVLl3kmcRmu6gS56dMZ1kzutYv0Nub99acbfjvt/u5Vurj0N8/jF04Lz+B1rj4lXcH2KjwR9ig+dxrp4F8aDdPM/GcZ3PRi7n6Y11qWt1wiI8RV9rJbWRIzWxFzVsMdwcFMurDdPY3pZ1R5V9VQ6240tCVpaY3FD0J6xJTW3B1XQb1mxWtdbY9LpoNnLqauJlyWZpyWiWmj9tozS/9T3lnTT8cbp5FT9UfCg4wSl/WK6/DOVjujivyJJp9+9rHQvf+JeJt3LNe7lVvfyDffyiHt5yr285F5+517Ct7raOfeSci+D7mWNe7nIvVzuXv7CvRygS+R89T3d1riosb2j40uG9/PhrXeoKWMfuN0b
*/