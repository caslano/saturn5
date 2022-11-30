/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    Copyright (c) 2001 Daniel Nuffer
    Copyright (c) 2002 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_KLEENE_STAR_HPP)
#define BOOST_SPIRIT_KLEENE_STAR_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/primitives/primitives.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include <boost/spirit/home/classic/meta/as_parser.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  kleene_star class
    //
    //      Handles expressions of the form:
    //
    //          *a
    //
    //      where a is a parser. The expression returns a composite
    //      parser that matches its subject zero (0) or more times.
    //
    ///////////////////////////////////////////////////////////////////////////
    struct kleene_star_parser_gen;
    
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

    template <typename S>
    struct kleene_star
    :   public unary<S, parser<kleene_star<S> > >
    {
        typedef kleene_star<S>              self_t;
        typedef unary_parser_category       parser_category_t;
        typedef kleene_star_parser_gen      parser_generator_t;
        typedef unary<S, parser<self_t> >   base_t;
    
        kleene_star(S const& a)
        : base_t(a) {}
    
        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            typedef typename ScannerT::iterator_t iterator_t;
            result_t hit = scan.empty_match();
    
            for (;;)
            {
                iterator_t save = scan.first;
                if (result_t next = this->subject().parse(scan))
                {
                    scan.concat_match(hit, next);
                }
                else
                {
                    scan.first = save;
                    return hit;
                }
            }
        }
    };
    
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

    struct kleene_star_parser_gen
    {
        template <typename S>
        struct result 
        {
            typedef kleene_star<S> type;
        };
    
        template <typename S>
        static kleene_star<S>
        generate(parser<S> const& a)
        {
            return kleene_star<S>(a.derived());
        }
    };
    
    //////////////////////////////////
    template <typename S>
    kleene_star<S>
    operator*(parser<S> const& a);

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

#include <boost/spirit/home/classic/core/composite/impl/kleene_star.ipp>

/* kleene_star.hpp
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
*/