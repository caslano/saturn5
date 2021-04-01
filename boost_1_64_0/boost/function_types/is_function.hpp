
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).
//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_FUNCTION_HPP_INCLUDED
#define BOOST_FT_IS_FUNCTION_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_function
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::function_tag> 
        >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_function,(T,Tag))
    };
  }
} 

#endif


/* is_function.hpp
jGf7Nlaxb+4gYm2W/FMQgbMLZAj3Qakj7SHmILP4W73X2+GLObO6BMq4OhwUA+6x1jDnJhYCzI5iv9utfQk2BVaKMU2Fb63BBiEvTdHEdBlXj1/51EmZnh1PsC5qtzuDq+6n0udf5lClhmnyT5kbaI3hVXDS43HlEvxQQnqgQAqqcD/sr0G5K+owNkrc3Wwa9029HmxM1yHx6TyWDPLIFXLHCdHTiEMbB6g4DjALZb7i+RwUQQmhXiYpl/gg8HyYoMsWsr4UYfZKczLQEKZLM8SdlQQZLol7NqMSA1QT5PLMZeiXIiZ8/UWFEFkYvaw8uPOm5woQKkcRITd0sJllFQRhpng+KVKhDfQUVHP5W1Ba+hm8R9N7pzT0Dg84Ml/gYn7HScfZhjxr/CWhDd7cb1pE9mUxrr8LOn/ryOFtC4x8a7pVI2UM0hllFXTdsA7tKQAaw298pPMZ6keBgDJ+pH8uJDrZPJPmnJv8OazPbhkf1uLX7uLcvGnHhOxZkpeJfoaksg974+pAsLf0dW1jVOLPb4KIEqoiTm8X9DE3JynP/qIotyeVhak7ew==
*/