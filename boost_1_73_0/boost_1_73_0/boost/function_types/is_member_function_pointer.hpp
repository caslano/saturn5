
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_MEMBER_FUNCTION_POINTER_HPP_INCLUDED
#define BOOST_FT_IS_MEMBER_FUNCTION_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_member_function_pointer
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::member_function_pointer_tag> >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_member_function_pointer,(T,Tag))
    };
  }
} 
#endif 


/* is_member_function_pointer.hpp
kI9WhieT8ck5ONStzcj8bDk8xcPBWK7LWI5sksPJYTbJzRdslWCvC/auYNghniYOzxv+XQerES/fiHbCwI4NpR0nv/rHqEdstlCxZvJSKGqakQZ1oRyupihDXgod0MU+VTcWVBYXlS8qWFBms+j1owTDp/WONcZC9CVwHYLLelYuDhriuwUetp+h24K4q3qA/QzdWPP+xy47O/scn+iFKhh7bkV8RnryZv1chCLWbEkQ8xfrMBre3tZYupMX5I4=
*/