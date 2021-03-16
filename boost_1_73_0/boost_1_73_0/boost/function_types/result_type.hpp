
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
nTZJgao96wgUIF09XX9TO9VhGPt4VyW+Tln23fnTkSOF0GzxhZudvRZbsOSSBYu+X9x2PuxweAjAAYKHgIsVGRpDCE2VqyiE7N9OIWR6NihZB6H+FHoZQsuTzfz0l4ThfOhHGmZwRYR3+K+B0JMU2gyhNgq9LaFPILSBSsFF1ZcIO81n9mah+o3NqeZC6GtKxSWv9RRaK6EXJfSRz7j1OQihFgpZwFk/USgEobUUOtU2+YZDyKJ7zLC9+9lvS8I=
*/