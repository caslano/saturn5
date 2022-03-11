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