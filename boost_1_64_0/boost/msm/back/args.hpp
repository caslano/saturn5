// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_ARGS_H
#define BOOST_MSM_BACK_ARGS_H

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/control/expr_if.hpp> 
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comparison/less.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/function.hpp>

#ifndef BOOST_MSM_VISITOR_ARG_SIZE
#define BOOST_MSM_VISITOR_ARG_SIZE 2 // default max number of arguments
#endif

namespace boost { namespace msm { namespace back
{
struct no_args {};
#define MSM_ARGS_TYPEDEF_SUB(z, n, unused) typedef ARG ## n argument ## n ;
#define MSM_ARGS_PRINT(z, n, data) data
#define MSM_ARGS_NONE_PRINT(z, n, data) class data ## n = no_args                          \
    BOOST_PP_COMMA_IF( BOOST_PP_LESS(n, BOOST_PP_DEC(BOOST_MSM_VISITOR_ARG_SIZE) ) )                  

#define MSM_VISITOR_MAIN_ARGS(n)                                                        \
    template <class RES,                                                                \
              BOOST_PP_REPEAT(BOOST_MSM_VISITOR_ARG_SIZE, MSM_ARGS_NONE_PRINT, ARG)>    \
    struct args                                                                         \
    {                                                                                   \
        typedef ::boost::function<RES(BOOST_PP_ENUM_PARAMS(n, ARG))> type;              \
        enum {args_number=n};                                                           \
        BOOST_PP_REPEAT(n, MSM_ARGS_TYPEDEF_SUB, ~ )                                    \
    };

#define MSM_VISITOR_ARGS(z, n, unused)                                                              \
    template <class RES BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class ARG)>                    \
    struct args<RES,                                                                                \
                BOOST_PP_ENUM_PARAMS(n,ARG)                                                         \
                BOOST_PP_COMMA_IF(n)                                                                \
                BOOST_PP_ENUM(BOOST_PP_SUB(BOOST_MSM_VISITOR_ARG_SIZE,n), MSM_ARGS_PRINT, no_args)     \
                >                                                                                   \
    {                                                                                               \
        typedef ::boost::function<RES(BOOST_PP_ENUM_PARAMS(n, ARG))> type;                          \
        enum {args_number=n};                                                                       \
        BOOST_PP_REPEAT(n, MSM_ARGS_TYPEDEF_SUB, ~ )                                                \
    };
MSM_VISITOR_MAIN_ARGS(BOOST_MSM_VISITOR_ARG_SIZE)
BOOST_PP_REPEAT(BOOST_MSM_VISITOR_ARG_SIZE, MSM_VISITOR_ARGS, ~)

#undef MSM_VISITOR_ARGS
#undef MSM_ARGS_PRINT

}}}

#endif //BOOST_MSM_BACK_ARGS_H


/* args.hpp
OmTzM4lmfQ9xUGhq9dLteMZEShSjIh2L3dUhzhJbsY9n9JEURTuWlCBOnvAk5sqiJYWvqaYRe55ve6pnRDVQQsRZIOaVM2ydgejSbqeHokqMtrM5XkjULwEpy5ZJIec1NXsd1a6zY0hEKouJGfe237HA1wlT5Zlkg3rhCY+k7yMjSum0INHgReBfndtx55ocUKnKEXAqSSJB3BNX3mKbzu4R+lEGucWLOd4eA+IxG8Kcz2zNddmTdFWZNF0zrsN/yD7cUC5F0ahJfQr97bE05ab/YtegTUxw+g34MBAR1WO1WANf9USP2DOVMKcA9HwlXJDZBTXdX0ykPGug+WgkuTQ0ogT2S9eVC9zP5hsLw+nytPGHXBHdjih7Mgl+Vt2isvRZ5O+Rp7pDow+T1UkugNbmf4Y1HsvWWgXQ3ne0Fk+gIGlPWOuAvSct2mPjlcg8Gz9WoOANIMTv1bSHv7UTkFcs3hO8i2GGR+sk/W1aZppnbzK3+9Y6Yt7BK2//DEtXuowvVkuLjCnmorO0uatq99pcqBu0eU1aBauiFFlfnEuuB8xCOcJ0GW7xPQ==
*/