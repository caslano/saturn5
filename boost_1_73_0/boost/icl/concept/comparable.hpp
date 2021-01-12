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
vV9kdyG2KoBR7WxFZmeU37s9uvM8e3vktcT4+m2h13ghgJvbABwkqeyGoMSs5s8oUIr4xz62UMbOm5DbCY4Vr1pjs8fOeGCZJPM1CxorJW/ZZMUP7KHct72I3Kd3sJW0Cv77HJKHTv/afPf2IvE1KhZAV8k8+jKEHHkt3yJkG95RSzTghCDOWkumHQNJJkrh6H5FpKePyzXCfaBvbq14h++/RmZm/IzzZxw/lUQTg7ky5MCF
*/