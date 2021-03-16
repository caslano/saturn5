
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
eFsUtp6TCWmFdmMpB37IWgPGIlZWDV0mshHcB6SOa7piDaJUgCqw3iBFLO0JzVizVZFK+KclhFIVZauuWrODNyGnjmxfZAow9kSP6/g/Co2dMPJIo6tsrCvvqt22dO6o/5TO+zigMdGq3avp7LXj/XTW3uwEOg7o7nTW0rwBtB7oX9JZK/M20Bad/1Edx7Xf94Bu0jjy3AvCcy9QOy8WbLJgVYJFBLtdsJWC9bIMdpJlsDMFGyBYnmDDo5jHuMI=
*/