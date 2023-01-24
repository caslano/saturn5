
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_CORE_DETAIL_CALL_HPP
#define BOOST_PHOENIX_CORE_DETAIL_CALL_HPP

#include <boost/phoenix/core/detail/cpp03/preprocessed/call.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_CORE_DETAIL_CALL_HPP
#define BOOST_PHOENIX_CORE_DETAIL_CALL_HPP

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/call_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/phoenix/support/iterate.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#define M0(Z, N ,D) \
            typedef \
                typename proto::result_of::child_c<Expr, N>::type \
                BOOST_PP_CAT(A, N); \
/**/
#define M1(Z, N ,D) \
    BOOST_PP_COMMA_IF(N) proto::child_c<N>(e)
/**/
    

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (1, BOOST_PHOENIX_LIMIT,                                                \
    <boost/phoenix/core/detail/cpp03/call.hpp>))
#include BOOST_PHOENIX_ITERATE()

#undef M0
#undef M1

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else
        
        template <typename Fun, typename Expr, typename State, typename Data>
        struct call_impl<Fun, Expr, State, Data, BOOST_PHOENIX_ITERATION>
            : proto::transform_impl<Expr, State, Data>
        {
            typedef
                typename boost::phoenix::result_of::context<State, Data>::type
                context_type;

            BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, M0, _)

            typedef
                typename boost::result_of<
                    Fun(BOOST_PHOENIX_A, context_type)
                >::type
                result_type;

            result_type operator()(
                typename call_impl::expr_param e
              , typename call_impl::state_param s
              , typename call_impl::data_param d
            ) const
            {
                return
                    Fun()(
                        BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, M1, _)
                      , boost::phoenix::context(s, d)
                    );
            }
        };

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* call.hpp
QLa3K93ZlmxuitbXhO/e8d+85r18yfnxR9aTJ4KXLwJSEXSPdqHQzGahaYNm+fw8H4vl45DztO4iyU71in34nsXB0Oi1iWw0rmeb73qnNu2fSTlOocgjFHiFgoCAH+TzWD/+CHf4dBg2j2thYP1228znd5PJTvJilotz7DzRjsebsWg9FKr4fFALOZvt3KhrZDNjDBvU671qFYOHGUwTkFKxHi9d8QsXx+nEcUInDW1UqwKXS6njceyHDPdbpvcHifW1RcbwCIU+Pt8v4Ns5HOXhIXUk0urc2Lrttk0mg4ERY8MuztsJNJ4GPMiDARhSyeMuQCXabNkzS8ZkujQa0h73da83brXQ8CpVlFqtV2/WHfUcp5RkpBOMuEXo3S6VaZGwRikVGBl0xwbN84zheyS2PbPIj708XoDLE759W7i4oA6GM5mbFsbWSSYD3/5Ta+O/feT88SPn649cyJ8m+RrdArez//CR9VXdo+8U87dY47ZRvq4XrxvFW6w8TpXr0lyZl07z0+e8hFvopacyu+mURq2VK4Wss4MT55sjzw80/1d85zda7VsLm2ETCBYEsZT0rvst+ORfq2//5SPvm4/8R3geT4L/EW6HcXL++IH/bSNzOcJat732LVb/0Gt+aDa69mpNVKhI0xlZOik6D4i80khs+yojtpxpZTKBlnV6tnXkeHnkeXTi/3eF4a10fX3U7y+MrYf1Vozt
*/