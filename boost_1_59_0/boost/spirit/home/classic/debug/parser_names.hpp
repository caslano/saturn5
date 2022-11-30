/*=============================================================================
    Copyright (c) 2001-2003 Joel de Guzman
    Copyright (c) 2002-2003 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_PARSER_NAMES_HPP)
#define BOOST_SPIRIT_PARSER_NAMES_HPP

#if defined(BOOST_SPIRIT_DEBUG)

//////////////////////////////////
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
//
//  Declaration of helper functions, which return the name of a concrete
//  parser instance. The functions are specialized on the parser types. The
//  functions declared in this file are for the predefined parser types from
//  the Spirit core library only, so additional functions might be provided as
//  needed.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//  from actions.hpp
    template <typename ParserT, typename ActionT>
    std::string
    parser_name(action<ParserT, ActionT> const& p);

///////////////////////////////////////////////////////////////////////////////
//  from directives.hpp
    template <typename ParserT>
    std::string
    parser_name(contiguous<ParserT> const& p);

    template <typename ParserT>
    std::string
    parser_name(inhibit_case<ParserT> const& p);

    template <typename A, typename B>
    std::string
    parser_name(longest_alternative<A, B> const& p);

    template <typename A, typename B>
    std::string
    parser_name(shortest_alternative<A, B> const& p);

///////////////////////////////////////////////////////////////////////////////
//  from grammar.hpp
    template <typename DerivedT, typename ContextT>
    std::string
    parser_name(grammar<DerivedT, ContextT> const& p);

///////////////////////////////////////////////////////////////////////////////
//  from numerics.hpp
    template <typename T, int Radix, unsigned MinDigits, int MaxDigits>
    std::string
    parser_name(uint_parser<T, Radix, MinDigits, MaxDigits> const& p);

    template <typename T, int Radix, unsigned MinDigits, int MaxDigits>
    std::string
    parser_name(int_parser<T, Radix, MinDigits, MaxDigits> const& p);

    template <typename T, typename RealPoliciesT>
    std::string
    parser_name(real_parser<T, RealPoliciesT> const& p);

///////////////////////////////////////////////////////////////////////////////
//  from operators.hpp
    template <typename A, typename B>
    std::string
    parser_name(sequence<A, B> const& p);

    template <typename A, typename B>
    std::string
    parser_name(sequential_or<A, B> const& p);

    template <typename A, typename B>
    std::string
    parser_name(alternative<A, B> const& p);

    template <typename A, typename B>
    std::string
    parser_name(intersection<A, B> const& p);

    template <typename A, typename B>
    std::string
    parser_name(difference<A, B> const& p);

    template <typename A, typename B>
    std::string
    parser_name(exclusive_or<A, B> const& p);

    template <typename S>
    std::string
    parser_name(optional<S> const& p);

    template <typename S>
    std::string
    parser_name(kleene_star<S> const& p);

    template <typename S>
    std::string
    parser_name(positive<S> const& p);

///////////////////////////////////////////////////////////////////////////////
//  from parser.hpp
    template <typename DerivedT>
    std::string
    parser_name(parser<DerivedT> const& p);

///////////////////////////////////////////////////////////////////////////////
//  from primitives.hpp
    template <typename DerivedT>
    std::string
    parser_name(char_parser<DerivedT> const &p);

    template <typename CharT>
    std::string
    parser_name(chlit<CharT> const &p);

    template <typename CharT>
    std::string
    parser_name(range<CharT> const &p);

    template <typename IteratorT>
    std::string
    parser_name(chseq<IteratorT> const &p);

    template <typename IteratorT>
    std::string
    parser_name(strlit<IteratorT> const &p);

    std::string
    parser_name(nothing_parser const &p);

    std::string
    parser_name(epsilon_parser const &p);

    std::string
    parser_name(anychar_parser const &p);

    std::string
    parser_name(alnum_parser const &p);

    std::string
    parser_name(alpha_parser const &p);

    std::string
    parser_name(cntrl_parser const &p);

    std::string
    parser_name(digit_parser const &p);

    std::string
    parser_name(graph_parser const &p);

    std::string
    parser_name(lower_parser const &p);

    std::string
    parser_name(print_parser const &p);

    std::string
    parser_name(punct_parser const &p);

    std::string
    parser_name(blank_parser const &p);

    std::string
    parser_name(space_parser const &p);

    std::string
    parser_name(upper_parser const &p);

    std::string
    parser_name(xdigit_parser const &p);

    std::string
    parser_name(eol_parser const &p);

    std::string
    parser_name(end_parser const &p);

///////////////////////////////////////////////////////////////////////////////
//  from rule.hpp
    template<typename T0, typename T1, typename T2>
    std::string
    parser_name(rule<T0, T1, T2> const& p);

///////////////////////////////////////////////////////////////////////////////
//  from subrule.hpp
    template <typename FirstT, typename RestT>
    std::string
    parser_name(subrule_list<FirstT, RestT> const &p);

    template <int ID, typename DefT, typename ContextT>
    std::string
    parser_name(subrule_parser<ID, DefT, ContextT> const &p);

    template <int ID, typename ContextT>
    std::string
    parser_name(subrule<ID, ContextT> const &p);

///////////////////////////////////////////////////////////////////////////////
//  from chset.hpp

///////////////////////////////////////////////////////////////////////////////
//
//  Decide, if a node is to be traced or not
//
///////////////////////////////////////////////////////////////////////////////
    template<
        typename DerivedT, typename EmbedT, 
        typename T0, typename T1, typename T2
    >
    bool
    trace_parser(impl::rule_base<DerivedT, EmbedT, T0, T1, T2> 
        const& p);

    template <typename DerivedT, typename ContextT>
    bool
    trace_parser(grammar<DerivedT, ContextT> const& p);

    template <int ID, typename ContextT>
    bool
    trace_parser(subrule<ID, ContextT> const& p);

    template <typename ParserT, typename ActorTupleT>
    struct init_closure_parser;

    template <typename ParserT, typename ActorTupleT>
    bool
    trace_parser(init_closure_parser<ParserT, ActorTupleT> const& p);

///////////////////////////////////////////////////////////////////////////////
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

//////////////////////////////////
#include <boost/spirit/home/classic/debug/impl/parser_names.ipp>

#endif // defined(BOOST_SPIRIT_DEBUG)

#endif // !defined(BOOST_SPIRIT_PARSER_NAMES_HPP)

/* parser_names.hpp
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
*/