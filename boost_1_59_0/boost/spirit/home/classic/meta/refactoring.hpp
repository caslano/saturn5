/*=============================================================================
    Copyright (c) 2002-2003 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_REFACTORING_HPP
#define BOOST_SPIRIT_REFACTORING_HPP

///////////////////////////////////////////////////////////////////////////////
#include <boost/static_assert.hpp>
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/meta/as_parser.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include <boost/spirit/home/classic/meta/impl/refactoring.ipp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

///////////////////////////////////////////////////////////////////////////////
//
//  refactor_unary_parser class
//
//      This helper template allows to attach an unary operation to a newly
//      constructed parser, which combines the subject of the left operand of
//      the original given parser (BinaryT) with the right operand of the
//      original binary parser through the original binary operation and
//      rewraps the resulting parser with the original unary operator.
//
//      For instance given the parser:
//          *some_parser - another_parser
//
//      will be refactored to:
//          *(some_parser - another_parser)
//
//      If the parser to refactor is not a unary parser, no refactoring is done
//      at all.
//
//      The original parser should be a binary_parser_category parser,
//      else the compilation will fail
//
///////////////////////////////////////////////////////////////////////////////

template <typename NestedT = non_nested_refactoring>
class refactor_unary_gen;

template <typename BinaryT, typename NestedT = non_nested_refactoring>
class refactor_unary_parser :
    public parser<refactor_unary_parser<BinaryT, NestedT> > {

public:
    //  the parser to refactor has to be at least a binary_parser_category
    //  parser
    BOOST_STATIC_ASSERT((
        boost::is_convertible<typename BinaryT::parser_category_t,
            binary_parser_category>::value
    ));

    refactor_unary_parser(BinaryT const& binary_, NestedT const& nested_)
    : binary(binary_), nested(nested_) {}

    typedef refactor_unary_parser<BinaryT, NestedT> self_t;
    typedef refactor_unary_gen<NestedT> parser_generator_t;
    typedef typename BinaryT::left_t::parser_category_t parser_category_t;

    template <typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
    parse(ScannerT const& scan) const
    {
        return impl::refactor_unary_type<NestedT>::
            parse(*this, scan, binary, nested);
    }

private:
    typename as_parser<BinaryT>::type::embed_t binary;
    typename NestedT::embed_t nested;
};

//////////////////////////////////
template <typename NestedT>
class refactor_unary_gen {

public:
    typedef refactor_unary_gen<NestedT> embed_t;

    refactor_unary_gen(NestedT const& nested_ = non_nested_refactoring())
    : nested(nested_) {}

    template <typename ParserT>
    refactor_unary_parser<ParserT, NestedT>
    operator[](parser<ParserT> const& subject) const
    {
        return refactor_unary_parser<ParserT, NestedT>
            (subject.derived(), nested);
    }

private:
    typename NestedT::embed_t nested;
};

const refactor_unary_gen<> refactor_unary_d = refactor_unary_gen<>();

///////////////////////////////////////////////////////////////////////////////
//
//  refactor_action_parser class
//
//      This helper template allows to attach an action taken from the left
//      operand of the given binary parser to a newly constructed parser,
//      which combines the subject of the left operand of the original binary
//      parser with the right operand of the original binary parser by means of
//      the original binary operator parser.
//
//      For instance the parser:
//          some_parser[some_attached_functor] - another_parser
//
//      will be refactored to:
//          (some_parser - another_parser)[some_attached_functor]
//
//      If the left operand to refactor is not an action parser, no refactoring
//      is done at all.
//
//      The original parser should be a binary_parser_category parser,
//      else the compilation will fail
//
///////////////////////////////////////////////////////////////////////////////

template <typename NestedT = non_nested_refactoring>
class refactor_action_gen;

template <typename BinaryT, typename NestedT = non_nested_refactoring>
class refactor_action_parser :
    public parser<refactor_action_parser<BinaryT, NestedT> > {

public:
    //  the parser to refactor has to be at least a binary_parser_category
    //  parser
    BOOST_STATIC_ASSERT((
        boost::is_convertible<typename BinaryT::parser_category_t,
            binary_parser_category>::value
    ));

    refactor_action_parser(BinaryT const& binary_, NestedT const& nested_)
    : binary(binary_), nested(nested_) {}

    typedef refactor_action_parser<BinaryT, NestedT> self_t;
    typedef refactor_action_gen<NestedT> parser_generator_t;
    typedef typename BinaryT::left_t::parser_category_t parser_category_t;

    template <typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
    parse(ScannerT const& scan) const
    {
        return impl::refactor_action_type<NestedT>::
            parse(*this, scan, binary, nested);
    }

private:
    typename as_parser<BinaryT>::type::embed_t binary;
    typename NestedT::embed_t nested;
};

//////////////////////////////////
template <typename NestedT>
class refactor_action_gen {

public:
    typedef refactor_action_gen<NestedT> embed_t;

    refactor_action_gen(NestedT const& nested_ = non_nested_refactoring())
    : nested(nested_) {}

    template <typename ParserT>
    refactor_action_parser<ParserT, NestedT>
    operator[](parser<ParserT> const& subject) const
    {
        return refactor_action_parser<ParserT, NestedT>
            (subject.derived(), nested);
    }

private:
    typename NestedT::embed_t nested;
};

const refactor_action_gen<> refactor_action_d = refactor_action_gen<>();

///////////////////////////////////////////////////////////////////////////////
//
//  attach_action_parser class
//
//      This helper template allows to attach an action given separately
//      to all parsers, out of which the given parser is constructed and
//      reconstructs a new parser having the same structure.
//
//      For instance the parser:
//          (some_parser >> another_parser)[some_attached_functor]
//
//      will be refactored to:
//          some_parser[some_attached_functor]
//              >> another_parser[some_attached_functor]
//
//      The original parser should be a action_parser_category parser,
//      else the compilation will fail.
//
//      If the parser, to which the action is attached is not an binary parser,
//      no refactoring is done at all.
//
///////////////////////////////////////////////////////////////////////////////

template <typename NestedT = non_nested_refactoring>
class attach_action_gen;

template <typename ActionT, typename NestedT = non_nested_refactoring>
class attach_action_parser :
    public parser<attach_action_parser<ActionT, NestedT> > {

public:
    //  the parser to refactor has to be at least a action_parser_category
    //  parser
    BOOST_STATIC_ASSERT((
        boost::is_convertible<typename ActionT::parser_category_t,
            action_parser_category>::value
    ));

    attach_action_parser(ActionT const& actor_, NestedT const& nested_)
    : actor(actor_), nested(nested_) {}

    typedef attach_action_parser<ActionT, NestedT> self_t;
    typedef attach_action_gen<NestedT> parser_generator_t;
    typedef typename ActionT::parser_category_t parser_category_t;

    template <typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
    parse(ScannerT const& scan) const
    {
        return impl::attach_action_type<NestedT>::
            parse(*this, scan, actor, nested);
    }

private:
    typename as_parser<ActionT>::type::embed_t actor;
    typename NestedT::embed_t nested;
};

//////////////////////////////////
template <typename NestedT>
class attach_action_gen {

public:
    typedef attach_action_gen<NestedT> embed_t;

    attach_action_gen(NestedT const& nested_ = non_nested_refactoring())
    : nested(nested_) {}

    template <typename ParserT, typename ActionT>
    attach_action_parser<action<ParserT, ActionT>, NestedT>
    operator[](action<ParserT, ActionT> const& actor) const
    {
        return attach_action_parser<action<ParserT, ActionT>, NestedT>
            (actor, nested);
    }

private:
    typename NestedT::embed_t nested;
};

const attach_action_gen<> attach_action_d = attach_action_gen<>();

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

///////////////////////////////////////////////////////////////////////////////
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif // BOOST_SPIRIT_REFACTORING_HPP


/* refactoring.hpp
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
*/