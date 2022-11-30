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
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
*/