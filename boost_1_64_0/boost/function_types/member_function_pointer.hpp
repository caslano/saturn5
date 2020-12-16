
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_MEMBER_FUNCTION_POINTER_HPP_INCLUDED
#define BOOST_FT_MEMBER_FUNCTION_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/detail/synthesize.hpp>
#include <boost/function_types/detail/to_sequence.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename Types, typename Tag = null_tag> 
    struct member_function_pointer
      : detail::synthesize_mfp< typename detail::to_sequence<Types>::type, Tag >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,member_function_pointer,(Types,Tag))
    };
  } 
} 

#endif


/* member_function_pointer.hpp
oAh9gw5W0zyOZuXfJ9sNPyhXqp725+bQtEAr1nFTk+x2bYfjlyFobK9DuLkrrXOKpJU7h9D4S1NoT7lA97f8x+/2RMO89zCPqZ9INUOWsPgPW+DeNJbk3FzhOjKYPZ7fQHvz0nnUkIPYuKkUc8OTSObVUb75RgpMxzxjo4Jfw/LnFRr5bQ22BblSgm85tE6/wu0GTyh4uXHLPHXs+1pCS0Uv0+zYWjr+/TxyP6rxeX/+Q2TfFlzRK6LHR5KgZ5CO/yk0D78QvDaKnyurJGVU9qjICKWIhpWQnSjSNMqqRJEkWYWQkpGsKBkVZVSy+pEQhYqsqKSQUCLpnrf3X7ife+/znO/31Fj1QmR0Lu7dPSl+GVWjnUOd3PVdn3fttBnT1x+bso+KxKluTDjbR74U5+k9TA0hZZnwOGAsl9UdR4fUGTww7TuPzIwBjM6y+8G5sHBUxYJWHtLVJ5L108rZqBSKwg0LpJbvF8wbOlKoG8UhNcyMKcxE4R8zaeJRB79Os2ScQhmWjenCCRXb+fONkRz8Zg5WRf6mS4obbwa2QfDTq3AyDBLnwp5wfXYO4xeFwzQsUlqa6mK94SXWPV/MxKrWaDVsHTr0TMDG6mjuvfEIdzfZsXJbCXsEJPDBCgP4LzKhPKUg3u6/wsKQkfLd5R3MtRvObr0bOL7QUDzLW4RZ5xyxT9cI7z0/Sa1utSy5/5/8plaOoqLT8uzRt3g1OEbczz3FFatjhIrzdfqaTkXq8UN4+mmiHHA6nemHh8m3568yZk8Cvgy5g1a7VIXT6TFUfRuH1/dUsbX7IC6a4EPTL3ZSd1YCJt4043W7o00MRANVPqfxIb6YUd5reOrQT6HZ6xwCXFfJ+A5ToXb0jTxi2AIdPE9y4vx/TPD4DqUsPzbye1Omeoa3mS+k3yk1fmi1EDf1r2K14jZR0WUnCyy2YtDa9UxxHYbI+csw0aCcSod9ecmyM2JtH2PEzs/41sMFq47kwvVwIPosfy19vC9w6mXKnyNT+LbPBWkco8/ZCuSqtzeY0blMqtrN48RuWVJdLZI1fpLLHy6k4hMV8WbIYSzf0U+46Gcyctg9mT6qDZcPrBDZLVV4ZdtY+bbsPP3NP4nSzynscyNf1l6vx822M8XmeQLF2xKg+C6L4wKtcOalA4/EZ4lx+wCLJYPFhflReLlpCk/oDsMxta5iw3d9fH14kQc33GbfOzfhdNUMpyI2kLHD2E1XTb5wno65+17JntoPOVexBTz7Z7NqhQtGmg+CT2o7ofdjDQ6JNzwam4G/7bYI00EBHPumgVMMUmE0fxM/zcxkSFCg6NT+OvVGNZ13RB8k1reRWru7o9riEld7jMK3m5eE7a843tT/zfDZqUxQ6cfwF+7YU7wOkdlHmJ+7T6heKUJCL1tS6wrWFp8U2cWOtGyZztvj59Dg7CGEdfGncU2K7GgRgn6hGbIxrwWzVweLgRc+Mtr9Og42nIFhsAYOHp6EiHvL5f5jLfht7xNsPLyDdofuyVYWZ/DveCyrpw+n5ugR7PvOEVXXlPkk5xk69KuTPaw+IXhFd5GyGvDxXSO2tvzHfUEnxdLxu2GtU8JvJWXMKQySMf6LmOb3GXorPmFca2NuDdmEC+/HyaSjGSgvLpE/X09AqspaYR1jDG//johxm0P96oUyOvgFPHlG9rtbiLC+M0R9fACOuERTw/A1D6iHYVBkLHUDr+HutEr6Bj3jueByFq7NQuV3LTQatqLPkqHslBPFlJBL1GimICI3z+M/tePC0rQLwpar4fJNUxpfNaHHxOHMah/EyPe2LO50iDvVr/Jv9GN81cvjjP0/xWLLp3CbnojFYRd4KKRK3MoMwaqZAeI=
*/