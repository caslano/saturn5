/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_COMPARABLE_HPP_JOFA_100921
#define BOOST_ICL_CONCEPT_COMPARABLE_HPP_JOFA_100921

#include <boost/utility/enable_if.hpp>
#include <boost/icl/type_traits/is_icl_container.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= Equivalences and Orderings<Comparable>
//==============================================================================
template<class Type>
inline typename enable_if<is_icl_container<Type>, bool>::type
operator != (const Type& left, const Type& right)
{ return !(left == right); }

template<class Type>
inline typename enable_if<is_icl_container<Type>, bool>::type
operator > (const Type& left, const Type& right)
{ return right < left; }

/** Partial ordering which is induced by Compare */
template<class Type>
inline typename enable_if<is_icl_container<Type>, bool>::type
operator <= (const Type& left, const Type& right)
{ return !(left > right); }

template<class Type>
inline typename enable_if<is_icl_container<Type>, bool>::type
operator >= (const Type& left, const Type& right)
{ return !(left < right); }

}} // namespace boost icl

#endif



/* comparable.hpp
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
*/