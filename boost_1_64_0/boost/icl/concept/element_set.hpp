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
U+qVN16UxL9vIfJcM0OOX3vznvGAQYKPbbS6t9IUeMI5mZmcnmWBLwrJ1EybExeH2TlGuOgpDmPqcH7ppJExg5vJLz+0dO7Rp+VYPf1UxtJ7AjOqoBMYq41XK9VnVmjQIHXcgA7Ba7fgojaLH2HALYPDrrlG1Awy0rn8vgCNby8dsxswZFppxV+X22w1yl+ZyRXBHxlpN1q5y+6y2TC40rRpZPihlqfi3+RvaH0UXns7IvxmZo4dWM6d7BYtfJlZNu4eauaiHY+HNmrJtawhvHoXLgFB5sFudGXwtR8f0wtrny8UdToNBO738bxu6Xak5rvVkRCakLfNjVPleYzuOzA+sTcWjT3ZPNLz7Z9CT8PpgZeh0PkiARkTlmyBIzpSzcsyZ6E4JQ2hAsvGAYCW3qVbfIJ7eOD3cgVPh4DRasLKSh2u7g9+cDQCz1RiaZGmnxItAmwi3/FKluaB09MsdqdbocwFOK+WzExzOlYSynJfP3oPkG04W5WsiMGWJnG85/XJ3orczmiu926CBDKTg3LJQqmINaJwGqmsC7LBv3OSi4zgDqcOHvtOdjKDm4BPXIG01sjXhTpSIsDr4lKos3UonF/P9mDBFarDe9Xf2gCTXsjrERf+klOaR6p0NDoxrndXbs9UcaiGLSs5xeg0N4/0nlVm2tIVHl8WCp2fMEhWMtXFVUdbfkJi774xshW1cAtSYF4kC8rHi+PycpuSpVMUSS45vndct+iByTH9O2I5JCYptUM+tykK5d9i8WYrX2VYImzJCdGJ6nhyXLeERHXa94zJFmHx5kFckwfpAvOApjRKSWvO9kFT8wucAdD5tzFyd9S0plhpLjO3k04NvUBZpYFqOheFkXfk8e9nNTwlS7IVpWl56IfTY9Kl5voecSnnu6jDAKQ5HwVN2mxkoYJo/GjOV96zCZrMzlSHhZ+2PE3GNz+S6urImereRtFB7Fe4Mne6jMoXheD5ynqb5TOUnIf9XpOB03i/td9GgM4tFMbQm1af/ajGFfukA0OabsUBmVIpDFxB51x8DtXnSf5lFtJOoNUqO6EZZu/67NItLoZ46NxaKsyW40g1e8s1YTTkwhvlOiPCm7bwska2bN7IyW/8a+QwZ5qhOh4JcJtI9XMXk29nBQYz9zG42XAWrk+2VBRH6tBQ+C22027DSXGeuojQ8IgkN/B446aRzsah4c1MgzhPmV/F11HmQKFxs8fT3CpYsF3xoNY7HlPlgZK6cuRdKrSBU7oNzaC6y9CQ6FHl1iSHEhDsL9WPn2FsbVC1wc2S6mlqCAsfGV7fIx8H3ZUCNhqIqOndOkt0D81bo4oW4zVNCi3Bq8IKzaAKhZsLrJjCnjF55N2b02/Kk5uW56MvG4uQJuxrRvr83GL6g5X8r0XjQffEN8n5qjTzlzNALgpABYTNBdR3sBD1FSY8u/8jXwxvldtMNQT8Pm3s4HA7UjMNtQ21+0c34peovtewUmkGQ8SLhp7GPIN7YZMnpORYMl34Uqw1fGG7A05yqgXr2OAmmxoaTFBetym0m1NVa4H7yjikTMONn5LWaPzAzt36tjbU/scaodpUQIjp1bVbr5iEf3h9uBp5CfsirtadjZomNy2obuW7w1wch3quxIKCAvCP8C8ggMc5pgCF5pFBHARO5sBlpLwycudTZDlN5gG4AP6kMnhcDjyPRPO2R8nPeYgr7QEG4A88nhc0HpdZwASi+oSX8yDH26O0IwiLTx/FxfKh+qSPwv8ofT4hTVGchrie0zkNGDGeR6JxrkSPAh9xTo3iHA+PlyOVTRw4HaBXypPkvDQuy4PcHk7jcgiyLG+jl8bzAHgZSn8QB8fTJ2BPu7kMP0AUdAA=
*/