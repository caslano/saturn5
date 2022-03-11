/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_CONTAINER_HPP_JOFA_100923
#define BOOST_ICL_CONCEPT_CONTAINER_HPP_JOFA_100923

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/icl/type_traits/is_container.hpp>
#include <boost/icl/type_traits/is_icl_container.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= Emptieness
//==============================================================================

/** Tests if the container is empty. 
    Complexity: constant. */
template<class Type>
typename enable_if<is_container<Type>, bool>::type
is_empty(const Type& object)
{
    return object.begin()==object.end();
}


/** All content of the container is dropped. 
    Complexity: linear. */
template<class Type>
typename enable_if<is_container<Type>, void>::type
clear(Type& object)
{
    object.erase(object.begin(), object.end());
}

//==============================================================================
//= Size
//==============================================================================

template<class Type> 
typename enable_if<mpl::and_< is_container<Type>
                            , mpl::not_<is_icl_container<Type> > >
                  , std::size_t>::type
iterative_size(const Type& object)
{ 
    return object.size(); 
}

//==============================================================================
//= Swap
//==============================================================================

template<class Type>
typename enable_if<is_container<Type>, void>::type
swap(Type& left, Type& right)
{
    left.swap(right);
}

//==============================================================================
//= Iteration
//==============================================================================

template<class Type>
typename enable_if<is_container<Type>, typename Type::iterator>::type
cyclic_prior(Type& object, typename Type::iterator it_)
{ return it_ == object.begin() ? object.end() : --it_; }

template<class Type>
typename enable_if<is_container<Type>, typename Type::const_iterator>::type
cyclic_prior(const Type& object, typename Type::const_iterator it_)
{ return it_ == object.begin() ? object.end() : --it_; }



}} // namespace boost icl

#endif



/* container.hpp
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
*/