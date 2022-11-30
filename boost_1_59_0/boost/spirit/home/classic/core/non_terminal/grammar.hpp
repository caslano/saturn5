/*=============================================================================
    Copyright (c) 2001-2003 Joel de Guzman
    Copyright (c) 2002-2003 Martin Wille
    Copyright (c) 2003 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_GRAMMAR_HPP)
#define BOOST_SPIRIT_GRAMMAR_HPP

///////////////////////////////////////////////////////////////////////////////
#if defined(BOOST_SPIRIT_THREADSAFE) && defined(BOOST_SPIRIT_SINGLE_GRAMMAR_INSTANCE)
#undef BOOST_SPIRIT_SINGLE_GRAMMAR_INSTANCE
#endif

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/non_terminal/parser_context.hpp>
#include <boost/spirit/home/classic/core/non_terminal/impl/grammar.ipp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
//
//  grammar class
//
///////////////////////////////////////////////////////////////////////////////
template <typename DerivedT, typename ContextT = parser_context<> >
struct grammar
    : public parser<DerivedT>
    , public ContextT::base_t
    , public context_aux<ContextT, DerivedT>
    BOOST_SPIRIT_GRAMMAR_ID
{
    typedef grammar<DerivedT, ContextT>         self_t;
    typedef DerivedT const&                     embed_t;
    typedef typename ContextT::context_linker_t context_t;
    typedef typename context_t::attr_t          attr_t;

    template <typename ScannerT>
    struct result
    {
        typedef typename match_result<ScannerT, attr_t>::type type;
    };

    grammar() {}
    ~grammar() { impl::grammar_destruct(this); }

    template <typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
    parse_main(ScannerT const& scan) const
    { return impl::grammar_parser_parse<0>(this, scan); }

    template <typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
    parse(ScannerT const& scan) const
    {
        typedef typename parser_result<self_t, ScannerT>::type result_t;
        typedef parser_scanner_linker<ScannerT> scanner_t;
        BOOST_SPIRIT_CONTEXT_PARSE(scan, *this, scanner_t, context_t, result_t)
    }

    template <int N>
    impl::entry_grammar<DerivedT, N, ContextT>
    use_parser() const
    { return impl::entry_grammar<DerivedT, N, ContextT>( this->derived()); }

    BOOST_SPIRIT_GRAMMAR_STATE
};

///////////////////////////////////////////////////////////////////////////////
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#undef BOOST_SPIRIT_GRAMMAR_ID
#undef BOOST_SPIRIT_GRAMMAR_STATE
#endif


/* grammar.hpp
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
*/