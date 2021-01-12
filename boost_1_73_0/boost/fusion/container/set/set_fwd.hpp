/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_SET_FORWARD_11062014_1720
#define FUSION_SET_FORWARD_11062014_1720

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR) \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_SET)
#   undef BOOST_FUSION_HAS_VARIADIC_SET
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_SET)
#   define BOOST_FUSION_HAS_VARIADIC_SET
# endif
#endif

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_SET)
# include <boost/fusion/container/set/detail/cpp03/set_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion
{
    struct set_tag;
    struct set_iterator_tag;

    template <typename ...T>
    struct set;
}}

#endif
#endif


/* set_fwd.hpp
eZPoG9O2ROaMlJblz6gqwMl7bDuSP9NGUwOmV3jIwstvBapJvd8L1a9rHt2hx6SzVB6km7ybdGsZ0XctTZ++k6mbpENk1UllVa17hGS65nHlcsO2qqwc5dGIqt5y2hrJu/EvmyZ4ycn4NfPU/g15F3fnmv+nelAfaOC4V/m3//X+5ddNGXJtn0Xdv+j78RE9qG49qGMtDn0GboLTMUX6+1w/dv29i9/l+vsDfs/W3/Mw0/T3
*/