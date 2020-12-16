/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller
    Copyright (c) 2015 John Fletcher

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_FUNCTION_ADAPT_FUNCTION_HPP
#define BOOST_PHOENIX_FUNCTION_ADAPT_FUNCTION_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#define BOOST_PHOENIX_ADAPT_FUNCTION_NULLARY(RESULT, NAME, FUNC)                \
    namespace detail0                                                            \
    {                                                                           \
        struct BOOST_PP_CAT(NAME, _impl_nullary)                                \
        {                                                                       \
            typedef RESULT result_type;                                         \
                                                                                \
            result_type                                                         \
            operator()() const                                                  \
            {                                                                   \
                return FUNC();                                                  \
            }                                                                   \
        };                                                                      \
    }                                                                           \
                                                                                \
    inline                                                                      \
    boost::phoenix::detail::expression::function_eval<                          \
        detail0:: BOOST_PP_CAT(NAME, _impl_nullary)                              \
    >::type const                                                               \
    NAME()                                                                      \
    {                                                                           \
        return boost::phoenix::detail::expression::                             \
                function_eval<detail0:: BOOST_PP_CAT(NAME, _impl_nullary)>       \
                    ::make(detail0:: BOOST_PP_CAT(NAME, _impl_nullary)());       \
    }                                                                           \
/**/

#define BOOST_PHOENIX_ADAPT_FUNCTION(RESULT, NAME, FUNC, N)                     \
    namespace detail1                                                            \
    {                                                                           \
        struct BOOST_PP_CAT(BOOST_PP_CAT(NAME, _impl_), N)                      \
        {                                                                       \
            template <typename Sig>                                             \
            struct result;                                                      \
                                                                                \
            template <typename This, BOOST_PHOENIX_typename_A(N)>               \
            struct result<This(BOOST_PHOENIX_A(N))>                             \
            {typedef RESULT type;};                                             \
                                                                                \
            template <BOOST_PHOENIX_typename_A(N)>                              \
            RESULT                                                              \
            operator()(BOOST_PHOENIX_A_ref_a(N)) const                          \
            {                                                                   \
                return FUNC(BOOST_PHOENIX_a(N));                                \
            }                                                                   \
        };                                                                      \
    }                                                                           \
                                                                                \
    template <BOOST_PHOENIX_typename_A(N)>                                      \
    inline                                                                      \
    typename                                                                    \
        boost::phoenix::detail::expression::function_eval<                      \
        detail1:: BOOST_PP_CAT(BOOST_PP_CAT(NAME, _impl_), N)                    \
          , BOOST_PHOENIX_A(N)>::type const                                     \
    NAME(BOOST_PHOENIX_A_const_ref_a(N))                                        \
    {                                                                           \
        return boost::phoenix::detail::expression::                             \
            function_eval<                                                      \
                detail1:: BOOST_PP_CAT(BOOST_PP_CAT(NAME, _impl_), N)            \
              , BOOST_PHOENIX_A(N)                                              \
            >::make(                                                            \
                detail1:: BOOST_PP_CAT(BOOST_PP_CAT(NAME, _impl_), N)()          \
              , BOOST_PHOENIX_a(N)                                              \
            );                                                                  \
    }                                                                           \
/**/

#define BOOST_PHOENIX_ADAPT_FUNCTION_VARARG(RESULT, NAME, FUNC)                 \
    BOOST_PHOENIX_ADAPT_FUNCTION_NULLARY(NAME, FUNC)                            \
    BOOST_PP_REPEAT_FROM_TO(                                                    \
        1                                                                       \
      , BOOST_PHOENIX_LIMIT                                                     \
      , BOOST_PHOENIX_ADAPT_FUNCTION_VARARG_R                                   \
      , (RESULT, NAME, FUNC)                                                    \
    )                                                                           \
/**/

#define BOOST_PHOENIX_ADAPT_FUNCTION_VARARG_R(Z, N, D)                          \
    BOOST_PHOENIX_ADAPT_FUNCTION(                                               \
        BOOST_PP_TUPLE_ELEM(3, 0, D)                                            \
      , BOOST_PP_TUPLE_ELEM(3, 1, D)                                            \
      , BOOST_PP_TUPLE_ELEM(3, 2, D)                                            \
      , N                                                                       \
    )                                                                           \
/**/

#endif

