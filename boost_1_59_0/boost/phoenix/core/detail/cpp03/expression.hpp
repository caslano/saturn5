
#if !BOOST_PHOENIX_IS_ITERATING

#include <boost/phoenix/support/iterate.hpp>
#include <boost/preprocessor/comparison/equal.hpp>

#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)

#include <boost/phoenix/core/detail/cpp03/preprocessed/expression.hpp>

#else

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/expression_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*=============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

    template <
        template <typename> class Actor
      , typename Tag
      , BOOST_PHOENIX_typename_A_void(BOOST_PHOENIX_COMPOSITE_LIMIT)
      , typename Dummy = void>
    struct expr_ext;

    template <
        typename Tag
      , BOOST_PHOENIX_typename_A_void(BOOST_PHOENIX_COMPOSITE_LIMIT)
      , typename Dummy = void
    >
    struct expr : expr_ext<actor, Tag, BOOST_PHOENIX_A(BOOST_PHOENIX_COMPOSITE_LIMIT)> {};

#define M0(Z, N, D)                                                             \
    BOOST_PP_COMMA_IF(N)                                                        \
    typename proto::detail::uncvref<BOOST_PP_CAT(A, N)>::type

#define M1(Z, N, D)                                                             \
    BOOST_PP_COMMA_IF(N) typename boost::add_reference<typename boost::add_const<BOOST_PP_CAT(A, N)>::type>::type BOOST_PP_CAT(a, N)

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (1, BOOST_PHOENIX_COMPOSITE_LIMIT,                                      \
    <boost/phoenix/core/detail/cpp03/expression.hpp>))                          \
/**/
    #include BOOST_PHOENIX_ITERATE()

#undef M0
#undef M1

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // PHOENIX_DONT_USE_PREPROCESSED_FILES

#else
    template <template <typename> class Actor, typename Tag, BOOST_PHOENIX_typename_A>
    struct expr_ext<Actor, Tag, BOOST_PHOENIX_A>
        : proto::transform<expr_ext<Actor, Tag, BOOST_PHOENIX_A>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain //proto::basic_default_domain
              , BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, M0, _)
            >::type
            base_type;

        typedef Actor<base_type> type;

        typedef
            typename proto::nary_expr<Tag, BOOST_PHOENIX_A>::proto_grammar
            proto_grammar;

        static type make(BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, M1, _))
      { //?? actor or Actor??
        //Actor<base_type> const e =
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain // proto::basic_default_domain
                    >(BOOST_PHOENIX_a)
                };
            return e;
        }

        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};

        typedef Tag proto_tag;
    #define BOOST_PHOENIX_ENUM_CHILDREN(_, N, __)                               \
        typedef BOOST_PP_CAT(A, N) BOOST_PP_CAT(proto_child, N);                \
    /**/
        BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, BOOST_PHOENIX_ENUM_CHILDREN, _)
    #undef BOOST_PHOENIX_ENUM_CHILDREN
    };

#endif

/* expression.hpp
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
*/