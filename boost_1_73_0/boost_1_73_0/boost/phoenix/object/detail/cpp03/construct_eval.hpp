
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
wMOz8T7YFKPRB+RzL85V/A070mU+kbtNZDX5cVP0lEST1qxr93ITI7TfNt+928Qz0AkzrVa4xeUC8l+S/xG9qqzVBkdn1ukkfc5KFfuQ9ob2lOqk1JCNNe6qCz5CT9t1eB6Jd4RjD9wpWFD7uqZpbS6mxWIO5CctWp2Az2+Dg5ds9p7ROdbZBOsW2YPgKJVgpdBWqg7jt5ksbdNKqq50glnbHZQyMY6qKOlS7Q6XDgz8VVsBT4zG+isS/XRwPZKxuoyJtFBJeNylieUiTCnDbhVy03KenBvz9mQhg049uEYfS5/yhQTy2vi0bRhskxjczmFpzKYH3tjG4w3ZoQbcu06XsDq+U8L/+SRqidkUb0mL57NpwrsTel8BlczU3mgIbmOP51d11Bao/e54PDg/74+cSbT9Vk8DR0ialhFAsGpXi5oAv6q7mkwTbR5ofB2e5CGuClCwK+DCvd9mnqpQ+KNNg/EIol6EUuiTiZr1cc77w+MxaBi86Pf+RZOGyAblYXkMYDiqbRpAat26ui0On/EHnlXKyKtjRGPB892/VlA7m0kttblJRm3NBDXUziB+L2pn6/f/Rm3FYY+ltvreUYfCUCbwmuo0QoFzQaGDlPEVWTcQ4Fu69NoDemvgtrgLtBwFhcL6SYFBKIX6
*/