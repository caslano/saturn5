//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SPIRIT_LEX_LEXER_SUPPORT_FUNCTIONS_HPP
#define BOOST_SPIRIT_LEX_LEXER_SUPPORT_FUNCTIONS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/detail/scoped_enum_emulation.hpp>
#include <boost/spirit/home/lex/lexer/pass_flags.hpp>
#include <boost/spirit/home/lex/lexer/support_functions_expression.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/as_actor.hpp>
#include <boost/phoenix/core/value.hpp> // includes as_actor specialization

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace lex
{
    ///////////////////////////////////////////////////////////////////////////
    // The function object less_type is used by the implementation of the 
    // support function lex::less(). Its functionality is equivalent to flex' 
    // function yyless(): it returns an iterator positioned to the nth input 
    // character beyond the current start iterator (i.e. by assigning the 
    // return value to the placeholder '_end' it is possible to return all but
    // the first n characters of the current token back to the input stream. 
    //
    //  This Phoenix actor is invoked whenever the function lex::less(n) is 
    //  used inside a lexer semantic action:
    //
    //      lex::token_def<> identifier = "[a-zA-Z_][a-zA-Z0-9_]*";
    //      this->self = identifier [ _end = lex::less(4) ];
    //
    //  The example shows how to limit the length of the matched identifier to 
    //  four characters.
    //
    //  Note: the function lex::less() has no effect if used on it's own, you 
    //        need to use the returned result in order to make use of its 
    //        functionality.
    template <typename Actor>
    struct less_type
    {
        typedef mpl::true_ no_nullary;

        template <typename Env>
        struct result
        {
            typedef typename remove_reference< 
                typename remove_const<
                    typename mpl::at_c<typename Env::args_type, 4>::type
                >::type
            >::type context_type;
            typedef typename context_type::base_iterator_type type;
        };

        template <typename Env>
        typename result<Env>::type 
        eval(Env const& env) const
        {
            typename result<Env>::type it;
            return fusion::at_c<4>(env.args()).less(it, actor_());
        }

        less_type(Actor const& actor)
          : actor_(actor) {}

        Actor actor_;
    };

    //  The function lex::less() is used to create a Phoenix actor allowing to
    //  implement functionality similar to flex' function yyless().
    template <typename T>
    inline typename expression::less<
        typename phoenix::as_actor<T>::type
    >::type const
    less(T const& v)
    {
        return expression::less<T>::make(phoenix::as_actor<T>::convert(v));
    }

    ///////////////////////////////////////////////////////////////////////////
    // The function object more_type is used by the implementation of the  
    // support function lex::more(). Its functionality is equivalent to flex' 
    // function yymore(): it tells the lexer that the next time it matches a 
    // rule, the corresponding token should be appended onto the current token 
    // value rather than replacing it.
    //
    //  This Phoenix actor is invoked whenever the function lex::more(n) is 
    //  used inside a lexer semantic action:
    //
    //      lex::token_def<> identifier = "[a-zA-Z_][a-zA-Z0-9_]*";
    //      this->self = identifier [ lex::more() ];
    //
    //  The example shows how prefix the next matched token with the matched
    //  identifier.
    struct more_type
    {
        typedef mpl::true_ no_nullary;

        template <typename Env>
        struct result
        {
            typedef void type;
        };

        template <typename Env>
        void eval(Env const& env) const
        {
            fusion::at_c<4>(env.args()).more();
        }
    };

    //  The function lex::more() is used to create a Phoenix actor allowing to
    //  implement functionality similar to flex' function yymore(). 
    //inline expression::more<mpl::void_>::type const
    inline phoenix::actor<more_type> more()
    {
        return phoenix::actor<more_type>();
    }

    ///////////////////////////////////////////////////////////////////////////
    // The function object lookahead_type is used by the implementation of the  
    // support function lex::lookahead(). Its functionality is needed to 
    // emulate the flex' lookahead operator a/b. Use lex::lookahead() inside
    // of lexer semantic actions to test whether the argument to this function
    // matches the current look ahead input. lex::lookahead() can be used with
    // either a token id or a token_def instance as its argument. It returns
    // a bool indicating whether the look ahead has been matched.
    template <typename IdActor, typename StateActor>
    struct lookahead_type
    {
        typedef mpl::true_ no_nullary;

        template <typename Env>
        struct result
        {
            typedef bool type;
        };

        template <typename Env>
        bool eval(Env const& env) const
        {
            return fusion::at_c<4>(env.args()).
                lookahead(id_actor_(), state_actor_());
        }

        lookahead_type(IdActor const& id_actor, StateActor const& state_actor)
          : id_actor_(id_actor), state_actor_(state_actor) {}

        IdActor id_actor_;
        StateActor state_actor_;
    };

    //  The function lex::lookahead() is used to create a Phoenix actor 
    //  allowing to implement functionality similar to flex' lookahead operator
    //  a/b.
    template <typename T>
    inline typename expression::lookahead<
        typename phoenix::as_actor<T>::type
      , typename phoenix::as_actor<std::size_t>::type
    >::type const
    lookahead(T const& id)
    {
        typedef typename phoenix::as_actor<T>::type id_actor_type;
        typedef typename phoenix::as_actor<std::size_t>::type state_actor_type;

        return expression::lookahead<id_actor_type, state_actor_type>::make(
            phoenix::as_actor<T>::convert(id),
            phoenix::as_actor<std::size_t>::convert(std::size_t(~0)));
    }

    template <typename Attribute, typename Char, typename Idtype>
    inline typename expression::lookahead<
        typename phoenix::as_actor<Idtype>::type
      , typename phoenix::as_actor<std::size_t>::type
    >::type const
    lookahead(token_def<Attribute, Char, Idtype> const& tok)
    {
        typedef typename phoenix::as_actor<Idtype>::type id_actor_type;
        typedef typename phoenix::as_actor<std::size_t>::type state_actor_type;

        std::size_t state = tok.state();

        // The following assertion fires if you pass a token_def instance to 
        // lex::lookahead without first associating this instance with the 
        // lexer.
        BOOST_ASSERT(std::size_t(~0) != state && 
            "token_def instance not associated with lexer yet");

        return expression::lookahead<id_actor_type, state_actor_type>::make(
            phoenix::as_actor<Idtype>::convert(tok.id()),
            phoenix::as_actor<std::size_t>::convert(state));
    }

    ///////////////////////////////////////////////////////////////////////////
    inline BOOST_SCOPED_ENUM(pass_flags) ignore()
    {
        return pass_flags::pass_ignore;
    }

}}}

#endif

/* support_functions.hpp
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
*/