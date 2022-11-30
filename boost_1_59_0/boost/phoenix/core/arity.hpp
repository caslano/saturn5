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
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
*/