
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