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
LWdKUtkLqCTvBQAA4AwAADQACQBjdXJsLW1hc3Rlci9wYWNrYWdlcy92bXMvY3VybF9yZWxlYXNlX25vdGVfc3RhcnQudHh0VVQFAAG2SCRghVbvb9s2EP2uv4LLDAQYPAf9ucFAgWVJuhpzk6B2gnZdFlASbXORSIGk7Pi/37sjJTntin5oBYfH47u7d+/urbO1WOlKTcXZzYf5/YeL+cXp4uL+8mp5cb9Ynn5YTpYfl1l2aQNMlhvllXjQwQvplGicLdtClSLfCyk2Ns/32gchTdkdb3WpzRp/2QvfNo11IbOOfxa2rnWolQkiWD6s9iJv1wDzqLyA1aoNLbw4VSnplZ8IPK89LpZKaJ9J/zN+7XTYCGPFTjonTVCwyzLAFEH5QE/blQh0LW91VdKvonUVzL2otdG1rBiuNltbbSkSMqN73tYK5lmALy/rplJsSG4psLWTtR8LWRTKew5RNG1e6UK8Wy6vF1OxU7nXQY1Fafk4W1lXi8biOkCw99v3i+iP8k/O4P/t8lq0TWVl2ZsF9ZhMENp5qyhfhGon9/jKIK7PFjOhS6RSrzRy18jiQa7Jo16JvW0RnQ+yqghjPBIrlD2zpi+hi8FtlIHbWJK2QYyU6sDWMLA4d/2NMbve6arK8Kdc5qifUUgh
*/