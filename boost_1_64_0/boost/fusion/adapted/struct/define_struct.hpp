/*=============================================================================
    Copyright (c) 2010-2011 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DEFINE_STRUCT_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DEFINE_STRUCT_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/adapted/struct/detail/define_struct.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_FUSION_DEFINE_TPL_STRUCT(                                         \
    TEMPLATE_PARAMS_SEQ, NAMESPACE_SEQ, NAME, ATTRIBUTES)                       \
                                                                                \
    BOOST_FUSION_DEFINE_TPL_STRUCT_IMPL(                                        \
        TEMPLATE_PARAMS_SEQ,                                                    \
        (0)NAMESPACE_SEQ,                                                       \
        NAME,                                                                   \
        BOOST_PP_CAT(BOOST_FUSION_DEFINE_STRUCT_FILLER_0(0,0)ATTRIBUTES,_END),  \
        2)                                                                      \
                                                                                \
    BOOST_FUSION_ADAPT_TPL_STRUCT(                                              \
        TEMPLATE_PARAMS_SEQ,                                                    \
        (BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ) NAME)\
            TEMPLATE_PARAMS_SEQ,                                                \
        ATTRIBUTES)

#define BOOST_FUSION_DEFINE_STRUCT(NAMESPACE_SEQ, NAME, ATTRIBUTES)             \
    BOOST_FUSION_DEFINE_STRUCT_IMPL(                                            \
        (0)NAMESPACE_SEQ,                                                       \
        NAME,                                                                   \
        BOOST_PP_CAT(BOOST_FUSION_DEFINE_STRUCT_FILLER_0(0,0)ATTRIBUTES,_END),  \
        2)                                                                      \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT(                                                  \
        BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ) NAME, \
        ATTRIBUTES)

#endif

/* define_struct.hpp
c4fqE7N5bNKqXeKIUKi0gpb+5BQVTcjJnSxWKBSW8XQz6woqsmlMDV3BYnRLf8igMTrZX5N9BLkZn8jjIFrWUFxeXlQ1lUMckjqDOaH0OoP2NGYXc3udeMzO5/MytlCOowjj+4xDbQgb4esK5oS6UFy60DuVHJfqOPvHr5Ob0EOcz3qI2lSsJsTvjyesvp3AaK0dvX8kvV/qvT+nOhaG39m+33WRGHQR28luRXG/luzoJIor9B0FYpzHYUcYpK6B/Dux3asTpVx+/xA/f4rnN7Lkc99JJp/C83bway1+PT+zf/z8N8Wzn4PxjUqbyQSeReZoMqeR6U7v7Cxg+apEbAGfm1VLeHqdTpah05nH6V41IVVbG2mErqVSjmUVnitPZTkcep38tsxNbGisr+ZzZPAN49KtnMbZRdEE5FWaV5VFEqm6pExHyneHcpweRZxIjsfY/ch07EhuyfF3Khatj9dF6iMxPgNLxqtP2nwn0+9KfpdiSmnj6YY2E3D50WLMn/F+t8Smhy7r1PDRZW8cX/5GVTpdQ3rdxzusUzhjYc093ee82zx1wqS7L5r2Zj2FfZDA135872kFT962POPz76d0uGLVbRR/xtsOuW3M8FjLmm1PPfTn1Xc+eFd6nQvNoxJ+6ZbR5/T5pG7tb28tKul87uaX0+ue3Dqg9Dopt24ona4qvW5lE8cr2aPymGGd220fu2h71eq6TS+m11UdMVjgpz6f9be5X913W2140w2nFL3XIZ1OKr0O7jPxbTNQN6HOWpIhy0RHAUAXczh0MD2gU5lM9miyRVkeS/Y5ZI8je6XQHUL3kkP24yIzkb1R1PdkbyV7ItnvkT2J7D+TXUj238kuIrst+TmF7M5kF5N9jKgwyc4lu5TsArLLhE6I7HKyp5NdQXaY7Klkn0/2NLIvJLuS7CtYN0rhIvsUsoUedwbZD2ZwmV/ykCjsZD8ndERk/4HsarL/RHYN2aLuDpMt0qkghPoB9UYr+qMlp4P8XdIytESk23KyRdm7gmxRL1xJttDPXkW2qGeubindo3KOssllltJdto/9Nd3YIdCNZYn6KUTuQkfWh2SX7kGXtWok67pYp7WZ/t5OpuMo+hv6q6GW3moD9FXjWUel9FN9PF0U9E89R9G7o6T+KW+U1EFVjCJ+lKmLSo4iNzX90+I0eqakpldaOUrqkhZruqNbRpn6o/WjpM5ohaYr2jZK6oqyff0Q4YS1Gk3hHd2kI2r6Nf2afk2/pl/T77/9+8/M/0dis6OxSGKGONYzXNdQ86/rAcSY/uRs6ttivNgWfeEMLyIYW82U/WYZAHnQOoLAO7l5jAVx5xhLjanSj53cY5L9nzc+qLnA75x+ZuVHLZffevaaDju2rL58Y/r521ye5x/9VZ9jK75cfNFdk07p/NEBl1BHf/UxAv/lvdc98dJz83af1X59x36tvpqSfr79dvY32eXiL849+bpTLjjuR79oO/RAGgAkGT//tutfff+Z7OxznylfGL109Uf7v47APQZLPyZ0r19IN9ZKP6aaMFjgk344/y+F7647a9Gm5T955p5bT5djqj5kkDfYrKP/RE+0Kz7+cJ4al2OlLCLmUD91KZlbyGwks53M7tFyLjprDPXLx2BOWpuLnkPYUjLryGwm8yGZVmOpz05mNJkZZBaOlXPUq8jeMFbOS39Idttx5DaZCjLJcbLvf804OV+9RuBibprsHWTEYpAsMgXj5Tz1zPFyXLBkPMmS2UhmO5ldZNZhjrpzDs1jk6kkEyezMkfOT68he0uOnKfemSPHCB0nUFjIzCCzhMyqCYSTeY9Mq1zyi0wY89UFuSSXS3K5chxxTa6aq16XS2HJlXM=
*/