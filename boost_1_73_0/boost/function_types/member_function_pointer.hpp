
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_MEMBER_FUNCTION_POINTER_HPP_INCLUDED
#define BOOST_FT_MEMBER_FUNCTION_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/detail/synthesize.hpp>
#include <boost/function_types/detail/to_sequence.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename Types, typename Tag = null_tag> 
    struct member_function_pointer
      : detail::synthesize_mfp< typename detail::to_sequence<Types>::type, Tag >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,member_function_pointer,(Types,Tag))
    };
  } 
} 

#endif


/* member_function_pointer.hpp
R4YXoWkcnhYaHBFdn5+x4SdjtVZUaJ2ghPCi8I7hAzBMsP9GxNnp35i1GKF6Lun9Kg/HmXPN3M9bJF/eJg16ST4keO14DZI+fiFnT5aas7IXyvUwT4LGaZnE8z6rPjFdbwWJ3x3ixe/CnEw9O0jTMVXsBsu99nOvi8SvbZ46vjUmpnyulmsdzLlDbcVtS3Om33C5/p41wpphzjsbJXbirMZafgaLnX96QthZ4SlrASVrrbXf
*/