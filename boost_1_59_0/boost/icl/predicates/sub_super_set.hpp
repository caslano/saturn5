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
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
*/