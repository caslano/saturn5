
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).
//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_FUNCTION_HPP_INCLUDED
#define BOOST_FT_IS_FUNCTION_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_function
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::function_tag> 
        >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_function,(T,Tag))
    };
  }
} 

#endif


/* is_function.hpp
AcJHAidzbe564sDA+cHbvdZWmHKH1+qFlDUhjMgWxErGLbIa9z1wPwrJR+xMimfwvxOyCH0anISUIyuRDcizyM7T8B/ZTDisQsKAfI/5I7jv+r3H2kwdtw6GWYTNS/oha/FvH9eDW1Bu+L0V6UV498DvkfhXCCPXViIbkZ3IISSpJWUPmYTMRVYiG5Fnkb1IcCuig/RCMpA1yCZkK7LPNovGTmvSGzaCc2El0onf6+BYWIxs
*/