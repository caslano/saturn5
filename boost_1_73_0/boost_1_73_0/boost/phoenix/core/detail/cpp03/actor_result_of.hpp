
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_CORE_DETAIL_ACTOR_RESULT_OF_HPP
#define BOOST_PHOENIX_CORE_DETAIL_ACTOR_RESULT_OF_HPP

#include <boost/phoenix/support/iterate.hpp>

#include <boost/phoenix/core/detail/cpp03/preprocessed/actor_result_of.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_CORE_DETAIL_ACTOR_RESULT_OF_HPP
#define BOOST_PHOENIX_CORE_DETAIL_ACTOR_RESULT_OF_HPP

#include <boost/phoenix/support/iterate.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/actor_result_of_" BOOST_PHOENIX_LIMIT_STR ".hpp")
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

        template <typename Expr
            , BOOST_PHOENIX_typename_A_void(BOOST_PHOENIX_ACTOR_LIMIT)
            , typename Dummy = void>
        struct actor;

        template <typename Expr>
        struct nullary_actor_result
        {
            typedef
                typename boost::phoenix::evaluator::impl<
                    Expr const&
                  , vector2<
                        vector1<const ::boost::phoenix::actor<Expr> *> &
                      , default_actions
                    > const &
                  , proto::empty_env
                >::result_type
                type;
        };

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (1, BOOST_PHOENIX_ACTOR_LIMIT,                                          \
    <boost/phoenix/core/detail/cpp03/actor_result_of.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else

        template <typename Expr, BOOST_PHOENIX_typename_A>
        struct actor<Expr, BOOST_PHOENIX_A>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            BOOST_PP_CAT(
                                vector
                              , BOOST_PP_INC(BOOST_PHOENIX_ITERATION)
                            )<const ::boost::phoenix::actor<Expr> *, BOOST_PHOENIX_A> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* actor_result_of.hpp
TKNYijfHJ78Oj971xPUsmswQyG26FPksXcahmAVXUmRyIqMrhrEIskKkUxgOwMMoLwDgsojSZB3mlqKQ2TxHGDh9EOepCK6CKA4uYKKgELOiWOQvNjYmyywG7DfCdJJvTPTy12fF3KzkV0BiHtyKdFGIIhXLXPYE9uyJeRpGU/wLBIHGxfIijvJZz2IDUyXhRpqJXMYxwoJxkcwZbSlOFXl62E0sAOOowD95muQ41fUsnZc6Ah0RynSZJTAR0AE6hSmQuSeWSSgz6kwr11MomhKBW1lj8Q1FmgAyorN/KoanHXER5FHeEz8Px++PP47Fz/uj0f7R+Fdx/FbsH/2KwP45PDoA1kcwWSbkzSKTOUyeiWi+iCMZqjm/3c/GyvdRMomXoRSdXGZXMvNzWSwX67OOffIyL8I4ulifvSq1ZVFyWWrrgMDEOHJlY1W8XSYTlB9Fpf3JRC6KXARi/OYEGJckkh4ThcRkmRfAnEUKQugNT66e4Zrh7053XYjThQw+5eLDj+OxpvlIBiEAmc+B07mYZjD27fBwIDxAXlwD9cTaGswxjS67LL+mL7QWWRqLWXoN7CaJBrODAgOcA2pLkspQToNlDOjKYDITEyB9UriIrxsNxzlY3z7J2+s0C/MXWi6OD47h7wZRAzjP
*/