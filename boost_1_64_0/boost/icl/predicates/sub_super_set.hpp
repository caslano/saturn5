/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_PREDICATES_SUB_SUPER_SET_HPP_JOFA_101102
#define BOOST_ICL_PREDICATES_SUB_SUPER_SET_HPP_JOFA_101102

#include <boost/icl/type_traits/predicate.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>

namespace boost{namespace icl
{

    /// Functor class template contained_in implements the subset relation.
    template<class Type> 
    struct sub_super_set : public relation<Type,Type>
    {
        /// Apply the subset relation.
        /** <tt>contained_in(sub, super)</tt> is true if <tt>sub</tt> 
            is contained in <tt>super</tt> */
        bool operator()(const Type& sub, const Type& super)const
        {
            return contains(super, sub);
        }
    };

    template<>
    inline std::string unary_template_to_string<icl::sub_super_set>::apply()  
    { return "C="; }

    /// Functor class template <b>contains</b> implements the superset relation. 
    template<class Type> 
    struct super_sub_set : public relation<Type,Type>
    {
        /// Apply the superset relation.
        /** <tt>contains(super, sub)</tt> is true if <tt>super</tt> containes 
            <tt>sub</tt> */
        bool operator()(const Type& super, const Type& sub)const
        {
            return contains(super, sub);
        }
    };

    template<>
    inline std::string unary_template_to_string<icl::super_sub_set>::apply()  
    { return "D="; }

}} // namespace icl boost

#endif


/* sub_super_set.hpp
IwBdYTL/9brgJ5t3jF/0BY4C/m6rVZJD5TwSyfcFUBMqMNV8o20q9ap90/RqnVKDc7YkWaTXurnaXq6wzweG9reHTSh3x5WJnIdc/YqmKU7sB1a8mk05F5yZeoZXREX3mfnEAzb7PNUq4Z5m0YH+mYHnIf69aH7iBnrUIhvKtXWcuVeR2Is+/x8DRghJpCJmG7XUzHMA3YTxpP5ub/7zBi344f/c5QEOPGJ0s7G+zhkRJKDf7Khq+gqm36wzq5ZyUbrwrjCHY5YWlsDLGT9SEovQZ2uPtvEo2MStv5QEI0ekV2UGkwIXi+ObOTQaGkxG9r1YQmQAYsEhzMUasXfj40ulR2Rw7hSpadH55bLjwFRS65oH5MAnZYYr2WsGWSAxAXiqoqa8nfcEG+TW2i5bw9w+GxNr5PpUSLrsrmx0fNi/ZUvcdJdhVBXcB62SzMAp5N7gCm84l//inWOfRkLtT8qV42C7fQ3N3Iub/tS5yKeNXnq6zHxWPh4XdzQtLEt4WGtAmtpg9XydyVF7+8pv5Uugpzm9/R0jxHeQmQvlTY1MxXy/2PGhk3ESnw==
*/