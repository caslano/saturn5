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
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
*/