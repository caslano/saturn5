/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    Copyright (c) 2001 Daniel Nuffer
    Copyright (c) 2002 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_ALTERNATIVE_HPP)
#define BOOST_SPIRIT_ALTERNATIVE_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/primitives/primitives.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include <boost/spirit/home/classic/meta/as_parser.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  alternative class
    //
    //      Handles expressions of the form:
    //
    //          a | b
    //
    //      where a and b are parsers. The expression returns a composite
    //      parser that matches a or b. One (not both) of the operands may
    //      be a literal char, wchar_t or a primitive string char const*,
    //      wchar_t const*.
    //
    //      The expression is short circuit evaluated. b is never touched
    //      when a is returns a successful match.
    //
    ///////////////////////////////////////////////////////////////////////////
    struct alternative_parser_gen;
    
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

    template <typename A, typename B>
    struct alternative
    :   public binary<A, B, parser<alternative<A, B> > >
    {
        typedef alternative<A, B>               self_t;
        typedef binary_parser_category          parser_category_t;
        typedef alternative_parser_gen          parser_generator_t;
        typedef binary<A, B, parser<self_t> >   base_t;
    
        alternative(A const& a, B const& b)
        : base_t(a, b) {}
    
        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            typedef typename ScannerT::iterator_t iterator_t;
            { // scope for save
                iterator_t save = scan.first;
                if (result_t hit = this->left().parse(scan))
                    return hit;
                scan.first = save;
            }
            return this->right().parse(scan);
        }
    };

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif
    
    struct alternative_parser_gen
    {
        template <typename A, typename B>
        struct result 
        {
            typedef 
                alternative<
                    typename as_parser<A>::type
                  , typename as_parser<B>::type
                > 
            type;
        };
    
        template <typename A, typename B>
        static alternative<
            typename as_parser<A>::type
          , typename as_parser<B>::type
        >
        generate(A const& a, B const& b)
        {
            return alternative<BOOST_DEDUCED_TYPENAME as_parser<A>::type,
                BOOST_DEDUCED_TYPENAME as_parser<B>::type>
                    (as_parser<A>::convert(a), as_parser<B>::convert(b));
        }
    };
    
    template <typename A, typename B>
    alternative<A, B>
    operator|(parser<A> const& a, parser<B> const& b);
    
    template <typename A>
    alternative<A, chlit<char> >
    operator|(parser<A> const& a, char b);
    
    template <typename B>
    alternative<chlit<char>, B>
    operator|(char a, parser<B> const& b);
    
    template <typename A>
    alternative<A, strlit<char const*> >
    operator|(parser<A> const& a, char const* b);
    
    template <typename B>
    alternative<strlit<char const*>, B>
    operator|(char const* a, parser<B> const& b);
    
    template <typename A>
    alternative<A, chlit<wchar_t> >
    operator|(parser<A> const& a, wchar_t b);
    
    template <typename B>
    alternative<chlit<wchar_t>, B>
    operator|(wchar_t a, parser<B> const& b);
    
    template <typename A>
    alternative<A, strlit<wchar_t const*> >
    operator|(parser<A> const& a, wchar_t const* b);
    
    template <typename B>
    alternative<strlit<wchar_t const*>, B>
    operator|(wchar_t const* a, parser<B> const& b);

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

#include <boost/spirit/home/classic/core/composite/impl/alternative.ipp>

/* alternative.hpp
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
*/