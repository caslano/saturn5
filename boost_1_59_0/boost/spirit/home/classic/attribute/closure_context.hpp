/*=============================================================================
    Copyright (c) 2002-2003 Joel de Guzman
    Copyright (c) 2002-2003 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_CLOSURE_CONTEXT_HPP)
#define BOOST_SPIRIT_CLOSURE_CONTEXT_HPP

#include <boost/spirit/home/classic/namespace.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

#if !defined(BOOST_SPIRIT_CLOSURE_CONTEXT_LINKER_DEFINED)
#define BOOST_SPIRIT_CLOSURE_CONTEXT_LINKER_DEFINED

///////////////////////////////////////////////////////////////////////////////
//
//  closure_context_linker
//  { helper template for the closure extendability }
//
//      This classes can be 'overloaded' (defined elsewhere), to plug
//      in additional functionality into the closure parsing process.
//
///////////////////////////////////////////////////////////////////////////////

template<typename ContextT>
struct closure_context_linker : public ContextT
{
    template <typename ParserT>
    closure_context_linker(ParserT const& p)
    : ContextT(p) {}

    template <typename ParserT, typename ScannerT>
    void pre_parse(ParserT const& p, ScannerT const& scan)
    { ContextT::pre_parse(p, scan); }

    template <typename ResultT, typename ParserT, typename ScannerT>
    ResultT&
    post_parse(ResultT& hit, ParserT const& p, ScannerT const& scan)
    { return ContextT::post_parse(hit, p, scan); }
};

#endif // !defined(BOOST_SPIRIT_CLOSURE_CONTEXT_LINKER_DEFINED)

///////////////////////////////////////////////////////////////////////////////
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif // BOOST_SPIRIT_CLOSURE_CONTEXT_HPP

/* closure_context.hpp
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
*/