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