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
5/qyqNDqy3z4slvzxX6n/Wf2JYusKTH78mShfVyUGqsvxhvewx8PpVJc6BVxTn8JFln7ywL4Uab5cdBTA5+9v9xbYvSXAPnzZxt/ToY/SzR/Dulkwmf3qaPY8GmeFqOB5nlLzJ9n6D59tjlLzJm5tnaTrY9gaATw/QKy5dVsWeerqf3aKiq5o46VVbCzx2ybf+ZzOcUhx5eGQULRSdQW09gYYvOnX/PF2NFwODG3q/fDeWxtt9rq+qy2tOvC1MFWW6eweUCzZd158W/Zuz6PvbKlhr3POs4Ne8bccsYQIbiL+uuLwFNZuwl7+d7aHLZNbcxcBmaAPhfT5y76zKa0S/A5Exafx9HnPiCbmybQ3MSDTPWooXqUDRXGf6uIsfBLZDcU3tPQbz1wNRP9o/Aw6qLNkw/iM2sEhWjFnCauKYpWJ6J1pVP6+NmBz3WB3Ll1D/lf6xLzWTXQg8IvNHL/D+GNkKjHkn9jLcavQ2ydEBWfn4Esuy6F47lrtQ4uv6BkbAC+8bk5ty6Fw4XRj12iLT6gOTDVxOuCeuhvssWiQjvRQS8xtTE74SBz1bjl/c9Ve+Av6z+99PkD+ryMPr9B9YNJ/nkv8Tew9qS20tcIUUH7M5XB60X2Wp+Xexe0skJO43GZ2Szi8lxpblz+THFpoLjUU1z2LrfEhRraPi6jDhKXia0Hn8PlOLxritMeIy68zntt6vyBUeec+WQLKqa942B/7lVEP76qldfRuA7ndOXDH4M5/TVu1Ms7Cvy0aIdFQdEOHcW8HeCTmFSrB7D3LpWVtwb/+NJH41p+dfaElpsn4PDGq4WM/vtv73Pfd+2OHWvefmHlaTe98RrWQlz+om985RdvPl1Zef7TrRtiV9y2B/2hiNFPLVPf+3x710kFfV3DznlL3YVrxiBG//Hwkd8PzZnzo8VFJy1Yd4wPPwp1Gqd//MoTg7987vlX1f36vXDstCnYaH8Hp9cGIuNfb3t3xpDUhN3nzf0AB2r+wd8P7Xj5yAUXFzT+s+6EIx/96Ql/wMGR97j8xJcjw+KfW3bh74dckpo8rfnrWPcMZvRbr+tseaDwr7979JYTPr1h22W34F6D08cMj/qfX76nZ/qU6zafs/Gb2Gj98kBGP6v0uieeWDd+xQtfO/PB3dNOww/pXMHr9d57Q798+8ytFy16blNmzNzX8INPv+N67j+14d2PF87bde1bf3g64or8DGvRIYz+0tm7nv30wJXvbrz82LH3bzkNui/k9AG3xCZNPve9BeM/GF8y+sGO38Aupz905bovztjycOcfxv7zrgNTj8MPAPm43XXHTit7YOy2ez/c+NBlz2/ejx8Lua2A0Zseuj3w6qd3+//+zS9dP/TOKThEeR+Pz96apgm9U7du+cG4RVuH7P4Em/OPHMro4394zpaPj2979NINS++95JFv4xDMLQN4fO4b+L0TT9n64dybBt+5OngDDs+0cflF7089MfjeOZfeVbdm3J5Bl5/HromMfufqs9r2DNx667m3j9y987arn0Rf5vJ3fPVW74WFBZ/UROZ/M/HafFyzpnD5h1+8/+WPjq47+8dL0s8/NedHWzGOuP/Z8ZsPnL/8hjUXT191c/GcITj08Buup+CxkmjHuvKv3XDnfas+mbQzgnXmMEbfs6XsK+VPJj4+f/+O716w49i72f0ao6de6LnkwN4Tn911jWfCjNer0U9WcvlvV45fOqerb/uihbWn7rj6FvwA2Hren3959evP1qixr57/zlkd9026AzHez677Ct3T073+C4jNEGCQBh3eaW9i16HzgdPYIASWswsJkF2/LwK2s+sz8DrgpcCvADcDtwO/AGR2Brvonp2viYU=
*/