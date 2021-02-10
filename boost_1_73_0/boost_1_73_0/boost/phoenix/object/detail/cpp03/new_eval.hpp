
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
5K1UqVw92uMM7Nr54UcJKVIyV75q4xs/X+0pr/D1Hu/tfQ+cjJxsvWFZyBpx+XO8Q0bPyIRLfLcCk8eJL2VEQUsg7zKJMUtVVjzACuCyKR7Z3q64cfJQZn0KVPEwmOSzloukLforllfh1jITXeNGWfdJgOJLOvgQ3EPUZmivt2N+pTQkUsM8lqZVE+e7vYTS9i08XIkJjUm6hFW9x7cSeY30ppzwJR9VSO6h/0JM5iGsKkSJJuWZvdZJDxja74TZL3twfli/6YGUVYE0jqdvN2kki3ec7HJDDaus9sZTRbNVN5oqmucuStk2wlKlV14w1beYLAC16FeSp7DpVkGSgxqSHFSQ5ACRPyjR5KCuoSIH/EkGDfiqruV3JsiB3iJldkDutehiHfjVwvigq1+IgJWdA9tNaNdfALMmskYKy3rtAfvQNp2ybPAok6tbN+EtvIRVq5Eza3sKIh58okeKcJnqp3f5Q41uZSbHeL4QdxCX0RQfg0MBzisAfouMLJCXts19Gu1G+ZLcGXeMC6bmXe3xhBPXx5Iari6IvS30QsPPbiYbaCQptSCt3PBKEHjJpkrLWE1IpBxO2jUVsMyVuWaFj3uMhp1znZ/pLvk0xFq3xwb8HX2dKpu7/vCbOjZjzwz+r3SHec8F80tK
*/