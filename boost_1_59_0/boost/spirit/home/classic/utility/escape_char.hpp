/*=============================================================================
    Copyright (c) 2001-2003 Daniel Nuffer
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_ESCAPE_CHAR_HPP
#define BOOST_SPIRIT_ESCAPE_CHAR_HPP

///////////////////////////////////////////////////////////////////////////////
#include <string>
#include <iterator>
#include <cctype>
#include <boost/limits.hpp>

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/debug.hpp>

#include <boost/spirit/home/classic/utility/escape_char_fwd.hpp>
#include <boost/spirit/home/classic/utility/impl/escape_char.ipp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
//
//  escape_char_action class
//
//      Links an escape char parser with a user defined semantic action.
//      The semantic action may be a function or a functor. A function
//      should be compatible with the interface:
//
//          void f(CharT ch);
//
//      A functor should have a member operator() with a compatible signature
//      as above. The matching character is passed into the function/functor.
//      This is the default class that character parsers use when dealing with
//      the construct:
//
//          p[f]
//
//      where p is a parser and f is a function or functor.
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename ParserT, typename ActionT,
    unsigned long Flags, typename CharT
>
struct escape_char_action
:   public unary<ParserT,
        parser<escape_char_action<ParserT, ActionT, Flags, CharT> > >
{
    typedef escape_char_action
        <ParserT, ActionT, Flags, CharT>        self_t;
    typedef action_parser_category              parser_category_t;
    typedef unary<ParserT, parser<self_t> >     base_t;

    template <typename ScannerT>
    struct result
    {
        typedef typename match_result<ScannerT, CharT>::type type;
    };

    escape_char_action(ParserT const& p, ActionT const& a)
    : base_t(p), actor(a) {}

    template <typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
    parse(ScannerT const& scan) const
    {
        return impl::escape_char_action_parse<Flags, CharT>::
            parse(scan, *this);
    }

    ActionT const& predicate() const { return actor; }

private:

    ActionT actor;
};

///////////////////////////////////////////////////////////////////////////////
//
//  escape_char_parser class
//
//      The escape_char_parser helps in conjunction with the escape_char_action
//      template class (see above) in parsing escaped characters. There are two
//      different variants of this parser: one for parsing C style escaped
//      characters and one for parsing LEX style escaped characters.
//
//      The C style escaped character parser is generated, when the template
//      parameter 'Flags' is equal to 'c_escapes' (a constant defined in the
//      file impl/escape_char.ipp). This parser recognizes all valid C escape
//      character sequences: '\t', '\b', '\f', '\n', '\r', '\"', '\'', '\\'
//      and the numeric style escapes '\120' (octal) and '\x2f' (hexadecimal)
//      and converts these to their character equivalent, for instance the
//      sequence of a backslash and a 'b' is parsed as the character '\b'.
//      All other escaped characters are rejected by this parser.
//
//      The LEX style escaped character parser is generated, when the template
//      parameter 'Flags' is equal to 'lex_escapes' (a constant defined in the
//      file impl/escape_char.ipp). This parser recognizes all the C style
//      escaped character sequences (as described above) and additionally
//      does not reject all other escape sequences. All not mentioned escape
//      sequences are converted by the parser to the plain character, for
//      instance '\a' will be parsed as 'a'.
//
//      All not escaped characters are parsed without modification.
//
///////////////////////////////////////////////////////////////////////////////

template <unsigned long Flags, typename CharT>
struct escape_char_action_parser_gen;

template <unsigned long Flags, typename CharT>
struct escape_char_parser :
    public parser<escape_char_parser<Flags, CharT> > {

    // only the values c_escapes and lex_escapes are valid for Flags
    BOOST_STATIC_ASSERT(Flags == c_escapes || Flags == lex_escapes);

    typedef escape_char_parser<Flags, CharT> self_t;
    typedef
        escape_char_action_parser_gen<Flags, CharT>
        action_parser_generator_t;

    template <typename ScannerT>
    struct result {

        typedef typename match_result<ScannerT, CharT>::type type;
    };

    template <typename ActionT>
    escape_char_action<self_t, ActionT, Flags, CharT>
    operator[](ActionT const& actor) const
    {
        return escape_char_action<self_t, ActionT, Flags, CharT>(*this, actor);
    }

    template <typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
    parse(ScannerT const &scan) const
    {
        return impl::escape_char_parse<CharT>::parse(scan, *this);
    }
};

template <unsigned long Flags, typename CharT>
struct escape_char_action_parser_gen {

    template <typename ParserT, typename ActionT>
    static escape_char_action<ParserT, ActionT, Flags, CharT>
    generate (ParserT const &p, ActionT const &actor)
    {
        typedef
            escape_char_action<ParserT, ActionT, Flags, CharT>
            action_parser_t;
        return action_parser_t(p, actor);
    }
};

///////////////////////////////////////////////////////////////////////////////
//
//  predefined escape_char_parser objects
//
//      These objects should be used for generating correct escaped character
//      parsers.
//
///////////////////////////////////////////////////////////////////////////////
const escape_char_parser<lex_escapes> lex_escape_ch_p =
    escape_char_parser<lex_escapes>();

const escape_char_parser<c_escapes> c_escape_ch_p =
    escape_char_parser<c_escapes>();

///////////////////////////////////////////////////////////////////////////////
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

/* escape_char.hpp
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
*/