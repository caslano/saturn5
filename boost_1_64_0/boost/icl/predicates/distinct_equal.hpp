/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_PREDICATES_DISTINCT_EQUAL_HPP_JOFA_101102
#define BOOST_ICL_PREDICATES_DISTINCT_EQUAL_HPP_JOFA_101102

#include <boost/icl/type_traits/predicate.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>

namespace boost{namespace icl
{
    template <class Type> 
    struct distinct_equal : public relation<Type,Type>
    {
        bool operator()(const Type& lhs, const Type& rhs)const
        {
            return is_distinct_equal(lhs, rhs);
        }
    };

    template<>
    inline std::string unary_template_to_string<icl::distinct_equal>::apply()  
    { return "==/0"; }

}} // namespace icl boost

#endif


/* distinct_equal.hpp
YiZrrzesIy/l+2GwXQVR/nAFpYC45m6Ejz/N8dD8ulTshK5B413KvwJkOa77m1wKjyQQLIRzr1eVl+L+VUmVPjBqWRm42UQOv/LppdhhDasi9GSBRy/xS/5qztD/4FGWJ8ty2+KqA7qdpaWtt2MUyV9ABX74LxUaWAa3xZGzsn65DTw1Y1DqCcdhui7VhZJhurEHJHU4aHEpJJV3SeP0CFfw3HBS1WmxCQRsew9s7GvhFkBXU3RAxxLmT5b4e+YbKjVR8jGYLEvB0cDj6dHngl+Tfh4SL7nJgb537h/Bp6X31XDbLIIEnuZQv4pYX2rYzH00/tBRUIucBDO0YviB78m2RAPhegQ3ia6QYi2bwwmrTYoj3h6IiJkjfpCOe/u4SRSLrPYUytJNYPy2ILwU57+vNkTIex8fl39hWt0WplatQnKFS9cqmikbL60TpDzaynrLQSy6YssKQHTmuR7fXrpfRiU3+Ij1wA65FQTHgCQyambcjz33rxVkIevXfEJc8Nz15IvEGc1xRpbuCVYCiLUA6RReyhw2e9pTzPUbYjkm8j8LnJDfE/q2Qw==
*/