/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    Copyright (c) 2001 Daniel Nuffer
    Copyright (c) 2002 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_POSITIVE_HPP)
#define BOOST_SPIRIT_POSITIVE_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/primitives/primitives.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include <boost/spirit/home/classic/meta/as_parser.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  positive class
    //
    //      Handles expressions of the form:
    //
    //          +a
    //
    //      where a is a parser. The expression returns a composite
    //      parser that matches its subject one (1) or more times.
    //
    ///////////////////////////////////////////////////////////////////////////
    struct positive_parser_gen;
    
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

    template <typename S>
    struct positive
    :   public unary<S, parser<positive<S> > >
    {
        typedef positive<S>                 self_t;
        typedef unary_parser_category       parser_category_t;
        typedef positive_parser_gen         parser_generator_t;
        typedef unary<S, parser<self_t> >   base_t;
    
        positive(S const& a)
        : base_t(a) {}
    
        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            typedef typename ScannerT::iterator_t iterator_t;
            result_t hit = this->subject().parse(scan);
    
            if (hit)
            {
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
                        break;
                    }
                }
            }
            return hit;
        }
    };

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif
    
    struct positive_parser_gen
    {
        template <typename S>
        struct result 
        {
            typedef positive<S> type;
        };
    
        template <typename S>
        static positive<S>
        generate(parser<S> const& a)
        {
            return positive<S>(a.derived());
        }
    };
    
    template <typename S>
    inline positive<S>
    operator+(parser<S> const& a);

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

#include <boost/spirit/home/classic/core/composite/impl/positive.ipp>

/* positive.hpp
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
*/