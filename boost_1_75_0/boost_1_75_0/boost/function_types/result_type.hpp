
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
FRj6KclnXAFTmmZc9RXzGWm448q8PPZZj/Ikpik7ybRgO0k8wK3rgZZivXaTKEI/x7WQ5z1KDSRxplXAWdED8PRFeKJJK7r9Fa9EvKmWMEAQ//c6mq0D/cP46sE8xbxuMUnlJEaauXRyjzAiCjjuEUcD8hd/qyHvYx66VJpOymiVFnAePQ8AbqZ6XX0e9LoZ9rqhDktRdsA5Fqoz+5m+P94Ut7FUhuW/1yKG5l/LcY40szOBIzFnvWZ6quVnAvxZPsPr+8nt2+X1sUu+1dUs9bxgV7NscGS9EAlPPzeShz38GfpioZYUMA6ltAlanAp7OYQPkH5nXcncWpqEV3/XVjmXJSqq2ImL4UbSoG9ZAvuWFTVHx7LXEU12FyVDuFiwVcu0L8aefk4+GMrJbAYXbK5Jx07rW5bYXcobUhtxJXvmT3Da+6xEmpmBxyhO0OZMwsJRXnYlu+t6enCrV/qmW3Q3ha9qLsi+WqQfu4LkSI+k6HOUKuZITc1XPDUZcmoy1NQc1ogsRUakqUmCMU/jqREY7bx0T9DUpKmpSdOnJo2+Fq2lNTQ1D/OIC54gKgtisH/DQkrIWzUxdC4y1FxkBM0F+X+fK+fCIsM05wIVP632xZNpNXLR5PG173oefsNNw7/nelN26dBkQrQVxdS9rKahxOPb7wUZGPrCsRmKmYEqcA6YoRyVZihi0k5NOzFfsDPF14E/cJfOMrzn
*/