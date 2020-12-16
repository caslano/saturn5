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
M+TM9ADdiSlxUyuNYWAkK1MT1jet95V0gTrIHtKeT7li503Zr5ffYiVfptstygXSnJELlkOcjlUp7+7eI9Bh8pUOwNf6+0ddVm/tDoAc8fnjOr9y5d1y3bGYWx+LSYL6KDmChZ/JRJRcGJlflvBgOoi4fLeHrLt/l2Jrl4eQfRNzpavxP/auBDyKIgtXBxREhIDcyCkqiGIuEBCREBIIhASTACqRsTPTkwyZi+mZEEAWFERFRHFVFFEOXQ+8bwTvW/FWFsVbUbwVWC+89q+umlT3zCTT3TPsfrsf/RGmj3qvql69u6qrBbygf4rzxSZQ0hFMcQrZXi3CAlv7ZjodIsVZbVEPACLXIgj+LEL4resnp9tqT5zW5cZpXW5oT6h2ti4G/5VNJZNWYXONvLNeCamegFkn2RnGPyupCAbQMDRrRH2upTrq3bZ9ouZf2M2LXydjYyEka6SKP2e4wVLHVNPv+Gjl7b3ymZNuNzopwrS9jmClitRfUMgyEQ2kZZGbpSqsbixvZJiA1+M066hqIBbeO4sqgBpL5c1H1Vp5Czu3aj/iba0BSnWQj0h0EPioVCcYouF9B5vcsjcV5Fkx30ISOaV4tTTU2rJVZ9ASbQN+t/afQ5XNfjdQwPgCNjbmjv9safK0Rc7+3+TI0Cs7mwHxfqV5b2wNn0mlYXX0zO/K0wi0/1LUjVVYSlM3QtnieZdiI3ec1Tf55jkpbjtiowqbi9wFLeSgxzotkr/wnW6Eqb+anPwLQlH9k1ryzxnwBbX/LOxNFYWx8s3CKIyV77MxGMc8C7X4VPpnpS8cQvV5fLZ3SLU0KrZqyEt1ikQg0CXlU50RSYJUmIdUv1RooyLhYdv/gGFu0re77eyY0Mhytt0SS17Ifq8hdX1q5iWhvL5pfr3RwrbL+makMODBOSGPVUVmWfXVySEbJjIr6fd1040wDV9XzjXBmSnms2xUYXP+Mjp+noDFAVdU1fp4p/haRPJXHiz1wLxHEIXw11vvMx+VFF9/EfBCP9ieizKBUihD2xNU9moRnG173sTEFHZavCMrNdj8gCTjPCvTDlEIl9mN5qMActh0TotBWFn14PTJTvqfjXnXFL79ZVEtaE20tLY7CiNbgdG+7sl/7E1FZ6XntSxDfJyWd7CaRUlHKj0vT1qshTJRiq9Y5qW4f6OAFzya4maNJlCmYQ7aXi1iEKwtA6Dfa0XoraawwCcnxcXoAl7YqxQXozeLUpiKFBejW61FWCRri9H5GAXcFiYdKIiVifAogNN0GMIAnJYaxT7ZC/3t9aI75qvSw/k8qvlO6QAt9U0P5wyb9lqNcDY76Ky23j92YvbjS9URt1sJaT+mv4fUCGMlt13txz8LSTpWvmFEbrbZ2R8GMScQMut8MQB1dsis79UIYFc/pr60Ue/2puXV/mZRUs2VovG1V4su4W7Jj+QjVOtx21gylpvuHFdShKnP19uowmZGi5E2pDityaOFr24xgGDIY3qj8ShECnl8E/t4piazZgJVu6NvvYbUv0VhIgJMy/d9rdRASZHupTU5phPUtkmZdIOwtCNMfWtHG1XY3N1JE24rHypgAL6I2bUDvHzQbIKelw/Y2VXdzMdUUuQmG1XY3FgxSghrit38vAYrXxcyvdKTAcBuKKZfCWUgNe4cG4tqk67TtIowhRcT7Sq8FPdhSrolUtoRpr7Hko0qxKyWXUKl8ulXu45HfLdyUutEUoRpm9mzVkca0rEpbtCY1zfNJjwpQkqY1LSNjSro+Ng24TVOG6sespr0IdK21bmNKhqpZ+1rO4wOSkPQxl5MvJW2GUrAi26mac+2hCgF6dK0jZu1WnQbrNkbIusjlJv006fpRrg=
*/