
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_NONMEMBER_CALLABLE_BUILTIN_HPP_INCLUDED
#define BOOST_FT_IS_NONMEMBER_CALLABLE_BUILTIN_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_nonmember_callable_builtin
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag,detail::nonmember_callable_builtin_tag> 
        >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_nonmember_callable_builtin,(T,Tag))
    };
  }
} 

#endif 


/* is_nonmember_callable_builtin.hpp
tzJm2ab8KyW7970CwdErcIMMosyFK6KY8uB9lJ8nyxzeB4tFMM9XkJxBMF+NeBfR/BS5wdCqBHrXSarQCwls27WMVo+Mf9NOd/z8HGbLRZykeZFl50W6PImjWXERrs6iOISX4B69hj96bhj+ygW3ZVeGAnDsvzz2D1FgngpK1K5QVJti4w95pRA6O4d5cBk6/4O/fo5F1gMHStjQ3cDvGmPH00B63VicbDVP0izKHJ/XzneMl21fUXhjjA+UbN461k4pUP65TxOzA88aJEuLnPmyP57z5dlQNkTCM+MeJ1t68Iv16zTMZosozaNk7qQEi0bGc9AJxjXj14ZmBNZ1tNdc16mND9tVPgjch6gGLrTplMpz9nmuaE36VltWr+uT78+Ty3DqK9VMWVVUiviIYBDZQFmzDZTfMCn4lnLt3BDJbA8bwlI9NMyHXmlw7wHc/XBBkxK1kM44PLSQO4NrMVEdnXMQwncc9HS+jGOYYBhIdbrt9A5MA/DrA3Oyw0xgELAP4pa1rRUixsNaa2HixGBejJPMOIGeSNPqGHAptp0ZB9jctRw7upPshqDMpmxoRPxuuLjljul8ITdoTzcwIsOR/8o//AEf+cbMwmvCOEafdJRnWYzBmPlHOuyzkhji4kygNtZhiCLkhtLO
*/