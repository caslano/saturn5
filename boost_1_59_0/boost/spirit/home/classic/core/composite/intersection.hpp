/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    Copyright (c) 2001 Daniel Nuffer
    Copyright (c) 2002 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_INTERSECTION_HPP)
#define BOOST_SPIRIT_INTERSECTION_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/primitives/primitives.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include <boost/spirit/home/classic/meta/as_parser.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  intersection class
    //
    //      Handles expressions of the form:
    //
    //          a & b
    //
    //      where a and b are parsers. The expression returns a composite
    //      parser that matches a and b. One (not both) of the operands may
    //      be a literal char, wchar_t or a primitive string char const*,
    //      wchar_t const*.
    //
    //      The expression is short circuit evaluated. b is never touched
    //      when a is returns a no-match.
    //
    ///////////////////////////////////////////////////////////////////////////
    struct intersection_parser_gen;
    
    template <typename A, typename B>
    struct intersection
    :   public binary<A, B, parser<intersection<A, B> > >
    {
        typedef intersection<A, B>              self_t;
        typedef binary_parser_category          parser_category_t;
        typedef intersection_parser_gen         parser_generator_t;
        typedef binary<A, B, parser<self_t> >   base_t;
    
        intersection(A const& a, B const& b)
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
                ScannerT bscan(scan.first, scan.first, scan);
                scan.first = save;
                result_t hr = this->right().parse(bscan);
                if (hl.length() == hr.length())
                    return hl;
            }
    
            return scan.no_match();
        }
    };
    
    struct intersection_parser_gen
    {
        template <typename A, typename B>
        struct result 
        {
            typedef 
                intersection<
                    typename as_parser<A>::type
                  , typename as_parser<B>::type
                >
            type;
        };
    
        template <typename A, typename B>
        static intersection<
            typename as_parser<A>::type
          , typename as_parser<B>::type
        >
        generate(A const& a, B const& b)
        {
            return intersection<BOOST_DEDUCED_TYPENAME as_parser<A>::type,
                BOOST_DEDUCED_TYPENAME as_parser<B>::type>
                    (as_parser<A>::convert(a), as_parser<B>::convert(b));
        }
    };
    
    template <typename A, typename B>
    intersection<A, B>
    operator&(parser<A> const& a, parser<B> const& b);
    
    template <typename A>
    intersection<A, chlit<char> >
    operator&(parser<A> const& a, char b);
    
    template <typename B>
    intersection<chlit<char>, B>
    operator&(char a, parser<B> const& b);
    
    template <typename A>
    intersection<A, strlit<char const*> >
    operator&(parser<A> const& a, char const* b);
    
    template <typename B>
    intersection<strlit<char const*>, B>
    operator&(char const* a, parser<B> const& b);
    
    template <typename A>
    intersection<A, chlit<wchar_t> >
    operator&(parser<A> const& a, wchar_t b);
    
    template <typename B>
    intersection<chlit<wchar_t>, B>
    operator&(wchar_t a, parser<B> const& b);
    
    template <typename A>
    intersection<A, strlit<wchar_t const*> >
    operator&(parser<A> const& a, wchar_t const* b);
    
    template <typename B>
    intersection<strlit<wchar_t const*>, B>
    operator&(wchar_t const* a, parser<B> const& b);
    
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

#include <boost/spirit/home/classic/core/composite/impl/intersection.ipp>

/* intersection.hpp
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
*/