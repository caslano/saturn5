
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).
//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_MEMBER_POINTER_HPP_INCLUDED
#define BOOST_FT_IS_MEMBER_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_member_pointer
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::member_pointer_tag> 
        >
    {
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_member_pointer,(T,Tag))
    };
  } 
} 

#endif


/* is_member_pointer.hpp
YGfQc9j7Dfw+e79RpPuNYt1vzNcyuECX5SYpy02Up7MFmyvYCsECgm0U7GHBvhXstGCRzk7VjQ2KrFB23yKsJpPd1kZrq9H2qsmBMQrQX1pZgE6fyj4zZi+9FIX3qioL5rOvp9PyimS5z5sClvMyiRmSRD9LEov8yyo4iZmW+ygA6AdnKNqwtYvKJieDAfIWAz49K3muUhS1PyFFPOXAUYfYopYozExu5hKGt+nCNCG6Keuim7IUhWH+7O56uoE=
*/