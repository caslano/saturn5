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
ouKhPOfDwzkP5WFySbBtwIeC1VAhfViixT66XYJhGaFiJFWg3Qyb3TId979hcvdPpA4+ASzxUOGFTlMnqNg8z6m9kva3Ku031SoDYJjRFvYAKoNQ1RjY5IwgRn/3JuWhrCekdNnKzm1xJvF7xmavsXPne4wtwCEbvYg/dRefXmCfkil9NygtC2U0Gc041bBsFvYsTVyLM9Ys1p0aivepep1NBLAuiTQB8ah+XMD1d7+2evByY6SCD4tO/QgYUxNW4LTKZ6M+kpg15yOIGn/+Y2LZZz8m/wf/OZ4fn/iYnKjDPw4Ui/vnq8HzJwxb7U9vw64i2+NMSydA2PC5LEzON5xN4POlKY8cdzpA1oTXrQ7F29M5PpC358kPEcZXPsJDyUd+dJYso6591UNGYck9C06AxR951T0mqhahiLIwsZsDcgpECEmlfJytIvyrSCrlK1Ipn0ml+SiVDoLZ5eibgLnZoaIaSJQ0DAdgbSaC0jrLlVYC1KBEYkHSAXa0UBm7nc4R99PWBEMxmJwjU7pajWYeL0a6y4htUjE8QAA16N0QToWNuMfhQaRcjIP7Rgq1yZSlkkeueIkU17UOQoqnPsAxb0kYiP3Qn36gnXtvviLTk5AuVmWIhyjSQt4yQetsS9HYpcFWPLbVX6tXR3CwjfJgv6wabIzRY8JgS4a4DlZHb+/LN3dMgdHr4Dl6CbSZD6sHSm+AL3KPRJ34
*/