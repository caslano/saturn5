
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
srVUYlfoWXjbqjfYjpQd7eHDUyXb5TyKnTi58Hw3cWazJA7wfuF+MP7R1X1lQTXxaD0cTBiJXDbYSOkdwcNNrZRXturKusnIOzlCG77I9MwmZr+z34Ds7f/jE81eDfeDK38eRHGEq7Gx01Ibu3tra4ckBRdSqEU8IcPenPO20mxjJZeVM+1U54vjLZxP3sKL14aTZf2L7tQ6PrN+1gFLN14tffjiLFausdRbIXQ5bhJcAus7dd96VCMWXdPwFttw/2roA1e+rjkJ9KlWoJrL/lSNItcFZxEF2LY+LQ+2whGeQlzp/2iwf2z8C1BLAwQKAAAACAAtZ0pSwDZVzvYHAAA0FQAANwAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfU1NIX0tFWUZVTkNUSU9OLjNVVAUAAbZIJGCtWG1v20YS/s5fMacDLraPoZKmaC5xUBwry2fVsiSIVHMGDBArcmXumdoluEvLatP/fjO7pC3JVmIXUZCIInfenmfemOCqA0ff7eMFpA6++Uns3wQ/+N0KTSr1P56apwWS5Au4Pyh4hd/PMNWFB6kvySE8S+oLHFippLH1ia6T5BnmrshJ+qdLwlcJXeIdJ9nI91S5rsR1buCgdwhvP3z4F7yG
*/