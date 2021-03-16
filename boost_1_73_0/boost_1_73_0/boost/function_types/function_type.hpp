
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_FUNCTION_TYPE_HPP_INCLUDED
#define BOOST_FT_FUNCTION_TYPE_HPP_INCLUDED

#include <boost/function_types/detail/synthesize.hpp>
#include <boost/function_types/detail/to_sequence.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename Types, typename Tag = null_tag> struct function_type
      : detail::synthesize_func<typename detail::to_sequence<Types>::type, Tag>
    {
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,function_type,(Types,Tag))
    };
  }
}

#endif
 

/* function_type.hpp
FPY5/KCXFxvJ6mVItgvdi06O16RXmNt3Tpbk+NcwFvmYR/8K3ATUVGGmUHgRJDlVzKKjh7EV5YM0vtoYEkxIhifjraVqC1oPC8u9ZthIOzDcBqSm2wH7I6kj7ECaHUi1AUNH2QH7a4cOtQNDVEIEkG4Lj7KFR9rCI2zh4bZwWtRYKnp2yTxIrQshJDqm9zzvF1DB0pSefJ2DEx4x2aL/DdAg/mEdQzVgPPB9Nb7GzSOyO4Hia+5y80z/O272pv8=
*/