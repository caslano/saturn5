//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_STRING_COMPARE_AUG_08_2009_0756PM)
#define BOOST_SPIRIT_KARMA_STRING_COMPARE_AUG_08_2009_0756PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/char_class.hpp>
#include <boost/spirit/home/karma/detail/generate_to.hpp>

namespace boost { namespace spirit { namespace karma { namespace detail
{
    template <typename Char>
    bool string_compare(Char const* attr, Char const* lit)
    {
        Char ch_attr = *attr;
        Char ch_lit = *lit;

        while (!!ch_lit && !!ch_attr)
        {
            if (ch_attr != ch_lit)
                return false;

            ch_attr = *++attr;
            ch_lit = *++lit;
        }

        return !ch_lit && !ch_attr;
    }

    template <typename Char>
    bool string_compare(Char const* attr, Char const* lit, unused_type, unused_type)
    {
        return string_compare(attr, lit);
    }

    template <typename Char>
    bool string_compare(unused_type, Char const*, unused_type, unused_type)
    {
        return true;
    }

    template <typename Char, typename CharEncoding, typename Tag>
    bool string_compare(Char const* attr, Char const* lit, CharEncoding, Tag)
    {
        Char ch_attr = *attr;
        Char ch_lit = spirit::char_class::convert<CharEncoding>::to(Tag(), *lit);

        while (!!ch_lit && !!ch_attr)
        {
            if (ch_attr != ch_lit)
                return false;

            ch_attr = *++attr;
            ch_lit = spirit::char_class::convert<CharEncoding>::to(Tag(), *++lit);
        }

        return !ch_lit && !ch_attr;
    }

    template <typename Char, typename CharEncoding, typename Tag>
    bool string_compare(unused_type, Char const*, CharEncoding, Tag)
    {
        return true;
    }

}}}}

#endif

/* string_compare.hpp
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
*/