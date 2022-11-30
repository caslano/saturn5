/*==============================================================================
    Copyright (c) 2005-2007 Dan Marsden
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_STATEMENT_THROW_HPP
#define BOOST_PHOENIX_STATEMENT_THROW_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/terminal.hpp>
#include <boost/phoenix/core/value.hpp>

namespace boost { namespace phoenix
{
    namespace tag
    {
        struct throw_ {};
    }

    namespace expression
    {
        template <typename A>
        struct throw_
            : expr<tag::throw_, A>
        {};
    }

    namespace rule
    {
        struct throw_
            : expression::throw_<meta_grammar>
        {};
    }

    template <typename Dummy>
    struct meta_grammar::case_<tag::throw_, Dummy>
        : enable_rule<rule::throw_, Dummy>
    {};

    struct throw_eval
    {
        typedef void result_type;

        template <typename ThrowExpr, typename Context>
        result_type
        operator()(ThrowExpr const& throw_expr, Context const & ctx) const
        {
            throw boost::phoenix::eval(throw_expr, ctx);
        }
    };
    
    template <typename Dummy>
    struct default_actions::when<rule::throw_, Dummy>
        : call<throw_eval>
    {};

    template <typename ThrowExpr>
    inline
    typename expression::throw_<ThrowExpr>::type const
    throw_(ThrowExpr const& throw_expr)
    {
        return expression::throw_<ThrowExpr>::make(throw_expr);
    }
    
    namespace detail
    {
        struct rethrow {};
    }
    
    namespace expression
    {
        struct rethrow
            : expression::value<detail::rethrow>
        {};
    }
    
    template<typename Dummy>
    struct is_custom_terminal<detail::rethrow, Dummy>
      : mpl::true_
    {};

    template<typename Dummy>
    struct custom_terminal<detail::rethrow, Dummy>
    {
        typedef void result_type;
      //#ifndef BOOST_PHOENIX_NO_SPECIALIZE_CUSTOM_TERMINAL
        typedef void _is_throw_custom_terminal; // fix for #7730
      //#endif

        template <typename Context>
        void operator()(detail::rethrow, Context &) const
        {
            throw;
        }
    };

    inline
    expression::rethrow::type const
    throw_()
    {
        return expression::rethrow::make(detail::rethrow());
    }

}}

#endif

/* throw.hpp
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
*/