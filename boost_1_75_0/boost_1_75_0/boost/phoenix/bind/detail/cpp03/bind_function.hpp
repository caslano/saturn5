/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !BOOST_PHOENIX_IS_ITERATING

#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>
#include <boost/phoenix/bind/detail/cpp03/function_ptr.hpp>

namespace boost { namespace phoenix {

    template <
        typename RT
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<0, RT, RT(*)()>
    >::type const
    bind(RT(*f)())
    {
        typedef detail::function_ptr<0, RT, RT(*)()> fp_type;
        return detail::expression::function_eval<fp_type>::make(fp_type(f));
    }

    template <
        typename RT
      , typename T0
      , typename A0
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<1, RT, RT(*)(T0)>
      , A0
    >::type const
    bind(RT(*f)(T0), A0 const & a0)
    {
        typedef detail::function_ptr<1, RT, RT(*)(T0)> fp_type;
        return detail::expression::function_eval<fp_type, A0>::make(fp_type(f), a0);
    }

#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
    #include <boost/phoenix/bind/detail/cpp03/preprocessed/bind_function.hpp>
#else

#if defined(__WAVE__) && defined (BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(preserve: 2, line: 0, output: "preprocessed/bind_function_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(preserve: 1)
#endif

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (2, BOOST_PP_DEC(BOOST_PHOENIX_ACTOR_LIMIT),                            \
            <boost/phoenix/bind/detail/cpp03/bind_function.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined (BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(output: null)
#endif

#endif

}}

#else

    template <
        typename RT
      , BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, typename T)
      , BOOST_PHOENIX_typename_A
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<
            BOOST_PHOENIX_ITERATION
          , RT
          , RT(*)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T))
        >
      , BOOST_PHOENIX_A
    >::type const
    bind(
        RT(*f)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T))
      , BOOST_PHOENIX_A_const_ref_a
    )
    {
        typedef detail::function_ptr<
            BOOST_PHOENIX_ITERATION
          , RT
          , RT(*)(BOOST_PP_ENUM_PARAMS(BOOST_PHOENIX_ITERATION, T))
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , BOOST_PHOENIX_A
            >::make(
                fp_type(f)
              , BOOST_PHOENIX_a
            );
    }

#endif

/* bind_function.hpp
107U5ef1y6oST3z72MhTguTQxJr7bSjiPNQmU7aJYaht5/kwMfebLvxftG78cVcdRj7WKrncpomgDHG6+wMAm16vPAdK5zx5m8uF2acLeYS9t7ODLetlRyLdOQe2JKSu6hOrS3DnljH1Eouwnye8C8mwBgI3NLqfO+Bo1xkkgVUNEn+H2pAdl2HwukTvpUzx+rT+HNGsHnHYL7FUbIvR/RS1ASfcpkp8USrU/FllIl3cvpGMLQEZt4BPRqStgOdIWOg+vTFpxuWV/hSRHI09dxCwgHpizx+WIiP6XTNHGEtoy4DXS9cm0jSRFTBAUJC+9bGqXp1E6WswvTxVOJGYgtAwYdraVsyS14xOB+beYrClUN7LWLD6ULp+9I1+9+Zbp0srwT0MGB3MZHF8ZJ1DVng3c3DksnQu3uvrSw6G860kuIS/j3FParxXaHykC4gMzBSOhaS4MwybMYvAMQMxfCH8QkhT7/fE1lUlCbN798XVPid796n+d3phVqzDPkQdYG5Aq9WxzquB70cn7yX+kyexB+SwTLcjSw7LA8yThJ81jYe+Bk+yhCssQHGgrmk+yDZL89Xtj9HM0bGPM4Tx1a65OxMSbih6dhRltttbwjqXcTxxj/cq8OrXZVMC7LN3BrX9qUg3TG0MSDMsrAsewXvlB1OBccAcYDSwnUrOG7v9HGrVQuEV/nU7pqqIOBTFwCgMU3HN8TWLzwTg
*/