
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_AUX_ADVANCE_FORWARD_HPP_INCLUDED
#define BOOST_MPL_AUX_ADVANCE_FORWARD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/next.hpp>
#   include <boost/mpl/apply_wrap.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if    !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER advance_forward.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/unrolling.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>
#   include <boost/mpl/aux_/config/eti.hpp>

#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/inc.hpp>

namespace boost { namespace mpl { namespace aux {

// forward declaration
template< BOOST_MPL_AUX_NTTP_DECL(long, N) > struct advance_forward;

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_UNROLLING, <boost/mpl/aux_/advance_forward.hpp>))
#   include BOOST_PP_ITERATE()

// implementation for N that exceeds BOOST_MPL_LIMIT_UNROLLING
template< BOOST_MPL_AUX_NTTP_DECL(long, N) > 
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<BOOST_MPL_LIMIT_UNROLLING>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - BOOST_MPL_LIMIT_UNROLLING) < 0
                    ? 0
                    : N - BOOST_MPL_LIMIT_UNROLLING
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_ADVANCE_FORWARD_HPP_INCLUDED

///// iteration, depth == 1

// For gcc 4.4 compatability, we must include the
// BOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // BOOST_PP_IS_ITERATING
#if BOOST_PP_ITERATION_DEPTH() == 1
#define i_ BOOST_PP_FRAME_ITERATION(1)

template<>
struct advance_forward< BOOST_PP_FRAME_ITERATION(1) >
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;

#if i_ > 0
#   define BOOST_PP_ITERATION_PARAMS_2 \
    (3,(1, i_, <boost/mpl/aux_/advance_forward.hpp>))
#   include BOOST_PP_ITERATE()
#endif
        typedef BOOST_PP_CAT(iter,i_) type;
    };

#if defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)
    /// ETI workaround
    template<> struct apply<int>
    {
        typedef int type;
    };
#endif
};

#undef i_

///// iteration, depth == 2

#elif BOOST_PP_ITERATION_DEPTH() == 2

#   define AUX778076_ITER_0 BOOST_PP_CAT(iter,BOOST_PP_DEC(BOOST_PP_FRAME_ITERATION(2)))
#   define AUX778076_ITER_1 BOOST_PP_CAT(iter,BOOST_PP_FRAME_ITERATION(2))

        typedef typename next<AUX778076_ITER_0>::type AUX778076_ITER_1;
        
#   undef AUX778076_ITER_1
#   undef AUX778076_ITER_0

#endif // BOOST_PP_ITERATION_DEPTH()
#endif // BOOST_PP_IS_ITERATING

/* advance_forward.hpp
tIoXNXvbbSp9q1O7IAE41uS8KH/DV4AQrO9B9Xw9PiTvuEIIPS3XqlY38y0+CVdyZXB3MrlWhUcw6zsLvmWwPXhHN8zGrPCTX4d7OPxbRszP1ulR+l9zEuHDuwrs+O3sxQdSsVfdTVsNG4mGJJQ0g60t7VoWE1TPoXJSmN8aSTr6KzRdrjLeFHfwftotuGG3z1GTDZWhOsFnqJMOIIdUFdZx4x84Ilo6ztisG2HNmFuuRjPUxiaXI1WzloTzWTYtAv/fl9RetLF/HbPjInmM4suLqmbK+cxQrxbt5R/BjmuQ2Y0nm7QKFqphG9n35/rMs84DVMobc1P64rBDsH+K3Yf5tCYgPbEMQ+XIFAK/azRKKvFSK6jUe7B/a3j/eiF5JSnuUfCkZpdfXFYRWz60/nKF35pMi0VfrLk/Et/MF+XNtxfG4x95Qf/PkP4OWpZHxUybwF6EOeCapQP1cxgjEkuunZlONgvsX1c8CgvcUumptd0AuyXbNYRb4KA/9KvDoh81vNdO1+8V7IR2AH7crChnDQb7lmD7AMs2/HSCQuC5bPPMdAl7HR60EvTOrHOglM3U+GHM21QSwngZf3z3YQ0k0l/UOhAgwSy970jhnMHvhtG1gvGyyJDqPhnMbJqFpAIRYDaJP4sh02R82fOAW9vH61Xb8Qhixd4r8QCCGKlO3DTco2Vc4XHsDwOqoRHznwfinNptbz5Hr0V+jCFIpUdvsLYSO2ut0d7nperw95Dmt4UeKbHm2MoqYflMq7yLi6e+ft546+eNXj9v8vUrK01p/bzx1s9LssPSxuvnbbx+1zrjrJ9XrN/BcyPWzxtn/egcTi75SdbvJMRusi8i6djwVaoThboteKsptNctsj0Y1DVuziVbS2b/SbwYq+WYQR0wG/HqL73Vxv/oZ7UU6mj2nmaPEQSosDqaBzxjTcp0vLgPpl8cZf9TmogeOgflNf9jfrL33luzY9tv3DMrsbz/t1fq/Gh6oOwWG73q4VcRCcnk7EJ20EfbjadXfy/IgT1/JPvbBzhVKOkOd0tNZCrwR0csATxUGE0geha/r2IJJzuezEJTLOv0FQfYg+zLUyM4qOk4eOrOe+octiz7q8tBBwhXDvZGbQN9wuezylQFya/kPYNKm9OV5C7YXBXtHW5nK4L7VklKWymp+qlUUFLtdIk1hFpCBDEl0+GRxj1TcGENOINfictGOnwYVjb6w8U3vaNxWo44EXVQy5/GOdTrpmE4VYekS3M0Ptb63wz6hNaoCuqXHhz+pW57WGaOykUzqvN/4HzAnCTe/QApC2qXj+nBPKhmbuJmjGfFrsp5QAbC78SP/aTyzGzwf8moWu43uY0lSSqNN3Di54pvKpz7F/Q3MI66gwb6O7dE6dVudSKwJ+tT096SmA+r5RG7BuaTXvENudr3PR0FnB9pxnk3qyOSa7nBQANKkyQTZpzpcKscHis0DQc6QkT01Moj1JHS2QE+VOzoBPa22YI4OJeVROrgyTzLlr2X+xdsk/NZNzYvwoa0tez8Fa1F8ylzW+CqgmtAC8Grnj6CR4niclhhlxzW7dyy0hrJQMuu8KVhEtmajACL8MbWryhXOJ9hMw5SI+hseJ7d9lY30iHcjtFDHYTuvWxOhlxhjsA7hQxJPdKQdAp0cL7nRy703X45+d/FiknpA/ysdmaoD67FdXgXvXIdAGe7LCgZuW25+8ciF7eTqJvw/Hm1k5kT6IjPnOp20Q8c5jZAyEMGKY1f8KC5tSTxUWEa4uEvZuWNyeKVfX1rcn217bclvr8uvyWJ/d8ZcfLFxkmh/7FJ+p8/MUn8z6lWfjT+G0dw8N0yR+tXu8r3uEN+46RzQCThEfA=
*/