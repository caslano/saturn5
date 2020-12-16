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
ORGXS39GlvhS5V7silosJ8878e/cWGTL3mKpkRp6Hno7hlwXpX9yRQWfzvPd3qIFm7lPPj8C/z9Ed7eiR3RalPGW9VSJ/d4S++IR4rW4kfz5A7Ax5jWXOXF+UX6e+Q3CZtjLyP0XXukvjW9XyUFVsJXTyLv7B6hZiWvnjsDm4W0puSaNHbZhLw9Sz47BT/6CLV2CXT09gfnxw/5/7CnWjDOQ7yHoZg2xpwBvXAtuQh4r8Zm7GYfYHbi7UYQu43e5J38xsiTOxn5LXGtH5i+izwbskZiUP51+WEeXd+P6U4OZM+u1pdj2Bfj6q/ja29Aj6DdEnPg+fr4VMZD5BIm/+X3hYwLrAcn/w/C8iLUoMqqsgR/GEOg2eD5x+gt4vJ/fyS3iPvh8CPnhE9UKP9civ72Jg/tR34KP5bEtzs5C6LQ0Gd2wzxnYQCx7DXtkvZz/U4C/f8n84DkErZzCT88mD7EHVsEPAreRZx/DfmP47b0DxLnYduFq+t2DWPA59fki8t5Y6s2zkQlrn+JO7Lew9ovM429afg87JQ5Wf46dvE+cwG4D3xhKXGZ+60ex78V4G6kH5JqH30Pk8uIvh6JH+n8BXYxF3yPRYdMo9rFlrUg8ABemRo6wF9e4kVzzkDyjQhYt8AcvebnH+wAxRT5fxfU858gxfoLUkwFkWKHfYBU5UcOn32OPYyF8sPeQexSeO6gNp8NbFfncRO4bP5y9AMH+JWtl4md+Pvb4CHGL+qTAd+KHXmMtCB/lOHMYx9jrsY/h4/HjYZwZMHf8PTiGmmpnbA6fqbIeCo7jvo345074xXXYx/bofSfmc+U49Ibs74S329ET69pQCt2dw9xZxwpsTyB3HhQjr5BTiGcl7C28iT1zatjy/fjhKH7Ye8vTV+VB+LqePv/Mmhx8lf3b3F7IEJ1X7oZ/fD7GeU6RmFn9CVjiUuxR6qMS88PP83KtLFgXLIUn+irJeCDXWNfgt4yTf55xVmAbu9A313Psb+dbsOe9aIvsyeIbgRXEg8/JUdsQDwYg9zx2/hkyGIyMO5HdidRnc9hHOAt7fQV5jyPe3s9Y1C7Fb2JXJ6PvzSPY8+TzFaPZD0J/tJXd8IEDiW3XoNc/kW+OGM66ihxAbM/zfZCBPYmtMWyX2JzLN3IewfcM7EVc4F0NwbjhlYz3FDnlz/K7k7lvJnEWuQV/Quwbibxlvt2ZH+QQGstcX8J2WLsWfgaPobHEP+zgTwHsbGvmxlnrePghH+Xx2/zH1IfMJX0yskdH5XEB/GkkcZbceBux9kZsaQ65HLlFyFmxl7amdoZ2Mp8Ho1PsUFzOPP+Jzxew4Ty2Q2wrPTKSvXZyF9hwIzlpMfhb6J91WWUgMeQC6NAqtGnWw3n6KWCz5S76fxy+/kwf+zOe3B9vQO/d+M2ZxMtLuPcpzpW4ll6GD7HPyXc3EksYB1sM7gm/JWx3A75Nf6UXiGcnIctTiHWr5L4l9lPAtlZjn8g/sJG4ha7T0EJ3YS8P44uPwUsSexuPzSNDcT82XBrPvio2dQ0xgbqs8AwyIs8Fyvj9q8hwOnYShxfiRXXPBuoS5jARu9mVczTiRA5/z49gTXwcMaOXGPiutBNk8jpjN1MbYaOBd7g2ESzxJsK8ith8Dp7y77BWmIytLsXeuvDTccixiB6PwA6gRyrY+D3cT17PB8GvHsu86ftq+pgynHg4jj026njmWJmB3xAfSzI3v05f1yBP6ffEnDJ/Wy3H/l0I/ko3cK69Ftr1+MDPyQHd0NP8vpGW897QDHyN+rKyjPkNgk/2i8N7IPtXsXHsvRDDH36E3f0CvzwcW2T+lWmsPeizgi1VXkU2WXyJdYdg/NK1jPU=
*/