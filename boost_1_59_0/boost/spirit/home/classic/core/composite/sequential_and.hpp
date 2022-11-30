/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    Copyright (c) 2001 Daniel Nuffer
    Copyright (c) 2002 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_SEQUENTIAL_AND_HPP)
#define BOOST_SPIRIT_SEQUENTIAL_AND_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/primitives/primitives.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include <boost/spirit/home/classic/meta/as_parser.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  sequential-and operators
    //
    //      Handles expressions of the form:
    //
    //          a && b
    //
    //      Same as a >> b.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename A, typename B>
    sequence<A, B>
    operator&&(parser<A> const& a, parser<B> const& b);
    
    template <typename A>
    sequence<A, chlit<char> >
    operator&&(parser<A> const& a, char b);
    
    template <typename B>
    sequence<chlit<char>, B>
    operator&&(char a, parser<B> const& b);
    
    template <typename A>
    sequence<A, strlit<char const*> >
    operator&&(parser<A> const& a, char const* b);
    
    template <typename B>
    sequence<strlit<char const*>, B>
    operator&&(char const* a, parser<B> const& b);
    
    template <typename A>
    sequence<A, chlit<wchar_t> >
    operator&&(parser<A> const& a, wchar_t b);
    
    template <typename B>
    sequence<chlit<wchar_t>, B>
    operator&&(wchar_t a, parser<B> const& b);
    
    template <typename A>
    sequence<A, strlit<wchar_t const*> >
    operator&&(parser<A> const& a, wchar_t const* b);
    
    template <typename B>
    sequence<strlit<wchar_t const*>, B>
    operator&&(wchar_t const* a, parser<B> const& b);

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

#include <boost/spirit/home/classic/core/composite/impl/sequential_and.ipp>

/* sequential_and.hpp
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
*/