/*=============================================================================
    Copyright (c) 2002-2003 Joel de Guzman
    Copyright (c) 2002-2003 Juan Carlos Arevalo-Baeza
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_FUNCTOR_PARSER_HPP
#define BOOST_SPIRIT_FUNCTOR_PARSER_HPP

///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  functor_parser class
    //
    //      Once a functor parser has been defined, you can build a real
    //      parser from it by passing it to this class as the template
    //      parameter.
    //
    ///////////////////////////////////////////////////////////////////////////
    template < class FunctorT >
    struct functor_parser : public parser<functor_parser<FunctorT> >
    {
        FunctorT functor;

        functor_parser(): functor() {}
        functor_parser(FunctorT const& functor_): functor(functor_) {}

        typedef typename FunctorT::result_t functor_result_t;
        typedef functor_parser<FunctorT> self_t;

        template <typename ScannerT>
        struct result
        {
            typedef typename match_result<ScannerT, functor_result_t>::type
            type;
        };

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename ScannerT::iterator_t   iterator_t;

            iterator_t const s(scan.first);
            functor_result_t functor_result;
            std::ptrdiff_t len = functor(scan, functor_result);

            if (len < 0)
                return scan.no_match();
            else
                return scan.create_match(std::size_t(len), functor_result, s, scan.first);
        }
    };

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

/* functor_parser.hpp
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
*/