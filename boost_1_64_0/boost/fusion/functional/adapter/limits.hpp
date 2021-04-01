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
EdqjnoFoNOaWFbR4/Y3ibu+RrpqRnKOakA723wc7NUq089hrPNNAIq/gcQgc+ThApN2NC6Nx+5F40xbnbPxWN/jCnFOGemSc8TDrxvdJwAMYY7hRwQFe5YdIGTABKhVXCHOJnBuWQgHFvL1thIOEJQbMWVxUD+gk72nrH0SrPmxMoRu3fv0RJnyNpeGO+x1aIuBIhYXtoH8lKZ0td2aoevWrWsxu+6ahPghr1+KsKCOwXenFagA8ysZQ+kiuH8qCcLVRFKAPZAm4efLJo3qgzuct5NU3HCcG0/PO6TX+0aLhrspR9OxjEGGFnC6OZE/sX8YB9j4+LhPPjpHdX74RaEZ4x5PdbsrLu378rjWPCyxv7EI2epc4wupOG4BvwY3sH0w+OGpqWUGCOFR/05rfUgt6dqhfnSCqECY4G/P2a/Q0K4mkamUGX6Zvzacdp5q/wnw/OzdiXy6p8IVp7bPs+zyPwjtnIkYgM2flqB3OQQPJjfnyHv75zdNiGPC0y1BDHoG54eE2sjrgXko3lVdw/NHOgTMLW9+JNEp+IqVa4gdttYJU1Ht1tLp69g==
*/