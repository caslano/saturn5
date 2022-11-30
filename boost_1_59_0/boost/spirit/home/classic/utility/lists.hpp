/*=============================================================================
    Copyright (c) 2002-2003 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_LISTS_HPP
#define BOOST_SPIRIT_LISTS_HPP

///////////////////////////////////////////////////////////////////////////////
#include <boost/config.hpp>
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/meta/as_parser.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>

#include <boost/spirit/home/classic/utility/lists_fwd.hpp>
#include <boost/spirit/home/classic/utility/impl/lists.ipp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
//
//  list_parser class
//
//      List parsers allow to parse constructs like
//
//          item >> *(delim >> item)
//
//      where 'item' is an auxiliary expression to parse and 'delim' is an
//      auxiliary delimiter to parse.
//
//      The list_parser class also can match an optional closing delimiter
//      represented by the 'end' parser at the end of the list:
//
//          item >> *(delim >> item) >> !end.
//
//      If ItemT is an action_parser_category type (parser with an attached
//      semantic action) we have to do something special. This happens, if the
//      user wrote something like:
//
//          list_p(item[f], delim)
//
//      where 'item' is the parser matching one item of the list sequence and
//      'f' is a functor to be called after matching one item. If we would do
//      nothing, the resulting code would parse the sequence as follows:
//
//          (item[f] - delim) >> *(delim >> (item[f] - delim))
//
//      what in most cases is not what the user expects.
//      (If this _is_ what you've expected, then please use one of the list_p
//      generator functions 'direct()', which will inhibit re-attaching
//      the actor to the item parser).
//
//      To make the list parser behave as expected:
//
//          (item - delim)[f] >> *(delim >> (item - delim)[f])
//
//      the actor attached to the 'item' parser has to be re-attached to the
//      *(item - delim) parser construct, which will make the resulting list
//      parser 'do the right thing'.
//
//      Additionally special care must be taken, if the item parser is a
//      unary_parser_category type parser as
//
//          list_p(*anychar_p, ',')
//
//      which without any refactoring would result in
//
//          (*anychar_p - ch_p(','))
//              >> *( ch_p(',') >> (*anychar_p - ch_p(',')) )
//
//      and will not give the expected result (the first *anychar_p will eat up
//      all the input up to the end of the input stream). So we have to
//      refactor this into:
//
//          *(anychar_p - ch_p(','))
//              >> *( ch_p(',') >> *(anychar_p - ch_p(',')) )
//
//      what will give the correct result.
//
//      The case, where the item parser is a combination of the two mentioned
//      problems (i.e. the item parser is a unary parser  with an attached
//      action), is handled accordingly too:
//
//          list_p((*anychar_p)[f], ',')
//
//      will be parsed as expected:
//
//          (*(anychar_p - ch_p(',')))[f]
//              >> *( ch_p(',') >> (*(anychar_p - ch_p(',')))[f] ).
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename ItemT, typename DelimT, typename EndT, typename CategoryT
>
struct list_parser :
    public parser<list_parser<ItemT, DelimT, EndT, CategoryT> > {

    typedef list_parser<ItemT, DelimT, EndT, CategoryT> self_t;
    typedef CategoryT parser_category_t;

    list_parser(ItemT const &item_, DelimT const &delim_,
        EndT const& end_ = no_list_endtoken())
    : item(item_), delim(delim_), end(end_)
    {}

    template <typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
    parse(ScannerT const& scan) const
    {
        return impl::list_parser_type<CategoryT>
            ::parse(scan, *this, item, delim, end);
    }

private:
    typename as_parser<ItemT>::type::embed_t item;
    typename as_parser<DelimT>::type::embed_t delim;
    typename as_parser<EndT>::type::embed_t end;
};

///////////////////////////////////////////////////////////////////////////////
//
//  List parser generator template
//
//      This is a helper for generating a correct list_parser<> from
//      auxiliary parameters. There are the following types supported as
//      parameters yet: parsers, single characters and strings (see
//      as_parser<> in meta/as_parser.hpp).
//
//      The list_parser_gen by itself can be used for parsing comma separated
//      lists without item formatting:
//
//          list_p.parse(...)
//              matches any comma separated list.
//
//      If list_p is used with one parameter, this parameter is used to match
//      the delimiter:
//
//          list_p(';').parse(...)
//              matches any semicolon separated list.
//
//      If list_p is used with two parameters, the first parameter is used to
//      match the items and the second parameter matches the delimiters:
//
//          list_p(uint_p, ',').parse(...)
//              matches comma separated unsigned integers.
//
//      If list_p is used with three parameters, the first parameter is used
//      to match the items, the second one is used to match the delimiters and
//      the third one is used to match an optional ending token sequence:
//
//          list_p(real_p, ';', eol_p).parse(...)
//              matches a semicolon separated list of real numbers optionally
//              followed by an end of line.
//
//      The list_p in the previous examples denotes the predefined parser
//      generator, which should be used to define list parsers (see below).
//
///////////////////////////////////////////////////////////////////////////////

template <typename CharT = char>
struct list_parser_gen :
    public list_parser<kleene_star<anychar_parser>, chlit<CharT> >
{
    typedef list_parser_gen<CharT> self_t;

// construct the list_parser_gen object as an list parser for comma separated
// lists without item formatting.
    list_parser_gen()
    : list_parser<kleene_star<anychar_parser>, chlit<CharT> >
        (*anychar_p, chlit<CharT>(','))
    {}

// The following generator functions should be used under normal circumstances.
// (the operator()(...) functions)

    // Generic generator functions for creation of concrete list parsers, which
    // support 'normal' syntax:
    //
    //      item >> *(delim >> item)
    //
    // If item isn't given, everything between two delimiters is matched.

    template<typename DelimT>
    list_parser<
        kleene_star<anychar_parser>,
        typename as_parser<DelimT>::type,
        no_list_endtoken,
        unary_parser_category      // there is no action to re-attach
    >
    operator()(DelimT const &delim_) const
    {
        typedef kleene_star<anychar_parser> item_t;
        typedef typename as_parser<DelimT>::type delim_t;

        typedef
            list_parser<item_t, delim_t, no_list_endtoken, unary_parser_category>
            return_t;

        return return_t(*anychar_p, as_parser<DelimT>::convert(delim_));
    }

    template<typename ItemT, typename DelimT>
    list_parser<
        typename as_parser<ItemT>::type,
        typename as_parser<DelimT>::type,
        no_list_endtoken,
        typename as_parser<ItemT>::type::parser_category_t
    >
    operator()(ItemT const &item_, DelimT const &delim_) const
    {
        typedef typename as_parser<ItemT>::type item_t;
        typedef typename as_parser<DelimT>::type delim_t;
        typedef list_parser<item_t, delim_t, no_list_endtoken,
                BOOST_DEDUCED_TYPENAME item_t::parser_category_t>
            return_t;

        return return_t(
            as_parser<ItemT>::convert(item_),
            as_parser<DelimT>::convert(delim_)
        );
    }

    // Generic generator function for creation of concrete list parsers, which
    // support 'extended' syntax:
    //
    //      item >> *(delim >> item) >> !end

    template<typename ItemT, typename DelimT, typename EndT>
    list_parser<
        typename as_parser<ItemT>::type,
        typename as_parser<DelimT>::type,
        typename as_parser<EndT>::type,
        typename as_parser<ItemT>::type::parser_category_t
    >
    operator()(
        ItemT const &item_, DelimT const &delim_, EndT const &end_) const
    {
        typedef typename as_parser<ItemT>::type item_t;
        typedef typename as_parser<DelimT>::type delim_t;
        typedef typename as_parser<EndT>::type end_t;

        typedef list_parser<item_t, delim_t, end_t,
                BOOST_DEDUCED_TYPENAME item_t::parser_category_t>
            return_t;

        return return_t(
            as_parser<ItemT>::convert(item_),
            as_parser<DelimT>::convert(delim_),
            as_parser<EndT>::convert(end_)
        );
    }

// The following functions should be used, if the 'item' parser has an attached
// semantic action or is a unary_parser_category type parser and the structure
// of the resulting list parser should _not_ be refactored during parser
// construction (see comment above).

    // Generic generator function for creation of concrete list parsers, which
    // support 'normal' syntax:
    //
    //      item >> *(delim >> item)

    template<typename ItemT, typename DelimT>
    list_parser<
        typename as_parser<ItemT>::type,
        typename as_parser<DelimT>::type,
        no_list_endtoken,
        plain_parser_category        // inhibit action re-attachment
    >
    direct(ItemT const &item_, DelimT const &delim_) const
    {
        typedef typename as_parser<ItemT>::type item_t;
        typedef typename as_parser<DelimT>::type delim_t;
        typedef list_parser<item_t, delim_t, no_list_endtoken,
                plain_parser_category>
            return_t;

        return return_t(
            as_parser<ItemT>::convert(item_),
            as_parser<DelimT>::convert(delim_)
        );
    }

    // Generic generator function for creation of concrete list parsers, which
    // support 'extended' syntax:
    //
    //      item >> *(delim >> item) >> !end

    template<typename ItemT, typename DelimT, typename EndT>
    list_parser<
        typename as_parser<ItemT>::type,
        typename as_parser<DelimT>::type,
        typename as_parser<EndT>::type,
        plain_parser_category        // inhibit action re-attachment
    >
    direct(
        ItemT const &item_, DelimT const &delim_, EndT const &end_) const
    {
        typedef typename as_parser<ItemT>::type item_t;
        typedef typename as_parser<DelimT>::type delim_t;
        typedef typename as_parser<EndT>::type end_t;

        typedef
            list_parser<item_t, delim_t, end_t, plain_parser_category>
            return_t;

        return return_t(
            as_parser<ItemT>::convert(item_),
            as_parser<DelimT>::convert(delim_),
            as_parser<EndT>::convert(end_)
        );
    }
};

///////////////////////////////////////////////////////////////////////////////
//
//  Predefined list parser generator
//
//      The list_p parser generator can be used
//        - by itself for parsing comma separated lists without item formatting
//      or
//        - for generating list parsers with auxiliary parser parameters
//          for the 'item', 'delim' and 'end' subsequences.
//      (see comment above)
//
///////////////////////////////////////////////////////////////////////////////
const list_parser_gen<> list_p = list_parser_gen<>();

///////////////////////////////////////////////////////////////////////////////
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

/* lists.hpp
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
*/