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
irKu2Sdq9kg6+1pmL0rNRF5f5LKMvI6Po8fLm695i9N5p5q8r0MlgUzQZ39K0NI06BUKirDYf/wFdwmn7ncXyX63Yfvg9IYh44WhHgQwDyRW8hRQ7jJyMyMPJ1Zu0VV1b/RZHxJw5j2rhSokC1WEi0sRF6piWagWs9NKZemt3cXt+h58o1gQdPzEsC+xfI9uXyWx0k09ZkcWQTjHdgFpIojOyy7n5TuFjY5xXn6fXCYtHihH
*/