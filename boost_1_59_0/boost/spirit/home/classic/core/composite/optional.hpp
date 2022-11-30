/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    Copyright (c) 2001 Daniel Nuffer
    Copyright (c) 2002 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_OPTIONAL_HPP)
#define BOOST_SPIRIT_OPTIONAL_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/primitives/primitives.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include <boost/spirit/home/classic/meta/as_parser.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  optional class
    //
    //      Handles expressions of the form:
    //
    //          !a
    //
    //      where a is a parser. The expression returns a composite
    //      parser that matches its subject zero (0) or one (1) time.
    //
    ///////////////////////////////////////////////////////////////////////////
    struct optional_parser_gen;
    
    template <typename S>
    struct optional
    :   public unary<S, parser<optional<S> > >
    {
        typedef optional<S>                 self_t;
        typedef unary_parser_category       parser_category_t;
        typedef optional_parser_gen         parser_generator_t;
        typedef unary<S, parser<self_t> >   base_t;
    
        optional(S const& a)
        : base_t(a) {}
    
        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            typedef typename ScannerT::iterator_t iterator_t;
            iterator_t save = scan.first;
            if (result_t r = this->subject().parse(scan))
            {
                return r;
            }
            else
            {
                scan.first = save;
                return scan.empty_match();
            }
        }
    };
    
    struct optional_parser_gen
    {
        template <typename S>
        struct result 
        {
            typedef optional<S> type;
        };
    
        template <typename S>
        static optional<S>
        generate(parser<S> const& a)
        {
            return optional<S>(a.derived());
        }
    };
    
    template <typename S>
    optional<S>
    operator!(parser<S> const& a);

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

#include <boost/spirit/home/classic/core/composite/impl/optional.ipp>

/* optional.hpp
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
*/