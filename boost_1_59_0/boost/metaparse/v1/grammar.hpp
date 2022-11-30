#ifndef BOOST_METAPARSE_V1_GRAMMAR_HPP
#define BOOST_METAPARSE_V1_GRAMMAR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/repeated.hpp>
#include <boost/metaparse/v1/repeated1.hpp>
#include <boost/metaparse/v1/sequence.hpp>
#include <boost/metaparse/v1/one_of.hpp>
#include <boost/metaparse/v1/transform.hpp>
#include <boost/metaparse/v1/lit.hpp>
#include <boost/metaparse/v1/lit_c.hpp>
#include <boost/metaparse/v1/token.hpp>
#include <boost/metaparse/v1/keyword.hpp>
#include <boost/metaparse/v1/middle_of.hpp>
#include <boost/metaparse/v1/last_of.hpp>
#include <boost/metaparse/v1/always.hpp>
#include <boost/metaparse/v1/one_char_except_c.hpp>
#include <boost/metaparse/v1/foldr1.hpp>
#include <boost/metaparse/v1/foldl_start_with_parser.hpp>
#include <boost/metaparse/v1/alphanum.hpp>
#include <boost/metaparse/v1/build_parser.hpp>
#include <boost/metaparse/v1/entire_input.hpp>
#include <boost/metaparse/v1/string.hpp>
#include <boost/metaparse/v1/impl/front_inserter.hpp>

#include <boost/mpl/at.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/insert.hpp>

