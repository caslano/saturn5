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