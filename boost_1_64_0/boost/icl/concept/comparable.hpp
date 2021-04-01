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
K3oNsWzt3JaNNNGxwJpHuq6nxJqXn8sPx53KCO8Xjkw9nIP1l1b5OGdNcqjqLD32ZWWmSPhmJECumSQ8o/uFOmZlLETiO9j1SYTKi7f3+nIfk6fa48R3qX/Bc8WBrxWv+LoNYcTCBWlmoR7BGNCR6a8qP6QieGSL3M3pKQQ+/C82VM2I1hPk6DqF2zgXSky0aq3J3HiklDeqaETKoxoZOjoKH+ZEYvMGk/Z02ScK7FRubBh9UCxBQovIteLDOy9a+w7oN/ukoeL8NfrZbswxxtx8tHIAYjwOCFmTJ+M86hqtEpcBnsYuZirJY6U5eYGKfyOFrzzBAyPcrD3GFueEZrXrFdNhcNiqBqNd+u4p7XrvWpgQLMNHCK7LVYtxiexO10thCNt9zVQPwyg3LuRYV5fXW7Tg+h0x5stofE4HmcZgCtbucJF8V8il7/9Q9XpsmoFGOJvnKNxbnkpeUJXikTX/yuOCHsgn/L0byyaGbl3TCdN1HZumEeC6pM97x0uU8oOElEJBzeUdflUpOM+Adh+cMMTy7Yzlj3cSWdXHnFhixuQExBaV9f0rSw==
*/