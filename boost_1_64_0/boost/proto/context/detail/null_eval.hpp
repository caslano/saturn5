#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/context/detail/preprocessed/null_eval.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_EVAL_N(Z, N, DATA)                                                          \
        proto::eval(proto::child_c<N>(expr), ctx);                                                  \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/null_eval.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file null_eval.hpp
    /// Contains specializations of the null_eval\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/context/detail/null_eval.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_EVAL_N

#else

    #define N BOOST_PP_ITERATION()

    template<typename Expr, typename Context>
    struct null_eval<Expr, Context, N>
    {
        typedef void result_type;

        void operator ()(Expr &expr, Context &ctx) const
        {
            BOOST_PP_REPEAT(N, BOOST_PROTO_EVAL_N, ~)
        }
    };

    #undef N

#endif

/* null_eval.hpp
NT6VgTkfZxfp8c8jHqnINFRhhUriyn2f1/0Z+KHJeleqV1Km1OeDK4/H7UFnJn6+2JdTAliSWxQaxdre2W/lmsBwFbYjeswdqSG+ZmiMocMJzj409JUTGeRdF/D7RlOXgx6QP/pgTO0c3xb1txR5l1S0JVtZztZzCusEV3qcgucn9uu3js+AvtK1avGttx/1iHudgJvDlpNZWBzPo5vxu5CUdQ21PuazsRmHWfiioTyOpXBfxAUjBYfZZjfWHgVeQZ+2ynkdl/WAQ3BITfWPXlt5xDRuzXZUdyq0TqoiT3JW9/1Atn/NaxtR3c+K6m76Qve1zk3d0IN6Wylvm7cZv/eVnSwJT9XNC1SGXeHU2qRqb3ft9rC7X4T4LBOY4PLy9nhqePnm0CNj2Wg3yEabTqaYn5ShqPxOHvnME73MMs4X66uTONov+Xwf//288y35uslbP7xK+cF9yMabv5eP68zK8dVIxVyZH0dlaONHSw0j39ZfWjlwYWEUncxAMD+f14d8vGY8whVYd+39XcjHMb67tWlKuJD393J8BPR1KEfKPjpml2HssgY+y9d0+R92Mpo5bZzvz9HHzcbdj0cm+Ev95YmzZfnocB+siz5ptiwbJT+GXzhvx/Bhy9OPkboyXwtl4g+BMu6bfzuUwcQcc897fMMPTfANldK6o4AumxvnYzF0F/sI7ZwPw68WyDTY3f2B8+lElpUqGxpjRG83Sh/yOHW2VxM9Qoab4ZBWgejgt9RH3NXdhSMeqWgzqPfLxAQ6mQii0/V8dCvWnehyKFrdNwKjZA54E+kNxh3YWqa3JxHwP6M25GLoVJo3XRX50IxfOmrI2QV3znL6jDCDkiZrZflvC4gwn7Z9u8h1ISNe7PpOTmJikpUPL4G8SztZDAjjRu6idCe3Ybzsaq10yLv8JA+klp/DLKepReEDQj1X9On/4Ow4Y/NYiqaKTugt9AeEnjhx4iAEe7e7129vsU1HGMd2iMGxjT8bQo/ovQsh6qP33kLvRQgQQgghhIAfgBCiCQFCiDbz7c3u7H2faS/vPTs7ZcttmZ2d8kCd1IHXdX05aP87k1PMZ4TdYAzD2VN7feG1rohxzv3ynPG5dT49iH2a5VlRWAn7sfMv8vqFBX2/Ppe4z9/x5Fi/1CjQs7mn/DMQNy5WDsyEfGJ/uSnXDzRFATcXa8X+3tl5f8/x97sj/LuOZREQoEpLchC6Daysoid4n+v6/kvZPNMuCa4T5H09aSs85TspIAzHNpkj7/o1HY2LEXB9b0vMgfeAld2NbRa9oxc+5vop0ndgn+b1HyM+mejyUulMdmIJqPoFAoKvZzd8y3zQa6P8wybPMDqhuAB3ZYfK1uK1PhPriaomb3WbZlxWHRPOwe6+v+qcfza2QKZZiXK/is8MfPu6zFawqwgc1QWX1ZbSYm+fdylI5kcArGI95aEjkb11YrNOJWIEpmSxTciDovo6kYGkVtiqgndlHFiMebK9BoIYG/ORs0eL+VyI+BiRYdR+WRjffxAaAw9occzG35M/cCSe1yDSFFkFIWpAV7nhgled3l3b8jJdRjIn0EX5rhory6bJvVzVxwPr9Q+BHQzmArPRe9VnBvJZjnFuYE83++fPkAprbeXxI9JJb4z6NCxjzpFv4k+jOVGIqmjyPO9cnNbI+nREubjwK2MwxF0IthXdm276Wa47bLOuqdK6xvUDbNzMDz6RHFfVosp1pkppe0+1/1R15H/wMM6rw9DQGBhQCTgHHgmiiMuv2+tnqf7NqP5SVFnRYrYpgfbh47nUk8HB4o7j/ZHXDD3a9fvm9F2Pje/L0E9/ELQ+D+tyfFcyRqa6Kbv4vozpd/u7LfIHqWU=
*/