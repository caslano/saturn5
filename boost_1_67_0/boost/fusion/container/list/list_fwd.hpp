/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_LIST_FORWARD_10262014_0528
#define FUSION_LIST_FORWARD_10262014_0528

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>

#if  defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_LIST)
#   undef BOOST_FUSION_HAS_VARIADIC_LIST
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_LIST)
#   define BOOST_FUSION_HAS_VARIADIC_LIST
# endif
#endif

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_LIST)
# include <boost/fusion/container/list/detail/cpp03/list_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion
{
    struct void_;

    template <typename ...T>
    struct list;
}}

#endif
#endif

/* list_fwd.hpp
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
*/