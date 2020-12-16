/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_DETAIL_DEQUE_INITIAL_SIZE_26112006_2139)
#define BOOST_FUSION_DEQUE_DETAIL_DEQUE_INITIAL_SIZE_26112006_2139

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#error "C++03 only! This file should not have been included"
#endif

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/vector.hpp>

namespace boost { namespace fusion
{
    struct void_;
}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/deque/detail/cpp03/preprocessed/deque_initial_size.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/deque_initial_size" FUSION_MAX_DEQUE_SIZE_STR ".hpp")
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

namespace boost { namespace fusion { namespace detail
{
    template<BOOST_PP_ENUM_PARAMS(FUSION_MAX_DEQUE_SIZE, typename T)>
    struct deque_initial_size
    {
        typedef mpl::vector<BOOST_PP_ENUM_PARAMS(FUSION_MAX_DEQUE_SIZE, T)> args;
        typedef typename mpl::find<args, void_>::type first_void;
        typedef typename mpl::distance<typename mpl::begin<args>::type, first_void>::type type;
    };
}}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

/* deque_initial_size.hpp
SbgKM3A1LsQ1uAjX4gO4DjfgetyCD+AxfBBP4EZ8DjdhMW7G88iylAPx+sh3FTws5V8L50k5/IksNcc/S7m/hSH4NvbBd3EiXsREfA9n4Ps4C0twFX6Aa/Aj3Igf4z78BB/DT1H65Ml3DtIq6dH2ydsh+2UnBuPD2BH34lDch3G4H014ALPwUbTgQVyKh3A5HsZ1+CQ+iEekXNJ85BsELJJ01MQJko71Mrb4AxiMG7AjbpR6uUnKZTNm4hY04zYplx04D3dq+8hJfK9JfNo+cgGkqzk2xnbYBEOwKfbBZjgaA3EiBmEmNkcztsQVGIxbsRVuxzZ4GNvik9gen8aO+CJ2wlews5TLAR95n4+V5bhRzjPbNWOn++FubIx7sCU+gmG4DwfgARyHj+J4fAzN+Diux4O4Fw9JPXkCn8An8RgewbfxKfwSj+G/8Dj+oBlD/TMfeZ8P6yS9Adb6Kv2spT6NwmCMx044GqNxLMZiAppwHE7G8TgfJ+BanCj1JxF3YRIeQROewGR8H1OkHFPluE/DOzEdh+NvMRYzcDJOwzTMxGloxhzMwqWYjSvRgrYxt+UdOwwmFDqMuf2G5PdNHIDnNesllbPey7LeK7LeGVSvQ7KeyeA61E3WC5HyDZXy7SHlG4ZTsDfOwj5SruH4CN6JhdgPL2F/rEo8A7A+RmJDjMLOOAi74mDsg9F4F96NgzEGE3AYTsDh6vEu73txscHxvlDOg7lyHlyEA/E+jMH7cSIuxkRcitm4HOfiSlyIq5D4OC/I+1Z8WuKrjaslvmckvmclvucwBJ/HPvgCjsYXJd7TmIkvoRnP4DI8iyvw97gdX8Wd+Druw3NYgMV4FN9Qz0fybhSLDM5HleV8VAXboS+GYFXsg9VwNN6CE7E6ZmINNOOtuBBvw2V4O27GWrgVa+MhrCPnp7pyHNXDk1gfpRzlXSZlZVCOl6Qc/y7l+A8pxy+lHEulHL+ScvxayvGfaMZvcDV+i2vxO9yFV3APfo+P41U8hj/g0/gjqsfjcefH1atyfLyGA/B1LBsDP0nWay7b0Y6BH6gZKz9PluvgYrliWa6di+V4z6XGm+Sw3FXNchGyXIfyl2PHSbwuliuS5RoYLGfSLFeixlvecoRC18ulEZJkuS0Gx/1xqecnpF4/LfvpdzgWT+IUPIXz8Blchc/iOnwBN+CLaOtLL+8gcLzEp+1Lnyn3u9OxL5pxDN6LZevnl7N+mqyfLuv/VtafijFVfVz2R6fPul3fq7030P/ql9IfPfQu9/pq/bf6pF9sWeV/sl+6/4CK6Zte1hfsEvks65uegvH/Z33TV8/y9fZPr4D+6ZfDfdU+6hkHmQ+BcJRwgXCF0OQQZUowEzYTigiXCLWf4O+EJMJiwgFCMeEKIegwcygQUgirCQWEYsJlQsMCX58wQgLBQthAOFrg7Rv3a/7dhPb/puzMbjfc/r8FffxnN1BeflX1qWwd3i8ycvSo/pHj+NR9b6LFQvKty1i6c9+3U5aJj4u3fd3TLiPbeViWiYvvHz86zm6xAJYprM928mWZUVFxsYmmHJ7rrGMNpLJ+hPa/abbfWv57gfW/R8Wx5bi40YxAGBc1akj/GHXJFrJc0K6y5SKjRpHagQbbylOXiRsyePiQ4YNty8qC6rZ4WcFyDsMEavP0PC8GzSwj6R4p/83at2K9Zk4FLtvqd1M/ucffRLkm5Vnv17SJTckxu+5TUdbOP6Gt2h9BjavEIK45LJevi8v6/dLDuEx239Lipb1/dVnhFkJXf/alPq50d+aIrk+ZRrB+knX/0ILZlGFdUZu/AokzUL79BhA2dyff+jj5/uu6LLVtYoJ99WW3Van/62XbjpU=
*/