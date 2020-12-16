// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_SPLIT_ARGS_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_SPLIT_ARGS_HPP

#include <boost/preprocessor/tuple/elem.hpp>

// Accessor macros for the split_args tuple.
#define BOOST_PARAMETER_SPLIT_ARG_REQ_COUNT(x) BOOST_PP_TUPLE_ELEM(4, 0, x)
#define BOOST_PARAMETER_SPLIT_ARG_REQ_SEQ(x) BOOST_PP_TUPLE_ELEM(4, 1, x)
#define BOOST_PARAMETER_SPLIT_ARG_OPT_COUNT(x) BOOST_PP_TUPLE_ELEM(4, 2, x)
#define BOOST_PARAMETER_SPLIT_ARG_OPT_SEQ(x) BOOST_PP_TUPLE_ELEM(4, 3, x)

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/seq/push_back.hpp>

// Helper macros for BOOST_PARAMETER_FUNCTION_SPLIT_ARGS.
#define BOOST_PARAMETER_FUNCTION_SPLIT_ARG_required(s_a, arg)                \
    (                                                                        \
        BOOST_PP_INC(BOOST_PARAMETER_SPLIT_ARG_REQ_COUNT(s_a))               \
      , BOOST_PP_SEQ_PUSH_BACK(BOOST_PARAMETER_SPLIT_ARG_REQ_SEQ(s_a), arg)  \
      , BOOST_PARAMETER_SPLIT_ARG_OPT_COUNT(s_a)                             \
      , BOOST_PARAMETER_SPLIT_ARG_OPT_SEQ(s_a)                               \
    )
/**/

#define BOOST_PARAMETER_FUNCTION_SPLIT_ARG_deduced_required(split_args, arg) \
    BOOST_PARAMETER_FUNCTION_SPLIT_ARG_required(split_args, arg)
/**/

#define BOOST_PARAMETER_FUNCTION_SPLIT_ARG_optional(s_a, arg)                \
    (                                                                        \
        BOOST_PARAMETER_SPLIT_ARG_REQ_COUNT(s_a)                             \
      , BOOST_PARAMETER_SPLIT_ARG_REQ_SEQ(s_a)                               \
      , BOOST_PP_INC(BOOST_PARAMETER_SPLIT_ARG_OPT_COUNT(s_a))               \
      , BOOST_PP_SEQ_PUSH_BACK(BOOST_PARAMETER_SPLIT_ARG_OPT_SEQ(s_a), arg)  \
    )
/**/

#define BOOST_PARAMETER_FUNCTION_SPLIT_ARG_deduced_optional(split_args, arg) \
    BOOST_PARAMETER_FUNCTION_SPLIT_ARG_optional(split_args, arg)
/**/

#include <boost/parameter/aux_/preprocessor/impl/argument_specs.hpp>
#include <boost/preprocessor/cat.hpp>

#define BOOST_PARAMETER_FUNCTION_SPLIT_ARG(s, split_args, arg)               \
    BOOST_PP_CAT(                                                            \
        BOOST_PARAMETER_FUNCTION_SPLIT_ARG_                                  \
      , BOOST_PARAMETER_FN_ARG_QUALIFIER(arg)                                \
    )(split_args, arg)
/**/

#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/seq/seq.hpp>

// Expands from the flattened BOOST_PARAMETER_FUNCTION et. al. arg sequence to
// the tuple (required_count, required_args, optional_count, optional_args).
#define BOOST_PARAMETER_FUNCTION_SPLIT_ARGS(args)                            \
    BOOST_PP_SEQ_FOLD_LEFT(                                                  \
        BOOST_PARAMETER_FUNCTION_SPLIT_ARG                                   \
      , (0, BOOST_PP_SEQ_NIL, 0, BOOST_PP_SEQ_NIL)                           \
      , args                                                                 \
    )
/**/

#endif  // include guard


