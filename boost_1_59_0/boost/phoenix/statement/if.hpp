/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_STATEMENT_IF_HPP
#define BOOST_PHOENIX_STATEMENT_IF_HPP

#include <boost/phoenix/config.hpp>
#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/is_actor.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4355) // 'this' used in base member initializer list
#endif

namespace boost { namespace phoenix
{
    template <typename> struct if_actor;
}}
    
BOOST_PHOENIX_DEFINE_EXPRESSION_EXT(
    if_actor
  , (boost)(phoenix)(if_)
  , (meta_grammar) // Cond
    (meta_grammar) // Then
)
    
BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(if_else_statement)
  , (meta_grammar) // Cond
    (meta_grammar) // Then
    (meta_grammar) // Else
)

namespace boost { namespace phoenix
{
    ////////////////////////////////////////////////////////////////////////////
    // If-Else statements
    ////////////////////////////////////////////////////////////////////////////
    
    // Function for evaluating lambdas like:
    // if_( foo )[ bar ]
    // and
    // if_( foo )[ bar ].else_[ baz ]
    struct if_else_eval
    {
        typedef void result_type;
        
        template<typename Cond, typename Then, typename Context>
        result_type
        operator()(Cond const & cond, Then const & then, Context const & ctx) const
        {
            if(boost::phoenix::eval(cond, ctx))
                boost::phoenix::eval(then, ctx);
        }
        
        template<typename Cond, typename Then, typename Else, typename Context>
        result_type
        operator()(
              Cond const & cond
            , Then const & then
            , Else const & else_
            , Context const & ctx
        ) const
        {
            if(boost::phoenix::eval(cond, ctx))
                boost::phoenix::eval(then, ctx);
            else
                boost::phoenix::eval(else_, ctx);
        }
    };
    
    template <typename Dummy>
    struct default_actions::when<rule::if_, Dummy>
        : call<if_else_eval, Dummy>
    {};
    
    template <typename Dummy>
    struct default_actions::when<rule::if_else_statement, Dummy>
        : call<if_else_eval, Dummy>
    {};


    // Generator for .else_[ expr ] branch.
    template<typename Cond, typename Then>
    struct else_gen
    {
        else_gen(Cond const & cond_, Then const & then_)
            : cond(cond_)
            , then(then_) {}

        template<typename Else>
        typename expression::if_else_statement<Cond, Then, Else>::type const
        operator[](Else const & else_) const
        {
            return expression::if_else_statement<Cond, Then, Else>::make(cond, then, else_);
        }

        Cond cond;
        Then then;
    };

    // We subclass actor so we can provide the member else_ (which is an
    // else_gen responsible for the .else_[ expr ] branch).
    template<typename Expr>
    struct if_actor : actor<Expr>
    {
        typedef actor<Expr> base_type;

        if_actor(base_type const & base)
            : base_type(base)
            , else_(proto::child_c<0>(*this), proto::child_c<1>(*this))
        {}

        typedef typename proto::result_of::child_c<Expr, 0>::type cond_type;
        typedef typename proto::result_of::child_c<Expr, 1>::type then_type;

        else_gen<cond_type, then_type> else_;
    };

    template <typename Expr>
    struct is_actor<if_actor<Expr> >
        : mpl::true_
    {};

    // Generator for if( cond )[ then ] branch.
    template<typename Cond>
    struct if_gen
    {
        if_gen(Cond const & cond_)
            : cond(cond_) {}

        template<typename Then>
        typename expression::if_<Cond, Then>::type const
        operator[](Then const & then) const
        {
            return expression::if_<Cond, Then>::make(cond, then);
        }

        Cond cond;
    };

    template<typename Cond>
    inline
    if_gen<Cond> const
    if_(Cond const & cond)
    {
        return if_gen<Cond>(cond);
    }
 
}}

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif

/* if.hpp
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
*/