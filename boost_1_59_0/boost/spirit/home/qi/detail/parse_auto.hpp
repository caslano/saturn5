/*=============================================================================
    Copyright (c) 2001-2011 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_DETAIL_PARSE_AUTO_DEC_02_2009_0426PM)
#define BOOST_SPIRIT_DETAIL_PARSE_AUTO_DEC_02_2009_0426PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/qi/parse.hpp>
#include <boost/spirit/home/qi/auto/create_parser.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/and.hpp>

namespace boost { namespace spirit { namespace qi { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Expr>
    struct parse_impl<Expr
      , typename enable_if<
            mpl::and_<
                traits::meta_create_exists<qi::domain, Expr>
              , mpl::not_<traits::matches<qi::domain, Expr> > >
        >::type>
    {
        template <typename Iterator>
        static bool call(Iterator& first, Iterator last, Expr& expr)
        {
            return qi::parse(first, last, create_parser<Expr>(), expr);
        }

        template <typename Iterator>
        static bool call(Iterator& first, Iterator last, Expr const& expr)
        {
            return qi::parse(first, last, create_parser<Expr>()
              , const_cast<Expr&>(expr));
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename Expr>
    struct phrase_parse_impl<Expr
      , typename enable_if<
            mpl::and_<
                traits::meta_create_exists<qi::domain, Expr>
              , mpl::not_<traits::matches<qi::domain, Expr> > >
        >::type>
    {
        template <typename Iterator, typename Skipper>
        static bool call(Iterator& first, Iterator last, Expr& expr
          , Skipper const& skipper, BOOST_SCOPED_ENUM(skip_flag) post_skip)
        {
            return qi::phrase_parse(first, last, create_parser<Expr>()
              , skipper, post_skip, expr);
        }

        template <typename Iterator, typename Skipper>
        static bool call(Iterator& first, Iterator last, Expr const& expr
          , Skipper const& skipper, BOOST_SCOPED_ENUM(skip_flag) post_skip)
        {
            return qi::phrase_parse(first, last, create_parser<Expr>()
              , skipper, post_skip, const_cast<Expr&>(expr));
        }
    };
}}}}

namespace boost { namespace spirit { namespace qi
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Iterator, typename Expr>
    inline bool
    parse(
        Iterator& first
      , Iterator last
      , Expr& expr)
    {
        // Make sure the iterator is at least a forward_iterator. If you got a 
        // compilation error here, then you are using an input_iterator while
        // calling this function, you need to supply at least a 
        // forward_iterator instead.
        BOOST_CONCEPT_ASSERT((ForwardIterator<Iterator>));

        return detail::parse_impl<Expr>::call(first, last, expr);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Iterator, typename Expr, typename Skipper>
    inline bool
    phrase_parse(
        Iterator& first
      , Iterator last
      , Expr& expr
      , Skipper const& skipper
      , BOOST_SCOPED_ENUM(skip_flag) post_skip = skip_flag::postskip)
    {
        // Make sure the iterator is at least a forward_iterator. If you got a 
        // compilation error here, then you are using an input_iterator while
        // calling this function, you need to supply at least a 
        // forward_iterator instead.
        BOOST_CONCEPT_ASSERT((ForwardIterator<Iterator>));

        return detail::phrase_parse_impl<Expr>::call(
            first, last, expr, skipper, post_skip);
    }
}}}

#endif


/* parse_auto.hpp
+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
*/