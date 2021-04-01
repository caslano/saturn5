
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
JoiWHuhGhiiXyRUU5A1QEhNaEgyUaR5Q9isIZwOYKVbF+V1IZIk7h9d+3GQu4xRtRNHTQxvmVzRVGSWF0fsVt3D1qVn215MgcaxNtHcNahxZLo1krndDosGbzYTVS+YcShrT3wEQKwwosljH1iBOdqAzx5xs1WFO2sWVdmDO9DqObkObCp0cOImt6N70SrdKPW6kK/aTZ3OAzw8tZoe74HU3ZfHVWbVhQnNRdAbSfi0TKPkTTVyP58nynZizFOF3d2rLMK5VUgNG9I9ex3GCGayTFioedPhVN0x7xwZ/+soEuUKLJdxwaq4B+oCagiLmyoYTEYYKg19ekLnYsSWKCrEMwyw0PqhyL6dYt9BV8XKTqvPN7jb5IuhA7NXNJOQDIVRAUvUGGyCY7tz8sO/jaCvV48u/0U6i6cGCZ2FI4IuTUjVJHEVPae030UssckT5M6i96uwYoQ1ERrrnBUM/n7atUd1RuKPSpsPQ0XCYc65WUk5Ec09HQ4PyW01JpE+fVhvRhNngokoSqm01e3dEe0CmSFdonljJ3XWMkGAfCChycGXcgpJfvYWFPw==
*/