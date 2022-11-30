//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_DEFAULT_WIDTH_APR_07_2009_0912PM)
#define BOOST_SPIRIT_KARMA_DEFAULT_WIDTH_APR_07_2009_0912PM

#if defined(_MSC_VER)
#pragma once
#endif

///////////////////////////////////////////////////////////////////////////////
//
//  The BOOST_KARMA_DEFAULT_FIELD_LENGTH specifies the default field length
//  to be used for padding.
//
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_KARMA_DEFAULT_FIELD_LENGTH)
#define BOOST_KARMA_DEFAULT_FIELD_LENGTH 10
#endif

///////////////////////////////////////////////////////////////////////////////
//
//  The BOOST_KARMA_DEFAULT_FIELD_MAXWIDTH specifies the default maximal field 
//  length to be used for the maxwidth directive.
//
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_KARMA_DEFAULT_FIELD_MAXWIDTH)
#define BOOST_KARMA_DEFAULT_FIELD_MAXWIDTH 10
#endif

///////////////////////////////////////////////////////////////////////////////
//
//  The BOOST_KARMA_DEFAULT_COLUMNS specifies the default number of columns to
//  be used with the columns directive.
//
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_KARMA_DEFAULT_COLUMNS)
#define BOOST_KARMA_DEFAULT_COLUMNS 5
#endif

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////
    struct default_width
    {
        operator int() const
        {
            return BOOST_KARMA_DEFAULT_FIELD_LENGTH;
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    struct default_max_width
    {
        operator int() const
        {
            return BOOST_KARMA_DEFAULT_FIELD_MAXWIDTH;
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    struct default_columns
    {
        operator int() const
        {
            return BOOST_KARMA_DEFAULT_COLUMNS;
        }
    };

}}}}

#endif

/* default_width.hpp
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
*/