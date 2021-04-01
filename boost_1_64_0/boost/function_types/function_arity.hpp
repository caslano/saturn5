
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_FUNCTION_ARITY_HPP_INCLUDED
#define BOOST_FT_FUNCTION_ARITY_HPP_INCLUDED

#include <boost/blank.hpp>
#include <boost/mpl/if.hpp>

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/is_callable_builtin.hpp>
#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename T> struct function_arity
      : mpl::if_
        < function_types::is_callable_builtin<T>
        , typename components<T>::function_arity, boost::blank
        >::type
    {
      BOOST_MPL_AUX_LAMBDA_SUPPORT(1,function_arity,(T)) 
    };
  }
}

#endif


/* function_arity.hpp
MQiBtuIkRr3+SSwrxnu58MVb0l5y39lq9G4xP0IGJb2cioXI0RMP41WYiXCYjB4DKrG/iwqwoZJgCD/oEdOTWGeYVN2lkstQSPEQ+SxSo9qJ25jqH05Avp/NGHCw0hszHwLGO7sH/xiIubBdmL6usIDoMoexkE4nwjGPDMK+DHIi94WuzTqdF6Cl1MJu8gWnY2gGtyR9xxlwc4f6w8AhAMcLXDpsXSP77Nnd0dL2dYBYUEm2sxeqdDDVyz5Oe2+qJJwFTLi4c5Bo/TgxxVFdx9XgEU1maOkTDbNQqID4Pjc4OU8pZiSVSmTc9q1GHPEB8M5a3GqJAq1AiGfXCqI1zbhEWyH2VvVCyI1El9BmuShvtFPOfeKEMa2spzmYkZiYfVcmaOeA8Dyonh6tL204fO94Y63MHSxorT70iTMNRQv3f5VlEz6dtR58F1h75Vmmq6mtflLIxIN/chhivwyu+vKs8+JM0575iE2c9oNMsbZdrsuO2zDLcd0yTjiUEXb37Jf+aOyoBJ41Vea/DT8j4F/yH58LkVKgWATY363WQOtEJwLZ4XkuV8V6rg==
*/