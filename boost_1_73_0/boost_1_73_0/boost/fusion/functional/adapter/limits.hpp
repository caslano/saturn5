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
jltEivPa7LypYZW+FjrkTQZ+pDnwbWxEjtud7/9g22MvkZkWxRzelcXi8ko2caRZFxJNNg+Oc/YsCCjJWNSzB/D0rHNBOi5AqkD3tVkanqjiTlZzm0g0QFY2o9FpY+5sGWzdQC2jqy6/cI/RCmW2bOI5mXBGPjyJpHFogaOpCvfCwCbRLsiGVqq7S7GRYYqg3nZQY3zyNLncMftUa5PcwWrulEzJyAwmdA57hil5kZuIh0/yC/vbsZ76gk2MGaOk4CszzCW/gclN+axBHHNQ+Qm54bMhmR9GeAacNaFJgtuYreh8hmgNBOUppVR5rp5tLhKhfKdJZE9klEcAO2Ew4/LZfBDM5rmm55dNj4I1Kiftsi+eUmPzVlLgXkbpx0Mvs9g6MZqJwOkbsrsBcutjgkyeN4zoxCczT8zGPQd5IFDlO2Cx71Bb0LTMBdnTV5uCWphC4FZf/e0ymfe2xV30x2TCT3jU/6hPfVmUR2Tg9Y26mqqkOcMsPZMKj5L5Yr66RJ5vZGm4bYKXT28wk7c12RCkl7epLJGmj60TjMVIlhPkC+PimpxyEpHjjRCPw+y/fHn+4vTkp7+/8BQ3pJxvdkK4NZ4nIrmm1d+n0kagoYsg8gKImui2LHgoUglumxiHAk2u8G2wM8TGUxqA
*/