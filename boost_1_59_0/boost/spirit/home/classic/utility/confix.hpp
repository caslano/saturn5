/*=============================================================================
    Copyright (c) 2002-2003 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_CONFIX_HPP
#define BOOST_SPIRIT_CONFIX_HPP

///////////////////////////////////////////////////////////////////////////////
#include <boost/config.hpp>
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/meta/as_parser.hpp>
#include <boost/spirit/home/classic/core/composite/operators.hpp>

#include <boost/spirit/home/classic/utility/confix_fwd.hpp>
#include <boost/spirit/home/classic/utility/impl/confix.ipp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
//
//  confix_parser class
//
//      Parses a sequence of 3 sub-matches. This class may
//      be used to parse structures, where the opening part is possibly
//      contained in the expression part and the whole sequence is only
//      parsed after seeing the closing part matching the first opening
//      subsequence. Example: C-comments:
//
//      /* This is a C-comment */
//
///////////////////////////////////////////////////////////////////////////////

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

template<typename NestedT = non_nested, typename LexemeT = non_lexeme>
struct confix_parser_gen;

template <
    typename OpenT, typename ExprT, typename CloseT, typename CategoryT,
    typename NestedT, typename LexemeT
>
struct confix_parser :
    public parser<
        confix_parser<OpenT, ExprT, CloseT, CategoryT, NestedT, LexemeT>
    >
{
    typedef
        confix_parser<OpenT, ExprT, CloseT, CategoryT, NestedT, LexemeT>
        self_t;

    confix_parser(OpenT const &open_, ExprT const &expr_, CloseT const &close_)
    : open(open_), expr(expr_), close(close_)
    {}

    template <typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
    parse(ScannerT const& scan) const
    {
        return impl::confix_parser_type<CategoryT>::
            parse(NestedT(), LexemeT(), *this, scan, open, expr, close);
    }

private:

    typename as_parser<OpenT>::type::embed_t open;
    typename as_parser<ExprT>::type::embed_t expr;
    typename as_parser<CloseT>::type::embed_t close;
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

///////////////////////////////////////////////////////////////////////////////
//
//  Confix parser generator template
//
//      This is a helper for generating a correct confix_parser<> from
//      auxiliary parameters. There are the following types supported as
//      parameters yet: parsers, single characters and strings (see
//      as_parser).
//
//      If the body parser is an action_parser_category type parser (a parser
//      with an attached semantic action) we have to do something special. This
//      happens, if the user wrote something like:
//
//          confix_p(open, body[f], close)
//
//      where 'body' is the parser matching the body of the confix sequence
//      and 'f' is a functor to be called after matching the body. If we would
//      do nothing, the resulting code would parse the sequence as follows:
//
//          start >> (body[f] - close) >> close
//
//      what in most cases is not what the user expects.
//      (If this _is_ what you've expected, then please use the confix_p
//      generator function 'direct()', which will inhibit
//      re-attaching the actor to the body parser).
//
//      To make the confix parser behave as expected:
//
//          start >> (body - close)[f] >> close
//
//      the actor attached to the 'body' parser has to be re-attached to the
//      (body - close) parser construct, which will make the resulting confix
//      parser 'do the right thing'. This refactoring is done by the help of
//      the refactoring parsers (see the files refactoring.[hi]pp).
//
//      Additionally special care must be taken, if the body parser is a
//      unary_parser_category type parser as
//
//          confix_p(open, *anychar_p, close)
//
//      which without any refactoring would result in
//
//          start >> (*anychar_p - close) >> close
//
//      and will not give the expected result (*anychar_p will eat up all the
//      input up to the end of the input stream). So we have to refactor this
//      into:
//
//          start >> *(anychar_p - close) >> close
//
//      what will give the correct result.
//
//      The case, where the body parser is a combination of the two mentioned
//      problems (i.e. the body parser is a unary parser  with an attached
//      action), is handled accordingly too:
//
//          confix_p(start, (*anychar_p)[f], end)
//
//      will be parsed as expected:
//
//          start >> (*(anychar_p - end))[f] >> end.
//
///////////////////////////////////////////////////////////////////////////////

template<typename NestedT, typename LexemeT>
struct confix_parser_gen
{
    // Generic generator function for creation of concrete confix parsers

    template<typename StartT, typename ExprT, typename EndT>
    struct paren_op_result_type
    {
        typedef confix_parser<
            typename as_parser<StartT>::type,
            typename as_parser<ExprT>::type,
            typename as_parser<EndT>::type,
            typename as_parser<ExprT>::type::parser_category_t,
            NestedT,
            LexemeT
        > type;
    };
  
    template<typename StartT, typename ExprT, typename EndT>
    typename paren_op_result_type<StartT, ExprT, EndT>::type 
    operator()(StartT const &start_, ExprT const &expr_, EndT const &end_) const
    {
        typedef typename paren_op_result_type<StartT,ExprT,EndT>::type 
            return_t;

        return return_t(
            as_parser<StartT>::convert(start_),
            as_parser<ExprT>::convert(expr_),
            as_parser<EndT>::convert(end_)
        );
    }

    // Generic generator function for creation of concrete confix parsers
    // which have an action directly attached to the ExprT part of the
    // parser (see comment above, no automatic refactoring)

    template<typename StartT, typename ExprT, typename EndT>
    struct direct_result_type
    {
        typedef confix_parser<
            typename as_parser<StartT>::type,
            typename as_parser<ExprT>::type,
            typename as_parser<EndT>::type,
            plain_parser_category,   // do not re-attach action
            NestedT,
            LexemeT
        > type;
    };

    template<typename StartT, typename ExprT, typename EndT>
    typename direct_result_type<StartT,ExprT,EndT>::type
    direct(StartT const &start_, ExprT const &expr_, EndT const &end_) const
    {
        typedef typename direct_result_type<StartT,ExprT,EndT>::type
            return_t;

        return return_t(
            as_parser<StartT>::convert(start_),
            as_parser<ExprT>::convert(expr_),
            as_parser<EndT>::convert(end_)
        );
    }
};

///////////////////////////////////////////////////////////////////////////////
//
//  Predefined non_nested confix parser generators
//
///////////////////////////////////////////////////////////////////////////////

const confix_parser_gen<non_nested, non_lexeme> confix_p =
    confix_parser_gen<non_nested, non_lexeme>();

///////////////////////////////////////////////////////////////////////////////
//
//  Comments are special types of confix parsers
//
//      Comment parser generator template. This is a helper for generating a
//      correct confix_parser<> from auxiliary parameters, which is able to
//      parse comment constructs: (StartToken >> Comment text >> EndToken).
//
//      There are the following types supported as parameters yet: parsers,
//      single characters and strings (see as_parser).
//
//      There are two diffenerent predefined comment parser generators
//      (comment_p and comment_nest_p, see below), which may be used for
//      creating special comment parsers in two different ways.
//
//      If these are used with one parameter, a comment starting with the given
//      first parser parameter up to the end of the line is matched. So for
//      instance the following parser matches C++ style comments:
//
//          comment_p("//").
//
//      If these are used with two parameters, a comment starting with the
//      first parser parameter up to the second parser parameter is matched.
//      For instance a C style comment parser should be constrcuted as:
//
//          comment_p("/*", "*/").
//
//      Please note, that a comment is parsed implicitly as if the whole
//      comment_p(...) statement were embedded into a lexeme_d[] directive.
//
///////////////////////////////////////////////////////////////////////////////

template<typename NestedT>
struct comment_parser_gen
{
    // Generic generator function for creation of concrete comment parsers
    // from an open token. The newline parser eol_p is used as the
    // closing token.

    template<typename StartT>
    struct paren_op1_result_type
    {
        typedef confix_parser<
            typename as_parser<StartT>::type,
            kleene_star<anychar_parser>,
            alternative<eol_parser, end_parser>,
            unary_parser_category,          // there is no action to re-attach
            NestedT,
            is_lexeme                       // insert implicit lexeme_d[]
        >
        type;
    };

    template<typename StartT>
    typename paren_op1_result_type<StartT>::type 
    operator() (StartT const &start_) const
    {
        typedef typename paren_op1_result_type<StartT>::type
            return_t;

        return return_t(
            as_parser<StartT>::convert(start_),
            *anychar_p,
            eol_p | end_p
        );
    }

    // Generic generator function for creation of concrete comment parsers
    // from an open and a close tokens.

    template<typename StartT, typename EndT>
    struct paren_op2_result_type
    {
        typedef confix_parser<
            typename as_parser<StartT>::type,
            kleene_star<anychar_parser>,
            typename as_parser<EndT>::type,
            unary_parser_category,          // there is no action to re-attach
            NestedT,
            is_lexeme                       // insert implicit lexeme_d[]
        > type;
    };

    template<typename StartT, typename EndT>
    typename paren_op2_result_type<StartT,EndT>::type
    operator() (StartT const &start_, EndT const &end_) const
    {
        typedef typename paren_op2_result_type<StartT,EndT>::type
            return_t;

        return return_t(
            as_parser<StartT>::convert(start_),
            *anychar_p,
            as_parser<EndT>::convert(end_)
        );
    }
};

///////////////////////////////////////////////////////////////////////////////
//
//  Predefined non_nested comment parser generator
//
///////////////////////////////////////////////////////////////////////////////

const comment_parser_gen<non_nested> comment_p =
    comment_parser_gen<non_nested>();

///////////////////////////////////////////////////////////////////////////////
//
//  comment_nest_parser class
//
//      Parses a nested comments.
//      Example: nested PASCAL-comments:
//
//      { This is a { nested } PASCAL-comment }
//
///////////////////////////////////////////////////////////////////////////////

template<typename OpenT, typename CloseT>
struct comment_nest_parser:
    public parser<comment_nest_parser<OpenT, CloseT> >
{
    typedef comment_nest_parser<OpenT, CloseT> self_t;

    comment_nest_parser(OpenT const &open_, CloseT const &close_):
        open(open_), close(close_)
    {}

    template<typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const &scan) const
    {
        return do_parse(
            open >> *(*this | (anychar_p - close)) >> close,
            scan);
    }

private:
    template<typename ParserT, typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
        do_parse(ParserT const &p, ScannerT const &scan) const
    {
        return
            impl::contiguous_parser_parse<
                typename parser_result<ParserT, ScannerT>::type
            >(p, scan, scan);
    }

    typename as_parser<OpenT>::type::embed_t open;
    typename as_parser<CloseT>::type::embed_t close;
};

///////////////////////////////////////////////////////////////////////////////
//
//  Predefined nested comment parser generator
//
///////////////////////////////////////////////////////////////////////////////

template<typename OpenT, typename CloseT>
struct comment_nest_p_result
{
    typedef comment_nest_parser<
        typename as_parser<OpenT>::type,
        typename as_parser<CloseT>::type
    > type;
};

template<typename OpenT, typename CloseT>
inline typename comment_nest_p_result<OpenT,CloseT>::type 
comment_nest_p(OpenT const &open, CloseT const &close)
{
    typedef typename comment_nest_p_result<OpenT,CloseT>::type
        result_t;

    return result_t(
        as_parser<OpenT>::convert(open),
        as_parser<CloseT>::convert(close)
    );
}

///////////////////////////////////////////////////////////////////////////////
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

/* confix.hpp
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
*/