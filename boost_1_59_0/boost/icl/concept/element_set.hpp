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
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
*/