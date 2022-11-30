/*=============================================================================
    Copyright (c) 2001-2003 Joel de Guzman
    Copyright (c) 2001-2003 Daniel Nuffer
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_CHSET_OPERATORS_HPP
#define BOOST_SPIRIT_CHSET_OPERATORS_HPP

///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/utility/chset.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
//
//  chset free operators
//
//      Where a and b are both chsets, implements:
//
//          a | b, a & b, a - b, a ^ b
//
//      Where a is a chset, implements:
//
//          ~a
//
///////////////////////////////////////////////////////////////////////////////
template <typename CharT>
chset<CharT>
operator~(chset<CharT> const& a);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator|(chset<CharT> const& a, chset<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator&(chset<CharT> const& a, chset<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator-(chset<CharT> const& a, chset<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator^(chset<CharT> const& a, chset<CharT> const& b);

///////////////////////////////////////////////////////////////////////////////
//
//  range <--> chset free operators
//
//      Where a is a chset and b is a range, and vice-versa, implements:
//
//          a | b, a & b, a - b, a ^ b
//
///////////////////////////////////////////////////////////////////////////////
template <typename CharT>
chset<CharT>
operator|(chset<CharT> const& a, range<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator&(chset<CharT> const& a, range<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator-(chset<CharT> const& a, range<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator^(chset<CharT> const& a, range<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator|(range<CharT> const& a, chset<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator&(range<CharT> const& a, chset<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator-(range<CharT> const& a, chset<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator^(range<CharT> const& a, chset<CharT> const& b);

///////////////////////////////////////////////////////////////////////////////
//
//  chlit <--> chset free operators
//
//      Where a is a chset and b is a chlit, and vice-versa, implements:
//
//          a | b, a & b, a - b, a ^ b
//
///////////////////////////////////////////////////////////////////////////////
template <typename CharT>
chset<CharT>
operator|(chset<CharT> const& a, chlit<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator&(chset<CharT> const& a, chlit<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator-(chset<CharT> const& a, chlit<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator^(chset<CharT> const& a, chlit<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator|(chlit<CharT> const& a, chset<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator&(chlit<CharT> const& a, chset<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator-(chlit<CharT> const& a, chset<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator^(chlit<CharT> const& a, chset<CharT> const& b);

///////////////////////////////////////////////////////////////////////////////
//
//  negated_char_parser<range> <--> chset free operators
//
//      Where a is a chset and b is a range, and vice-versa, implements:
//
//          a | b, a & b, a - b, a ^ b
//
///////////////////////////////////////////////////////////////////////////////
template <typename CharT>
chset<CharT>
operator|(chset<CharT> const& a, negated_char_parser<range<CharT> > const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator&(chset<CharT> const& a, negated_char_parser<range<CharT> > const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator-(chset<CharT> const& a, negated_char_parser<range<CharT> > const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator^(chset<CharT> const& a, negated_char_parser<range<CharT> > const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator|(negated_char_parser<range<CharT> > const& a, chset<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator&(negated_char_parser<range<CharT> > const& a, chset<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator-(negated_char_parser<range<CharT> > const& a, chset<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator^(negated_char_parser<range<CharT> > const& a, chset<CharT> const& b);

///////////////////////////////////////////////////////////////////////////////
//
//  negated_char_parser<chlit> <--> chset free operators
//
//      Where a is a chset and b is a chlit, and vice-versa, implements:
//
//          a | b, a & b, a - b, a ^ b
//
///////////////////////////////////////////////////////////////////////////////
template <typename CharT>
chset<CharT>
operator|(chset<CharT> const& a, negated_char_parser<chlit<CharT> > const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator&(chset<CharT> const& a, negated_char_parser<chlit<CharT> > const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator-(chset<CharT> const& a, negated_char_parser<chlit<CharT> > const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator^(chset<CharT> const& a, negated_char_parser<chlit<CharT> > const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator|(negated_char_parser<chlit<CharT> > const& a, chset<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator&(negated_char_parser<chlit<CharT> > const& a, chset<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator-(negated_char_parser<chlit<CharT> > const& a, chset<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator^(negated_char_parser<chlit<CharT> > const& a, chset<CharT> const& b);

///////////////////////////////////////////////////////////////////////////////
//
//  literal primitives <--> chset free operators
//
//      Where a is a chset and b is a literal primitive,
//      and vice-versa, implements:
//
//          a | b, a & b, a - b, a ^ b
//
///////////////////////////////////////////////////////////////////////////////
template <typename CharT>
chset<CharT>
operator|(chset<CharT> const& a, CharT b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator&(chset<CharT> const& a, CharT b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator-(chset<CharT> const& a, CharT b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator^(chset<CharT> const& a, CharT b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator|(CharT a, chset<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator&(CharT a, chset<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator-(CharT a, chset<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator^(CharT a, chset<CharT> const& b);

///////////////////////////////////////////////////////////////////////////////
//
//  anychar_parser <--> chset free operators
//
//      Where a is chset and b is a anychar_parser, and vice-versa, implements:
//
//          a | b, a & b, a - b, a ^ b
//
///////////////////////////////////////////////////////////////////////////////
template <typename CharT>
chset<CharT>
operator|(chset<CharT> const& a, anychar_parser b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator&(chset<CharT> const& a, anychar_parser b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator-(chset<CharT> const& a, anychar_parser b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator^(chset<CharT> const& a, anychar_parser b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator|(anychar_parser a, chset<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator&(anychar_parser a, chset<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator-(anychar_parser a, chset<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator^(anychar_parser a, chset<CharT> const& b);

///////////////////////////////////////////////////////////////////////////////
//
//  nothing_parser <--> chset free operators
//
//      Where a is chset and b is nothing_parser, and vice-versa, implements:
//
//          a | b, a & b, a - b, a ^ b
//
///////////////////////////////////////////////////////////////////////////////
template <typename CharT>
chset<CharT>
operator|(chset<CharT> const& a, nothing_parser b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator&(chset<CharT> const& a, nothing_parser b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator-(chset<CharT> const& a, nothing_parser b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator^(chset<CharT> const& a, nothing_parser b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator|(nothing_parser a, chset<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator&(nothing_parser a, chset<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator-(nothing_parser a, chset<CharT> const& b);

//////////////////////////////////
template <typename CharT>
chset<CharT>
operator^(nothing_parser a, chset<CharT> const& b);

///////////////////////////////////////////////////////////////////////////////
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

#include <boost/spirit/home/classic/utility/impl/chset_operators.ipp>

/* chset_operators.hpp
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
*/