
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
E3JJnpxgTeL2IFib0VgHouvDAtahzi7ZyIcHOFhj1uRkUeZMUQm4GyuysSjcgDWeZgxYo1mjeU0M3Iw1IM2iizCKlgNQ8ZrFWlIe/rb9rDldOtu6mdARbjJ8k6PvOMq0cQWV1uyOpOaxoDp5OB582ZPTV8iEPIiaqoRNm56N00sr4mW0drB2e2bx8ImjoRlw2qFkyPaztgZ3s5EPD3K0LUj6F7Iu7CrrlOA21S4DZ7bJWL1vLzTopkzblZjHgmc14EpaCC1q01cCBlpQawdE+2QSrW3m9qcM1rTATbH20CZYe0DWIDdzMjKLcHMNc3aC1TN7O38b23A3V8w60MEGsU7rFtZA3cG6pKusPwCahjuZTlwsRYdlFj92Zh7HqKcxTduFmaSRS0jokxkC6T0RFmvm1oi0xbxcFXLaTlmIdTXB2hyydgHpGbz2N0jFwd0c0q7zAevSLtt1aQbBuvL/CutgMdZB4qw5RmH0TnecB2P8FUGL2hGO7EoafWMWImqbiQ2+xFnrS+iG6JCm/QHWke7uuUkgN0uDPjwxRFicKsLN5N5GDa2RlqHVFafh5WANcCEAwI1Zc19Ul5mhURfjI3CjckphC7mdODFzmNp7tvOsQ5C4cIvHbsQa1lFFuL2JwB3HLJUTExvQJPNIUcezKZK25jeUuaY7kByCEduwmLBxs/ranKyxG/dgsAbx2tnYMsrDPRykZ44gZINs
*/