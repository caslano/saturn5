/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    Copyright (c) 2001 Daniel Nuffer
    Copyright (c) 2002 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_SEQUENCE_HPP)
#define BOOST_SPIRIT_SEQUENCE_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/primitives/primitives.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include <boost/spirit/home/classic/meta/as_parser.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  sequence class
    //
    //      Handles expressions of the form:
    //
    //          a >> b
    //
    //      where a and b are parsers. The expression returns a composite
    //      parser that matches a and b in sequence. One (not both) of the
    //      operands may be a literal char, wchar_t or a primitive string
    //      char const*, wchar_t const*.
    //
    //////////////////////////////////////////////////////////////////////////
    struct sequence_parser_gen;
    
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

    template <typename A, typename B>
    struct sequence : public binary<A, B, parser<sequence<A, B> > >
    {
        typedef sequence<A, B>                  self_t;
        typedef binary_parser_category          parser_category_t;
        typedef sequence_parser_gen             parser_generator_t;
        typedef binary<A, B, parser<self_t> >   base_t;
    
        sequence(A const& a, B const& b)
        : base_t(a, b) {}
    
        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            if (result_t ma = this->left().parse(scan))
                if (result_t mb = this->right().parse(scan))
                {
                    scan.concat_match(ma, mb);
                    return ma;
                }
            return scan.no_match();
        }
    };

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif
    
    struct sequence_parser_gen
    {
        template <typename A, typename B>
        struct result 
        {
            typedef
                sequence<
                    typename as_parser<A>::type
                  , typename as_parser<B>::type
                >
            type;
        };
    
        template <typename A, typename B>
        static sequence<
            typename as_parser<A>::type
          , typename as_parser<B>::type
        >
        generate(A const& a, B const& b)
        {
            return sequence<BOOST_DEDUCED_TYPENAME as_parser<A>::type,
                BOOST_DEDUCED_TYPENAME as_parser<B>::type>
                    (as_parser<A>::convert(a), as_parser<B>::convert(b));
        }
    };
    
    template <typename A, typename B>
    sequence<A, B>
    operator>>(parser<A> const& a, parser<B> const& b);
    
    template <typename A>
    sequence<A, chlit<char> >
    operator>>(parser<A> const& a, char b);
    
    template <typename B>
    sequence<chlit<char>, B>
    operator>>(char a, parser<B> const& b);
    
    template <typename A>
    sequence<A, strlit<char const*> >
    operator>>(parser<A> const& a, char const* b);
    
    template <typename B>
    sequence<strlit<char const*>, B>
    operator>>(char const* a, parser<B> const& b);
    
    template <typename A>
    sequence<A, chlit<wchar_t> >
    operator>>(parser<A> const& a, wchar_t b);
    
    template <typename B>
    sequence<chlit<wchar_t>, B>
    operator>>(wchar_t a, parser<B> const& b);
    
    template <typename A>
    sequence<A, strlit<wchar_t const*> >
    operator>>(parser<A> const& a, wchar_t const* b);
    
    template <typename B>
    sequence<strlit<wchar_t const*>, B>
    operator>>(wchar_t const* a, parser<B> const& b);
    
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

#include <boost/spirit/home/classic/core/composite/impl/sequence.ipp>

/* sequence.hpp
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
*/