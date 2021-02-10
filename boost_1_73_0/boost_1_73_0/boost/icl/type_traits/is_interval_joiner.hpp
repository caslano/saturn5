/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_JOINER_HPP_JOFA_100901
#define BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_JOINER_HPP_JOFA_100901

#include <boost/config.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_interval_joiner
    { 
        typedef is_interval_joiner<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* is_interval_joiner.hpp
RaJJ96FUgDO7NmlJFrcnGLA69q7Hx+ZdqZlDVrGYXWPBkaugM9t2/D0dhRl5el3Qp8xjus89cfGhzgOTjMg/Nue0bMyoxdkcvQpEBdKuDrzDEDdMk82jZfrW+C1lbI5h4QQQuAbG9bBd1FfksRRbGIpZONV6cT2LMumYPbGw9d/i3e6ETD5g9elVIfSGl93mLecGtH530L/q93vNO4EtAtelYjdC13N8R8ek19grTTVQlrdpm76EDDoKHb5mzCLRsD1oqHhzLRyL+/xSAoZXTYDuBJZh+6HHETjn5NjdQoJHl6+Dp46Qlq862nGs7tg213ewrrKKW256Rii4h0pGXtda7JDKUsa+ewx9guXlXKbrWPShwW0TBVUb0a6Ox6vbkYje5Sk3XIZ0DZcvtRNsmkT0O6+wzZts/ZMB0LRB2Mg7jpdYbCV+OOF+I02DyxMuXknEUC1FoqqTKZDNX7hcYkfKcujIYDKcQ5ujxBxZxr6QfO8QPOicyIcm8zHoKgv4O3B8Hla7VQ3RlBVMfTSJpgIPW3IT2lPLETc7ha13QlKa1NTgUnE6cC2HGbWGJaiv+I0nEMUXtQfgY0DojMMZnzmeLIqB2gUclw5uuPuFvjnjOGVv8VQv0EYSoTYDSg01KMV1tQ0cZjAQnNqB
*/