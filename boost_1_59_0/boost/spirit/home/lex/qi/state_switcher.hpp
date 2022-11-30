//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c)      2010 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_STATE_SWITCHER_SEP_23_2007_0714PM)
#define BOOST_SPIRIT_LEX_STATE_SWITCHER_SEP_23_2007_0714PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/qi/detail/attributes.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/string_traits.hpp>
#include <boost/spirit/home/support/has_semantic_action.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/spirit/home/qi/skip_over.hpp>
#include <boost/spirit/home/qi/domain.hpp>
#include <boost/spirit/home/qi/parser.hpp>
#include <boost/spirit/home/qi/meta_compiler.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////

    // enables set_state(s)
    template <typename A0>
    struct use_terminal<qi::domain
      , terminal_ex<tag::set_state, fusion::vector1<A0> >
    > : traits::is_string<A0> {};

    // enables *lazy* set_state(s)
    template <>
    struct use_lazy_terminal<
        qi::domain, tag::set_state, 1
    > : mpl::true_ {};

    // enables in_state(s)[p]
    template <typename A0>
    struct use_directive<qi::domain
      , terminal_ex<tag::in_state, fusion::vector1<A0> >
    > : traits::is_string<A0> {};

    // enables *lazy* in_state(s)[p]
    template <>
    struct use_lazy_directive<
        qi::domain, tag::in_state, 1
    > : mpl::true_ {};

}}

namespace boost { namespace spirit { namespace qi
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::set_state;
    using spirit::in_state;
#endif
    using spirit::set_state_type;
    using spirit::in_state_type;

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename Iterator>
        inline std::size_t
        set_lexer_state(Iterator& it, std::size_t state)
        {
            return it.set_state(state);
        }

        template <typename Iterator, typename Char>
        inline std::size_t
        set_lexer_state(Iterator& it, Char const* statename)
        {
            std::size_t state = it.map_state(statename);

            //  If the following assertion fires you probably used the
            //  set_state(...) or in_state(...)[...] lexer state switcher with
            //  a lexer state name unknown to the lexer (no token definitions
            //  have been associated with this lexer state).
            BOOST_ASSERT(std::size_t(~0) != state);
            return it.set_state(state);
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    //  Parser switching the state of the underlying lexer component.
    //  This parser gets used for the set_state(...) construct.
    ///////////////////////////////////////////////////////////////////////////
    template <typename State>
    struct state_switcher
      : primitive_parser<state_switcher<State> >
    {
        typedef typename 
            remove_const<typename traits::char_type_of<State>::type>::type 
        char_type;
        typedef std::basic_string<char_type> string_type;

        template <typename Context, typename Iterator>
        struct attribute
        {
            typedef unused_type type;
        };

        state_switcher(char_type const* state)
          : state(state) {}

        template <typename Iterator, typename Context
          , typename Skipper, typename Attribute>
        bool parse(Iterator& first, Iterator const& last
          , Context& /*context*/, Skipper const& skipper
          , Attribute& /*attr*/) const
        {
            qi::skip_over(first, last, skipper);   // always do a pre-skip

            // just switch the state and return success
            detail::set_lexer_state(first, state.c_str());
            return true;
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            return info("set_state");
        }

        string_type state;
    };

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename Iterator>
        struct reset_state_on_exit
        {
            template <typename State>
            reset_state_on_exit(Iterator& it_, State state_)
              : it(it_)
              , state(set_lexer_state(it_, traits::get_c_string(state_))) 
            {}

            ~reset_state_on_exit()
            {
                // reset the state of the underlying lexer instance
                set_lexer_state(it, state);
            }

            Iterator& it;
            std::size_t state;

            // silence MSVC warning C4512: assignment operator could not be generated
            BOOST_DELETED_FUNCTION(reset_state_on_exit& operator= (reset_state_on_exit const&))
        };
    }

    ///////////////////////////////////////////////////////////////////////////
    // Parser, which switches the state of the underlying lexer component
    // for the execution of the embedded sub-parser, switching the state back
    // afterwards. This parser gets used for the in_state(...)[p] construct.
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename State>
    struct state_switcher_context 
      : unary_parser<state_switcher_context<Subject, State> >
    {
        typedef Subject subject_type;
        typedef typename traits::char_type_of<State>::type char_type;
        typedef typename remove_const<char_type>::type non_const_char_type;

        template <typename Context, typename Iterator>
        struct attribute
        {
            typedef typename
                traits::attribute_of<subject_type, Context, Iterator>::type
            type;
        };

        state_switcher_context(Subject const& subject
              , typename add_reference<State>::type state)
          : subject(subject), state(state) {}

        // The following conversion constructors are needed to make the 
        // in_state_switcher template usable
        template <typename String>
        state_switcher_context(
                state_switcher_context<Subject, String> const& rhs)
          : subject(rhs.subject), state(traits::get_c_string(rhs.state)) {}

        template <typename Iterator, typename Context
          , typename Skipper, typename Attribute>
        bool parse(Iterator& first, Iterator const& last
          , Context& context, Skipper const& skipper
          , Attribute& attr) const
        {
            qi::skip_over(first, last, skipper);   // always do a pre-skip

            // the state has to be reset at exit in any case
            detail::reset_state_on_exit<Iterator> guard(first, state);
            return subject.parse(first, last, context, skipper, attr);
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("in_state", subject.what(context));
        }

        Subject subject;
        State state;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(state_switcher_context& operator= (state_switcher_context const&))
    };

    ///////////////////////////////////////////////////////////////////////////
    // Parser generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Modifiers, typename State>
    struct make_primitive<terminal_ex<tag::set_state, fusion::vector1<State> >
      , Modifiers, typename enable_if<traits::is_string<State> >::type>
    {
        typedef typename add_const<State>::type const_string;
        typedef state_switcher<const_string> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(traits::get_c_string(fusion::at_c<0>(term.args)));
        }
    };

    template <typename State, typename Subject, typename Modifiers>
    struct make_directive<terminal_ex<tag::in_state, fusion::vector1<State> >
      , Subject, Modifiers>
    {
        typedef typename add_const<State>::type const_string;
        typedef state_switcher_context<Subject, const_string> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, Subject const& subject
          , unused_type) const
        {
            return result_type(subject, fusion::at_c<0>(term.args));
        }
    };
}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename State>
    struct has_semantic_action<qi::state_switcher_context<Subject, State> >
      : unary_has_semantic_action<Subject> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename State, typename Attribute
        , typename Context, typename Iterator>
    struct handles_container<qi::state_switcher_context<Subject, State>
          , Attribute, Context, Iterator>
      : unary_handles_container<Subject, Attribute, Context, Iterator> {}; 
}}}

#endif

/* state_switcher.hpp
+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
*/