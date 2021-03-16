
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_NONMEMBER_CALLABLE_BUILTIN_HPP_INCLUDED
#define BOOST_FT_IS_NONMEMBER_CALLABLE_BUILTIN_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_nonmember_callable_builtin
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag,detail::nonmember_callable_builtin_tag> 
        >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_nonmember_callable_builtin,(T,Tag))
    };
  }
} 

#endif 


/* is_nonmember_callable_builtin.hpp
MflUjDpDYP48HIzORcyNGH0SQvib+lO0IttBh9ZfhmVmF8qHnewnVedkz7pNTvasq9NCuVGEcuP/cXYl4FEV2bpu3yxt0qSbVVCB+NxRmGAIRtFnYlAaCUMYQIMsSSBhDRBDR6OIJgYeyVwjCC6gAaOi4vYGxpGHC5p5cQYYF0BGB7dRx6czjMsgKiKO8s5Sdfr27U4A832dU/VX3br31q1TderUqVPUiCYKNkWwGwRbLFiLYK2CvSBYm2AfCPY=
*/