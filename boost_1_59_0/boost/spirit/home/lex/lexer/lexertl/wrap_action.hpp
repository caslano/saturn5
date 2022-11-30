/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2001-2011 Hartmut Kaiser
    http://spirit.sourceforge.net/

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_WRAP_ACTION_APR_19_2008_0103PM)
#define BOOST_SPIRIT_WRAP_ACTION_APR_19_2008_0103PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/attributes.hpp>
#include <boost/spirit/home/lex/lexer/pass_flags.hpp>
#include <boost/phoenix/core/argument.hpp>
#include <boost/phoenix/bind.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace lex { namespace lexertl 
{ 
    namespace detail
    {
        template <typename FunctionType, typename Iterator, typename Context
          , typename IdType>
        struct wrap_action
        {
            // plain functions with 5 arguments, function objects (including 
            // phoenix actors) are not touched at all
            template <typename F>
            static FunctionType call(F const& f)
            {
                return f;
            }

            // semantic actions with 4 arguments
            template <typename F>
            static void arg4_action(F* f, Iterator& start, Iterator& end
              , BOOST_SCOPED_ENUM(pass_flags)& pass, IdType& id
              , Context const&)
            {
                f(start, end, pass, id);
            }

            template <typename A0, typename A1, typename A2, typename A3>
            static FunctionType call(void (*f)(A0, A1, A2, A3))
            {
                void (*pf)(void(*)(A0, A1, A2, A3)
                  , Iterator&, Iterator&, BOOST_SCOPED_ENUM(pass_flags)&
                  , IdType&, Context const&) = &wrap_action::arg4_action;

                using phoenix::arg_names::_1;
                using phoenix::arg_names::_2;
                using phoenix::arg_names::_3;
                using phoenix::arg_names::_4;
                using phoenix::arg_names::_5;
                return phoenix::bind(pf, f, _1, _2, _3, _4, _5);
            }

            // semantic actions with 3 arguments
            template <typename F>
            static void arg3_action(F* f, Iterator& start, Iterator& end
              , BOOST_SCOPED_ENUM(pass_flags)& pass, IdType
              , Context const&)
            {
                f(start, end, pass);
            }

            template <typename A0, typename A1, typename A2>
            static FunctionType call(void (*f)(A0, A1, A2))
            {
                void (*pf)(void(*)(A0, A1, A2), Iterator&, Iterator&
                  , BOOST_SCOPED_ENUM(pass_flags)&, IdType
                  , Context const&) = &wrap_action::arg3_action;

                using phoenix::arg_names::_1;
                using phoenix::arg_names::_2;
                using phoenix::arg_names::_3;
                using phoenix::arg_names::_4;
                using phoenix::arg_names::_5;
                return phoenix::bind(pf, f, _1, _2, _3, _4, _5);
            }

            // semantic actions with 2 arguments
            template <typename F>
            static void arg2_action(F* f, Iterator& start, Iterator& end
              , BOOST_SCOPED_ENUM(pass_flags)&, IdType, Context const&)
            {
                f (start, end);
            }

            template <typename A0, typename A1>
            static FunctionType call(void (*f)(A0, A1))
            {
                void (*pf)(void(*)(A0, A1), Iterator&, Iterator&
                  , BOOST_SCOPED_ENUM(pass_flags)&
                  , IdType, Context const&) = &wrap_action::arg2_action;

                using phoenix::arg_names::_1;
                using phoenix::arg_names::_2;
                using phoenix::arg_names::_3;
                using phoenix::arg_names::_4;
                using phoenix::arg_names::_5;
                return phoenix::bind(pf, f, _1, _2, _3, _4, _5);
            }

            // we assume that either both iterators are to be passed to the 
            // semantic action or none iterator at all (i.e. it's not possible 
            // to have a lexer semantic action function taking one arguments).

            // semantic actions with 0 argument
            template <typename F>
            static void arg0_action(F* f, Iterator&, Iterator&
              , BOOST_SCOPED_ENUM(pass_flags)&, IdType, Context const&)
            {
                f();
            }

            static FunctionType call(void (*f)())
            {
                void (*pf)(void(*)(), Iterator&, Iterator&
                  , BOOST_SCOPED_ENUM(pass_flags)&
                  , IdType, Context const&) = &arg0_action;

                using phoenix::arg_names::_1;
                using phoenix::arg_names::_2;
                using phoenix::arg_names::_3;
                using phoenix::arg_names::_4;
                using phoenix::arg_names::_5;
                return phoenix::bind(pf, f, _1, _2, _3, _4, _5);
            }
        };

        // specialization allowing to skip wrapping for lexer types not 
        // supporting semantic actions
        template <typename Iterator, typename Context, typename Idtype>
        struct wrap_action<unused_type, Iterator, Context, Idtype>
        {
            // plain function objects are not touched at all
            template <typename F>
            static F const& call(F const& f)
            {
                return f;
            }
        };
    }

}}}}

#endif

/* wrap_action.hpp
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
*/