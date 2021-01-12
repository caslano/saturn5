
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
Lz5Nh/010yErPy/niGlwcK05l8/9XEsNu7239iaPfEdhvYg/EeGRrvtpW+577OLmyPE5aKfRr3BcJ+pq2zzjqU+z+z5d3P72j0aNazHtr28debxnxzu2+ddRW7c9+tmQ/We3bjNlwpq5VmAcyLlXjRQWLQ+b4TBE1iOY502ea7lWB8moLky6NCrV0vVBMA5OgPFwJGwDR8EOcAzspNdPgWfBPqrXdRlatnl+9H7OdRmT9H5Z
*/