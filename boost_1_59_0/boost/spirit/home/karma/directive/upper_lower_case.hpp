//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c) 2001-2011 Joel de Guzman
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SPIRIT_KARMA_DIRECTIVE_UPPER_LOWER_CASE_HPP
#define BOOST_SPIRIT_KARMA_DIRECTIVE_UPPER_LOWER_CASE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/modify.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/meta_compiler.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharEncoding>
    struct use_directive<
        karma::domain, tag::char_code<tag::upper, CharEncoding> > // enables upper
      : mpl::true_ {};

    template <typename CharEncoding>
    struct use_directive<
        karma::domain, tag::char_code<tag::lower, CharEncoding> > // enables lower
      : mpl::true_ {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename CharEncoding>
    struct is_modifier_directive<karma::domain
        , tag::char_code<tag::upper, CharEncoding> >
      : mpl::true_ {};

    template <typename CharEncoding>
    struct is_modifier_directive<karma::domain
        , tag::char_code<tag::lower, CharEncoding> >
      : mpl::true_ {};

    ///////////////////////////////////////////////////////////////////////////
    // Don't add tag::upper or tag::lower if there is already one of those in
    // the modifier list
    template <typename Current, typename CharEncoding>
    struct compound_modifier<
            Current
          , tag::char_code<tag::upper, CharEncoding>
          , typename enable_if<
                has_modifier<Current, tag::char_code<tag::lower, CharEncoding> > 
            >::type
          >
      : Current
    {
        compound_modifier()
          : Current() {}

        compound_modifier(Current const& current, 
                tag::char_code<tag::upper, CharEncoding> const&)
          : Current(current) {}
    };

    template <typename Current, typename CharEncoding>
    struct compound_modifier<
            Current
          , tag::char_code<tag::lower, CharEncoding>
          , typename enable_if<
                has_modifier<Current, tag::char_code<tag::upper, CharEncoding> > 
            >::type
          >
      : Current
    {
        compound_modifier()
          : Current() {}

        compound_modifier(Current const& current, 
                tag::char_code<tag::lower, CharEncoding> const&)
          : Current(current) {}
    };
}}

#endif

/* upper_lower_case.hpp
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
*/