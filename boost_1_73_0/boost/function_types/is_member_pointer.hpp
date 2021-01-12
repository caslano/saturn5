
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).
//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_MEMBER_POINTER_HPP_INCLUDED
#define BOOST_FT_IS_MEMBER_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_member_pointer
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::member_pointer_tag> 
        >
    {
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_member_pointer,(T,Tag))
    };
  } 
} 

#endif


/* is_member_pointer.hpp
MBJOhkkwF9aHObCh6tn+gflGGePSecWfP9bF/OcvMgdZ/iuZh/y1zUH6j9OFbWNueFtgfjCgAiqgAiqgAiqg/rfVie//d/3F+v8vBub/f7P9vsD8f0AFVEAFVEAFVEAFVEAFVEAF1H9Xnfj+v3b/f4H+/0OO+X8MRE320r+DQ2FUEvN5V/jmvbOzOFo5Mysnp+RH5+XKOVx7/nn4cOsVtv223up5+uiVNc/yCpfr57nPi1/h
*/