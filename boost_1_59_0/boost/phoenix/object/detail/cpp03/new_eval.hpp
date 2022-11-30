
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_OBJECT_DETAIL_NEW_EVAL_HPP
#define BOOST_PHOENIX_OBJECT_DETAIL_NEW_EVAL_HPP

#include <boost/phoenix/object/detail/cpp03/preprocessed/new_eval.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_OBJECT_DETAIL_NEW_EVAL_HPP
#define BOOST_PHOENIX_OBJECT_DETAIL_NEW_EVAL_HPP

#include <boost/preprocessor/repetition/enum_shifted_binary_params.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/new_eval_" BOOST_PHOENIX_LIMIT_STR ".hpp")
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
    <boost/phoenix/object/detail/cpp03/new_eval.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else

        template <typename This, BOOST_PHOENIX_typename_A, typename Context>
        struct result<This(BOOST_PHOENIX_A, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type  construct_type;
            typedef typename target_type::type * type;
        };

        template <BOOST_PHOENIX_typename_A, typename Context>
        typename result<new_eval(BOOST_PHOENIX_A_const_ref, Context &)>::type
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
                new typename result<
                    new_eval(BOOST_PHOENIX_A_const_ref, Context &)
                    >::construct_type(
                        BOOST_PP_REPEAT_FROM_TO(
                            1
                          , BOOST_PHOENIX_ITERATION
                          , EVAL_a
                          , _
                        )
                );
#undef EVAL_a
        }

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* new_eval.hpp
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
*/