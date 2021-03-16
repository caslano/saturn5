
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
2EnfCQXWOcxX4AJc8201NJ6F8bdllNvfwveE5zFG4vYA/gDIfH6w5kCL/DKsNbm1NZ9QAbzlC8WFOoXVnvD9T1u5f0WcqSf5WuoCACXiaOo/9Jds+zOYOJwm0MHltsfRfx2T42LBnTzCei1wfOeExKSwjocV7zLqU9HlY6sbq+MI4LYRB0MylePCu3gwDQ+4L4JSGULclcLNBe55eqIIuO3ElQD3R+JKgXuOuArg6onzA/cicUuB20HcCuB2Exc=
*/