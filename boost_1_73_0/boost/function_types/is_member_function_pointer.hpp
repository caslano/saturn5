
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_MEMBER_FUNCTION_POINTER_HPP_INCLUDED
#define BOOST_FT_IS_MEMBER_FUNCTION_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_member_function_pointer
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::member_function_pointer_tag> >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_member_function_pointer,(T,Tag))
    };
  }
} 
#endif 


/* is_member_function_pointer.hpp
pBeSgeQj2m6izeRrK21HnG2keMTZJtL2EG2go7d//Ns+tHtMW6cYqUDc2ze4RfzaNQEVUAEVUAEVUAEVUAEVUAEVUL8KdaL7/3nF3X+x/v/LcZY503Gjzpn11Xj0QZK4vmGt73ysvOLzu88qKpleeoQ96GJsf8R+M/yv477PMtf5x1WzJ5Vxu0OuxXHNYyWYfQjtu2bKbZ3nIuxWf6r3ahqNYbcYlz3qjmN/PtmvR9Nhvtdv
*/