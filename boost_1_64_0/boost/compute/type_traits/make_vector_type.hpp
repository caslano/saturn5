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
hSAcSS67O19pN95rEWtpHeySNA/y2fvG+uzmR2qhUqqmA//9IXbwwbeP7zaS78X1ijhQz+fU4s/Tj8tHPrLrf096YDS6P4uNeeJaSt/F+DrNf0+fmOedG6JM3coQ1P/7nr5tPX8/KqrqIJqqez9WNg/weUdL9Hi+58hU0XbFEzamtC8tuJsD6ZW6tZzb7r3bgEunbt+9J0fn+cZZHMel46YWCtpXPINheDaRwwAD5vGvlcmm4xVotx+8TpJ1ZqJBeNdAfnBdJIf3DOIKr1/I4R0DG3HNFmHg/YJYsxsiObxbN+/nDj7+mpvHuYOVg1hWB/l+/2tlMR16/aDdSZNFJuZ9c11eekz8xvT8cK809zCt8SGDaUwS+/rd2D8aBL0JTy4k/E5sMdOFrIOLKR4ifUm6uMKVWw/zNG+9asRduQFKk08e5js+fd0sZivOfHcG4xWLF+ONi1ODBwP2eV+Yh53uoB6w/V6VuOfjehG7/tRdHLO8McyznLx0zUxXHCic37jQ5+9gwLwOYbZ3ctidBztbCZMEk62uXKdRih1myH/461VSvew/fXt1qLPzg2z3TyCL9d1Jz999KLfFlN+4FSEeeDd99Ye0dAndHnAneInbW0uXsPb5AdzujUrc2tNj5OPGaq8P4ujuMsOh4sswu4vTfMcm9YzNjSsR7N5D2by007O3NzXWN6zedfX1BWX0ggELbeRgSPe7QTbt0WcNLU1YbUNfZA33+YILXEv7X89FpdIf1u4PUrl+PfnlOE++G48D6OfC75x8Qfd8mogoTS9kJ/tQ9PW3BM7kYveG7e13+q56jThu62Tdq5Lm07o9RDdO8XXd83SmT7TR274nPOuaTGf/7r3svkmWvXcdqvt1L07URJ/T6z3Z4eaUfTr3r9d1+igMmI1nC/TYJWw3vRFziHlK4uC/5z4Uc/8j8fZ9HkjHK/xCOgui1ysKvRg5X6fpONh/5DqbQidGYp337zlhVDY9rcjXzfs0nOvwU4cSf4V6f2z2fKiCxLnnifg9m6Z7dzeFK2d1+ITC9pSNzAL2ieN0lnBol2tTe8k3Qfouzp4NyYN2uVnonqJAL5T/bsIN/qV/H49l5X9Q6MFInK9b9zovZTp79wd186xCH0LNSd/zMl2Di8zT96JCH0ai9IHOl2U6U4hccgC5zlcVOjFyfp5fl+tcXdndyNrjmwp9GSpXBnX9tg6fXPmsLb4dno190LsL/QmVK05rTh/J5u2ts+cmZ8/50O9zfO2dSpk8d846fTaPYYxz80+DMSr0a0D+hGvmcvhuQL/5e9fK5SmZvcfJY92vk2Pgw7KT72N62XUT5kgfE8u83xeGcfN9Uab3VddD+NLPgN5j1/+3ONALe2AAn72HWV/0T0iO3lPQ8aIbAAa+MWi/wg3H8l4F6PhKgem9HeR/6cQ8OWQHbH0W4VBbhj03p290JGZU7p8psfhNh3I/eeN/hwO1M70FvvRwoPcm/w43R2+BL70I6L3pv8PN0Yvx2C+mb8ag92YFbuw/AfsZjI1LXTAu6I6fO5bp/cTNMXZeT2Whx4Zb/EcsZPDOsDcKOOU3GdKweSRmrO+rIyw0aShTcqsSg5o11NVXxri5HbUH9viH3vq/wUOSZ/E9mFeO0SBvn79NiQNPCGX19tseielCv9FY9nYY231Zch8E8uL70X87vhNjyqyQdFLLx03OciPFoxoZeUM8RCez7lwZJ/nU40mSViwhRCx2z7N5z6sjzPo2YGDNMp6/lDAb2+nS//VC/2HHTVHqDzw9sJMM7j1ey+ckhVa2bbnqzgBJB4bGQQ+cForWsA+meuNRFKAV1uifdRWQ7+x2MSM4TftT2WqRJqR/r8c=
*/