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
k00qg+Gax+7Sth9ZvOp8jyzmeNihuzVT1uKqCMrrDmi6ldbtuHt6wl5NYu12ygtbFXCF+4nCrcEyJ1lIBV5yETWBq/lXSGzr70aTMr1+IznK7j8JgheqXPAaz7Xf/8wMGOBXprifLbcObXX5xXSTzFBMzf47oZW2zRqpYCLqXeuajC4pkvBXxm8Ku5YaJR7pLgbhSJhyZ+5vvJkvuXariORIcTrySSQSrKFPqQmOXxe4jo5L4dn6eH4Vv8FHlFnj6hYFV26+mI8QKKyXJw8+XZSvuTkgrCfaNjt5PxwwwN2o+vQdG0FGWKAlV4pygyFbFrKYfCAcruzORp7T8ll7VxnqJ1V4HjulSfHQUMNSc9GpwtsCbUmknBNMraHarSX2rd1pepRWZnXyElPwr6gvYdXMC4iJP3c8OVHmyPxkVv+asJAkRKB/2V2vmTjo6GNRjfT6p/j3vQut9EaCQlYnQpH9VpgM7IIuOapdbeALKHyeAoHAH6J6NZ0yXPthRFztFp/iYSgKWXOs2SxLk8BK/p2Bc0DhB/cBSruQnt39wLr7h4SQ96iob5iALxpUahe/v3hjXmrEf0RU+KFKfrRmWxkqG1AfhxZntEG032q9jtY1R3KILxU/jpwus5UU0Z/J05A3YlKyFKXscJcoz252u4B4vlpu9ZmevVohMzHQfVI0M9Yd54+xU878sjtlerRUCv7FnzeUnU7zq8A3
*/