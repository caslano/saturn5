
#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_STATEMENT_DETAIL_CATCH_PUSH_BACK_HPP
#define BOOST_PHOENIX_STATEMENT_DETAIL_CATCH_PUSH_BACK_HPP

#include <boost/phoenix/support/iterate.hpp>

#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)

#include <boost/phoenix/statement/detail/preprocessed/catch_push_back.hpp>

#else

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/catch_push_back_" BOOST_PHOENIX_LIMIT_STR ".hpp")
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

    #define BOOST_PHOENIX_CATCH_PUSH_BACK_R0(Z, N, DATA)                        \
        BOOST_PP_COMMA_IF(N)                                                    \
        typename proto::result_of::child_c<TryCatch, N>::type                   \
    /**/

    #define BOOST_PHOENIX_CATCH_PUSH_BACK_R1(Z, N, DATA)                        \
        BOOST_PP_COMMA_IF(N) proto::child_c<N>(try_catch)                       \
    /**/

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
        (3, (2, BOOST_PHOENIX_CATCH_LIMIT,                                      \
        <boost/phoenix/statement/detail/catch_push_back.hpp>))
#include BOOST_PHOENIX_ITERATE()
    
    #undef BOOST_PHOENIX_CATCH_PUSH_BACK_R0
    #undef BOOST_PHOENIX_CATCH_PUSH_BACK_R1

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

#endif

#else
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, BOOST_PHOENIX_ITERATION>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Capture
                  , Expr
                >::type
                catch_expr;

            typedef phoenix::expression::try_catch<
                BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, BOOST_PHOENIX_CATCH_PUSH_BACK_R0, _)
              , catch_expr> gen_type;
            typedef typename gen_type::type type;

            static type
            make(
                TryCatch const& try_catch
              , Capture const& capture
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        BOOST_PP_REPEAT(
                            BOOST_PHOENIX_ITERATION
                          , BOOST_PHOENIX_CATCH_PUSH_BACK_R1
                          , _
                        )
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };

        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, BOOST_PHOENIX_ITERATION>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Expr
                >::type
                catch_expr;

            typedef phoenix::expression::try_catch<
                BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, BOOST_PHOENIX_CATCH_PUSH_BACK_R0, _)
              , catch_expr> gen_type;
            typedef typename gen_type::type type;

            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        BOOST_PP_REPEAT(
                            BOOST_PHOENIX_ITERATION
                          , BOOST_PHOENIX_CATCH_PUSH_BACK_R1
                          , _
                        )
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };

        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, BOOST_PHOENIX_ITERATION>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;

            typedef phoenix::expression::try_catch<
                BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, BOOST_PHOENIX_CATCH_PUSH_BACK_R0, _)
              , catch_expr> gen_type;
            typedef typename gen_type::type type;

            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        BOOST_PP_REPEAT(
                            BOOST_PHOENIX_ITERATION
                          , BOOST_PHOENIX_CATCH_PUSH_BACK_R1
                          , _
                        )
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };

#endif

/* catch_push_back.hpp
PuVXjrnn36j8hCpjPGZ4L04i3Jx/K2qYRjCS7Cq9eSPiq0KhEbKTxD15uf2gBpXRWHb/Mu/sN1wXFmDMIpvoDTsIP/t2BYXltjzd69n6BR2VOxpfsY2UG+3qtNsRL0S4jSwtNrdeYGMCYLe8u9itLOhxAwXe6iLgn+zbF7GczP7pb3TyfMOX/JEQvdJdtyux3atGxqGDWorV86GLjaF8uVk2i6UWx7de5tktATu3Nh8dXfxqgR7Cy6CFzavHRsdjkaEz8zSf5rcxCGj2aRjAIvjbY07HIo04SV0PfEiPVhaXJeuxzwI+PQqKwkpg+6T5P07I1yNVZXETxaI6sifFYbiPM8GHfpR/srsCvvM/s16UHdDRMgzYk4ZtR2ANPNBhmBOcEb/LqKqxWycmsQL7A/uDWfD3rBljV6hVMOEqQRUPkN7s/QsXfp0RB3n3Du8TOvZ2zFty42deUsBWXGhAIun8W3iwnWz5dJ623NnBZ+RNYPsCDbb3W9Cn4Pl2ZGQr7/5F9eZQxBAamSxpZt1nPlef/DLAS3dbdrCxE9tROdTH6t4sefaTUeSy3X5/4IyvsL3mYr7RF3fQSLWRmQWNEgHXtmp1NL7pxKvKz0O/isDJ8KfZDbBQGQ/V8SrpqZ2+xxqch2S/GHIKsOhWG4OLnz89c/sTvqusZxT+CA1WG0WYF87T4Q+0L8V5CAsdc9iovV1L6YeEZdXO/Cch
*/