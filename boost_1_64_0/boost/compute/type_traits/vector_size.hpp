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
JaVOsOXCQlO2uLTG2jQOQy9QC9tnT6htCZnDzTXsLljf0Vf9EfZt8Bw3zdy6FPLca1G28xMbq6syCnodEu3Bbb5npfXeTRjkgetmWHcOz8BgbCr52FRmaeE6RSb0CtB4XuKEen7OqttXmXwkIifMK6euhbQGviCdZ9CjO/KdHX1lCMmjbl8z5XORh34R+G4paEZopiipq02adyydx0EV1E7oC6ohnSAdYyxcWLiIJGWaYfONq/jdp7j04iqNYi0PHxXDomrimTTj8TzhOV6WZ7GgXU0tS+9wL0vx/ktDapPv2RNqzWh8c89WfA2W1Y7n+m4l5pepDciUdUVSO+9Za6mK6yKq6yIu3cCUtSbWqPvrwQifH+eVG/pFIpTa+08SyS0lakD0ZGgzqJxwm32gio/ZUVV7WR1EWp7a3YaSX1ymF6HoiXqsW5o83Kh4+8mqKCpLxxfynTdKlcRnZU3QhENpwfpu3LLKX+dhXsS1Z8uv92Yhbn6z7lbWWtSPgrrOS1NeSs4vGdJN2uO1vc4vfb+ofVuWJW2kfbDmaXt1GThBkVnyC2bB3abeXxxluo/Dwo19zxGGrq2uB93jm1nz8aPI/TIIglQsr6wsfI4epVLjcrsFyTjQdmuufzevaQexFHjdWHcl1Sa4/i7XvO7DwC8Lz/eF2hLX2Uc87bHzWm3NN+uszhK3kPKXpMQ8b3h83Dn7xy3m99cN/KCMax+iA40b64fVUVZfgee4Xl1EXOiEuSXk4Ptr59Urcicqcshi2MG3G+uAX5iytagypyyT2BV6VqwG9s119C30jduWftO6rt0qC4V8B3h1nXK6fGF5Q1bN5Tn5ttRAv438yEetbwMNDmkdSPkePQD27Allg06VJLVMBp7WHt7PuL7Cwgsrv8zZ20W8XWGNJ8y0KxGVeRqHaSkuyq+h/jTR+NLS1dkvjppyRRi7rpNWJIfcQs5oD/VHrfuklesnaUZy+IjaY8c5ph9XVH4cB34VKSFUJ0TZfPUGk01FXmVxXVWB6MuRmN380X/DZuxjcVQiz6MqK7NCSLWS0IrMNs11V+RRm1J3f07Rs/c871l5qSMvi7LIEfqun9ZA39ck/yhjLnLgOR5HmHmVG1e5FcfCRRYH78/TLA5fFEWdp4UXi/5dQh0FqYWGc74vdbtn1Hst0jiK0zgQ8smzi/IBWbQZNv5cYelFInQSN83raiAlbc+Mq9B2/3jNko8rL4qCqBbmFWnKNEYEPg+5Z8p7gcgdWi6FqSkP3Us16uakHvKSEaEch0/bc9A8z5My6YjH3B9dbPIRM/lSxH6dB3XAxaXNy/mF9f48Zl0aZs73Wuv/tdPWutGp6jqOHR6RfOqsL/ls2KyFTDnPE34ehFFcRlyONSRUCmUAY+xpqz7KOg8tLdArYf2JlLXGsWS90vHDLPEEHYew76l6x77pjatuM49g8qmIiiKovMSR8qvU9dSJMmaArEEskc+5k/IceuIzdKZIC8f2e21PS/zcLPCh77V9dPBeGxHhzx1vO32D7h4u92YwRswYQ4Rhqxjw89zAS2hi+cB+QuB31owvdkTpOzK2Ice5cgHcf+xT91r183kZm3G/LTTiCxIRpZXjZl7wf++lyW1b+s481/RhMx6vEn4e+VkSdWaMqm+4Y3AxOAuP+D1Lt3DqIEn9IXF22FCeoA7ea+ITLL5UhKnjp2nuPWh85l2nms6E7YM0oy39ahQcfmBmcL66lXPgodDgTI+1OY0dLmzVujjqjQfZ1U0/vtttHjybw2bibzanfVgH7vz4EO6aPKDR5+3wj7ATXNUmcTcMNvEcb87MzDiWdnOObSN+ZG8bl1EAf22C49qJOvD5RzTODhk=
*/