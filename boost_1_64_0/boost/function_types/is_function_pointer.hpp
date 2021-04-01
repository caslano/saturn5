
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_FUNCTION_POINTER_HPP_INCLUDED
#define BOOST_FT_IS_FUNCTION_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_function_pointer
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::pointer_tag> 
        >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_function_pointer,(T,Tag))
    };
  }
}

#endif

/* is_function_pointer.hpp
HwU5NGMmjlhw0V3em6vJRiVTiCeWBzxzQFPElgbUOAliwuHKKmktIh2x7tbd8dSgyo+afPV9RDDBHla/8o+blN6t384Cz+AW+s3C74AotJeDrmKqJl0wz0563xEeN4jqwI7IAjMuI649wvy5fewJ7KDQkHZDbTDSKXqvbe/nlc2bPTZnaO/IO/f04sF2CG6zePyS2Ru4PEVlhlY00WBhWQjgJq+ZbIgy0YCPPrWVs9bsL5G493/0BsYepYN3Sb4t1UrswRlTVefOmj7etX6cOb/ompYZb7MQx6pbimc/M83XSys5Q6hKvS5mTg7Y19iTwFRjOItzgu66Xzc42LXOnCSE7bXd2Wz6DrtSGzxdkw5YnLdaAPKjduO35meCetUP6j1ZGgekh1jqeygazcth+moaOPw6wndyB/DDzQgM7YV+Nw9LDKBrjDKWms+Du4mvA3gDjYkggasHOIFpA7SKauc84uVgiFF0WndZG9fYKh/Btz1vTxK8MAqe9P3+V9P8DRP7hKok4jNXpQRX7E3a/Tkp6UvvnLh6ajTWzNCn9FqtV/oaiN+/YQVXSQ==
*/