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
h2tbfAsHc6wuFt2Bn6BBaI9DZ2m6SaoxpCzwtgWsnDpXmVTxHfbsxZ49FSOTruiqiap2SXz3QavSgL7mwszZWT8furwSJ5Xxv0OrdRqRYne0l1juy1KwRMGytgHY1j1O2i6X+tKmslVawoKD+mierEFPbXMBQEuE2I+FXYwOR/uCM9exIeXr0LPvSbnkziLBlH7MtvYNO11/zJprReau/BQ5ebv3YBx+wsV9vuGCYQHqaPoAhBf9+F59VyPnqSMqQ2HpOqqcicGQ7ncl8rK7FKMUvSokr2wjVuU1JFweQgpHxShyOJx1MaQdeGgLKSqr88VPIzBccglSu8JRVSmrP6oIh0WGnBmGMn1ye3uLVeZ03Zu6yRVUsVffoJE8ikWgrGniTBNOI8VYyL0XmmW6WJ/6rWvetk27Rp9aYA/bNvw0bx1+Nm3fQ7YOP8X2vWhudA+HP2j7JJz7mf5B0Kpyv+GyfaX4Vc0Cf0JVGsy4hNq58cfx1vht73ywjy3g6zmi1tB2m91joiq6XIiQYmMbLC/KCD08HvdeDwcTHJbtL026LXywqiWcv2DD7nH39fDw7Rm26xRp5kQJYE6ZBU7LERJV0AIuX2ZZmlds0Dy9m1QsBWi6BW2dMqZaLdm8bA88xGMrah5cpVMse1AY
*/