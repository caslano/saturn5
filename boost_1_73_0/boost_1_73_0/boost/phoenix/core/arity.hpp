/*==============================================================================
    Copyright (c) 2010 Thomas Heller
    Copyright (c) 2010 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_ARITY_HPP
#define BOOST_PHOENIX_CORE_ARITY_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/is_placeholder.hpp>
#include <boost/mpl/max.hpp>
#include <boost/mpl/int.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/terminal_fwd.hpp>
#include <boost/phoenix/support/vector.hpp>
#include <boost/proto/matches.hpp>
#include <boost/proto/transform/fold.hpp>

namespace boost { namespace phoenix
{
    /////////////////////////////////////////////////////////////////////////////
    //
    //  Calculate the arity of an expression using proto transforms
    //
    /////////////////////////////////////////////////////////////////////////////
    
    struct arity;

    namespace result_of
    {
        template <typename Expr>
        struct arity
            : mpl::int_<
                evaluator::impl<
                    Expr const&
                  , vector2<
                        mpl::int_<0>
                      , boost::phoenix::arity
                    >&
                  , proto::empty_env
                >::result_type::value
            >
        {};
    }

    struct arity
    {
        template <typename Rule, typename Dummy = void>
        struct when
            : proto::fold<
                proto::_
              , mpl::int_<0>
              , proto::make<mpl::max<
                    proto::_state
                  , proto::call<
                        evaluator(
                            proto::_
                          , proto::call<
                                functional::context(_env, _actions)
                            >
                        )
                    >
                >()>
            >
        {};
    };

    template <typename Dummy>
    struct arity::when<rule::argument, Dummy>
        : proto::make<is_placeholder<proto::_value>()>
    {};
    
    template <typename Dummy>
    struct arity::when<rule::custom_terminal, Dummy>
        : proto::make<mpl::int_<0>()>
    {};
    
    template <typename Dummy>
    struct arity::when<rule::terminal, Dummy>
        : proto::make<mpl::int_<0>()>
    {};
}}

#endif

/* arity.hpp
JIDN2nrH4ii5wI4sC2jGMtl17byoyaa2Saqc7fKz2VMovEosDAzOSgFWNjq1Afjm5WAAy0Wg2zgVfGXDA6uRyVt0xx/dsjCVcRDPR5G/flWnGDOkDTfl4HqlEPSxNX2QUQuyBgVR1buhE3p9pB+fl7nIedJBsXdjpDObk1SuH4OEEYOru1WbXE69wRUL3qMTrmwRq35Bg7O6+FUs+rvCT/wxJi303KBRtXl/PJx4A/QROGrkhd54FHzjYpt2A3H+8M2cbg8a7/+Yx+tfbr/mSUN5T/Dm9hCgIr9H2kPrNnQR5WouiwVbRF+4qRPD3LSaw/qtizczY3tCnfq+OwqP5vVQuBsbIFiqx6/1Y4qGlqUd89aej633yF8uRa40Ihvf+M4w2NZpAy0dce83imZev9+sCdCAmJzUNk1KzgjfgxZGYF6arzkKYk4g3fjxyRxYnmbRHlia/1viZBQ/L4MvLn/75pTEYgmu1/OTInyR8Fl5d0pGiwVf1b6067iOvnMttQZZrRViw4Eq2y0pAKvwkZwntHACkJk9pNn1B7WVjL+g5pjt+uF5/ecCw8hjSDROgPGTJupCWQqpa3faJz3XS7COuZ/wxvzeTduN/wBQSwMECgAAAAgALWdKUovqypFVBAAADAoAACQACQBj
*/