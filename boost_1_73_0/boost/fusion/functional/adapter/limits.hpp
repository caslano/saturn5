/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_LIMITS_HPP_INCLUDED)
#   define BOOST_FUSION_FUNCTIONAL_ADAPTER_LIMITS_HPP_INCLUDED

#   include <boost/fusion/container/vector/detail/config.hpp>
#   if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#       include <boost/fusion/container/vector/detail/cpp03/limits.hpp>
#   endif

#   if !defined(BOOST_FUSION_UNFUSED_MAX_ARITY)
#       define BOOST_FUSION_UNFUSED_MAX_ARITY 6
#   elif !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR) && \
         (BOOST_FUSION_UNFUSED_GENERIC_MAX_ARITY > FUSION_MAX_VECTOR_SIZE)
#       error "BOOST_FUSION_UNFUSED_GENERIC_MAX_ARITY > FUSION_MAX_VECTOR_SIZE"
#   endif
#   if !defined(BOOST_FUSION_UNFUSED_TYPED_MAX_ARITY)
#       define BOOST_FUSION_UNFUSED_TYPED_MAX_ARITY 6
#   elif !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR) && \
         (BOOST_FUSION_UNFUSED_TYPED_MAX_ARITY > FUSION_MAX_VECTOR_SIZE)
#       error "BOOST_FUSION_UNFUSED_TYPED_MAX_ARITY > FUSION_MAX_VECTOR_SIZE"
#   endif

#endif


/* limits.hpp
FV1r3SNxDtBrTlFZlmtGzNr0uWbG+r4V1EN07wDMsw7svCOz2TiT0r68OloeAp0K10uE3hk3EfdmnVsG5b5SgmfO2P9O19SvShg6VX8rmE3bB2leE3/tD5rmHMJcfjm64WuXTssKpbtcwyaE13waNo2worawprqGVv+Tw2lyxv3kcFjOGJ9EWJT9a9GxhTKv0Gtp59wzLCY11vEOzTnDopfE6+z8xBa4+JW4Nd4Uym3tiwv8
*/