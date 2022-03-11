
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