//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_CREATE_NOV_21_2009_0340PM)
#define BOOST_SPIRIT_KARMA_CREATE_NOV_21_2009_0340PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/auto/meta_create.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace result_of
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct create_generator
      : spirit::traits::meta_create<karma::domain, T> {};
}}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
    // Main API function for generator creation from data type
    template <typename T>
    typename result_of::create_generator<T>::type
    create_generator()
    {
        return spirit::traits::meta_create<karma::domain, T>::call();
    }
}}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace traits
{
    // Meta function returning true if create_generator does return a valid
    // generator for the given type T.
    template <typename T>
    struct create_generator_exists
      : meta_create_exists<karma::domain, T> {};
}}}

#endif

/* create_generator.hpp
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
*/