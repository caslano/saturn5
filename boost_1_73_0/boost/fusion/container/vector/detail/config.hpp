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
h+mwBDaGC2AuLNd2pgw2V/1BuD+yXgcztX579l9Tfw/qOOMLmA6/ge2hGySfVD9I9WNU/wPVT1d9keqXwnh4GWwAN8Mw/C1MgTthNvwjbAJfgG3gK7AtfE31f1b9PpgJP1bzL9T8S9gKfqvmrivm+p7RtSY42f+eiZHblw+bwR4wD/aEPWAveDzsDU+AfeBEI08Qv11dX9H1o42Q6kv+aj6F6N/BxXAoXAJHwvPgVFgKf6j6
*/