/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    Copyright (c) 2001 Daniel Nuffer
    Copyright (c) 2002 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_SEQUENTIAL_OR_HPP)
#define BOOST_SPIRIT_SEQUENTIAL_OR_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/primitives/primitives.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include <boost/spirit/home/classic/meta/as_parser.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  sequential-or class
    //
    //      Handles expressions of the form:
    //
    //          a || b
    //
    //      Equivalent to
    //
    //          a | b | a >> b;
    //
    //      where a and b are parsers. The expression returns a composite
    //      parser that matches matches a or b in sequence. One (not both) of
    //      the operands may be a literal char, wchar_t or a primitive string
    //      char const*, wchar_t const*.
    //
    ///////////////////////////////////////////////////////////////////////////
    struct sequential_or_parser_gen;
    
    template <typename A, typename B>
    struct sequential_or : public binary<A, B, parser<sequential_or<A, B> > >
    {
        typedef sequential_or<A, B>             self_t;
        typedef binary_parser_category          parser_category_t;
        typedef sequential_or_parser_gen        parser_generator_t;
        typedef binary<A, B, parser<self_t> >   base_t;
    
        sequential_or(A const& a, B const& b)
        : base_t(a, b) {}
    
        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            typedef typename ScannerT::iterator_t iterator_t;
            { // scope for save
                iterator_t save = scan.first;
                if (result_t ma = this->left().parse(scan))
                {
                    save = scan.first;
                    if (result_t mb = this->right().parse(scan))
                    {
                        // matched a b
                        scan.concat_match(ma, mb);
                        return ma;
                    }
                    else
                    {
                        // matched a
                        scan.first = save;
                        return ma;
                    }
                }
                scan.first = save;
            }
    
            // matched b
            return this->right().parse(scan);
        }
    };
    
    struct sequential_or_parser_gen
    {
        template <typename A, typename B>
        struct result 
        {
            typedef 
                sequential_or<
                    typename as_parser<A>::type
                  , typename as_parser<B>::type
                > 
            type;
        };
    
        template <typename A, typename B>
        static sequential_or<
            typename as_parser<A>::type
          , typename as_parser<B>::type
        >
        generate(A const& a, B const& b)
        {
            return sequential_or<BOOST_DEDUCED_TYPENAME as_parser<A>::type,
                BOOST_DEDUCED_TYPENAME as_parser<B>::type>
                    (as_parser<A>::convert(a), as_parser<B>::convert(b));
        }
    };
    
    template <typename A, typename B>
    sequential_or<A, B>
    operator||(parser<A> const& a, parser<B> const& b);
    
    template <typename A>
    sequential_or<A, chlit<char> >
    operator||(parser<A> const& a, char b);
    
    template <typename B>
    sequential_or<chlit<char>, B>
    operator||(char a, parser<B> const& b);
    
    template <typename A>
    sequential_or<A, strlit<char const*> >
    operator||(parser<A> const& a, char const* b);
    
    template <typename B>
    sequential_or<strlit<char const*>, B>
    operator||(char const* a, parser<B> const& b);

    template <typename A>
    sequential_or<A, chlit<wchar_t> >
    operator||(parser<A> const& a, wchar_t b);
    
    template <typename B>
    sequential_or<chlit<wchar_t>, B>
    operator||(wchar_t a, parser<B> const& b);
    
    template <typename A>
    sequential_or<A, strlit<wchar_t const*> >
    operator||(parser<A> const& a, wchar_t const* b);
    
    template <typename B>
    sequential_or<strlit<wchar_t const*>, B>
    operator||(wchar_t const* a, parser<B> const& b);

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

#include <boost/spirit/home/classic/core/composite/impl/sequential_or.ipp>

/* sequential_or.hpp
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
*/