/* split_args.hpp
E7g3+HTwFeAzwYPBXcHp4HPAN4HPAw8H9wCPAvcCjwVfBH4C3Ac8HXwxeBa4L3ge+DLwAlrz+iF4IPgrWvO6SgDHbhtbTNe/gIeAS8DXgTeA08Gb6XnbwJeQPmbpv4ehU9KHGTKF9HEj6eNmcCJYAbcCW0kvGaQXG/g0cCa4GzgLfD7YQXoZAe4PdpJ+csEDwW7SSx7YDb4TPBrsA98Jvo3KuVb/rYW2onK2ghRROd+gcs4HnwB+m95ZH1C/WEjt9Qn4HPBi8KXgJdQ/PgbfTPczwcvAPvCX4LvAheDx4K/Bk8DLwTPAK8Evgr+j9ikCvwdeRWuC14A/AxeDN4JLwJspvAy8AbwbvJHqmab/lkCfonoeA+lH9XwO8WLBz9Ma5BfAx4FfBFuoH3Sg61TwHN03TN+f9B0/N8A3nE+fq6fp+U9Rut7a9wa4A6VrCOlG6XZQup3gxuC9VK4K6h8HwP2QuGg/nR8Ijq2AfxjSDZIG8UKM/ucpuNb8z9s2VPdBf15R0w+9GmHBzhssRXjcgfB80QUb/f7oZMQ3+qSn4N42OpMwmG+6bGOVbzp5iJC+6YQ/sZ661O+fLg7lo0acYH7qbsg/HTIO8iZkBaQUEnuQfdcMBoPBYDAYDMb/AdE//8/g/8d2cL7hZ+JOfecA1N/Hn48xyDNpfLUdmTvtyU61QO6DQflFhRxfpeHVusdUv6iIbEz1i4rIxlSN8RPCOMcgGmOo6nj+LzQ//NW2VWOqe2KOvrHT9Blq+Efu41Y9tnh8xbXelbdPOXj6dB47PRxjp721/kifm4kBYzWJNFbTDtwCfCKNlXUEW2iMszDIegCM09S5l119xmDC2dMOYyv+8ZQI5vwP5TETBoPBYDAYDMa/ENGf/1+1it3tOTps/7eTBNmw/555QWzDRteGVdu/6CDNEwDHVsJuhHSDDIDYIGMgBtuU5gnUPUdAt03D3Gc9+Bp1mg8QfJ26Pg9gaUlka9MZDMbf7F0HcBtFFD1LinES2XFJbGMSYyCACQRiQknokAQSCCaAKQMBochnW0SWzEkOCb0NvZje62ToHYahDYQOA0MvobdAKKa3UMO7vbfnlXy25SAFmNk3s36+0+7+v3/3Ttrbv/80NDQ0NDQ0NDTyF/+vMxWNRVMLcrD3f00jiD3ayCneWxdNKqH5mkPhpO1lYKyDPHevjnVEkQcv/O+MmXwXHTSfj23aqfCcmGlsyHzbeeULHdIZjcwNKdmNjSl7Zv/1qirl5FnFR5XoD7kPjEuMI+mnUI70Mtqw/Z/OPjCxU7klnExhm3Ik0WyGOhJRu9u2mpeINtfV43Ocj40bt169fWK9bQxgGHwOXhQ+Bx2qLwPqzPRl2LXsvALMWaHDx9Ap6CsVe+b/qLTLzgvHOk2jhPuOG0XZIeLz9ir782RbtCUlPrd13l18HjB8RmNZDfJ0GoAvFEqakU4LQyUUSSTmRnvqm8H6+vF3OFnEXKS/g92eDu7/krZ70M/3GNJ2q9F2+/WynRn/p7bbz8N2L/qgpJ+2G1Lap20OFmWLhW1WpL0ytuVCbu4sZnuHI72KfEep7bUSqXDKbWrI6UWjV7+qbTsqo22Z7XD9WzLyBo1+30sp2lPO9kA2Jff4qkCGI4Ht3IPt3GCI204BO+85tfBjSYuliZuYlTg0FLZa56G1sWhkwRZbRBLxlmhrp2WK04ayR3EJ5H9SObC+6n7zTVYxBKYqe2jehL2vcOzdEo03hzpMe4jbr8J09uy+4fgSteOtm6E54aTdXHfMLxTlhqXZ/oretmc/WfPCtq04hh4T+VaHjCFqf7C82x9Ch7dWN4CWqJVMSeWEDhU4e5fIX2qUi+MCWS+OA0o=
*/