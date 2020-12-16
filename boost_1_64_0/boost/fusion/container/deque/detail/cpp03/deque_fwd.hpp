/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PP_DEQUE_FORWARD_02092007_0749)
#define FUSION_PP_DEQUE_FORWARD_02092007_0749

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#error "C++03 only! This file should not have been included"
#endif

#include <boost/fusion/container/deque/detail/cpp03/limits.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/deque/detail/cpp03/preprocessed/deque_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/deque" FUSION_MAX_DEQUE_SIZE_STR "_fwd.hpp")
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

    template<
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
            FUSION_MAX_DEQUE_SIZE, typename T, void_)>
    struct deque;
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

/* deque_fwd.hpp
74/a17kIg30WbbjPtPXTmgSpn/r9GOSwz6R8OVbVdRM5x1vzf3fZOVrGyNtMaCJ99pU6GvGYPv+MojiVpi+pyenZJC4xJX1KuiXbzfI495haHteVf8e8BhvkNUgdy0mS5jBm4W0y5t0iyes8Qke26/O4Lq+2iyPje85IT051d5/Pevz68ljfbh9LnAb71LEdVXUZ4+41qbuvSN0t0OWHjEyWgbbczEv6wYrIixql23U2wKjfHpXWcV8WSt4ryzXyB0KAP3k/aJR3Ey35ElMzpzAdp5vX9HsOafOvzVOmaVqq83NkGL5eV/mb/Zhr/rdem3+4Ca6Ua4HPE7r0UnlTsy3Z7l3Tcw7bp9NssJ9mOTmucg32R1uDa0GwG9eCMPVaIMmX8/gp5fsIeV/Bv99X8qqrI7R/s57KpUy153dN+72jftZrRIr2HmGQlG2RlO1g23FNHZGyLdCVbWp2tm2QwnRundJM6ZnuHNue1H+j85W2HiTdZpzWJH1ap2elpCpftm5q+opul3t2qacTpJ4W6dJnO5+kp2a7VU9vOfLz1lO595Q6WJY0d+tvlTop7JdTt9vmDU590vN6KsfAtTaYlmlmqat25VtQ61r74ebSfrgzecs9oivfbPa+KcON+qmU77+PXN/5uqw+tLCV7yRPztVyfyFlLsl1uEbtvUPmzJT8HpVrVNen9PlNn5KZmqUcnm7Mzazk+c9P3Vier91TeZ5nnttkXdvVSXtt2i4juxZJnk9KnoOOOsmznPLdORcp+X7raEXke1rK9exr23lYSXYiG3DY19b/5R6b0Fz2eVe2W/uYs3xPTXX3fuTksYrIsxKf8+e7JA/KoaCObE/Z/Q7n0IF+Tq5Hx+3LQd57KDcULsvgevKsO8dLu+9CP/08+svqcw06bjCHvNKNwoOxTJfUN55DP7qu8bz1ecdv7rz1ZWVQXFc/p/+K+vzdID226fzdT8uS+q7n8+8p6Yjw1++LXkr74hPa8WXpIzNohLIr3E5Djy7G+6HYX78fQkJJhz4+dTd4sv/bd9Hvhy/qON8PCfX0+6Ev28jVp8e6GzypEz26uL8fjko6GhBul32xIZBzuH06rAMq52RkuEyDdtvh9fVl/hDbLrHbtlrcLrct+eO5Xl/W2/TjBqv9PU4ZpGNzIFsttE9HTnbadaXBz+6dptmS5VAOGxrYtrBF6vsGQqhy72uL35JtPeasE31MzjD9PPe9Ze/5UjNSbNcBtU4oUZZ7HZB1bbVQm6+G0jFmvJTrGEIP1g962i5f6Zmsmp7i+non+XJ43tTmy0JS7Y+jfCdpyLdPQ8b06VNzqGam9IyKTcdl9KnirF2a5+3DjPuOOG8PZ9yOzVk7P8/byRm3e/O8b4pxHx3nfVaM28N53pfF03aHxu0XnffZMu7TU3F9ifa1VP6++8mtz7/5+3uvzPUr9O9Q/bthnve1ctZ356y1PWJUpd/fPzHq1YRbH8va9NPod3Y464NVfl+fWB/5xoUmQqFDHxuL9EHJwUCcgeE4EwfiLByLc3ACztWOJSvb3Sbb1Y6t2lH6jHTCxtgZg7ErDsBusv0QHI+hmIw9cBn2xPXYCx/CMIm3iCDfnvgmZYu3njzLKb++Em+4xHunxNsPO2F/HIoDMBYjcRIOxBQchHNxMD6M0XgEh+AzeDeew6H4Lg7Dv+AI/BhjsQbpGokBOAqDMQ7bYbxafvLdCHcblN9Y2S8JGITjsB2Ox8E4AYfgREl/Iv4Wk3AtmnAzTsIdmCzxEqF88+FbkJRfU/7/ZYl3ZiXb2NGzMBjnYDjOxSich0m4ABfiQszDXNyI9+EzeD8W42L8Gy7Bb3ApVifeZdgal2MIrsAoXIk=
*/