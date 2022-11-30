/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    Copyright (c) 2001 Daniel Nuffer
    Copyright (c) 2002 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_DIFFERENCE_HPP)
#define BOOST_SPIRIT_DIFFERENCE_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/primitives/primitives.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include <boost/spirit/home/classic/meta/as_parser.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  difference: a - b; Matches a but not b
    //
    //      Handles expressions of the form:
    //
    //          a - b
    //
    //      where a and b are parsers. The expression returns a composite
    //      parser that matches a but not b. One (not both) of the operands
    //      may be a literal char, wchar_t or a primitive string char const*,
    //      wchar_t const*.
    //
    ///////////////////////////////////////////////////////////////////////////
    struct difference_parser_gen;

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

    template <typename A, typename B>
    struct difference
    :   public binary<A, B, parser<difference<A, B> > >
    {
        typedef difference<A, B>                self_t;
        typedef binary_parser_category          parser_category_t;
        typedef difference_parser_gen           parser_generator_t;
        typedef binary<A, B, parser<self_t> >   base_t;
    
        difference(A const& a, B const& b)
        : base_t(a, b) {}
    
        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            typedef typename ScannerT::iterator_t iterator_t;
            iterator_t save = scan.first;
            if (result_t hl = this->left().parse(scan))
            {
                std::swap(save, scan.first);
                result_t hr = this->right().parse(scan);
                if (!hr || (hr.length() < hl.length()))
                {
                    scan.first = save;
                    return hl;
                }
            }
    
            return scan.no_match();
        }
    };

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif
    
    struct difference_parser_gen
    {
        template <typename A, typename B>
        struct result 
        {
            typedef 
                difference<
                    typename as_parser<A>::type
                  , typename as_parser<B>::type
                > 
            type;
        };
    
        template <typename A, typename B>
        static difference<
            typename as_parser<A>::type
          , typename as_parser<B>::type
        >
        generate(A const& a, B const& b)
        {
            return difference<BOOST_DEDUCED_TYPENAME as_parser<A>::type,
                BOOST_DEDUCED_TYPENAME as_parser<B>::type>
                    (as_parser<A>::convert(a), as_parser<B>::convert(b));
        }
    };
    
    template <typename A, typename B>
    difference<A, B>
    operator-(parser<A> const& a, parser<B> const& b);
    
    template <typename A>
    difference<A, chlit<char> >
    operator-(parser<A> const& a, char b);
    
    template <typename B>
    difference<chlit<char>, B>
    operator-(char a, parser<B> const& b);
    
    template <typename A>
    difference<A, strlit<char const*> >
    operator-(parser<A> const& a, char const* b);
    
    template <typename B>
    difference<strlit<char const*>, B>
    operator-(char const* a, parser<B> const& b);
    
    template <typename A>
    difference<A, chlit<wchar_t> >
    operator-(parser<A> const& a, wchar_t b);
    
    template <typename B>
    difference<chlit<wchar_t>, B>
    operator-(wchar_t a, parser<B> const& b);
    
    template <typename A>
    difference<A, strlit<wchar_t const*> >
    operator-(parser<A> const& a, wchar_t const* b);
    
    template <typename B>
    difference<strlit<wchar_t const*>, B>
    operator-(wchar_t const* a, parser<B> const& b);

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

#include <boost/spirit/home/classic/core/composite/impl/difference.ipp>

/* difference.hpp
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
*/