
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_FUNCTION_REFERENCE_HPP_INCLUDED
#define BOOST_FT_IS_FUNCTION_REFERENCE_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_function_reference
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::reference_tag> >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_function_reference,(T,Tag))
    };
  }
} 

#endif


/* is_function_reference.hpp
BHnP0JdfN/o0QWm18fIrW5mMRsw+GV3q5LHcIifbMMudbO69WU9GPyKV+hHK1BsEu1GwlYLdLthDgm0S7LRg/xIspmmtGpV83ro9UI8zeqpqqGUu+3JAdmALqbdsf8J8ONK5t+bFAwj6rY9m2h59prVHeznwrRPQTSUbPZzfyKzNG9myLqBoIJOKaeGBtJn1aNemxMwjrzF1ShJHNVZfY5oUpD003zUHRB5MZyqk8/l2yySiOfHnOu0gc1+DZE4=
*/