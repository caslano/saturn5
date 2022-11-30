/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_ELEMENT_MAP_HPP_JOFA_100921
#define BOOST_ICL_CONCEPT_ELEMENT_MAP_HPP_JOFA_100921

#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/icl/detail/on_absorbtion.hpp>
#include <boost/icl/type_traits/unit_element.hpp>
#include <boost/icl/type_traits/is_total.hpp>
#include <boost/icl/type_traits/absorbs_identities.hpp>
#include <boost/icl/type_traits/is_associative_element_container.hpp>
#include <boost/icl/type_traits/is_combinable.hpp>

#include <boost/icl/concept/map_value.hpp>
#include <boost/icl/detail/map_algo.hpp>


namespace boost{ namespace icl
{

//NOTE: Some forward declarations are needed by some compilers.
template<class Type, class Predicate>
typename enable_if<is_associative_element_container<Type>, Type>::type&
erase_if(const Predicate& pred, Type& object);


//==============================================================================
//= Containedness<ElementMap>
//==============================================================================
//------------------------------------------------------------------------------
//- bool within(c P&, c T&) T:{m} P:{b} fragment_types
//------------------------------------------------------------------------------
/** Checks if a key-value pair is in the map */
template<class Type>
typename enable_if<is_element_map<Type>, bool>::type
within(const typename Type::element_type& value_pair, const Type& super)
{ 
    typedef typename Type::const_iterator const_iterator;
    const_iterator found_ = super.find(value_pair.first);
    return found_ != super.end() && (*found_).second == value_pair.second;
}

//------------------------------------------------------------------------------
//- bool contains(c T&, c P&) T:{m} P:{b} fragment_types
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_element_map<Type>, bool>::type
contains(const Type& super, const typename Type::element_type& value_pair)
{
    return icl::within(value_pair, super);
}

//==============================================================================
//= Equivalences and Orderings<ElementMap>
//==============================================================================

/** Protonic equality is equality on all elements that do not carry an identity element as content. */
template<class Type>
inline typename enable_if<is_element_map<Type>, bool>::type
is_distinct_equal(const Type& lhs, const Type& rhs)
{
    return Map::lexicographical_distinct_equal(lhs, rhs);
}

//==============================================================================
//= Addition<ElementMap>
//==============================================================================
/** \c add inserts \c value_pair into the map if it's key does 
    not exist in the map.    
    If \c value_pairs's key value exists in the map, it's data
    value is added to the data value already found in the map. */
template <class Type>
typename enable_if<is_element_map<Type>, Type>::type&
add(Type& object, const typename Type::value_type& value_pair)
{
    return object.add(value_pair); 
}

/** \c add add \c value_pair into the map using \c prior as a hint to
    insert \c value_pair after the position \c prior is pointing to. */
template <class Type>
typename enable_if<is_element_map<Type>, typename Type::iterator>::type
add(Type& object, typename Type::iterator prior, 
    const typename Type::value_type& value_pair) 
{ 
    return object.add(prior, value_pair); 
}

//==============================================================================
//= Erasure
//==============================================================================
//------------------------------------------------------------------------------
//- T& erase(T&, c P&) T:{m} P:{b} fragment_type
//------------------------------------------------------------------------------
template <class Type>
typename enable_if<is_element_map<Type>, typename Type::size_type>::type
erase(Type& object, const typename Type::element_type& value_pair)
{
    typedef typename Type::size_type             size_type;
    typedef typename Type::iterator              iterator;
    typedef typename Type::on_identity_absorbtion on_identity_absorbtion;

    if(on_identity_absorbtion::is_absorbable(value_pair.second)) 
        return identity_element<size_type>::value();

    iterator it_ = object.find(value_pair.first);
    if(it_ != object.end() && value_pair.second == (*it_).second)
    {
        object.erase(it_);
        return unit_element<size_type>::value();
    }

    return identity_element<size_type>::value();
}

template<class Type>
typename enable_if<is_element_map<Type>, Type>::type&
erase(Type& object, const typename Type::set_type& erasure)
{
    typedef typename Type::set_type set_type;
    ICL_const_FORALL(typename set_type, elem_, erasure) 
        icl::erase(object, *elem_); 

    return object; 
}

//==============================================================================
//= Subtraction
//==============================================================================
//------------------------------------------------------------------------------
//- T& subtract(T&, c P&) T:{m} P:{b} fragment_type
//------------------------------------------------------------------------------
template <class Type>
inline typename enable_if<is_element_map<Type>, Type>::type&
subtract(Type& object, const typename Type::element_type& operand) 
{ 
    return object.subtract(operand); 
}

//------------------------------------------------------------------------------
//- T& subtract(T&, c P&) T:{m} P:{e} key_type
//------------------------------------------------------------------------------
template <class Type>
typename enable_if<is_element_map<Type>, Type>::type&
subtract(Type& object, const typename Type::domain_type& key_value)
{
    return icl::erase(object, key_value);
}

//------------------------------------------------------------------------------
//- T& subtract(T&, c P&) T:{m} P:{s} set key_type 
//------------------------------------------------------------------------------
template <class Type>
inline typename enable_if<is_element_map<Type>, Type>::type&
operator -= (Type& object, const typename Type::set_type& operand) 
{ 
    typedef typename Type::set_type           set_type;
    typedef typename set_type::const_iterator co_iterator;
    typedef typename Type::iterator           iterator;

    co_iterator common_lwb_, common_upb_;
    if(!Set::common_range(common_lwb_, common_upb_, operand, object))
        return object;

    co_iterator it_ = common_lwb_;
    iterator    common_;

    while(it_ != common_upb_)
        object.erase(*it_++);

    return object;
}

template <class Type>
inline typename enable_if<is_element_map<Type>, Type>::type
operator - (Type object, const typename Type::set_type& subtrahend) 
{ 
    return object -= subtrahend; 
}

//==============================================================================
//= Selective Update<ElementMap>
//==============================================================================
//------------------------------------------------------------------------------
//- T& set_at(T&, c P&) T:{m} P:{b}
//------------------------------------------------------------------------------
template<class Type>
inline typename enable_if<is_element_map<Type>, Type>::type&
set_at(Type& object, const typename Type::element_type& operand)
{
    typedef typename Type::iterator         iterator;
    typedef typename Type::codomain_combine codomain_combine;
    typedef on_absorbtion<Type,codomain_combine,absorbs_identities<Type>::value>
                                            on_identity_absorbtion;

    if(!on_identity_absorbtion::is_absorbable(operand.second))
    {
        std::pair<iterator,bool> insertion = object.insert(operand);
        if(!insertion.second)
            insertion->second = operand.second;
    }
    return object;
}


//==============================================================================
//= Intersection
//==============================================================================
template<class Type>
inline typename enable_if<is_element_map<Type>, void>::type
add_intersection(Type& section, const Type&               object, 
                       const typename Type::element_type& operand)
{
    object.add_intersection(section, operand);
}

template<class Type>
inline typename enable_if<is_element_map<Type>, void>::type
add_intersection(Type& section, const Type& object, const Type& operand)
{
    ICL_const_FORALL(typename Type, it_, operand) 
        icl::add_intersection(section, object, *it_); 
}

//------------------------------------------------------------------------------
//- T& op &=(T&, c P&) T:{m} P:{b m} fragment_types
//------------------------------------------------------------------------------

template<class Type>
inline typename enable_if<mpl::and_<is_element_map<Type>, is_total<Type> >, Type>::type&
operator &=(Type& object, const typename Type::element_type& operand)
{
    object.add(operand);
    return object;
}

template<class Type>
inline typename enable_if<mpl::and_<is_element_map<Type>, mpl::not_<is_total<Type> > >, Type>::type&
operator &=(Type& object, const typename Type::element_type& operand)
{
    Type section;
    icl::add_intersection(section, object, operand);
    object.swap(section);
    return object; 
}

template<class Type>
inline typename enable_if<is_element_map<Type>, Type>::type
operator & (Type object, const typename Type::element_type& operand)
{
    return object &= operand;
}

template<class Type>
inline typename enable_if<is_element_map<Type>, Type>::type
operator & (const typename Type::element_type& operand, Type object)
{
    return object &= operand;
}


template<class Type>
inline typename enable_if<mpl::and_<is_element_map<Type>, is_total<Type> >, Type>::type&
operator &=(Type& object, const Type& operand)
{
    object += operand; 
    return object;
}

template<class Type>
inline typename enable_if<mpl::and_<is_element_map<Type>, mpl::not_<is_total<Type> > >, Type>::type&
operator &=(Type& object, const Type& operand)
{
    Type section;
    icl::add_intersection(section, object, operand);
    object.swap(section);
    return object; 
}

template<class Type>
inline typename enable_if<is_element_map<Type>, Type>::type
operator & (Type object, const typename Type::key_object_type& operand)
{
    return object &= operand;
}

template<class Type>
inline typename enable_if<is_element_map<Type>, Type>::type
operator & (const typename Type::key_object_type& operand, Type object)
{
    return object &= operand;
}

//==============================================================================
//= Intersection<ElementMap> bool intersects(x,y)
//==============================================================================
template<class Type, class CoType>
inline typename enable_if< mpl::and_< is_element_map<Type>
                                    , is_total<Type>      > 
                         , bool>::type
intersects(const Type&, const CoType&)
{
    return true;
}

template<class Type>
inline typename enable_if< mpl::and_< is_element_map<Type>
                                    , mpl::not_<is_total<Type> > > 
                         , bool>::type
intersects(const Type& object, const typename Type::domain_type& operand)
{
    return icl::contains(object, operand);
}

template<class Type>
inline typename enable_if< mpl::and_< is_element_map<Type>
                                    , mpl::not_<is_total<Type> > > 
                         , bool>::type
intersects(const Type& object, const typename Type::set_type& operand)
{
    if(object.iterative_size() < operand.iterative_size())
        return Map::intersects(object, operand);
    else
        return Map::intersects(operand, object);
}

template<class Type>
inline typename enable_if< mpl::and_< is_element_map<Type>
                                    , mpl::not_<is_total<Type> > > 
                         , bool>::type
intersects(const Type& object, const typename Type::element_type& operand)
{
    Type intersection;
    icl::add_intersection(intersection, object, operand);
    return !intersection.empty();
}

template<class Type>
inline typename enable_if< mpl::and_< is_element_map<Type>
                                    , mpl::not_<is_total<Type> > > 
                         , bool>::type
intersects(const Type& object, const Type& operand)
{
    if(object.iterative_size() < operand.iterative_size())
        return Map::intersects(object, operand);
    else
        return Map::intersects(operand, object);
}

//==============================================================================
//= Symmetric difference
//==============================================================================
template<class Type>
inline typename enable_if<is_element_map<Type>, Type>::type&
flip(Type& object, const typename Type::element_type& operand)
{
    return object.flip(operand);
}

template<class Type, class CoType>
inline typename enable_if< mpl::and_< is_element_map<Type>
                                    , is_total<Type>       
                                    , absorbs_identities<Type> > 
                         , Type>::type&
operator ^= (Type& object, const CoType&)
{
    icl::clear(object);
    return object;
}

template<class Type>
inline typename enable_if< mpl::and_< is_element_map<Type>
                                    , is_total<Type>       
                                    , mpl::not_<absorbs_identities<Type> > > 
                         , Type>::type&
operator ^= (Type& object, const typename Type::element_type& operand)
{
    return object.flip(operand);
}

template<class Type>
inline typename enable_if< mpl::and_< is_element_map<Type>
                                    , is_total<Type>       
                                    , mpl::not_<absorbs_identities<Type> > > 
                         , Type>::type&
operator ^= (Type& object, const Type& operand)
{
    ICL_const_FORALL(typename Type, it_, operand)
        icl::flip(object, *it_);

    ICL_FORALL(typename Type, it2_, object)
        (*it2_).second = identity_element<typename Type::codomain_type>::value();

    return object;
}


template<class Type>
inline typename enable_if< mpl::and_< is_element_map<Type>
                                    , mpl::not_<is_total<Type> > > 
                         , Type>::type&
operator ^= (Type& object, const typename Type::element_type& operand)
{
    return icl::flip(object, operand);
}

template<class Type>
inline typename enable_if< mpl::and_< is_element_map<Type>
                                    , mpl::not_<is_total<Type> > > 
                         , Type>::type&
operator ^= (Type& object, const Type& operand)
{
    typedef typename Type::const_iterator const_iterator;
    const_iterator it_ = operand.begin();
    while(it_ != operand.end())
        icl::flip(object, *it_++);

    return object;
}


//==============================================================================
//= Set selection
//==============================================================================
template<class Type>
inline typename enable_if<is_element_map<Type>, 
                          typename Type::set_type>::type&
domain(typename Type::set_type& domain_set, const Type& object)
{
    typename Type::set_type::iterator prior_ = domain_set.end();
    typename Type::const_iterator it_ = object.begin();
    while(it_ != object.end())
        prior_ = domain_set.insert(prior_, (*it_++).first);

    return domain_set;
}

//==============================================================================
//= Neutron absorbtion
//==============================================================================
template<class Type>
inline typename enable_if<mpl::and_< is_element_map<Type>
                                   , absorbs_identities<Type> >, Type>::type&
absorb_identities(Type& object)
{
    typedef typename Type::element_type element_type;
    return icl::erase_if(content_is_identity_element<element_type>(), object);
}

template<class Type>
inline typename enable_if<mpl::and_< is_element_map<Type>
                                   , mpl::not_<absorbs_identities<Type> > >
                         , Type>::type&
absorb_identities(Type&){}

//==============================================================================
//= Streaming<ElementMap>
//==============================================================================
template<class CharType, class CharTraits, class Type>
inline typename enable_if<is_element_map<Type>, std::basic_ostream<CharType, CharTraits> >::type&
operator << (std::basic_ostream<CharType, CharTraits>& stream, const Type& object)
{
    stream << "{";
    ICL_const_FORALL(typename Type, it, object)
        stream << "(" << it->first << "->" << it->second << ")";

    return stream << "}";
}


}} // namespace boost icl

#endif



/* element_map.hpp
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
*/