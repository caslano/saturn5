//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_DETAIL_GENERATE_TO_FEB_20_2007_0417PM)
#define BOOST_SPIRIT_KARMA_DETAIL_GENERATE_TO_FEB_20_2007_0417PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/char_class.hpp>
#include <boost/spirit/home/karma/detail/output_iterator.hpp>

namespace boost { namespace spirit { namespace karma { namespace detail 
{
    ///////////////////////////////////////////////////////////////////////////
    //  These utility functions insert the given parameter into the supplied 
    //  output iterator.
    //  If the attribute is spirit's unused_type, this is a no_op.
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename OutputIterator, typename Attribute, typename CharEncoding
      , typename Tag>
    inline bool 
    generate_to(OutputIterator& sink, Attribute const& p, CharEncoding, Tag)
    {
        *sink = spirit::char_class::convert<CharEncoding>::to(Tag(), p);
        ++sink;
        return detail::sink_is_good(sink);
    }

    template <typename OutputIterator, typename Attribute>
    inline bool 
    generate_to(OutputIterator& sink, Attribute const& p, unused_type, unused_type)
    {
        *sink = p;
        ++sink;
        return detail::sink_is_good(sink);
    }

    template <typename OutputIterator, typename CharEncoding, typename Tag>
    inline bool generate_to(OutputIterator&, unused_type, CharEncoding, Tag)
    {
        return true;
    }

    template <typename OutputIterator, typename Attribute>
    inline bool 
    generate_to(OutputIterator& sink, Attribute const& p)
    {
        *sink = p;
        ++sink;
        return detail::sink_is_good(sink);
    }

    template <typename OutputIterator>
    inline bool generate_to(OutputIterator&, unused_type)
    {
        return true;
    }

}}}}   // namespace boost::spirit::karma::detail

#endif  // KARMA_CORE_DETAIL_INSERT_TO_HPP

/* generate_to.hpp
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
*/