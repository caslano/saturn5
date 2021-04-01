
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_FUNCTION_POINTER_HPP_INCLUDED
#define BOOST_FT_FUNCTION_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/function_type.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename Types, typename Tag = null_tag> struct function_pointer
    {
      typedef typename function_types::function_type<Types,Tag>::type * type;

      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,function_pointer,(Types,Tag))
    };
  } 
} 

#endif


/* function_pointer.hpp
kY+oA1MzFbTNihHP4XX3gwA2n2k660T2PsQ2EqEi1s2ausjMjjhps5XTMMwgLBBc6FRzoBG30CpC7ou+AgolBzTKAfsShUbucvZldbKcUyl7cJYgrDMohDwReNSy441Y9jSceSWmpui7KRHcjxSIXyC/mF+mb+4NWYQNdiwnImoooJRE0gvae5Y7HPe7yTTezT84efndgULdtvX0Ol1PNAM02IHFEWaZ4SLACXt5dvVa7GW4iYkeYxLMcVNrlQ8/QZPEG9P5zMEyq787RKyq1uUOpefPd1v5yDNTkfBCJzRZUkNJjJqRAuh57zpCsK5Gnjucio2/S4+Z3CUc9m43IAG1Ed5lyNMbp0Btc3Nh+OxGeE/UqhBtZOIclFY7AZMds5ujPjFHozXcfMgYmiCaJWoDf6IwvWIGSTM1BU+ven3CNZyC2GTnG0Il652k8ikukrozLKJIC7eJL+82z9iHDsMvFdt1cwFU7+uAutcs1tP3m5n9D6FUP7oXLJxp6XzqdgtfTGzdmYqSfKTkxL6wy+PyrK1RcMHMLAqjnHWGTIIXEKPrpkXFgeoIsg==
*/