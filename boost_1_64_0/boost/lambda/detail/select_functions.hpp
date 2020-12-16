// -- select_functions.hpp -- Boost Lambda Library --------------------------

// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org


#ifndef BOOST_LAMBDA_SELECT_FUNCTIONS_HPP
#define BOOST_LAMBDA_SELECT_FUNCTIONS_HPP

namespace boost { 
namespace lambda {
namespace detail {


// select functions -------------------------------
template<class Any, CALL_TEMPLATE_ARGS>
inline Any& select(Any& any, CALL_FORMAL_ARGS) { CALL_USE_ARGS; return any; }


template<class Arg, CALL_TEMPLATE_ARGS>
inline typename Arg::template sig<tuple<CALL_REFERENCE_TYPES> >::type
select ( const lambda_functor<Arg>& op, CALL_FORMAL_ARGS ) { 
  return op.template call<
    typename Arg::template sig<tuple<CALL_REFERENCE_TYPES> >::type
  >(CALL_ACTUAL_ARGS); 
}
template<class Arg, CALL_TEMPLATE_ARGS>
inline typename Arg::template sig<tuple<CALL_REFERENCE_TYPES> >::type
select ( lambda_functor<Arg>& op, CALL_FORMAL_ARGS) { 
  return op.template call<
    typename Arg::template sig<tuple<CALL_REFERENCE_TYPES> >::type
  >(CALL_ACTUAL_ARGS); 
}

// ------------------------------------------------------------------------
// select functions where the return type is explicitly given
// Note: on many functions, this return type is just discarded.
// The select functions are inside a class template, and the return type
// is a class template argument.
// The first implementation used function templates with an explicitly 
// specified template parameter.
// However, this resulted in ambiguous calls (at least with gcc 2.95.2 
// and edg 2.44). Not sure whether the compilers were right or wrong. 
  
template<class RET> struct r_select {

// Any == RET
  template<class Any, CALL_TEMPLATE_ARGS>
  static 
  inline RET go (Any& any, CALL_FORMAL_ARGS) { CALL_USE_ARGS; return any; }


  template<class Arg, CALL_TEMPLATE_ARGS> 
  static 
  inline RET go (const lambda_functor<Arg>& op, CALL_FORMAL_ARGS ) {
    return op.template call<RET>(CALL_ACTUAL_ARGS); 
  }
  template<class Arg, CALL_TEMPLATE_ARGS> 
  static 
  inline RET go (lambda_functor<Arg>& op, CALL_FORMAL_ARGS ) { 
    return op.template call<RET>(CALL_ACTUAL_ARGS); 
  }
};
   
} // namespace detail
} // namespace lambda
} // namespace boost

#endif

/* select_functions.hpp
T/0cPje83Pdb1vD0Fr+UOm9QcJ6p5YT1Ytr0Rp59VfuMxaZcx+y1axrt8bDITFJ98Pd8kMWm1Gu3STJwhzxP4r2jfi/3MZzPfvJnUbo2eJk2GOixwSIOc81l2akEFbp7fT8bZAM5p2hW6VTXFlGdc5D0bHRnFZFPdP5O+OCDfS0geC1nmvJcHdt5oppfr11zY8C8wnT7kvBcrTryzK1JYhXG1Dibq7fwlSDMl+pzuHoiXdrj2UroXgUqgsLVGaD0E5+51UW1T75NdGLD+YoKyzkG4deowU56XWNa0LmhtIdxLpesedPxCU77wwxUPfP/btYpmzxpb2z7ELZe2SIyr6mR+FsNmm+vV6A7cr1yXJ5PVAPt9QrkI9crFz7XVK8wbVivAP9Ddcuw53TdErT+vrGjvW7Z9JzdtlzEG7Z+2fLciesX6I5Yv3yI52b9krip9eqXA7QD6xfdPznE8wXTqCQV9FJfpXLF7xr03eQAELbJxVUVpbMry0ur9Lmep/fVba4tztTjeO1mzTvk1fFd04Jz0RAOtsvMC5Y+2aDAejV2QvpRUV/Q+bCLrynOEkdEFuFgPWZfF0p+h3zh14WSz7DXTRJQ634zHnspT99vkjzvoW20NgobddF1l7nelPcIM+st2hBhY57xi1/S59Hrq4piWr6+yr6OquXrouzrZsKvi9p3rgP31acn9H/0wAc71O3njVr29uHrw61/avk6J/v6qv/8+if7Oqf/3Xqm1lq3pOfnb2xe57DBM3/la5y/8nVgHPB21bzOxE+5bMqZ60xqKfctYEfOR0ziPMRk4LeBvTg/sQ/d+wKXAvvzXs8npD8JlvBV0Z+5wM7A2yhX5xLl1lIuFbSZchM5P2oS0HW/EZjB+VDDOB/qQuCtwOHAqZwfPx14KfAmzo+fAbwWOBM4ifzXAW/hOqBy4CzOk/oqcLYxX+oe8n8DeB3wcc7LWuO6Mx41up+MsDEeiaAqxmMM4zGO8ZgAzOT89rM4v/1szgc7B3glUNbgcH78VcDhfH4x58sXcZ78jXTn+gf2H2FrhkOvf+A80gTg40zPFfTvKWAO571fwPnuhZznPh24HjiH6xkqXX76V6/7Nrimf2mg7fSvD+Pdj/NYc5hvBgJHAQcBx3KdwHjgl5heQ5le53E9w/nAEs7vqub8rjspdxfnbS3mvK1vAUcAvwu8BLgKOBL4JPnXAfsDdwLPBu6mO9OR/RF7OnZnfFKZjj2ZjhlMx0ym45m06+lMx15MxzOYjmcyHdOYjunAG+nO8sR2HzyW8vQAy9MihmMx5fLZVorNKdde7Ml1VJSbx/I+H5gIvJfleiEQc6WjmivG+V6c66Xndun5XHmeeVzeOVwHQeOvtM7P0nOzykANuF4I5BwrzK8y51ZxPhUoMG+qCrQI5JkrpedIHQOa86GGg0pAnP8k8544x4lzm5rnNRWASkDmHKZFwMCcpVpjjtJGYD3INh+pDFQF4vwjmXu0HbQfdNTFQnM+UeS5RMdB+SP1/CFjrpA5T0jPEZL5QelAy5ygsPN/DoICc37KQeacngJQEcics7MSVAcazzk5DaDNmJuyHxT7TJzKBo0HlYNqQZtA+0Hq2bb5K22/tl/br+3X9mv7tf3afm2//83vv/b9f3rrfP9fl6H0d9djMVzXxnH8v7nXeJ61Kmgcn8cmhH4f7M3x+77Cf1QVuFKgRSpevQh8zzqWT/0cp82Cg6PmzLXv90pefueaG+Dld6DA95lK4fkmxgVi8G7fUc2w7/dIXeb3uJn272se3rmqiRfeCm+KwZviDaNY1H9L5cyvT1MuH+cO3C08E/FuH8/5BI76UNxSg77nXN9DEHTq33NgW7g=
*/