/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_PARSER_HPP)
#define BOOST_SPIRIT_PARSER_HPP

#include <boost/config.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/scanner/scanner.hpp>
#include <boost/spirit/home/classic/core/nil.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    template <typename ParserT, typename ActionT>
    class action; //  forward declaration

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Parser categories
    //
    //      Helper template classes to distinguish different types of
    //      parsers. The following categories are the most generic. More
    //      specific types may inherit from these. Each parser has a typedef
    //      parser_category_t that defines its category. By default, if one
    //      is not specified, it will inherit from the base parser class
    //      which typedefs its parser_category_t as plain_parser_category.
    //
    //          - plain parser has nothing special
    //          - binary parser has subject a and b (e.g. alternative)
    //          - unary parser has single subject  (e.g. kleene star)
    //          - action parser has an attached action parser
    //
    ///////////////////////////////////////////////////////////////////////////
    struct plain_parser_category {};
    struct binary_parser_category       : plain_parser_category {};
    struct unary_parser_category        : plain_parser_category {};
    struct action_parser_category       : unary_parser_category {};

    ///////////////////////////////////////////////////////////////////////////
    //
    //  parser_result metafunction
    //
    //      Given a scanner type ScannerT and a parser type ParserT, the
    //      parser_result metafunction provides the actual result of the
    //      parser.
    //
    //  Usage:
    //
    //      typename parser_result<ParserT, ScannerT>::type
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ParserT, typename ScannerT>
    struct parser_result
    {
        typedef typename boost::remove_reference<ParserT>::type parser_type;
        typedef typename parser_type::template result<ScannerT>::type type;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  parser class
    //
    //      This class is a protocol base class for all parsers. This is
    //      essentially an interface contract. The parser class does not
    //      really know how to parse anything but instead relies on the
    //      template parameter DerivedT (which obviously is assumed to be a
    //      subclass) to do the actual parsing.
    //
    //      Concrete sub-classes inheriting from parser must have a
    //      corresponding member function parse(...) compatible with the
    //      conceptual Interface:
    //
    //          template <typename ScannerT>
    //          RT parse(ScannerT const& scan) const;
    //
    //      where RT is the desired return type of the parser and ScannerT
    //      scan is the scanner (see scanner.hpp).
    //
    //      Concrete sub-classes inheriting from parser in most cases need to
    //      have a nested meta-function result that returns the result type
    //      of the parser's parse member function, given a scanner type. The
    //      meta-function has the form:
    //
    //          template <typename ScannerT>
    //          struct result
    //          {
    //              typedef RT type;
    //          };
    //
    //      where RT is the desired return type of the parser. This is
    //      usually, but not always, dependent on the template parameter
    //      ScannerT. If a parser does not supply a result metafunction, a
    //      default is provided by the base parser class.
    //
    //      The parser's derived() member function returns a reference to the
    //      parser as its derived object.
    //
    //      An operator[] is provided. The operator returns a semantic action
    //      handler (see actions.hpp).
    //
    //      Each parser has a typedef embed_t. This typedef specifies how a
    //      parser is embedded in a composite (see composite.hpp). By
    //      default, if one is not specified, the parser will be embedded by
    //      value. That is, a copy of the parser is placed as a member
    //      variable of the composite. Most parsers are embedded by value. In
    //      certain situations however, this is not desirable or possible.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename DerivedT>
    struct parser
    {
        typedef DerivedT                embed_t;
        typedef DerivedT                derived_t;
        typedef plain_parser_category   parser_category_t;

        template <typename ScannerT>
        struct result
        {
            typedef typename match_result<ScannerT, nil_t>::type type;
        };

        DerivedT& derived()
        {
            return *static_cast<DerivedT*>(this);
        }

        DerivedT const& derived() const
        {
            return *static_cast<DerivedT const*>(this);
        }

        template <typename ActionT>
        action<DerivedT, ActionT>
        operator[](ActionT const& actor) const
        {
            return action<DerivedT, ActionT>(derived(), actor);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  parse_info
    //
    //      Results returned by the free parse functions:
    //
    //      stop:   points to the final parse position (i.e parsing
    //              processed the input up to this point).
    //
    //      hit:    true if parsing is successful. This may be full:
    //              the parser consumed all the input, or partial:
    //              the parser consumed only a portion of the input.
    //
    //      full:   true when we have a full hit (i.e the parser
    //              consumed all the input.
    //
    //      length: The number of characters consumed by the parser.
    //              This is valid only if we have a successful hit
    //              (either partial or full).
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename IteratorT = char const*>
    struct parse_info
    {
        IteratorT   stop;
        bool        hit;
        bool        full;
        std::size_t length;

        parse_info(
            IteratorT const& stop_ = IteratorT(),
            bool hit_ = false,
            bool full_ = false,
            std::size_t length_ = 0)
        : stop(stop_)
        , hit(hit_)
        , full(full_)
        , length(length_) {}

        template <typename ParseInfoT>
        parse_info(ParseInfoT const& pi)
        : stop(pi.stop)
        , hit(pi.hit)
        , full(pi.full)
        , length(pi.length) {}
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Generic parse function
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename IteratorT, typename DerivedT>
    parse_info<IteratorT>
    parse(
        IteratorT const&        first,
        IteratorT const&        last,
        parser<DerivedT> const& p);

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Parse function for null terminated strings
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharT, typename DerivedT>
    parse_info<CharT const*>
    parse(
        CharT const*            str,
        parser<DerivedT> const& p);

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

#include <boost/spirit/home/classic/core/impl/parser.ipp>

/* parser.hpp
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
*/