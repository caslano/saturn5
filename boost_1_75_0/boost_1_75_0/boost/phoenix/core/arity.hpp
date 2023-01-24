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
C/4gJvRvtiZ0fqxWWBB0qsExo8Vmp26S+NhoRsNLcArKUsBwTANSdUhyFMTbCgN8NfQHwUvxYKVE+4WMA236i1Z1gv7YaG/qj2GpOM3sj0ecPwyasxebRxUWRxvq5m1esed0uPwdXtYlpTAMAUKH1+6QcMbn9cIySCItgsmCzQeiXODaCBsZHdIaio1iMCxJay9S7vG4umWMVUsFLDroaNrgR2KznyrYAPMzAgVorWku9/u9zqYOP5OvxrEA0Ki9UvdVReG8ToVJDDhBUclzNHW0wmquTnAvhhYWGFnn6PB7ba5FohF882Gm3QEWDk6Oqiu0oDIF6AozQmcArRyG2PYmF3OtCjmg6Yfg9tqaHVDfK5UoNvui/Rkmgyt7p8G+v8Th9cGo0DsSumSLs7XDS1e9vaOrHD671+kJjGSmpymgDdhW0ZCvd2KowuYOuz9Upp5ur7O1LWQUtEt3txIhTpgo3e9scrqcflVs9SqHnVWyn7oGtkalrRVyb/fAWhSnRMSxyu7q8Dk7md9k60e0C3oROoUJIsHc3Quq07DN67V1M0YA9S105if2r8qWVpoZXUVgpavo6I5xbiaOYkucNhipSVuXuxnvC3Dq66ZcbFkFfqsVCQ29CGzhLhqiQKxKjGln01X2VhiBorJArW2lg+0SiATsUyzk6XCvrBLsVTa/rXoVLCpV8qu8ti6RGXIWPSld3kilqIJFEJCg
*/