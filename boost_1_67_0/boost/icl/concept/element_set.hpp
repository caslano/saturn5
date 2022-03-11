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