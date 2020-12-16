/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR_FORWARD_07072005_0125)
#define FUSION_VECTOR_FORWARD_07072005_0125

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/cpp03/limits.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

#include <boost/fusion/container/vector/detail/cpp03/vector10.hpp>
#if (FUSION_MAX_VECTOR_SIZE > 10)
#include <boost/fusion/container/vector/detail/cpp03/vector20.hpp>
#endif
#if (FUSION_MAX_VECTOR_SIZE > 20)
#include <boost/fusion/container/vector/detail/cpp03/vector30.hpp>
#endif
#if (FUSION_MAX_VECTOR_SIZE > 30)
#include <boost/fusion/container/vector/detail/cpp03/vector40.hpp>
#endif
#if (FUSION_MAX_VECTOR_SIZE > 40)
#include <boost/fusion/container/vector/detail/cpp03/vector50.hpp>
#endif

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vvector" FUSION_MAX_VECTOR_SIZE_STR "_fwd.hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
    struct void_;

    template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
            FUSION_MAX_VECTOR_SIZE, typename T, void_)
    >
    struct vector;
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

/* vector_fwd.hpp
B2M85GrZzjdhGyyQdgVrsBvegmNwLU7DdbI9bpXtsaEybp1UJPkkSv21kPaHyvSCbI8X0Yol2BVfxiH4CkbiQUzGVzENX8Nl+Dr+Hg/hXvwzHsHDsn8fwS/wLfwZ38a+Ek9+PR7FkXgMZ+N7GIfv6/enMK2dTfQltrPJJ5XK8g5LvevbEaRLfWRJPWTjCLTL/rMIp2AeLsDFuAaX4EZcivdjPu7E5fgarlDbP8h9NQ6X/PVxuCmyPgswAlPRGY8q98jYXdZDH49q1c1n93K+YplvgJRDP99mdT65x4OQKpYX1s+7fO1ezlfs5XxlMl/XqsrX3/Py2unLJ/OFVDFfkczXuor5SrxcXpmX5QsbIOt7kfnCSXaZb5Bj+xrbGf1O9vMHsQM+hH1xJ1ZeF0vk+xdMrou7ZD/dI+el38tynsQ+WIwx+BQuwL24Bp/G+3TtW57BP+AfsASfxb/ifvwGn7N413f5/0qcorcxit70W345YxOrikuM+byBz7GJrnGJGSxjM2kP6QipnNTiC/oPJsWQMkibSXtIpaRyUsfTxDKSMkibSftIJ0n1vySGkRRDyiNtJz1POvGlP1bRP/kn//TfNV3m9/+Zdsf/1cz4/8r7/9/o3v+H1ZK2TfIsaBqpoZVld3b8Xhg5ZVJ0/MiYWK/HWax85lPP+ew7L1/ej9bv4vz90chqfD+5U/JvQrpKnnteyzyRXYz5L7D5Ps7zr9QyGPMMknf4Q2SdB5KCmTfBJE+l80Nf+taRPLNdx9jcLXlulTzvVJbJvMXGPL0eNzJS0ereb149l7Ekm4c6672BS70XSlzAvfJbdhvJyjz2UK08ylowSm9u/PyM7KT0qp//SRyDbttrfZFZ62n9HBn7SMnmhao6hjDzGfvxsqvzpTGfSf9ksp6HZT2buKxnfl3z9Qzrqq2nLd+emJXsXEtf4jV+ifXc1NWwnupxfFrW8xo5jpqQ2jNPmbaejv1ZiXLwpT+71lbzsdJj5Z17gOTXmNSBeQO7GfPj+Lmk/Mr5LLyW5+elDR3tsB+/cXnsuXp3PLx6d/OTRx7ZctDzc2Dz57e+P3f19XlvTT0X/SBf+XzuzR0DSgYdyXv017bc5E2/vki/O84xCOV8Luf5+rWMYxD2lvu/MGyDfTAY+2F37I9DcCBOw0Hq8w85T8v+Vt/l+YdV+pcIwQBsr35PzrU4xOR7N0p5ZuNAnKM+Z5PzJW6V7+mfszWT77WU77XCwdgax2IQLsRf4c3YBjdiMN6J16n5yHkQ7zXJZ4iMWXgDhuFQHISROB+HYxqOwFU4ErfgaNyGY7R8OA95zme85DNJ8pks+URLPlMln2mSz3TJZ4bkM1PfL47kc41JfXeT7dQdm2AP9XtyPGOAyfc6yfc6Y2PsgmHMczCCe2ZSRYR2H3+IlHoD96ukQ6TTpPpDuRcnKffwRVhCKuW/A4cZx5Q5xN8VmBDpvCcvwIOR2tgyQcOZ70wDy1bU33v3H8E9OamAVEJyHWum/iju3Ul5pELSflIqyzmOFaQeo7mvJSn30mVYeR8dNoYyk5JJQf1ZztjalnDSDpLrPXN+FPfgLHM76XnSCVIFKfgs99yk2LP+e1r/5J/8k3/6X52u0P1/jY3/t5sfQPbuXMsdP9Pdx/+bzw+hEvXf3cf/u8eL8f8SlN+b+vH/WFJ1xv+rX+u/b/w/X+8VfB3nL2CZ47d8j9kvHt6R3rLi1p/H9O7Usm7lOH9St1LnZRbjO9Qu8lu7G3bD7hiOPXAM9sYJGIabseJcA0vQV+7j/EXJ+xPtd5jrmH7ejednHMtPxvEzebcQ/pX/d5B/8k/+yT/5J//kn/yTf/JP/um/f7oC9//xy9U=
*/