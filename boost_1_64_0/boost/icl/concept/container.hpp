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
kkK14pwd0v7hhsNaGm+akBz5tBLqLxwLVZF0wKw+xHi7m6C1SnLxW0hE5uh5G02MP3ldCVxC7jcAawb2orVhVSOZm67KsWa5/sEwcWX37YTjQixlTPWjKs6XV6extSnTvazFQse34YcKArCVUam46Ci2xKqKOKCQXgzF2EYXkOAwnRlu6kbpvxUn3WP3FwIplMAA51f0BxpBkAaBVHB52FU/4J4sUkmNomxLhY8bSU4Z6+Cajwm8K1PfY5uICZRunpNgsgBj31Jh4oFBS1ueAcLAKqVzSq4yBFkggojdddiGSDN8BXALzdw0pbogpttcLFtGezKuqAIUYuy1+WcXd4PkSnk+jbWan3VH03UGLblUOzLS1GUFSOnl1li3lkA7w4Zo8eRt8HE3kF2S8nT5yOMgJYA+H+M38/Ns1DNM+8/taeMZrK0O3RZ8Ud+zM8Yc3BDD8Z57jHcsAdgoGHAro0z+Tb3/N1uOGhsKpys+epq4Xb+MEstZeudGI+681yjVHf9iI35sPDmCZA9x2dPCHL52Lf5+f+H+f6xErfN3dTYgBvwGng3zFdoH8A==
*/