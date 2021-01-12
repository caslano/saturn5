/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_TUPLE_FORWARD_14122014_0051
#define FUSION_TUPLE_FORWARD_14122014_0051

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

#if  !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR) \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_TUPLE)
#   undef BOOST_FUSION_HAS_VARIADIC_TUPLE
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_TUPLE)
#   define BOOST_FUSION_HAS_VARIADIC_TUPLE
# endif
#endif

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_TUPLE)
# include <boost/fusion/tuple/detail/tuple_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion
{
    template <typename ...T>
    struct tuple;
}}

#endif
#endif


/* tuple_fwd.hpp
dm6k+Wu9LIVqs8lJ7431zohx1jyJ3AU8we5M+OK1Uf0YySF7/Q0l7LMnIsn6OqffK9818p3qro1w1O6Ly3ctfMdX+vn4wUR2j75OlzukciiVSNQmtVNR4ywinU2z5BA9Z6mzah7IoUdsoOYcugc4Khdb9LSXanq2SLyKtNuNfJxtBGMIsMb0auX5gn7Djj7djoTVjmv4foj2u7HeW3uIQ2paQDtKo1uG0Z2tddIX42hNbH51
*/