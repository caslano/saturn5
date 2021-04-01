
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
+7GqCZt+dzkrkK9oYhjrpy1HKxgumI2zcTjzTFELsYLuctGYotwqrSCd6PiA2G7+QaNF/36grYUeMbqPsxiYj/7BRQvfD+y5fYiZhFqDvdNSMXf9PbedZNahMvxA2my1YLxyKe8Af0iljxSkl/NS6Hbt+75y1uNGJQB3JmhyO3lYUjEvGd8VY8JLkYoayRPzcYxl1qWwijLi3HCibQgfJOkRKaqNRsfGsTjMLUCI3MNWNDe4VpdlmPTorVwyZR3dW/2qMhIyTn9gfqH4SIfcstL5dbJBzAvhZllbOgqsQZm0l7U7Yiu6lGShyppOZsHajR0nkUOGRT0kemqY4Szybqn59zlzabsk6C9Ne7VkWAAj1cTA4xjV1w33ERzNGuV9pk1RBVYhoG5oU8pKnNlm7j+m1lgoWGtALPKT0n3Om6QWFkvfx2JmFeYPJ2dU30TelDvKC+YQzYI5tj2+d88HYEueWVww964LDMjPuCctF/uE5QxJeVNeFTWxPY/zTkYMVytDpkXAXKPKh8Y1nr5uuomAwicU3z6OkD4IDnKPqWs72aEuacQpUzY+NQ==
*/