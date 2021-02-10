
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_RESULT_TYPE_HPP_INCLUDED
#define BOOST_FT_RESULT_TYPE_HPP_INCLUDED

#include <boost/blank.hpp>
#include <boost/mpl/if.hpp>

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/mpl/at.hpp>

#include <boost/function_types/is_callable_builtin.hpp>
#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T > struct result_type;

    namespace detail
    {
      template<typename T> struct result_type_impl
        : mpl::at_c
          < typename function_types::components<T>::types, 0 >
      { };
    }

    template<typename T> struct result_type
      : mpl::if_
        < function_types::is_callable_builtin<T>
        , detail::result_type_impl<T>, boost::blank
        >::type
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(1,result_type,(T)) 
    };
  }
}

#endif


/* result_type.hpp
F4t57YsbdrvQ7ocjvMT8Nd7NCVUZuEh6BGsH9vWy8z9QSwMECgAAAAgALWdKUqzGLGOcBAAA9wkAADMACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1NTTENFUlRUWVBFLjNVVAUAAbZIJGCtVW1v2zYQ/q5fcVC/2IUiJ82KrF1XTHWUxYttCZbc1EAAgZZOFVeZFEQqL1j233ek5KXJCjQDasMifbx77nj33Mm/cuHlD/s4voGD734y+8voQ+veKG7ln5jrbxtk2T30XzK8ovUZribwYHWfjeFZVvcwslbZ4Oud2WfZM9xdmSDNY2KMrzKzJUlvOdhPZXPX8s+VhtF0DEdv3vwMB/Dq8Oi1Z54nHpwywbGGRKPYYvvZg3eFlfxWsdtbX+F7D1ADq/1HsGnFFShZ6hvWItC+5jkKhQUwBQWqvOVb+sMF6Aqh5DXCNIo3s+XvHtxUPK8GnDvZgapkVxdQsWuEFnPk1z1Mw1oNsiQEwi+40oTZaS6FT+4RNLY7NcCYIFitJLBrxmu2JXdMQ6V1o95OJnnX1nSTSSFzNcn3CfErvXtyqw1Fs2N3IBsNWkKn0AOj78FOFrw0K6WIhE23rbmqvIewyKEoJrIFhXU9wJEpR9VfASEZ
*/