/*
 * The grammar
 *
 * rule_definition ::= name_token define_token expression
 * expression ::= seq_expression (or_token seq_expression)*
 * seq_expression ::= repeated_expression+
 * repeated_expression ::= name_expression (repeated_token | repeated1_token)*
 * name_expression ::= char_token | name_token | bracket_expression
 * bracket_expression ::= open_bracket_token expression close_bracket_token
 */

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace grammar_util
      {
        template <char Op, class FState>
        struct repeated_apply_impl
        {
          typedef repeated_apply_impl type;
        
          template <class G>
          struct apply :
            repeated<typename FState::template apply<G>::type>
          {};
        };

        template <class FState>
        struct repeated_apply_impl<'+', FState>
        {
          typedef repeated_apply_impl type;
        
          template <class G>
          struct apply :
            repeated1<typename FState::template apply<G>::type>
          {};
        };

        struct build_repeated
        {
          typedef build_repeated type;
        
          template <class FState, class T>
          struct apply : repeated_apply_impl<T::type::value, FState> {};
        };
        
        struct build_sequence
        {
          typedef build_sequence type;
        
          template <class FState, class FP>
          struct apply_impl
          {
            typedef apply_impl type;
        
            template <class G>
            struct apply :
              sequence<
                typename FState::template apply<G>::type,
                typename FP::template apply<G>::type
              >
            {};
          };
        
          template <class FState, class FP>
          struct apply : apply_impl<FState, FP> {};
        };
        
        struct build_selection
        {
          typedef build_selection type;
        
          template <class FState, class FP>
          struct apply_impl
          {
            typedef apply_impl type;
        
            template <class G>
            struct apply :
              one_of<
                typename FState::template apply<G>::type,
                typename FP::template apply<G>::type
              >
            {};
          };
        
          template <class FState, class FP>
          struct apply : apply_impl<FState, FP> {};
        };
        
        template <class G, class Name>
        struct get_parser
        {
          typedef
            typename boost::mpl::at<typename G::rules, Name>::type
              ::template apply<G>
            p;
        
          template <class Actions>
          struct impl : transform<typename p::type, typename Actions::type> {};
        
          typedef
            typename boost::mpl::eval_if<
              typename boost::mpl::has_key<typename G::actions, Name>::type,
              impl<boost::mpl::at<typename G::actions, Name> >,
              p
            >::type
            type;
        };
        
        struct build_name
        {
          typedef build_name type;
        
          template <class Name>
          struct apply_impl
          {
            typedef apply_impl type;
        
            template <class G>
            struct apply : get_parser<G, Name> {};
          };
        
          template <class Name>
          struct apply : apply_impl<Name> {};
        };
        
        struct build_char
        {
          typedef build_char type;
        
          template <class C>
          struct apply_impl
          {
            typedef apply_impl type;
        
            template <class G>
            struct apply : lit<C> {};
          };
        
          template <class C>
          struct apply : apply_impl<C> {};
        };
        
        typedef token<lit_c<'*'> > repeated_token;
        typedef token<lit_c<'+'> > repeated1_token;
        typedef token<lit_c<'|'> > or_token;
        typedef token<lit_c<'('> > open_bracket_token;
        typedef token<lit_c<')'> > close_bracket_token;
        typedef token<keyword<string<':',':','='> > > define_token;

        typedef
          middle_of<
            lit_c<'\''>,
            one_of<
              last_of<
                lit_c<'\\'>,
                one_of<
                  always<lit_c<'n'>, boost::mpl::char_<'\n'> >,
                  always<lit_c<'r'>, boost::mpl::char_<'\r'> >,
                  always<lit_c<'t'>, boost::mpl::char_<'\t'> >,
                  lit_c<'\\'>,
                  lit_c<'\''>
                >
              >,
              one_char_except_c<'\''>
            >,
            token<lit_c<'\''> >
          >
          char_token;
        
        typedef
          token<
            foldr1<
              one_of<alphanum, lit_c<'_'> >,
              string<>,
              impl::front_inserter
            >
          >
          name_token;
        
        struct expression;
        
        typedef
          middle_of<open_bracket_token, expression, close_bracket_token>
          bracket_expression;

        typedef
          one_of<
            transform<char_token, build_char>,
            transform<name_token, build_name>,
            bracket_expression
          >
          name_expression;

        typedef
          foldl_start_with_parser<
            one_of<repeated_token, repeated1_token>,
            name_expression,
            build_repeated
          >
          repeated_expression;
        
        typedef
          foldl_start_with_parser<
            repeated_expression,
            repeated_expression,
            build_sequence
          >
          seq_expression;
        
        struct expression :
          foldl_start_with_parser<
            last_of<or_token, seq_expression>,
            seq_expression,
            build_selection
          >
        {};
        
        typedef sequence<name_token, define_token, expression> rule_definition;

        typedef build_parser<entire_input<rule_definition> > parser_parser;
        
        template <class P>
        struct build_native_parser
        {
          typedef build_native_parser type;
        
          template <class G>
          struct apply
          {
            typedef P type;
          };
        };
        
        template <class S>
        struct build_parsed_parser
        {
          typedef typename parser_parser::apply<S>::type p;
          typedef typename boost::mpl::front<p>::type name;
          typedef typename boost::mpl::back<p>::type exp;
        
          struct the_parser
          {
            typedef the_parser type;
        
            template <class G>
            struct apply : exp::template apply<G> {};
          };
        
          typedef boost::mpl::pair<name, the_parser> type;
        };
        
        typedef build_parser<name_token> name_parser;
        
        template <class S>
        struct rebuild : name_parser::template apply<S> {};
        
        struct no_action;
        
        template <class G, class P, class F>
        struct add_rule;
        
        template <class G, class Name, class P>
        struct add_import;
        
        template <class Start, class Rules, class Actions>
        struct grammar_builder
        {
          typedef grammar_builder type;
          typedef Rules rules;
          typedef Actions actions;
        
          // Make it a parser
          template <class S, class Pos>
          struct apply :
            get_parser<
              grammar_builder,
              typename rebuild<Start>::type
            >::type::template apply<S, Pos>
          {};
        
          template <class Name, class P>
          struct import :
            add_import<grammar_builder, typename rebuild<Name>::type, P>
          {};
        
          template <class Def, class Action = no_action>
          struct rule :
            add_rule<grammar_builder, build_parsed_parser<Def>, Action>
          {};
        };
        
        template <class Start, class Rules, class Actions, class P>
        struct add_rule<grammar_builder<Start, Rules, Actions>, P, no_action> :
          grammar_builder<
            Start,
            typename boost::mpl::insert<Rules, typename P::type>::type,
            Actions
          >
        {};
        
        template <class Start, class Rules, class Actions, class P, class F>
        struct add_rule<grammar_builder<Start, Rules, Actions>, P, F> :
          grammar_builder<
            Start,
            typename boost::mpl::insert<Rules, typename P::type>::type,
            typename boost::mpl::insert<
              Actions,
              boost::mpl::pair<
                typename P::name,
                typename boost::mpl::lambda<F>::type
              >
            >
            ::type
          >
        {};
        
        template <class Start, class Rules, class Actions, class Name, class P>
        struct add_import<grammar_builder<Start, Rules, Actions>, Name, P> :
          grammar_builder<
            Start,
            typename boost::mpl::insert<
              Rules,
              boost::mpl::pair<Name, build_native_parser<P> >
            >::type,
            Actions
          >
        {};
      }

      template <class Start = string<'S'> >
      struct grammar :
        grammar_util::grammar_builder<
          Start,
          boost::mpl::map<>,
          boost::mpl::map<>
        >
      {};
    }
  }
}

#endif

/* grammar.hpp
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
*/