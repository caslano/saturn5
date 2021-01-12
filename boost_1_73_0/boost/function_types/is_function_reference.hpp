
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_FUNCTION_REFERENCE_HPP_INCLUDED
#define BOOST_FT_IS_FUNCTION_REFERENCE_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_function_reference
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::reference_tag> >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_function_reference,(T,Tag))
    };
  }
} 

#endif


/* is_function_reference.hpp
BVRAVfV7p1ieGGClnpYxqqRoasaQvLK0mZMzzs8unj41Y/LMvPycMnb1Ks3IZtPpjPIe3dvb+3oUzSptX5Kbn5GfNzkjdUTW9NzBefnYQWtb65CTV5Jh78BdOruwQ3aHosm/w//TrF4xFg2wWlac1cBaUGwZjsjLLikqLZpSltx6TJvkkfY5anlz+JQ+ObXqVBh7b9L0mK32PvH2mMRv6NulwDdK8o2SzHPOjTx2u/NIbcxk
*/