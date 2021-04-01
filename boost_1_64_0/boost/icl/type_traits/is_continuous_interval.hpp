/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_CONTINUOUS_INTERVAL_HPP_JOFA_100331
#define BOOST_ICL_TYPE_TRAITS_IS_CONTINUOUS_INTERVAL_HPP_JOFA_100331

#include <boost/icl/type_traits/is_interval.hpp>

namespace boost{ namespace icl
{

template <class Type> struct is_continuous_interval
{ 
    typedef is_continuous_interval<Type> type;
    BOOST_STATIC_CONSTANT(bool, value = false);
};

}} // namespace boost icl

#endif



/* is_continuous_interval.hpp
KE/IQk309QiAdXNf9tW6p9CilQdbhT5gy59eHuaBkQScl03c3Agaec1ruZYXQYvP96a9GPc0aUH69KMMdo6zalDtSm5EHQlGPbBKRJPlXiJeqfGJKUAQ2xpJcLho2ncKJ7n53+NBIA4nZb/+m+6oxJWTGxEmhXquuIwtoQomQjpkiau8DUxD7IBN72AFszeZ0QlJYYmxC+bXxiRIT43egUcadR3m7ADEBvERkWm0Hi55Sjeth+8zwT/TCSUalry/ZP1dU+EPHdTJBlkfeFuKVDkPmt4WBRWeAALaSCIMHmrE5lcNw3ToRtmchybF3ZJqlzxVsWjE3AhFZcOJblEvA2HKwfKKwORjEcZnuJVlMLAxYnYlD7HU+zXtfW2OVXZ0V4iUUNfh9yBfI02csaHvEKqaPHSM15g80rLZugCNWUf/U03qTmSRks90Hou6Jv+Jcy3uFcHpDPvMGkQ5sSKvwwI2ZswZuBBif84/bhnKl2BOwDB+IBCbPLuveShUYa6jCVsezWYxzKFF9rK92fWckk0iDgvoYOjI3vCibMITi/0iWeT362tiiTEW3A==
*/