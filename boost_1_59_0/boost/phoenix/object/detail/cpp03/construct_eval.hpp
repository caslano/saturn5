
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
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
*/