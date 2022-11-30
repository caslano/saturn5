//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_BOOL_UTILS_SEP_28_2009_0644PM)
#define BOOST_SPIRIT_KARMA_BOOL_UTILS_SEP_28_2009_0644PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/char_class.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/karma/detail/generate_to.hpp>
#include <boost/spirit/home/karma/detail/string_generate.hpp>
#include <boost/spirit/home/karma/numeric/detail/numeric_utils.hpp>
#include <boost/detail/workaround.hpp>

namespace boost { namespace spirit { namespace karma 
{ 
    ///////////////////////////////////////////////////////////////////////////
    //
    //  The bool_inserter template takes care of the boolean to string 
    //  conversion. The Policies template parameter is used to allow
    //  customization of the formatting process
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct bool_policies;

    template <typename T
      , typename Policies = bool_policies<T>
      , typename CharEncoding = unused_type
      , typename Tag = unused_type>
    struct bool_inserter
    {
        template <typename OutputIterator, typename U>
        static bool
        call (OutputIterator& sink, U b, Policies const& p = Policies())
        {
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1600))
            (void)p; // suppresses warning: C4100: 'p' : unreferenced formal parameter
#endif
            return p.template call<bool_inserter>(sink, T(b), p);
        }

        ///////////////////////////////////////////////////////////////////////
        //  This is the workhorse behind the real generator
        ///////////////////////////////////////////////////////////////////////
        template <typename OutputIterator, typename U>
        static bool
        call_n (OutputIterator& sink, U b, Policies const& p)
        {
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1600))
            (void)p; // suppresses warning: C4100: 'p' : unreferenced formal parameter
#endif
            if (b) 
                return p.template generate_true<CharEncoding, Tag>(sink, b);
            return p.template generate_false<CharEncoding, Tag>(sink, b);
        }
    };

}}}

#endif


/* bool_utils.hpp
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
*/