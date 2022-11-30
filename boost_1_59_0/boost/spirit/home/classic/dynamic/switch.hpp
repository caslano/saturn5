/*=============================================================================
    Copyright (c) 2003 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_SWITCH_HPP
#define BOOST_SPIRIT_SWITCH_HPP

///////////////////////////////////////////////////////////////////////////////
//
//  The default_p parser generator template uses the following magic number
//  as the corresponding case label value inside the generated switch()
//  statements. If this number conflicts with your code, please pick a
//  different one.
//
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_SPIRIT_DEFAULTCASE_MAGIC)
#define BOOST_SPIRIT_DEFAULTCASE_MAGIC 0x15F97A7
#endif

///////////////////////////////////////////////////////////////////////////////
//
//  Spirit predefined maximum number of possible case_p/default_p case branch
//  parsers.
//
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_SPIRIT_SWITCH_CASE_LIMIT)
#define BOOST_SPIRIT_SWITCH_CASE_LIMIT 3
#endif // !defined(BOOST_SPIRIT_SWITCH_CASE_LIMIT)

///////////////////////////////////////////////////////////////////////////////
#include <boost/static_assert.hpp>

///////////////////////////////////////////////////////////////////////////////
//
// Ensure   BOOST_SPIRIT_SELECT_LIMIT > 0
//
///////////////////////////////////////////////////////////////////////////////
BOOST_STATIC_ASSERT(BOOST_SPIRIT_SWITCH_CASE_LIMIT > 0);

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/config.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/composite/epsilon.hpp>
#include <boost/spirit/home/classic/dynamic/impl/switch.ipp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
//
//  The switch_parser allows to build switch like parsing constructs, which
//  will have much better performance as comparable straight solutions.
//
//  Input stream driven syntax:
//
//      switch_p
//      [
//          case_p<'a'>
//              (...parser to use, if the next character is 'a'...),
//          case_p<'b'>
//              (...parser to use, if the next character is 'b'...),
//          default_p
//              (...parser to use, if nothing was matched before...)
//      ]
//
//  General syntax:
//
//      switch_p(...lazy expression returning the switch condition value...)
//      [
//          case_p<1>
//              (...parser to use, if the switch condition value is 1...),
//          case_p<2>
//              (...parser to use, if the switch condition value is 2...),
//          default_p
//              (...parser to use, if nothing was matched before...)
//      ]
//
//  The maximum number of possible case_p branches is defined by the p constant
//  BOOST_SPIRIT_SWITCH_CASE_LIMIT (this value defaults to 3 if not otherwise
//  defined).
//
///////////////////////////////////////////////////////////////////////////////
template <typename CaseT, typename CondT = impl::get_next_token_cond>
struct switch_parser
:   public unary<CaseT, parser<switch_parser<CaseT, CondT> > >
{
    typedef switch_parser<CaseT, CondT>     self_t;
    typedef unary_parser_category           parser_category_t;
    typedef unary<CaseT, parser<self_t> >   base_t;

    switch_parser(CaseT const &case_)
    :   base_t(case_), cond(CondT())
    {}

    switch_parser(CaseT const &case_, CondT const &cond_)
    :   base_t(case_), cond(cond_)
    {}

    template <typename ScannerT>
    struct result
    {
        typedef typename match_result<ScannerT, nil_t>::type type;
    };

    template <typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
    parse(ScannerT const& scan) const
    {
        return this->subject().parse(scan,
            impl::make_cond_functor<CondT>::do_(cond));
    }

    CondT cond;
};

///////////////////////////////////////////////////////////////////////////////
template <typename CondT>
struct switch_cond_parser
{
    switch_cond_parser(CondT const &cond_)
    :   cond(cond_)
    {}

    template <typename ParserT>
    switch_parser<ParserT, CondT>
    operator[](parser<ParserT> const &p) const
    {
        return switch_parser<ParserT, CondT>(p.derived(), cond);
    }

    CondT const &cond;
};

///////////////////////////////////////////////////////////////////////////////
template <int N, typename ParserT, bool IsDefault>
struct case_parser
:   public unary<ParserT, parser<case_parser<N, ParserT, IsDefault> > >
{
    typedef case_parser<N, ParserT, IsDefault> self_t;
    typedef unary_parser_category               parser_category_t;
    typedef unary<ParserT, parser<self_t> >     base_t;

    typedef typename base_t::subject_t          self_subject_t;

    BOOST_STATIC_CONSTANT(int, value = N);
    BOOST_STATIC_CONSTANT(bool, is_default = IsDefault);
    BOOST_STATIC_CONSTANT(bool, is_simple = true);
    BOOST_STATIC_CONSTANT(bool, is_epsilon = (
        is_default && boost::is_same<self_subject_t, epsilon_parser>::value
    ));

    case_parser(parser<ParserT> const &p)
    :   base_t(p.derived())
    {}

    template <typename ScannerT>
    struct result
    {
        typedef typename match_result<ScannerT, nil_t>::type type;
    };

    template <typename ScannerT, typename CondT>
    typename parser_result<self_t, ScannerT>::type
    parse(ScannerT const& scan, CondT const &cond) const
    {
        typedef impl::default_case<self_t> default_t;

        if (!scan.at_end()) {
            typedef impl::default_delegate_parse<
                value, is_default, default_t::value> default_parse_t;

            typename ScannerT::iterator_t const save(scan.first);
            return default_parse_t::parse(cond(scan), *this,
                *this, scan, save);
        }

        return default_t::is_epsilon ? scan.empty_match() : scan.no_match();
    }

    template <int N1, typename ParserT1, bool IsDefault1>
    impl::compound_case_parser<
        self_t, case_parser<N1, ParserT1, IsDefault1>, IsDefault1
    >
    operator, (case_parser<N1, ParserT1, IsDefault1> const &p) const
    {
        //  If the following compile time assertion fires, you've probably used
        //  more than one default_p case inside the switch_p parser construct.
        BOOST_STATIC_ASSERT(!is_default || !IsDefault1);

        typedef case_parser<N1, ParserT1, IsDefault1> right_t;
        return impl::compound_case_parser<self_t, right_t, IsDefault1>(*this, p);
    }
};

///////////////////////////////////////////////////////////////////////////////
struct switch_parser_gen {

//  This generates a switch parser, which is driven by the condition value
//  returned by the lazy parameter expression 'cond'. This may be a parser,
//  which result is used or a phoenix actor, which will be dereferenced to
//  obtain the switch condition value.
    template <typename CondT>
    switch_cond_parser<CondT>
    operator()(CondT const &cond) const
    {
        return switch_cond_parser<CondT>(cond);
    }

//  This generates a switch parser, which is driven by the next character/token
//  found in the input stream.
    template <typename CaseT>
    switch_parser<CaseT>
    operator[](parser<CaseT> const &p) const
    {
        return switch_parser<CaseT>(p.derived());
    }
};

switch_parser_gen const switch_p = switch_parser_gen();

///////////////////////////////////////////////////////////////////////////////
template <int N, typename ParserT>
inline case_parser<N, ParserT, false>
case_p(parser<ParserT> const &p)
{
    return case_parser<N, ParserT, false>(p);
}

///////////////////////////////////////////////////////////////////////////////
struct default_parser_gen
:   public case_parser<BOOST_SPIRIT_DEFAULTCASE_MAGIC, epsilon_parser, true>
{
    default_parser_gen()
    :   case_parser<BOOST_SPIRIT_DEFAULTCASE_MAGIC, epsilon_parser, true>
            (epsilon_p)
    {}

    template <typename ParserT>
    case_parser<BOOST_SPIRIT_DEFAULTCASE_MAGIC, ParserT, true>
    operator()(parser<ParserT> const &p) const
    {
        return case_parser<BOOST_SPIRIT_DEFAULTCASE_MAGIC, ParserT, true>(p);
    }
};

default_parser_gen const default_p = default_parser_gen();

///////////////////////////////////////////////////////////////////////////////
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}}  // namespace BOOST_SPIRIT_CLASSIC_NS

#endif // BOOST_SPIRIT_SWITCH_HPP

/* switch.hpp
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
*/