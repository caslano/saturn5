/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_ELEMENT_SET_HPP_JOFA_100921
#define BOOST_ICL_CONCEPT_ELEMENT_SET_HPP_JOFA_100921

#include <boost/icl/type_traits/is_combinable.hpp>
#include <boost/icl/concept/set_value.hpp>
#include <boost/icl/detail/std_set.hpp>
#include <boost/icl/detail/set_algo.hpp>


namespace boost{ namespace icl
{

//==============================================================================
//= Addition<ElementSet>
//==============================================================================
/** \c add inserts \c operand into the map if it's key does 
    not exist in the map.    
    If \c operands's key value exists in the map, it's data
    value is added to the data value already found in the map. */
template <class Type>
typename enable_if<is_element_set<Type>, Type>::type&
add(Type& object, const typename Type::value_type& operand)
{
    object.insert(operand); 
    return object;
}

/** \c add add \c operand into the map using \c prior as a hint to
    insert \c operand after the position \c prior is pointing to. */
template <class Type>
typename enable_if<is_element_set<Type>, typename Type::iterator>::type
add(Type& object, typename Type::iterator prior, 
    const typename Type::value_type& operand) 
{ 
    return object.insert(prior, operand); 
}

//==============================================================================
//= Subtraction
//==============================================================================
/** If the \c operand's key value is in the map, it's data value is
    subtraced from the data value stored in the map. */
template<class Type>
typename enable_if<is_element_set<Type>, Type>::type&
subtract(Type& object, const typename Type::value_type& operand)
{
    object.erase(operand);
    return object;
}


//==============================================================================
//= Intersection
//==============================================================================
template<class Type>
inline typename enable_if<is_element_set<Type>, bool>::type
intersects(const Type& object, const typename Type::key_type& operand)
{
    return !(object.find(operand) == object.end()); 
}

template<class Type>
inline typename enable_if<is_element_set<Type>, bool>::type
intersects(const Type& object, const Type& operand)
{
    if(iterative_size(object) < iterative_size(operand))
        return Set::intersects(object, operand);
    else
        return Set::intersects(operand, object);
}

//==============================================================================
//= Symmetric difference
//==============================================================================
template<class Type>
inline typename enable_if<is_element_set<Type>, Type>::type&
flip(Type& object, const typename Type::value_type& operand)
{
    typedef typename Type::iterator iterator;
    std::pair<iterator,bool> insertion = object.insert(operand);
    if(!insertion.second)
        object.erase(insertion.first);

    return object;
}

template<class Type>
inline typename enable_if<is_element_set<Type>, Type>::type&
operator ^= (Type& object, const typename Type::element_type& operand)
{
    return icl::flip(object, operand); 
}

/** Symmetric subtract map \c x2 and \c *this.
    So \c *this becomes the symmetric difference of \c *this and \c x2 */
template<class Type>
inline typename enable_if<is_element_set<Type>, Type>::type&
operator ^= (Type& object, const Type& operand)
{
    typedef typename Type::const_iterator const_iterator;
    const_iterator it_ = operand.begin();
    while(it_ != operand.end())
        icl::flip(object, *it_++);

    return object;
}

//==============================================================================
//= Streaming<ElementSet>
//==============================================================================
template<class CharType, class CharTraits, class Type>
inline typename enable_if<is_element_set<Type>, std::basic_ostream<CharType, CharTraits> >::type&
operator << (std::basic_ostream<CharType, CharTraits>& stream, const Type& object)
{
    stream << "{";
    ICL_const_FORALL(typename Type, it, object)
        stream << (*it) << " ";

    return stream << "}";
}


}} // namespace boost icl

#endif



/* element_set.hpp
dsXueTLrvfv1YfIuuIUvIugLijNXEoJ8RvngcGdKjsof6ScXkcQwv5cimWJ6vEhq/14Ar/wDOGD1I8G/+yzo/nnNb543xip4Nv7xeemmsYIiF/ftsll9TLoZUUb/0dvzCD1na5dfsYtJoupBnfRYoWKh6X6wFrt6aj8LH7kmX7g6UiECpb67Zj/IGhGXgmpQoy/HTVfOVDP575VH0K7KXv2/i+fusjt43Rf0uTQPH2U6ghinLN5BbrMM8L9iOIx9fFs41Cp1hF+V4Gnr/PHm7XTNd872p4GtIi3jBVQHP/9My4TPYv7Up9qIy6670zo71rYOiPBfH56etzy3cx7/uJ5eljCNP4xVKTdesLKBMNuhwKdrPuerl6b/ZE5xh13GI61TkqBXkoAIvXonSoJNNd1vmdqvnKBG3/qIqrWHCjLRPz6JcKz+knAZlya9+NPwxofux9mxuMM20nP1nDs3L5kdxfmLzl5Fh0SFw1Ysdpv9U10O4gw2ED3tPigsrdaZEWR95rgdP3r07kbYul3a55f4Lbo+nbde6QhKiPS3aDpNRZRzf0rTP1DVUKv/YWVom5amnQDMFPnmlPXsV1XJiRJEaXJwTyn9F4rbH6V38aC+eivDHyE3+q7zUWwLxmls5dmq9FJ/vghVrMix1hdLvEGwyEWZYU1La6Si7x1yhUk8lKiJjMxWipHPqtoWePqN/uZhwN+xnFuv6vef
*/