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
Q2g/8Cv74yIR1I/xnpJUUJrRMwouvu9m3JiXp+1BqISuUD8Wi4iJeFqjx0wXEBgXr1Z5b0+I3ku9Rqd5ea4N3J57tpS2n46S0vfP7i5t/5GhdydJDkrp30HukE+V0mVsZbwfJUjpv3t+l3wTbME75hRJ8pAEqWe0tL2BwR2eA8k+FLgfF8xFTo1x6DBup9TzCGOs3isAGWwcVSLckBKW/T+DzXRGQmF1RnszHEpJ3uoEgoRojh9LvoU27UIkCNuG8zCwNEderu9t8L8sgPDSWqzE+M9uiDGRSKesLtRlOSjidxwaGINn32yOEijcfGKjYIK4XxfeHc3ZDgZGDIsBr4eNKeAbdrNK/7NL6QftSyDXVLZ8uy27Zw/X9n+jMJoWn215v7T/KCwnEzrSa+a0xHTVUvX2erAsMfExKsaVvmv25S443DwMOwMID2iO0uLTpgSTaZZDGZ19jCF5Q/AyKX2nfQnYhYIHURRUVs1iQgP7EpmVomLFkJYk1SX/K23/lVF5FWYZ00ozovhLTs+fKU81JsqBaLQ55T+5+4QtWs6s5hdNcql7grt4nbXZ8hC2dm0BLSCwCcPbAcDj2P4otLnSz7gvgsOH7g8AZlUnsBcMs1gJeTSbnkOS94d6+PzeMDY83wDX9l+iciJPZfvm2KTIr1z+qO8k35AEIBIF4WIlhqZRTv11XN2jfMMmJyQWFOD6xcE40DzelKHh
*/