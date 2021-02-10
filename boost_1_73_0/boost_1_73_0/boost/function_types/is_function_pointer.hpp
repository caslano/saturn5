
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_FUNCTION_POINTER_HPP_INCLUDED
#define BOOST_FT_IS_FUNCTION_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_function_pointer
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::pointer_tag> 
        >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_function_pointer,(T,Tag))
    };
  }
}

#endif

/* is_function_pointer.hpp
WXZZXMXJp/gyyfIMTmB0fAZ/9MKo+/sRjDjbmPLDaXByGrzBBfOvoETtCkW1KTR+UVMKYbNLiMPrmfc/2OvXTsiCbCk0kldM3LiCoeGtkPcCV5VWFihbxUmaRZn3HRMl7ysK74xnp8XmvWedlBLXnwc0NjvwqkGVcBTLy8GgLhvSwavaBHP0i3V5PsumiyjNoyT2UoLFINBKJrSRCXYGiJ7z10YsTBBTc1N9zOBpJo/5OTl5Nq3CpOX2XFcEYDvwcVO53aGT8YRFS1oqDDdmz6tlt8WexL5WfdvKzkSw2eHc2CjVvA0gGhrdAhmltrRkNQrJh30N7xnnqFS+80hZUixdKYXA0W3Kh5u6cfwjjnHUDQG6dkN1UqHdQCIuGd/ZEA/jKhtDgW3rEm7pLoAlJrGuowP6Z6uLZTw1BI9PjtZ1annleujDitak59rbUBxlDDtBOkHYABATxlumjvbOAs8zHJIWu6UkJgfsbJwWQmo3ChH7ltLWQg+lIp3EtgdSG5eoFu3qhnPCiTgYdHARLue5Fy/nc7uQLpI8mSbzzMsu8tSGk01TuzX7M7xO5zMvELXndGeZ/vWJKplgeowSY/XYLB7B3x78V7Rm4VGsePNhpGrd4vilDwRHAg1KuZ0Y3kcI9kWEZ3L3Xnjx
*/