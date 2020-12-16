// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_unique.hpp
//
/////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BOOST_PHOENIX_HAS_UNIQUE_EN_14_12_2004
#define BOOST_PHOENIX_HAS_UNIQUE_EN_14_12_2004

#include "./is_std_list.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_unique
        : is_std_list<T>
    {
    };
}

#endif

/* has_unique.hpp
V3wdTYVah964HmvgBmyEf8HRuBGz8a/4ABZgHm7C1bgZ38YteAa34VksxH/im3gdd2A1GcO2Ae5C8/1ecm6B12U7++Jiu/tbmmAQNsVQvBu7YDMcgM1xPEbgg9gCl2JL3IKtcBtG4kFsjR9jFJ7CaLyAbfAqtsWLSBnl/IHjvWx/luV+WnmWm8TXCQOxKzbAbtgOu2NfjMHB2ANTsRfOwd64BPvgcuyHa7E/7sYBeAAH4g84CK/gYPQihiFYH4diaxyG7TEWh+M9mIpx+Djei/k4CtfjaNyM92EhjsF9OBa/x3F4Du/Hn3A8XsV4DKEuErA5TsROmITD0ID3YjJOwBRMxVScg5PxeZyCGzENC3AqbsUMfAuNuBszcR9m4aeYjUcxB+U+Ljk/IC/SQrv7uGbLdsqT+8bmYDA+gn1wLo7FeTgB5+NEXIBJ+ChyXsp13rKvBYe1YoxMUqHumMC35hrxuQdvfJ3YlTGBG852eK2YC/W35nrxlodufM047OEbXze2XDMeTR2Xdd3YI6/SbR8j+GauG6e0crvh+MA3e+3Yct04bu6//9pxLuXTu37sO+/WjRG8hDzU14+959/cNeRbef24gNgOky6RfCMZH5gURzKS8kkFkRXXeyteFa+KV8Wr4lXxqnhVvCpeFa+Kl/Ov23v9Py114i0Y/990/X9ZCN+PFpuuqSQlpBviueJkvr6/3beSMmbkOPk6FEaqQqpLeoXlCgJLr/kM6zkwfmKWISEzMSW+9NJaqjHFkBmfyk8zzl8Pz2WCIZSU6+FZvtRfQpbNeFXZ5jFxbcYCZKL0NYjkQ+pHKuBHpOJA9b0H1nGGErMz+TnL+TEe9cbU5lqZEtN68ko2msfQDa8hfdlDbMcOnSkx/knq71nSa7wnpoZtjCkGAjSah92MpzJcqb9U3kWcNnVTIvlGS920Ir0ewp8g23zT2HbxGTQQRhm+mboJJ2VQF+oYjHI/QaTEEGEpu10M2fGpWfGG9ISJaYYkV2KQctvcr7FWrjVPqUqe4hK2U559njQFUz61y8yHUvLKrcWyyjQvmfbnOvTOmvzb9FPY0DbtKsm8563z2lrmZVnntbHMG2idF22ZV986L9Iy70KIZV50e8u8P1vnKctmW+dFWeYNt85rbZnX1zpPyaOzMi+qo2VepHVeB8u8RtZ5Siy1rPOUOrjLOk+pg6rWeUod/BaszFPKcd46TynH99Z5SjmOW+cp5dirzGutlONN6zylHKus85RyLLHOU8rxgHWeUo4x1nlKOQZb5ynlaGedp5QjyDpPKYeHdV5kJSeOP/7qMYEZkA+UcfxKx1djnvpaeun7SKbj1KWa5ra7LsR2X+0t1/bby74aLccL39o2+43pg0IOGqV3wzi9r9rfzxVOMq/Bev9M6TEkM3WS/T1eWyS2IDmGBpJa8WeCNjY5jDh/7JS4bOpinNy00FDyCydtoC7ydPKbahpY0TSMoAvHa/vtOolpNquyXcNIpeuVZQKRedRNkk2cVyTOtrLNWss2K9CJkwjNW8yF4+vNbLN5ntpnXrQ3FaSOOjbZXByOXTnuW+KqpdovuB0tlTEE+Rgz3UtksPlMKJFYvOT+ozvxL9RTvm0sphunbnjPijqGBLQd89Hu86+ath1tJN+wMJt8JxmyI9WDOTrdjvQ+909KntUlT2/SJvKM1cszOy1jUnxWdkZm+fK0bOs4L22eb5CnUSdPjk0JU8uxr6jLuF/yayT5NSBtNm1PnfzklIozKufzVJexr+X4KDfTBUqe/qQt5Fmkkyf3aeVkpmbPYlzd0tGPb/ZcrlDy9pK8PUlbybtYk3dpMyrdos7c51rWNm3qo70XdBt5XtDkKec=
*/