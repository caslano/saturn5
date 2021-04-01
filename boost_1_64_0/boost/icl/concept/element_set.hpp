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
Mn4G0m6LLQ3h5ImZLX5qcIHiPBH68SdFeji5njG1RRMO0DdAtgp7GCfl1yqvnfR0dVYPhkf/VuCoJyTOgyFRzV7Tvsf4jxsyWJWb5y5PJtCKxeV8fEeb+y3Ww+FjDsCS0fbBA1s+4ahrXPAUy+Lz7m+T07dbha3srEOCDrshxWQLTMppfv3Ec6AQ+dSbs2adXusipVjSaHvSQuxv8ErGio374NqCN1xsYnXlHxrsBe7GRIiifNR77LBBXW1v3dvyQxhgv4b6COOkJjcjtaPe4aCd0gmnM3EvFsiRLEabL48l4BWGyMk/uifg+6I9Rf6LJQGMi6Dh7eR+4uRAMtCyKk0CJxILneQ4QHANktDKeRBKN5Bw/FiizksrxOPDg8H0k6JVMM2mhlHX3FBGKX7Q2mVGcoX+S8QkbFzBZ5CmfQzFQa5Kzntdm+p5y7+gr/Pxg3wNCgoR8ite5oF5xYW6+Nwmx9mW6goU1dytCELPAroZkxUydzqGzOcTNbLTVzqkc5CQxoiFYtz0a86z1qVU6hpnR0143N29vzm4BpgXitcTaAz2v1Uu3vvCig==
*/