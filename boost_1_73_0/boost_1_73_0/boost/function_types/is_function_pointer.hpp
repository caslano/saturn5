
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_FUNCTION_POINTER_HPP_INCLUDED
#define BOOST_FT_IS_FUNCTION_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_function_pointer
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::pointer_tag> 
        >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_function_pointer,(T,Tag))
    };
  }
}

#endif

/* is_function_pointer.hpp
dZODe2mvKtOcRy13cP/qVbdpzkO99E7C1mnOox5ycF/vVZs051F/cLAm4FXbNOfB9V2kJ3hVk+Y86g0H6wRe3F6JOI/6wMHahld9rDmP+srBuohX/VNzHtXiYA3Eq5xO5jwq0cn6iVd11ZxHzXea5bHQKeUm2CrBQtXfgpycOtL/cPAe5GS89SFco9sw3V443ERJmSgqKCvW9tt5pQXzeSMKrVhUlkbZbxPEfsuxI024cdT7nk98+eIF3Jnjy90=
*/