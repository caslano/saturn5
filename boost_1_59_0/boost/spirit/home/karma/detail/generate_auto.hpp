//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_DETAIL_GENERATE_AUTO_DEC_01_2009_0743PM)
#define BOOST_SPIRIT_KARMA_DETAIL_GENERATE_AUTO_DEC_01_2009_0743PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/generate.hpp>
#include <boost/spirit/home/karma/auto/create_generator.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/and.hpp>

namespace boost { namespace spirit { namespace karma { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Expr>
    struct generate_impl<Expr
      , typename enable_if<
            mpl::and_<
                traits::meta_create_exists<karma::domain, Expr>
              , mpl::not_<traits::matches<karma::domain, Expr> > >
        >::type>
    {
        template <typename OutputIterator>
        static bool call(
            OutputIterator& sink
          , Expr const& expr)
        {
            return karma::generate(sink, create_generator<Expr>(), expr);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename Expr>
    struct generate_delimited_impl<Expr
      , typename enable_if<
            mpl::and_<
                traits::meta_create_exists<karma::domain, Expr>
              , mpl::not_<traits::matches<karma::domain, Expr> > >
        >::type>
    {
        template <typename OutputIterator, typename Delimiter>
        static bool call(
            OutputIterator& sink
          , Expr const& expr
          , Delimiter const& delimiter
          , BOOST_SCOPED_ENUM(delimit_flag) pre_delimit)
        {
            return karma::generate_delimited(
                sink, create_generator<Expr>(), delimiter, pre_delimit, expr);
        }
    };

}}}}

#endif


/* generate_auto.hpp
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
*/