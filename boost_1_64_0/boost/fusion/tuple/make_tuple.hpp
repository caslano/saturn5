/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_MAKE_TUPLE_14122014_0048
#define FUSION_MAKE_TUPLE_14122014_0048

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/tuple/tuple_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_TUPLE)
# include <boost/fusion/tuple/detail/make_tuple.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/tuple/tuple.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion
{
    template <typename ...T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline tuple<typename detail::as_fusion_element<
        typename remove_const<
            typename remove_reference<T>::type
        >::type
    >::type...>
    make_tuple(T&&... arg)
    {
        typedef tuple<typename detail::as_fusion_element<
            typename remove_const<
                typename remove_reference<T>::type
            >::type
        >::type...> result_type;
        return result_type(std::forward<T>(arg)...);
    }
}}

#endif
#endif


/* make_tuple.hpp
6XL8locctqgtkZSSuch0tdtsjWU0BLwdv63hHI94nYzCKhnI+RkD8THnJZK1vAhZvCJXiy2yjyBZHZxkqpAFiCK/jVY2EJtUYMlmcnBjcfaa59++2cch+jyW98tARzKBfB+H6HtYPhSdTKER5Ps4RI929TFZRQnyL7iN6jP8/AvJF5szE8lW+asqv/f8Xv7JWD6JKCRlAeT7+j8Ty0efrGHKg3xf/+tY3i8N2AWr8ucr+VtYnmD5wJmh3tBRfgfLFyyvuIzGBL3Sz43ru2/q2vtqLF+YyYqJtX62xJlaYPnklaC8BJDv9fM2LB+FtEIED/K9ft6B5T130bi01k+V7/XzHiwfgjXSOgryvX4ewfK2JCZD5Gv9vOBGr59PT8aDZsGHlfzN67d6+c939VGaGyPS0N4qvzPR5/ewPNOKKhbEuvzbk/56FMtn5bzgTK/Kv3Xz+Rf9+P93+94pkstJsqU/7+L5z7+xkb42jn8kz3QQ1iQG8rCZw/jH8soKmb1eyd/YnZZ/Hdcn+8ySViA/KZ9geS2psmZd/u3rr5+UX5A8V8FEat1GflqfVyP57LwT0oM4VGcc/7i9mTlqeFwB9m5M6/M2JB+90CzIspSvm+BU/h1IPrnIrAh0Iz+t/3uwPGeFliRX8ju3p+U/guSV5UnasJKvh4hp+Z9G8kUwL4VYKWjnxvOn8p9H8obp5Ixeln/1/OffnMp/D9fHSxqlNyA/GQ+PInnPBoAtK3kY/SBff/7TyltvnSoygvyNyfhH8okGn4QNS/m6G031+UwkH4VMMhi5kd8y/pF8tpoyGwzIT8c/kpeMpRS9WsnvbSm/IHntBbVFa5C/MRn/SN7lmHlWq/Jv3NzS3gXWZxIuaO838hfT8Y/kCzMiZsHW8ntbxj/Wj2OZFSlX8rtb6vMeXL7PzpoQNvIX0/GP9UOtV6asxsOt61vq82kkb4RJsVCxkd8y/vH4iZIb6lf633nB86flfw+PnxJUtspt5KH8MZ7rfzqbMWlUjEbBaXRI7nQ6RFIbDptvujq5hCII5Fa79gRURtRS+FzMw8u4OSnjeleGdZQLK+jDy7g1KaN0ZTjKHHWGPbyMnUkZi66MEIRUPvCHl3F7UsY7ujI850WHIh5exgsmZTzSlTHsPMaI+PAydidlfL4rQ0QfpTbp4WXsTcp4FJVhSSkpRW3j/xgf64xrzfh4DC4j66iLiel/lPH8vozrXRkx5eAlzf+jDHjLhbWsLWPPMObyMDrqBRhYIqDcKq9GnJxwKaOlRsEl0fIiDGFvwB10iy0kSq1tEmUdfjjOFovRcxzuMRCfIcmxQjlPk+DDGE7BrgXhGeGKc+G1IvXO7fg19c4NN/Qe5PFAOE9UoVRZmoHXrvBbGkzgPrgtIxMWnHRMGZJnrz+ZV4s0yW+kO3s3J/e6f21xt03IxTvGVjlr19IJ7D0fiziUTIoaRzuOWxOOJz+25RDSZ1GSXnGspRPYYjz9cdiGi3pKaRSE0yhDsBRHWR14DsDmvfK0WC2yTdlIclAvE09Ojmco2irGXnsG5k1CRGNUAV4UPRRjr3e8kRrpXbbAu8RiXnjz7niZ5cqmDLR9UMwNp+k4GY/eau2AcwnEnDCvOqxMjFOpHZCiiLkY+6DDqqx88ikDL4qci7Hv6LA522xEUVjH23k/0GFLitonybGOt/N+usOKKKiKRmIlb+f9WoflxVjLo8B63s77aD8ec+DOqTwZy2rK+8THYaxJxUuT3WQsv3bK+8wOGxPPOUeO9bydd7fDpqy1oEZhPW/nLR2WFUcjkwLrGfOC/8ekzpaVIrGagbbxKUI4TqTPNLpkgbN/rW7q+64OWwm1N3ybjifYRzo=
*/