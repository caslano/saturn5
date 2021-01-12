
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
E6TnLmoYNe47Cc9LYn8B5U/KPap0VlZxZllBsWXCESf3SDT3tEQfJmc4r/Xy/IRYXKF8egeEtwtvTZaEhNj3i4w3z5FJjz5yv5NVT1qq3470MGecda16Xj1PWJ30HFZKl9jfwCn4uZwJFiTx2Ec8xmq8q88Eb6BljfMs5BydCM/FByNCQyKCKCz29QTKS7CeqfpIXNUY0xV6Rlprj+sZaamyhof1L0EQPwmRlGPCfpqcL1jP
*/