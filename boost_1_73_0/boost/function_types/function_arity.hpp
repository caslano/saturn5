
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_FUNCTION_ARITY_HPP_INCLUDED
#define BOOST_FT_FUNCTION_ARITY_HPP_INCLUDED

#include <boost/blank.hpp>
#include <boost/mpl/if.hpp>

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/is_callable_builtin.hpp>
#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename T> struct function_arity
      : mpl::if_
        < function_types::is_callable_builtin<T>
        , typename components<T>::function_arity, boost::blank
        >::type
    {
      BOOST_MPL_AUX_LAMBDA_SUPPORT(1,function_arity,(T)) 
    };
  }
}

#endif


/* function_arity.hpp
YBxsCNNgUzgUJsOJqtd46XdhlDGXeA0O5TmBaTAMDoND4Ug4Do7S/tNoWAbPheUwA86GZ8HL4NmwEo6DV6u968SejidUfyMFEzQcwUg7DccanUe+AUbDG2E9uFb7h9Ge6m+RcKP9ryZIsPa/7vLwvoL3wCR4H0yGm2APuBmmwSfhefAZOBW+Cy+GL8Gr4FZ4G3wV3gNfg/fB1+FDav89+CE8DD+G9njDQZgKD8GJ8DCcDr06
*/