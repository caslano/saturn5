
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
xblmo+cRkCn9ospSkA9EmyxNsHU/L10mWXIjS+nOY0QH6tuQmzoutaezmEmgtyOuEhlPiXzKJNJk41ubSuQOPrZQLrt6O/J29bbg2179eKTL3en74WVmp285QiBBGrjT9xXAcJW8RRxSQbCXqHf6ZmelTLc5c3b6lnAMBeLMl2ewm5bb7JBaVpGSanUE0ChoW38BvVPRzF++0NYSizVxI+Cwb9ydf3VKYnMlYouTMvXy+nLq5VcHrZdvep/w961uxYodzIpt71Op3fq+3NTeI8KzJPinpS21inw3OhjbflzXGF5/aOo4EMrE3jLmao53Et6Z8D+zWYRfe7M4LbGL60Ys2z7Cpn3cealtkxF1mH8CV8AyCKaBND9s4em/vWyqfKO9XT05aLu6871SJF+D3zBOXUg1iuhFw05pEhscXK1yRzRQmDui/dIQAHhDwDRFwBkIVeXktm1b3h3U25bU5epty1+bLvdqjeen7xE8hx32Po9pcWIHM4+W5wwtN9rbv8JxR35+oGQXgJ8m0Ixu0Fap4WGmB8OTaIsn18Mt80pylK5QdPOB+ZdNsmfYymCKJJs5IyMWrXr0XvC16Ods5z4WuLQO60QRqurz9S1+kXDRWlYfsZ8T+N8XIp74nfid+OXev3H/qP7+HEX8XlgHq2cBLkt+r2+FJx2uJ0FkQSN5fYg1r/vcVXxTP59uTbwktiQXs8axG/5aJgOP3NPx7MOiGJyrZ3AXo+lOdBbMr+mhFP4JYj+jL/9kEZuK5v2Co3l2z2MX8fn3AATJFWHvCpJ4xp1aFi/+yXCQP0v0Zwl/esvUp5c/ffrTlxkHD2CtqBV8M2VHjrclfNltiW7b5OivS9R05TlxzEQvjwGcOeLkWLwH4cMehGjw7seLCe+uU2J560dP8LDGB7QsvekXsuhu3pFCMKvl92i18B69f9JTUWM1VMld5N1h6y7B0xLql1g4hFJW38OpBNcHx7bUH/M/EILopubYWTXd0ztf7Joe6kWimXtQJUQpoS5Cb6tvvyZIricCnGJcFzOKt1NYm/9PT7yG7ZR/+o/bg5v2f7158tx5L+tNPi+71FkLKtx7fLLj4F/3PbDcdlnDKRdpAfjFtishPBepgn6hTk3RHTy3ordjJebffX1min6H2ZgJ0EbwvRxDgVAlyG5xtFUjuk2c5YewVxGaPg2gtr2Oz6h0GSB/FY3pDXnXWlfW5c6aoU5FAbipQ0efgU8SKs/QDNlFLqf/099mPi1+2cz62E11jR2tKXpjo9yfSPGUCJ80F+Z/VD3iPpoLVywpLInNjHxLWMAHhzeJSlh1bfbgMJ2UC7WCBjbHzihQ6TFJLwlbJXVK92L19MgDA9G8HDZonisCm+ppnrs9dz11ca0pQtvCf2GtKsI3igP2yfuoCPGWIuzJFuF3c4vweU6UQaQITReQbOYiNGtClt1rHpbYeoofh23lx/Cy7VSMXQOCj41O7OKI/uZkfkmA1zL/ZocUTEUo0LAkh3fePFbmfgazdkuUvyrC1hCX3eIxQYiJSjI3YhcE3txZJciIJdfROssfVtw7Q2dkAfxpA28FSpJgwlbmnQrmGXaw0IYO+x803LwZeHVJngUgbS5rZF6OQaHIQ9ghDKioR91D4g5d6TiMc+fy4rR3F9fSam4HV2hK6gwlpWjqf3CpbcaxWY23tlJqEWNoHPXSd3Mp46F3MlWOd97BLP+6o6QJj1NXzXMRyuhkU1JujK2CCH4SoRxn8yQ/Rkvvzr8OsDcPTGQ8XpBxnZV4tRCllzAym+dY+HE9oHeumhYjIk0tpo2GZ3ZEC5UFSjfnqBZwXKhfX8H1OupFdlR1GY1bCsLHKHCTBGauj2I=
*/