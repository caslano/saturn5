
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
ODMGxx5L7mXOwm4mbpt6d1pnu511g3v/89TsFCvMKsitCt9uwtdO/GjprT6jLU70z3u6WOkeMUPXWcIcS5iCXM/IcYazrOpsNU5qdz+HzRmm+CQLxeminMPO8gGxf5Aw2f5sqjqHq7C0s28dQZKEo6mV6DhnvKeY1bdquLF8ZwD/8cqqM4CXEnoxM/GJkvjY55ttsOTsAuvP5H/QgPDOnFAWH2Yf/Rs+NDw91MvxZRERtcLC
*/