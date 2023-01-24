
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_MEMBER_OBJECT_POINTER_HPP_INCLUDED
#define BOOST_FT_MEMBER_OBJECT_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/detail/synthesize.hpp>
#include <boost/function_types/detail/to_sequence.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename Types> 
    struct member_object_pointer
      : detail::synthesize_mop< typename detail::to_sequence<Types>::type >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(1,member_object_pointer,(Types))
    };
  } 
} 

#endif



/* member_object_pointer.hpp
2a/d3cjLCfxAwZ8O43KmSecSSNVNRiAUP/gOa8RPAG1AH0k00/QxMYkmqie+igjNeQjxf3LZ/uU2nN2X6DL3tvD2o29/Yk4weikeV2GlTeOt9el6WFzURYqX/QvATPJBsRFbF7nYLXK1WXRXTM31+sfnechApJVHGoi4fVMhk1k2xuZ/u4rVjjgmLjUUmelNyZqwzhZsRgrxP4dr9Fbv85KPw/Q5yPpx+xXhMPs+cMUYC103fhf99kCeSuqsqZvLDdk4Sq9oCopHhvSBEPyywSr+8+AG7QJ//SjI+k5PkBB3hb5zpPrEOWsA8gdnBJx7esP54TaBQwNy2R7ptlw5PwOs8wgvBuTJUnmqVJ61VJ7q+MzeliS5DUQ2bh6ItwWbGYbIHKpI5nDyQyVzgMMKqoSOYRCoXocxeglMYAnGAetNOFuCOLsFz0ioHBrUTPOao4NFebLM/QX3Aee/0wTcHt+QAvnIuHPY8YDdQeXt3cUR+YDdQd7TB+zxsB79zp8udTJVSB0hVmC2rzXpNX0Oj28LeHFQXhW0HWom6J5oA5xdqmP0lu9MA7ecIYWq4T+GnrbhG1TDi+9oQsN7L6eGh1sa/uNyaPjpedo4GIWnb3vlJbLt9Ka0fT+3XRett11IbS/Q2z5062nbvki1vfr2JrR94DJqu8jS9qHLcMBLMNAy8C2cs8jT+5LkogRIfBNwLoEyFZckQ7nlwG9k
*/