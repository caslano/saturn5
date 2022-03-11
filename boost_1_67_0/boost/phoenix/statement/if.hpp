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