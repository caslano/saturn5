/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_ACCESS_SPECIFIER_HPP
#define BOOST_MULTI_INDEX_DETAIL_ACCESS_SPECIFIER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

/* In those compilers that do not accept the member template friend syntax,
 * some protected and private sections might need to be specified as
 * public.
 */

#if defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)
#define BOOST_MULTI_INDEX_PROTECTED_IF_MEMBER_TEMPLATE_FRIENDS public
#define BOOST_MULTI_INDEX_PRIVATE_IF_MEMBER_TEMPLATE_FRIENDS public
#else
#define BOOST_MULTI_INDEX_PROTECTED_IF_MEMBER_TEMPLATE_FRIENDS protected
#define BOOST_MULTI_INDEX_PRIVATE_IF_MEMBER_TEMPLATE_FRIENDS private
#endif

/* GCC does not correctly support in-class using declarations for template
 * functions. See http://gcc.gnu.org/bugzilla/show_bug.cgi?id=9810
 * MSVC 7.1/8.0 seem to have a similar problem, though the conditions in
 * which the error happens are not that simple. I have yet to isolate this
 * into a snippet suitable for bug reporting.
 * Sun Studio also has this problem, which might be related, from the
 * information gathered at Sun forums, with a known issue notified at the
 * internal bug report 6421933. The bug is present up to Studio Express 2,
 * the latest preview version of the future Sun Studio 12. As of this writing
 * (October 2006) it is not known whether a fix will finally make it into the
 * official Sun Studio 12.
 */

#if BOOST_WORKAROUND(__GNUC__,==3)&&(__GNUC_MINOR__<4)||\
    BOOST_WORKAROUND(BOOST_MSVC,==1310)||\
    BOOST_WORKAROUND(BOOST_MSVC,==1400)||\
    BOOST_WORKAROUND(__SUNPRO_CC,BOOST_TESTED_AT(0x590))
#define BOOST_MULTI_INDEX_PRIVATE_IF_USING_DECL_FOR_TEMPL_FUNCTIONS public
#else
#define BOOST_MULTI_INDEX_PRIVATE_IF_USING_DECL_FOR_TEMPL_FUNCTIONS private
#endif

#endif

/* access_specifier.hpp
KtZ+JPyX6Jkr4RmTbJhebNgORxYH+wbZCyeeRyeoDvCBtY+cx7IJhwRu8dacUyjsEjASwjbMtxmusKqjbXFTc+SaxubIEJhm1QqRapi2cr6Wl2GlGMOsRlu5Z4iWUP1vhTfdSG1C+urDAkqajGR01Z/nQEBdib9wzTKJN8iXTSanbMfkEPklhSFs6j+N3D0UDw8NjmihzT/NY2QJKuQsz0SCtHpHpJHCeM2OSC2FccCx8A3NacBbTEKQPShz8d2ZwZ4Ci+exp8AfNBrUd4a570xz3+31vn+Z34q+bxV9v270/cd2U99/bTf1Pet1re/nW9P3kSLsmyukUpBiZVGQ1bVx+WiRUaj2x7DGRsHvR2Pe6tw8K3K+cfznoTxTbjwQlho50m8eHeRIT6I4UkckHl7/oCpSbx2I0LajW+YhRykYE5cjdtf73kJEGolRslgIWlTO2sfFoBEVMuFZ2NIX05Zfthm2/u2GvawQ2oh8uH6sGAH9Oy34i/lYhYsZhSgmiADQPco+7LbB6rtOr71convdAW48U2gqtGIv3AOb19rKcH5bD/waIE7OAnY2tuTdgHlybgvnLXBqMeWDurxpx/bC6dhPbjjt7JXC+jALwNjfQhkNRHb1YXH9MW+BhHRl2TtWg7mtFMytXDA39tz4vQD1baz25r3I1wUGPZ4ebm5bUyAC3OzF48J1YZJ7TtPJRETtanbMI03Lck3T
*/