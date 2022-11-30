/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEQUE_FORWARD_02092007_0749)
#define FUSION_DEQUE_FORWARD_02092007_0749

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>

#if (defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)   \
  || defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS))   \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#   undef BOOST_FUSION_HAS_VARIADIC_DEQUE
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#   define BOOST_FUSION_HAS_VARIADIC_DEQUE
# endif
#endif

#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)
# if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#   undef BOOST_FUSION_HAS_VARIADIC_DEQUE
# endif
#endif

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
# include <boost/fusion/container/deque/detail/cpp03/deque_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion
{
    template <typename ...T>
    struct deque;
}}

#endif
#endif

/* deque_fwd.hpp
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
*/