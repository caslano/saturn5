
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).
//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_MEMBER_POINTER_HPP_INCLUDED
#define BOOST_FT_IS_MEMBER_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_member_pointer
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::member_pointer_tag> 
        >
    {
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_member_pointer,(T,Tag))
    };
  } 
} 

#endif


/* is_member_pointer.hpp
ZFkupBr6pR4VbH8J0clvzRxi873ofS9faP4KiNKYRL4lEjo7xp6+bulmCowMN0xtoATdT14F0R/ShfdBwyh+Kzh6fe73rSCs5WyJbsLl2DzH9RRa2peUhd4BblXvCLXp9zeEUzvAtjr/F7kIHrYKqIS5NVQ4xQ6U/RL9c7aU5Hmq988L9huzMINwJH4TW09LvOEqjMAUKksJbGYG/O74ZM+ILQekz63Z1rH4DSQavS4Pae4rYwiniO4qmmzUCoVc0vzUhY/3SP4po13aJB4A5Kf/5LgRsreaKQKBCdmiAHZ5nDeun98Q1cIU4Pf30ipc8KZB/zPU+oRilKu5NBHH1q2RoCKjnRSNRVrq9Lg9y5gRtDs++uKFvlHLrxpAO9FN8Ra4IrzQKseXwAbYG8c7v/rIJ/idK/lN1VZ2EJSJBPDbkHfIi96UzKKAPx5X6RsIkDzJHmWAAfHg4joQNDBNTTHmSYRn8KCioqXTgvIpLH/qwW2CEWF+SwS/2DjjQdPynpWrLIkYJKb+AA/pl7QDqul9vM9qoOnGZQIbWVBragQDP4p5rtB7tg4m2w==
*/