
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
zhANV8N4uB42hA/DRvAV2AxugynwHdgK7oFh8Au4z0M6QNzQ3rWv67yx+Z6FOk3TtS4yV9OVsiXjDH+EteDtMAXeAVvDJ2FH+CfYG94NU+E9MB3eC8fD+2G22p8GH4Tnw01wrppredPvSMhvl/JWl/6YzTgYChvBerAZPAm2ge3hYNgdpsLecAgcCIfDQXAYTFf9CNgcjhS97zkq1nQ52eU5ep5y5YE7tJy9AevDnbAVfBO2
*/