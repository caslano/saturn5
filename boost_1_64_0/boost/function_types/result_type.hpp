
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
bfacZpKE+ZaSwHqEaBpawaoyYdMZH537UADnSEGcOWIQ30zsvA8d3wasz8jcrAmO3fAFP2isVeFOGoSeIzMkBsgf2GMjsyAhNWR5ASkg5KtBDiktiJpfGj4j5DwPGdm851uVftI6ttQqt6c1biq2pNAULSbI+24mO/0NF7BpLI+t3uFR18jw8cxFeU7q0fxyeQfMONtQez/HS86VSiJrM/4Sc1UPOjl4z7bEtn51MNuDxiX+svQzcgsfkvuCWr5AZctA29dPEjuaZ0XFj58pIxbie6/DDTolykNWlrSOMrgfib82fJkY6vFcWpasT8juFU22UafXfBsU+MFhHABjxI7LDxT/YdnM4LxEo0KjsXH1W1Z18aVh5micmyUepO0V15nTYxiCcAAWsa0UbTOfhTAor00lZhG+bI6EmogV9l8SSOKpiUbt8CstwNd0O7uF3KBy0u7fb+lFI8u9HCrh7OSCLR/aOwTAM5oR0fvZ4zyarEvZXBlVYeHGs+t0WLZcVW5WdG3GY7rhZu0j+spB4k1d8ztz1AMhYufAXQH9V5YQT4I6hrbkbYaJ9Q==
*/