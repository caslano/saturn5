/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    Copyright (c) 2001 Daniel Nuffer
    Copyright (c) 2002 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_LIST_HPP)
#define BOOST_SPIRIT_LIST_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/primitives/primitives.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include <boost/spirit/home/classic/meta/as_parser.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  operator% is defined as:
    //  a % b ---> a >> *(b >> a)
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename A, typename B>
    sequence<A, kleene_star<sequence<B, A> > >
    operator%(parser<A> const& a, parser<B> const& b);
    
    template <typename A>
    sequence<A, kleene_star<sequence<chlit<char>, A> > >
    operator%(parser<A> const& a, char b);
    
    template <typename B>
    sequence<chlit<char>, kleene_star<sequence<B, chlit<char> > > >
    operator%(char a, parser<B> const& b);
    
    template <typename A>
    sequence<A, kleene_star<sequence<strlit<char const*>, A> > >
    operator%(parser<A> const& a, char const* b);
    
    template <typename B>
    sequence<strlit<char const*>,
        kleene_star<sequence<B, strlit<char const*> > > >
    operator%(char const* a, parser<B> const& b);
    
    template <typename A>
    sequence<A, kleene_star<sequence<chlit<wchar_t>, A> > >
    operator%(parser<A> const& a, wchar_t b);
    
    template <typename B>
    sequence<chlit<wchar_t>, kleene_star<sequence<B, chlit<wchar_t> > > >
    operator%(wchar_t a, parser<B> const& b);
    
    template <typename A>
    sequence<A, kleene_star<sequence<strlit<wchar_t const*>, A> > >
    operator%(parser<A> const& a, wchar_t const* b);
    
    template <typename B>
    sequence<strlit<wchar_t const*>,
        kleene_star<sequence<B, strlit<wchar_t const*> > > >
    operator%(wchar_t const* a, parser<B> const& b);

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

#include <boost/spirit/home/classic/core/composite/impl/list.ipp>

/* list.hpp
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
*/