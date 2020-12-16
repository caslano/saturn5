
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
qLW+YKjcw7XE59V9zEWn9FV1T45OnqSlXTkX7V6pvqSlloiKlnUv+fFwTynPPqRfA1chScnSL9JxzoqzXQsY5zPr8wUarsekcxWHXmO/Jft0eWZiiMMSo8Vi3A7GtjHx4/8L6nVixoxApudodaINWJKWCquFKwc9bn29BOViO5D14LVeJL/2vlyGfVeOT1ImtRkyo1q2ouFcKNOlFmS7d3mGI/Uo9aLvM5XZFkZR9k5sA59rZWVew/lRtV2oy6RAWS8P+8nzIsO1k3HbbhSqF/5RVSa5B3xRnQMuO+pR700ra+cOjpFaG31qiv2ZgKGvmr0eU036NKrFbdsKMDyb5D6bqJyfCWdJWXpLWXoQ/h5IfFcMZRkfl2BWdZGHfo32vlVSjpcCmaaOK5InP8l3imFdXjPk25jHlLZ6Ar0kj90lj1lueSTFPOaRBe4wj/o2cVnyGC557Et4hfhCrjryqLUaqQ5OuchjoOQx2LVPlORhO3EzsNCpnTbtXj2CkZKHYYQd6vztKQ/asMQ7z4fUhVM+UtrJOBB17BVfDSSOP1zyoXZ+dR2Si/oobSqp92dXcRj+XmT/u5D/TP3ftfr2b6v9nWz/O1T7O97+dxvtb4v979ba32Psf7fS/h5m/7ul/fgfbOj/ZjwmlJQbnSJS5oK4U13LXnMt8+33Ebb3yZRjIch2yrxyXHA9D++XfM2XbSKNsEddB113yZfKVoJZreJcH6vs7+GVfO1Wxw3Dtapcj7hey8SZXZ7PkjQTnfenkA7ufS7fUPXpId9xebhWkTw6ba/mjjIWQdZdR9ynttcbjrRcenjnuc3Xtu7s/axlmv2YzlAot2M602zjXoJkvmhusKfJfllZm0+mqRkN50A1PYFbxphYl37OnATc2vRdzqUTDetHS5Nl3Ma6dNILu0S2q4cIb6tni6ZC9jqTyorS8mcx53l7l+1Krqdc6kvyFGA4HsZySLPls4fk85rk813J59smvf3C6mPPJ/mzJnBMTKD7gu0iWGvIMJlyf+2T2/aKqoaxZ8lcp9kbvqVhSLuOk/83tokb28udFnF5nnotTM9cZ9mWO8jzSGuBW5dXeyB5F55H3qLtQbYrx//Z2kJM5P0c4Xd1fie/bs8wDc8qL8n/v+XvfN/Xvoue0fel/O/56H1Z/Xzt5ZdLXO2uj8bo6MnMdtvPK233eYGGa391Y2GxcE/j5TpT9lHjvavXa0/ZL+U+XuqpM/c1XfTvKJ7WyiX3CjKfVj6S97ify/Z11dDXy3jcPdFdL3TLItSf+K7qi1jYpf6kYUPV29hcnLdjS7G8tPmtKFrIdl5tbZJpDzqmtbJNm+qY1tI2Lc4xrYVt2ijHtOa2aQMc05pp9cu088WYJn0EtVOlXDe8XlKbzqDuW6/n3IwfUvMEGfpBGu8D5UF5fDTJ2/tOqfOo9ijNsL0b1td52/py7bswVcYyOJ4NShuwtr7ljRaSmGwjWfY2oKS4GO67E80WbZsKY3syd9PvA1YUcex7W2X+RDln2uY9x7xvMFMVvZ6d7j/lpl67Gjdu/0kylkfFEcvyZwnzTcSjxyF9l+QcJH+fsJ23ZFs15qEc22o3ps8qLstL+79aVzHRzvk9zrx7mOlEcUd+TxvXiTzoCJA+SqX9VRxRZlt+g+Qdt+r5Y70Sjji22+JQixvOwZlavmV6suRF4skiqI28t9ruDH2atG3Mca512zfP9ZD+PHJsm4TP8j9jy7jum9oRJM/XKMZ3VVjdxm96v7dkfulfKW0ZHvpAVpR9wG27lPo91Z3tgfLdz9/PlXE+9tdQ9Runt+8Yz+0pPfXCfO/DvPgNhqt7Ln/X+mDsYnxcjGrPNzxb0+qn0U0=
*/