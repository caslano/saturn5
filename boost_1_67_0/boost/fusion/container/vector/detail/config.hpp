/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR_CONFIG_11052014_1720
#define FUSION_VECTOR_CONFIG_11052014_1720

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/fusion/support/config.hpp>

#if (defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) \
  || defined(BOOST_NO_CXX11_RVALUE_REFERENCES) \
  || defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)  \
  || defined(BOOST_NO_CXX11_DECLTYPE)) \
  || defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS) \
  || defined(BOOST_FUSION_DISABLE_VARIADIC_VECTOR) \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   undef BOOST_FUSION_HAS_VARIADIC_VECTOR
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   define BOOST_FUSION_HAS_VARIADIC_VECTOR
# endif
#endif

#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)
# if defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   undef BOOST_FUSION_HAS_VARIADIC_VECTOR
# endif
#endif

#endif


/* config.hpp
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
*/