
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_FUNCTION_REFERENCE_HPP_INCLUDED
#define BOOST_FT_IS_FUNCTION_REFERENCE_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_function_reference
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::reference_tag> >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_function_reference,(T,Tag))
    };
  }
} 

#endif


/* is_function_reference.hpp
jSY4Memk5KS7vcXiTgJU0uSJKJ2jDl9fT/PBkWu06JI5jKTklIi+3W/94wU1szSFH8NoHn6I5lG+8sKqcq+20+D4LPjRHljM8uUiho/hfDnzFlTjwFY2l1mRXAFzs9kVyYp73wL+cGgZ22SLxLavMUAd+DhOvQFkmRfJRXE9u04WqwEPBX6P7cSE6uualczou6GkxdYhJXVaGGWzGYTzLMHx9mFxwG64zC+LfJXOMhihnLFeB9uG9yJdfphHUyP84vr8h/05719QSwMECgAAAAgALWdKUnOBCiqLBAAAxgkAADsACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1NTSF9QUklWQVRFX0tFWUZJTEUuM1VUBQABtkgkYK1VbW+jRhD+zq8Y0X5wIoIvTdU0bXoqcciZxjHI4KSWLKE1LGEvmEW7ixOr6X/v7ILzcm0v+XBYBrw788zsM8+M3aUN+9/sslwNB29eqfmmeOFz5xQJ/plm6r8d0vQRug86LvH5jlBDePZ6TPfgXV6PMDBeaR/rVL+n6TvCLXWS+jbUzstUv+JK59n7j3izFey2VDAY7cHhycnPcAA/fDj80dH3YwfOSc1oBbGi9YqKWwdOc7Pye0keHlxJPzpAFZDK
*/