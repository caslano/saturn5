/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_PREDICATES_STD_EQUAL_HPP_JOFA_101102
#define BOOST_ICL_PREDICATES_STD_EQUAL_HPP_JOFA_101102

#include <boost/icl/type_traits/predicate.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>

namespace boost{namespace icl
{
    template <class Type> struct std_equal : public relation<Type,Type>
    {
        bool operator()(const Type& lhs, const Type& rhs)const
        {
            return lhs == rhs;
        }
    };

    //-----------------------------------------------------------------------------

    template<>         
    inline std::string unary_template_to_string<icl::std_equal>::apply()
    { return "=="; }

}} // namespace icl boost

#endif


/* std_equal.hpp
ymvu255v7PkeQE5RyaeoCGM7vlJygN/8TGjV000uz+N6Uu3PI3kieiBR0xpftXeR7KnW7l3MTeiB3c8FkC+5omAzf3fLiFJqg2ABdSvBe6WEEVnXKIH8xXjxtlbQS4UE3zVB2iRam4iupe7XwfCKm/2qTrhd4QdyyGQ3a7UoeaxWKc7qeDWkYvt3N8sZEYY8N/8LY2jAY2YjsCde3YRdOxWJm6AnAht67DJawiZ1ZHzvB40S
*/