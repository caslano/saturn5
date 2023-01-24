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
MwoY73CqQDIkUGdNU8SQXTusMR02B+l9P16zjM2Eo2zzrEWoEnp0GiYsoX/vR/6pzvBo7vLxC2nX331nvJkUckKV8AVkxgRM0+YxwZ2aRYqKf5Y3bAW7vKuhLp63ttDiTG5LDfXvXzhYZ2ZtWO+wSTcy0z7wWF1FFsxt/4aeQ7675bOQ6RwBy+Og5vn91nS0qXsWzJ+n9F627Ffxy1PI6ReeqjbDb6MDag/UGWD8cmIklLjjQLdHlpX3AnMaqJOv3oNRRVKw7orXaJB5WCR8fqNvSL+C/bP/I9ZaL5bAGG9iJc/NNjeRP/CQ+PKo16edMv+RtIzHAYEr26Ic0YrPmO80bk8Cz88d7HBTeMJ3bEdQab8kkKT/bHS0QiPh5tNKpp3Ls8Enj/1fmtUgnVlKiaxDQfz5rdidjbs6W2yZEVz5smTBDqDJ/RDf+xSsqfr6yyapl3zXgyzOJQQVy6aIUWL9Az7vsYi264ZsQES1NkVTtvNB68YO0ip8H+sbNOfkb7rIdyxx6NKqzNCYqsdReQGPUekwa/sNHyYT+9o3NPFVl+3LCRVyN+ygxYJjXRu6e3mwfcdW4Vl+htdJFZ/XzyL5xlIut12Siw6Aq+7+ejMj4E1AUIq5rpKVeWKEOnnXZ5n7BHYPoHTeaCLFYMDWbSZ9CTeiHtr19P0DvH+Wnh1eKnRWaktvMVHMrGumvreguvtlJsZRdP+Yw/9B
*/