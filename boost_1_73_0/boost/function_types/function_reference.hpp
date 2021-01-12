
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
gW9B6WeZ7x0Is/oXgnRV/97T8rtby+/76t8HsCH8UP2Z5tE18vo9w3rYFsnQcnw5+RoMV8N28FrYHV4HU+GrcDTcBivgDvhnuB8+A2+CL8Jb4A64Du6F98Ev4P3QfmYeghFwP4yHj+k42lOwH3wFjlB9MXwWzoHPwHmqP9lLOsIOcD/sBm3za9T8JjVfr+aPwefgk3r9ab3+oppvha/Ad+AO+AF8B34Gd8Mv4QfQXrf2GTwF
*/