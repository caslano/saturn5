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