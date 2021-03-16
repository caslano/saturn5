
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
ZmbLR6GaDU5qsFJmNTGfFdwYhnKDIdRozVaNImEDm+ltChLDYOapt7L6b8QwPE33zWmpUM1JI/zoSY4RhjJrA+rnlpbL8SSoJefDLTwLJGvMxtNAKjtCGBnL280ZMYiCMZd8lb36mP9EdLzM2oyWmtPnLnkDbkHhqMyan4yVnv30gUbkB8FQcR0GoFvZFArscoZx6j5CmX3xYzP7SmxE6YNn9M0Kzugrnzpx9UH/IDO10Nq1mPmrDyau8sHYNic=
*/