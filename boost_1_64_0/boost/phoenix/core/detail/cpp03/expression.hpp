
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
7XNDPI7L+Qtwdfz8EC8IOX5hiCdD9l8e4hUhXhly/lUh21eHpL8mxGtDvA6X1/9znf5cXG0fx9XxE/Wuyu+Q7QtC0lcYkr5kyP7LQ7wixCtDzq8qJP3VIemvweX1D/E6vJu6fl9QP1P5g3cWXhXitXh34blf0j6k3i94iZp/Du+i2kfwPcX2Nbgf/5Kp/MdbivkFcv4e8bZ6u3rnKcHemuJbjJfg/vrOeNL4Ztyf//Ar3b9QiKv2+yK8n8o/vI+6//AKMX5sC36ZGD/2LL5E1D8rvk7df1nmB7sKHy3ap67FB4v2qTo8X8RH7MBHifnhP8OHifTnf0P8m3j+L8W7qPkp8emi/vopPiVD/TWaTh8+SdRfP8cLRf21/FvGn6n+H3yBWB/qSrxYrA8V/wf9/6p8xhsLL8dLhOeSEyeo9j/8ONX+h58jxueehy8Q28cjUe9IlX68MJI9vu0SfCye6/jmCcH9V4EfbbzVxCA1L+Pferv6RNxfXwN/1/gG3C9fYlHvETG//CH4XeL+nYxfpuLbc6JeTNXvcDl/Cv6sl718vgR/uN4cb+PcnzfjtxjfvzDY2+34KuMXFgZnU9Eo6l2c4frF0t/3+IWO2+fzCnyR4/b5vBL/hVg/ulvjqPeqF7htvyvfLSqfnwr8ANU+gQ9T8Wu4er/nNol67YQn8E5q/GHI9klc1t9xWX/DL3fHr9vrh+/nur1++GDctm/41w9PGP96fPDrefwv3q5+2mlO+1GzqPeQuj74g6L8rcTvcNzGR63BzzLez0lfFT7f+EW4f381j3oHRrOvT3AJPgBv7/jwPYL58Zfgexnf1DdoH7oU72m8W7+gfegyPG58Ee7Pv9QqKud/GItPFu0vE/ATRPtLMT5GrE9Qgh8q1ieowQ9U38+to37/Zm6G909vvNBxe/2n43uK9Tsrcff+tf0Pt+O9I9nXd1qN94pkX98pkRul/W9Xb3tycLSh+KXG5+Lp1MbbRL3r1fgufKV4/x6Jq/mT6vDxYv3HT/ETHbf5O7gt5ZfrNr4EV/m7EFf5ezau8tdrp/O3Ea7ytw4vE/m7A58j8neP9lHvCJG/5fjxov6wCD9W5O9aXOVvHa7eD7kdol5Lkf+dcc/JXzs+owv+rRe4HZ+xFD/TeE5BcLTl+GzjU3F/fvWOvEnE+6cIj4r3zyTci2Sv30/GvxX1+6rdo17HWMP8Oyb9/Ya/xyH2c/wd7p8BqeO/iL9mvC8N5nulfv0ZrzW+AO+VOv7X+APGt+H++6+zLh9rcVU+vomr8nHvLrp8LMQPEPfPDHyAeH5L8P7i+a3DfyWe30/xK9Xz2zXqXaOeX3y5eH47dot6SdX/iavy8R5clY8f4+r5TXTX+TsCV/k7Elf5W42r/H0UV/lbTeVipppfBp8h8vct/Mcifwt68H0nysex+E9F/l6Aq/ytxlX5WIvvJvL/ffzvXvby8QP8C1E+ntpTl4+FuCofE72ifv9g+0zzu+GXOG7rbyfhhY7b+tt4/BTHbf3tNHyc47b+VodvEOOfduDVYvzTx/gD4vu4OZXj68T8Vy3wFcbbjHPSh89P7a1Tpvjh3pR/YvxdFd4/kj3+5i68r+N2/NDv8N4i/vBd/EMve/zhWAavnSviDxN9uf/E8zkI/0w8n1PwDY7b+YeK8WrjB50UpG8mfp/x63E/fp3BeVsj2ddPXYg/gdv1DRql63/4Y8Yn4Dmpo/0cf8T4GjyWbr/Dqx238QnVe0e9IWJ+GD7e9Pz3eBPhcbyX2H9BiJfjvVX/QojX4r8Q7ffb8Z87buM/38PLHLf1q/fxOY7b+tWifaJehUnfsOOc/B8Y9eaJ9qun8NNN+/9pY4Pcfh0=
*/