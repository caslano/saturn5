//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c) 2001-2011 Joel de Guzman
//  Copyright (c)      2010 Bryce Lelbach
//  Copyright (c)      2011 Thomas Heller
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_ARGUMENT_JUNE_07_2009_1106AM)
#define BOOST_SPIRIT_LEX_ARGUMENT_JUNE_07_2009_1106AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/string_traits.hpp>
#include <boost/spirit/home/lex/argument_phoenix.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/argument.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace lex
{
    ///////////////////////////////////////////////////////////////////////////
    //  The state_getter is a Phoenix actor used to access the name of the 
    //  current lexer state by calling get_state_name() on the context (which 
    //  is the 5th parameter to any lexer semantic actions).
    //
    //  This Phoenix actor is invoked whenever the placeholder '_state' is used
    //  as a rvalue inside a lexer semantic action:
    //
    //      lex::token_def<> identifier = "[a-zA-Z_][a-zA-Z0-9_]*";
    //      this->self = identifier [ std::cout << _state ];
    //
    //  The example shows how to print the lexer state after matching a token
    //  'identifier'.
    struct state_getter
    {
        typedef mpl::true_ no_nullary;

        template <typename Env>
        struct result
        {
            typedef
                typename remove_reference<
                   typename remove_const<
                        typename mpl::at_c<typename Env::args_type, 4>::type
                    >::type
                >::type
            context_type;

            typedef typename context_type::state_name_type type;
        };

        template <typename Env>
        typename result<Env>::type
        eval(Env const& env) const
        {
            return fusion::at_c<4>(env.args()).get_state_name();
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //  The state_setter is a Phoenix actor used to change the name of the 
    //  current lexer state by calling set_state_name() on the context (which 
    //  is the 5th parameter to any lexer semantic actions).
    //
    //  This Phoenix actor is invoked whenever the placeholder '_state' is used
    //  as a lvalue inside a lexer semantic action:
    //
    //      lex::token_def<> identifier = "[a-zA-Z_][a-zA-Z0-9_]*";
    //      this->self = identifier [ _state = "SOME_LEXER_STATE" ];
    //
    //  The example shows how to change the lexer state after matching a token
    //  'identifier'.
    template <typename Actor>
    struct state_setter
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
            fusion::at_c<4>(env.args()).set_state_name(
                traits::get_c_string(actor_.eval(env)));
        }

        state_setter(Actor const& actor)
          : actor_(actor) {}

        Actor actor_;
    };

    ///////////////////////////////////////////////////////////////////////////
    //  The value_getter is used to create the _val placeholder, which is a 
    //  Phoenix actor used to access the value of the current token.
    //
    //  This Phoenix actor is invoked whenever the placeholder '_val' is used
    //  as a rvalue inside a lexer semantic action:
    //
    //      lex::token_def<> identifier = "[a-zA-Z_][a-zA-Z0-9_]*";
    //      this->self = identifier [ std::cout << _val ];
    //
    //  The example shows how to use _val to print the identifier name (which
    //  is the initial token value).
    struct value_getter
    {
        typedef mpl::true_ no_nullary;

        template <typename Env>
        struct result
        {
            typedef
                typename remove_reference<
                   typename remove_const<
                        typename mpl::at_c<typename Env::args_type, 4>::type
                    >::type
                >::type
            context_type;

            typedef typename context_type::get_value_type type;
        };

        template <typename Env>
        typename result<Env>::type 
        eval(Env const& env) const
        {
            return fusion::at_c<4>(env.args()).get_value();
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //  The value_setter is a Phoenix actor used to change the name of the 
    //  current lexer state by calling set_state_name() on the context (which 
    //  is the 5th parameter to any lexer semantic actions).
    //
    //  This Phoenix actor is invoked whenever the placeholder '_val' is used
    //  as a lvalue inside a lexer semantic action:
    //
    //      lex::token_def<> identifier = "[a-zA-Z_][a-zA-Z0-9_]*";
    //      this->self = identifier [ _val = "identifier" ];
    //
    //  The example shows how to change the token value after matching a token
    //  'identifier'.
    template <typename Actor>
    struct value_setter
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
            fusion::at_c<4>(env.args()).set_value(actor_.eval(env));
        }

        value_setter(Actor const& actor)
          : actor_(actor) {}

        Actor actor_;
    };

    ///////////////////////////////////////////////////////////////////////////
    //  The eoi_getter is used to create the _eoi placeholder, which is a 
    //  Phoenix actor used to access the end of input iterator pointing to the 
    //  end of the underlying input sequence.
    //
    //  This actor is invoked whenever the placeholder '_eoi' is used in a
    //  lexer semantic action:
    //
    //      lex::token_def<> identifier = "[a-zA-Z_][a-zA-Z0-9_]*";
    //      this->self = identifier 
    //          [ std::cout << construct_<std::string>(_end, _eoi) ];
    //
    //  The example shows how to use _eoi to print all remaining input after
    //  matching a token 'identifier'.
    struct eoi_getter
    {
        typedef mpl::true_ no_nullary;

        template <typename Env>
        struct result
        {
            typedef
                typename remove_reference<
                   typename remove_const<
                        typename mpl::at_c<typename Env::args_type, 4>::type
                    >::type
                >::type
            context_type;

            typedef typename context_type::base_iterator_type const& type;
        };

        template <typename Env>
        typename result<Env>::type 
        eval(Env const& env) const
        {
            return fusion::at_c<4>(env.args()).get_eoi();
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    // '_start' and '_end' may be used to access the start and the end of 
    // the matched sequence of the current token
    typedef phoenix::arg_names::_1_type _start_type;
    typedef phoenix::arg_names::_2_type _end_type;
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    _start_type const _start = _start_type();
    _end_type const _end = _end_type();
#endif

    // We are reusing the placeholder '_pass' to access and change the pass
    // status of the current match (see support/argument.hpp for its 
    // definition).
    // typedef phoenix::arg_names::_3_type _pass_type;
    using boost::spirit::_pass_type;
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using boost::spirit::_pass;
#endif

    // '_tokenid' may be used to access and change the tokenid of the current 
    // token
    typedef phoenix::arg_names::_4_type _tokenid_type;
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    _tokenid_type const _tokenid = _tokenid_type();
#endif

    typedef phoenix::actor<value_context> _val_type;
    typedef phoenix::actor<state_context> _state_type;
    typedef phoenix::actor<eoi_getter> _eoi_type;
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    // '_val' may be used to access and change the token value of the current
    // token
    _val_type const _val = _val_type();
    // _state may be used to access and change the name of the current lexer 
    // state
    _state_type const _state = _state_type();
    // '_eoi' may be used to access the end of input iterator of the input 
    // stream used by the lexer to match tokens from
    _eoi_type const _eoi = _eoi_type();
#endif
}}}


#undef SPIRIT_DECLARE_ARG
#endif


/* argument.hpp
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
*/