
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_MEMBER_OBJECT_POINTER_HPP_INCLUDED
#define BOOST_FT_IS_MEMBER_OBJECT_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T > 
    struct is_member_object_pointer
      : function_types::detail::represents_impl
        < function_types::components<T>
        , detail::member_object_pointer_tag >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_member_object_pointer,(T))
    };
  }
} 

#endif 


/* is_member_object_pointer.hpp
BToQKNQP3NxLjXPynGABUJyDyHDyOQ5QCQJo3BsP9E59/z6gE4CiOexqoC8otK6oAM6nTQT6vo6HitMUoDhrBoIb6Ai/ZRpQdCGejg4tQGcCxWnz64GmAZ0NNB0oiCvNBd4AFAt1Lv4+g9NFGX1A2poHqG2YLtgswSoFWyLYBsEeFOxJwZ4RDOcfGcs3TMwv2FLBuOPICjVkefdmBasj+g6cVbTPUXXTFMvgghgyj8uG2u85urXTc3Rru+c401U=
*/