/* adapt_function.hpp
HEk129M049VvDNoSIie6/5fBegbS+v1rZWdoR61//vAfWYM+f3hLymywKFs86hstA8xFP8sUuTq3icG63CJZp0cL4b8ADYJ0Ghvg0bRtC7wX5sVSpgxkA9gpRC4jzyiPeWni6tyTwTLn/jGfT8shRXKGFPPzCoYVCQ+2Zd5tdPIo/102F5DTZ7P2mWVNfLutsUnhoP7uY0GQM++B3K4ozdtLSqubfDiQHmNMUVY56+0K5NyE3e2D8WZ+005fBRROJvpvGwsn7EYkekBTkXTbvbK3XQnZl88IDK3tVGFRP5huuqcPPT0zqe+6aWipG2oDQXhjTsnaTl4zwLrre1iKi9Q9O7aVBHE9v1v2nDQvz4+dHOBLurkDmlUumTfWrXlX64d4mz/ubBnXBXMkf2FsgM9s9qjGi5VFAd6QaBdrcmoFh7DVnkpO6a+9bqX0YFWgnQNbav+rRUYUiHBDSZTN5cYXZsFuwdhnQ1p+AvdG/CrjnqqE00ua1jrXUdtViT146zikSLVxyIsWCj/XeeuAu1aoM8VgXVzX6bPdBEcEmbq3RdbECW6f92MPVXRjRM+utxX1Y9+ceUst3LsHS/gniMs8fzD1fGHbzPsjv18UuOeWi2wrFE47jnpb5wuze0m7pTkRDes1/kC3ky9NeedFus7JrcpVS9c1VtfOr6mwM3BPcK8sMzH9jFOLnN4ACIlKUft6moyT+kCiHSbT7zzd1us1Bt6fOYP6GHRI61w99hrq9F2swXn92OlS27XvXc1neXXOJEif4J0Vme8XnKP6IAYeHc8Tm+AwVKyXr+v4fc5Xc+jtUv6pVy4RLIV3fybjsSxt1CQb2293UVZbIQmLag6X0M7BrK5WxvQx/GXZ+suRuabzz4s0TaSBzuvMNo4sKz2H4lEyB6am9eVVwuf1i+YRoRbdHrhn1yWa99o0Jb/+V0U6p89B1i7tg70rOCmIMaco3R6M4eucwMK+edrurlwdg/h1kX53KqX66NxH97RlyRu6NmDngvdE/iZdLwhXY9sbqYM96utqqsv4shWhUumvctF/m72NA+JyHrRFbVOfITAbZknbW7K21TefKm9b8wi0CByau7NQzfe39T82TX2dUSC62UMaTuv4vHGHxmgiQBqnrc36HMeZm78LUhLC+ubx3KfitAPEkVy2e8x4d88X9TnP7u0OxbrDKrZ3hdxZ6WIXDCQZTAlHO9Umlp6b/zqAtEQXBO4YbY0k3P2ihYF7/ZASkSmhZ6BPpDUyw3bMdm9ptDXSnK4bFaiLh2eaCX3LQh0kxNkEZLG9gfoSb47B8pnTXVXWu1OLS+aofoG67wXGDPRrD3eZfu5jDdQFntd/P1c3pf95Ohq4BGylnwJjbFG74Hj0M1synm03OdAuDHjv7Iw2u0FlT/ttwwD9tulo5v8lyGmsc1XxjOl7m758k4hEWhXfBHPTPbpO9XlUrmg0/p2bRe48xLmJOi80eGc2n8fIVr53cYnP79eJzndSJGEgxlP1Tv+4efhnScbPb1D2Es2zUuUuB+SUPyxko29J4Nk2zOo0UraAK52d/VV9ODt0zUXiXZMt+h6gfRid+547va30mbr/s8jpIpd8FMin9Nb4QJHSVzKf9N0Bf6NuYZsxO7hrluQ7bFI2XpU9KWUbc/yy56Ssyrbb0jO1cCzL+e+GrGdq/2B8jjSz5pU8r2MN+i4uFSN7scjznwZs9yrt0lML8UBAVbRHPpSRcb9lsJ1Emr1vPjncHUfLr4iSoSTfI/LPxV5UZ0L953L4mOEzad9vW4Up37W4LWaTw+OSv62eqWigDx4mBJ4TrE/P+/0iT77cU+UQoNfdppNIZQjjTmVtT7i+v+b+XYw=
*/