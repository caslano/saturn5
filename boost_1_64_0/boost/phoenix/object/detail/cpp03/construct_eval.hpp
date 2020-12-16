
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_OBJECT_DETAIL_CONSTRUCT_EVAL_HPP
#define BOOST_PHOENIX_OBJECT_DETAIL_CONSTRUCT_EVAL_HPP

#include <boost/phoenix/object/detail/cpp03/preprocessed/construct_eval.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_OBJECT_DETAIL_CONSTRUCT_EVAL_HPP
#define BOOST_PHOENIX_OBJECT_DETAIL_CONSTRUCT_EVAL_HPP

#include <boost/preprocessor/repetition/enum_shifted_binary_params.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/construct_eval_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (2, BOOST_PHOENIX_COMPOSITE_LIMIT,                                      \
    <boost/phoenix/object/detail/cpp03/construct_eval.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else

        template <typename This, BOOST_PHOENIX_typename_A, typename Context>
        struct result<This(BOOST_PHOENIX_A, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <BOOST_PHOENIX_typename_A, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS(
                BOOST_PHOENIX_ITERATION
              , A
              , const& a
            )
          , Context const & ctx
        ) const
        {
#define EVAL_a(_,n,__) \
            BOOST_PP_COMMA_IF(BOOST_PP_DEC(n)) boost::phoenix::eval(a ## n, ctx)

            return
                typename detail::result_of::target<A0>::type(
                    BOOST_PP_REPEAT_FROM_TO(
                        1
                      , BOOST_PHOENIX_ITERATION
                      , EVAL_a, _
                    )
                );
#undef EVAL_a
        }

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* construct_eval.hpp
Odaf1c2Cm3Wz2NHKQRWMuaGkNRXTXKeY0G9hlZkfpklgk4s+2bwkN0kmI4y3PTVGyMpI7JDEK9o4tUqkzfkhREkoK9gAwgQwmQByFXnwbRR5vgQBCtMdTjGZQ9TqPy5kpb1h1WoWxHF9ruD6FwuyePuDtnO+ztjFNi0+/HTkCmZFvMy2ZkXFzxuV1AB22dm2iu/m6DCl10YIytq4ObHbHp6URvLjl/vVBv/nF55Y9P3Lfln73+eKvWyx9tirNpi5jKknRVe3+gzu6jyj8FUTiI2x1RUXvgiyjyF92L79lNm+XR35gvQGH0ua3uDDiIXd6CCmlNjdg6RjEiMjvV30BLhYo2GU2djOPKVnaYBhQ/yVIjdy0UhZAySYElUXBcLkvroe39jQ9nnxdi8O+Gr1zZV3t6hpWw+mbbcarTCat2sCH29R07aefvwUfZi1VyxxBuL16ntPNejFT6eENNw1PeoriS8hHLRWrKf8NBSwRZ1cQV4TqbdkrsqU0Upkdf4kMObPS6sVRM8fMkHhQc+LP6MsL/EG8M1BcKY/e+w/3Hb0eSCfqk1qLw4UmfDotMhRFIVcF2p961Pm9I/LDpmFZ8WBYqMVxIYXrMAOjqZMBdYGJNFXtsabPf+GKYptKRrZAk+mS93KN1HRBd15h2P4F7MYfY43AT+3H6oU6s6FFVWYnptTEKnNTm589b2Rm0ziKHAw5Y5mbcxNmGLmo5l2XjsC56shahD7yFe/1X4QZLIolCHledyB+5R/wSse/TD3i4UqzHo/y9be/LXnSByYG81nPuAogANRRNzZm3izI/4x1HyswMCZyoV8hpJpPalczy6pscGwlYc5ijhoRRWhvhV0LA7JAD56LrORzyW+U5iIZTXZN4+7Mq/n5n00ORZc5pvBvdkNvl43NeHkWlo8t8tMJXo+44oujNwm/cUd67i/+Kceosva/38z8a8bTmPzkrvHRvSWn8zvMOhQ1Bh9KErY2O1WMdlcLvqHVPXYsDvUjRUzF+zjrzdMRItpeoSZWC+r09lO3lVCvY0HENNN0odAanEgnKwJ8Fau1FPLaCGZY1p8SMvX8H7qnvRqtZduz3hH9GOqNQVgYTGRUxI8kkBUwP1/5gw2nYgFt1W1ncGU9XAX/LhtezMbdYk06hKZLkfrfYl/fokM0Z4/OK+/f8j8vxH5Lwcr0VlPoruZy6MO8nGTXOsjX+NcGWUsdNTOSZldw6TY9Fe/Oec46c+OnhO55WBBwEYG7Ps2ccLKb091YBJH/h6lPCz70onOWTj//NVBzpudBQDr48DGJx2Hur+zC+Pg8e7vvJwReF/set/3Xl18RCHy0s7pnTh+PJAM/uXRiwi45fSsGt+ozrO4Uxk8msB3WlPPegwX8ncieLDw6Yzvxf3TawKjAHOc+3/3IQ/Mvvz7/Mafbdf3Y1ORmKvI0aW5dkko660PNOP31Hyl9K4NHN4EsFxjagFeEpK4Z7Q/0ePk4z8yw1sMkLroaNmuPyfnwnAUfnf6PLdaBnLk2Dhe8RsLgxer+c0anZIxt4r2r68Kn2m/Knw0tW+tuezIuSC8FzIU9PowzWo72wxPF6yWDPA5ZPM50nnYO6r+0FXo9bUUl8E8RTCLrjez2cdXNKqThLFVM6hz6gCe3mghUZRjUNnL9orbv6L7oMQjhcjOcFF7DWrmW6WTtbb83+YhrCIQQ057zI6nnZlFmLHBon3fTEc/M5IPEsBZ8QjihHpwsnqArdn0U1grIdWm672VIah2DQn3dcAZ8V/CGg0a5i/0rliEuBBtojum82ByI+dROQj2xJt0ZcAwXFFzNDakmck64M4x4ZaqfwY4eqR2XozaLUJTkobGh8TiYyw=
*/