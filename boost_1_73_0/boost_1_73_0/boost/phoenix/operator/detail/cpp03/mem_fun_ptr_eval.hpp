
#if !BOOST_PHOENIX_IS_ITERATING

#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)

#include <boost/phoenix/operator/detail/cpp03/preprocessed/mem_fun_ptr_eval.hpp>

#else

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/mem_fun_ptr_eval_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller
    Copyright (c) 2016 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

    #define BOOST_PHOENIX_MEMBER_EVAL(Z, N, D)                                  \
        BOOST_PP_COMMA_IF(BOOST_PP_NOT(BOOST_PP_EQUAL(N, 2)))                   \
        boost::phoenix::eval(BOOST_PP_CAT(a, N), ctx)                           \
    /**/

    #define BOOST_PHOENIX_ITERATION_PARAMS                                      \
        (3, (2, BOOST_PHOENIX_LIMIT,                                            \
        <boost/phoenix/operator/detail/cpp03/mem_fun_ptr_eval.hpp>))            \
    /**/
        #include BOOST_PHOENIX_ITERATE()
    #undef BOOST_PHOENIX_MEMBER_EVAL

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else // BOOST_PHOENIX_IS_ITERATING

        template <typename This, BOOST_PHOENIX_typename_A, typename Context>
        struct result<This(BOOST_PHOENIX_A, Context)>
            : result<This(BOOST_PHOENIX_A_const_ref, Context)>
        {};

        template <typename This, BOOST_PHOENIX_typename_A, typename Context>
        struct result<This(BOOST_PHOENIX_A_ref, Context)>
            : result_of::mem_fun_ptr_eval<Context, BOOST_PHOENIX_A>
        {};

        template <BOOST_PHOENIX_typename_A, typename Context>
        typename result_of::mem_fun_ptr_eval<Context, BOOST_PHOENIX_A>::type
        operator()(
            BOOST_PHOENIX_A_const_ref_a
          , Context const & ctx
        ) const
        {
            return
                (
                    get_pointer(boost::phoenix::eval(a0, ctx))
                    ->*boost::phoenix::eval(a1, ctx)
                )(
                    BOOST_PP_REPEAT_FROM_TO(
                        2
                      , BOOST_PHOENIX_ITERATION
                      , BOOST_PHOENIX_MEMBER_EVAL
                      , BOOST_PHOENIX_ITERATION
                    )
                );
        }

#endif

/* mem_fun_ptr_eval.hpp
i2Cr/VT0OQSrGi0z+mD5kiTdm+65qQLf65+bNw1Rr39uvKjfNH6Bv8/hb6OQjCCR25dnw9FZ7xWo+EJClspFLUqmJASDXfhWW1G8fbSwB8PRyeWbC8G1VTQojGFh17ZWIF+gVfq3v//970jSy5MLFX/5np916kl/Xp31XrbPxFuwe9FsWKeX/jT1lGEgwBeuYOE/2YeP4pAWz/+IzuU5EK2p0Khdxlo5QVUMZQF/1MRtk+uCE3PagwZUvXaK8hTZewLLLyhqtY/BYxkokLW278ssE1chWHO45m1og4v2cYcr1k7C7BNYSGAvQbe0gDiQIT/7EmScBf9l+6R3YTDuwrKaepFA+xUYWqalXqB298QaH4Yc4iK+2D0pqnb+0R0MDeI0PC9CFXUDWIRZntm4g7vS11XPQecuQR+ATZeaOjsHulf87ItbJejtadG6gv961rzUwGj2Mj8MawjlQAOtgUsi81rTAOXi88uzs+YdfYG8HE+yD08/Fk9Qdsbyc57E0qj3EDjgM0pNfKDVurJXga+slmCQppIUfKmlagQSVzXa2sD50JDiJ0mkBD9FUNOIomDGInZ7juV1hMv9UOxrAwHFK/T7HHudh0EQSR4DV5SfFzDfyE4uINBbV6QbD2G6WOiDQCE4+ChMwDig
*/