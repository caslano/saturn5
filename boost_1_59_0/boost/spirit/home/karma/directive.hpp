//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_DIRECTIVE_FEB_21_2007_0833PM)
#define BOOST_SPIRIT_KARMA_DIRECTIVE_FEB_21_2007_0833PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/directive/encoding.hpp>

///////////////////////////////////////////////////////////////////////////////
//  directives related to alignment 
//  left_align[...], right_align[...], center[...]
///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/karma/directive/left_alignment.hpp>
#include <boost/spirit/home/karma/directive/right_alignment.hpp>
#include <boost/spirit/home/karma/directive/center_alignment.hpp>

///////////////////////////////////////////////////////////////////////////////
//  directives related to truncating length
//  maxwidth[...], columns[]
///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/karma/directive/maxwidth.hpp>
#include <boost/spirit/home/karma/directive/columns.hpp>

///////////////////////////////////////////////////////////////////////////////
//  directives related to character case
//  lower[...] and upper[...]
///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/karma/directive/upper_lower_case.hpp>

///////////////////////////////////////////////////////////////////////////////
//  directives related to delimiting generators 
//  delimit[...] and verbatim[...]
///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/karma/directive/verbatim.hpp>
#include <boost/spirit/home/karma/directive/delimit.hpp>
#include <boost/spirit/home/karma/directive/no_delimit.hpp>

///////////////////////////////////////////////////////////////////////////////
//  repeat directives
//  repeat[...]
///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/karma/directive/repeat.hpp>

///////////////////////////////////////////////////////////////////////////////
//  omit, skip, and duplicate directives
//  omit[...], skip[...], duplicate[...]
///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/karma/directive/omit.hpp>
#include <boost/spirit/home/karma/directive/duplicate.hpp>

///////////////////////////////////////////////////////////////////////////////
//  buffer directive
//  buffer[...]
///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/karma/directive/buffer.hpp>

///////////////////////////////////////////////////////////////////////////////
//  strict and relaxed directives
//  strict[...], relaxed[...]
///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/karma/directive/strict_relaxed.hpp>

///////////////////////////////////////////////////////////////////////////////
//  as_string and as_wstring directives
//  as_string[...], as_wstring[...]
///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/karma/directive/as.hpp>

#endif

/* directive.hpp
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
*/