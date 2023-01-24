
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_FUNCTION_REFERENCE_HPP_INCLUDED
#define BOOST_FT_FUNCTION_REFERENCE_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/function_type.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename Types, typename Tag = null_tag> struct function_reference
    {
      typedef typename function_types::function_type<Types,Tag>::type & type;

      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,function_reference,(Types,Tag))
    };
  } 
} 

#endif


/* function_reference.hpp
jXG+4oBN1FVXuUoy0aaYkqI8gEnI6+HcJISnStQNDENYLZ7GWPGVOLKJ0FS1NjLiO20DryaGt14MrVo/tGrD0F7j4S5f49IFldtn/xvMGd5/BcP7R0bpb+Y54RhbQ8GIHeYSkWGhlp9SxAXpMv/iCbEnjBjeEC0ud22YUaQfzBjeAR7E61Sf1e7MV7vAa7XR8kaO6EbrXeLVpFkdWMAQclrMFojFlOsdEA4NVkYC5zvJQEyBtKBWKEdPS3P040bC2qQnjaWcNEbpSWOYShqX8VlsYOJkY2brTT3Fm2rvv6mHeVNPhrZOZSdxKttkoLInuws2ODMUyeiXqNQoaUam2aofWbxT2uwERpLxz5sgygB81fUcvc7gvVYaei3mm/bXdhpCcdpUK8huEqdNVe1Um6lcsZdU01cS30oSKBU5yXqKbe4U5I+5pAIMxPN8a/Fd67oEs3JzU1ZMzI1Hydh2umqku0eWikuXdukn7hrNhL8gij+EWashKHjj1YByDO83idEK+UEjFmYjsSjThryxiLP0qk+FsWprMJ7uF8Y9uomVfcVfVHCdDGPcOXpDz55iVEK2N4uTxL/k0jjZqh6jXqxR7eSArNHXk/8r1mjGZP+sEROGxrKisoYibrfmf00snMrGAJW9gX2AKTIaXMGEkr4n3n82GvUd4sS72evE6wu+V9ImILZ07kG3bq1+J13zIJrVgMbjrAGBv/mP
*/