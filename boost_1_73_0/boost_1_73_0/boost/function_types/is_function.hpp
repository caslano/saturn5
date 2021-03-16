
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).
//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_FUNCTION_HPP_INCLUDED
#define BOOST_FT_IS_FUNCTION_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_function
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::function_tag> 
        >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_function,(T,Tag))
    };
  }
} 

#endif


/* is_function.hpp
pKPeMHwA6H6gJ4AeBPqTxrEeHwDawcFhD9A/4Xfo8IU6fAnQN4FmaDxbhycAfRvoZI1fp8NzdRjVv62i/m0ltS5PsGmCbRHsOcEaBNsn2PuCfSTYj4L9LFg/w8TOM0xskGBDBcsRbKJgpYJVCBYQbJVgdYI9KtgJLm/AvtScB1eXUI/sVf/WnEdhfjcRFqc5j+ru4F7Qq3przkP9dSNhl2jOo0Y6uAf1Qr/AnAcad+5fvSpXc6BmO7j3BTVbcx4=
*/