
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_FUNCTION_REFERENCE_HPP_INCLUDED
#define BOOST_FT_FUNCTION_REFERENCE_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/function_type.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename Types, typename Tag = null_tag> struct function_reference
    {
      typedef typename function_types::function_type<Types,Tag>::type & type;

      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,function_reference,(Types,Tag))
    };
  } 
} 

#endif


/* function_reference.hpp
AO4F4lYB9xJxKDB7iLsLuAbiUFYaiVsP3F7iNgDXRBweHrSTuDrgdhGHx4TtI85sIheCSF9mayJ7OlmTRfpxmonqJtJm879BKwm9KM44xzCFc7KGmgHXIrjWwPVbuB6H6x243ofrZ7gGGobKhGs6XIvhehSuZ+H6FK5v4OrscKlBcEW2vL202mxQnkMu2eYY+kSM6uY4/mwMUec4EtUYuLrQPQN9k+Gvh9FJXUe+gV3o6VJzFXmJvKw7JYdj6e4=
*/