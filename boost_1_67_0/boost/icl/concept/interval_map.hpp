/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_INTERVAL_MAP_HPP_JOFA_100920
#define BOOST_ICL_CONCEPT_INTERVAL_MAP_HPP_JOFA_100920

#include <boost/icl/type_traits/element_type_of.hpp>
#include <boost/icl/type_traits/segment_type_of.hpp>
#include <boost/icl/type_traits/absorbs_identities.hpp>
#include <boost/icl/type_traits/is_combinable.hpp>
#include <boost/icl/type_traits/is_interval_splitter.hpp>

#include <boost/icl/detail/set_algo.hpp>
#include <boost/icl/detail/interval_map_algo.hpp>
#include <boost/icl/concept/interval.hpp>
#include <boost/icl/concept/joinable.hpp>

namespace boost{ namespace icl
{

template<class Type>
inline typename enable_if<is_interval_map<Type>, typename Type::segment_type>::type
make_segment(const typename Type::element_type& element)
{
    typedef typename Type::interval_type interval_type;
    typedef typename Type::segment_type  segment_type;
    return segment_type(icl::singleton<interval_type>(element.key), element.data);
}


//==============================================================================
//= Containedness<IntervalMap>
//==============================================================================
//------------------------------------------------------------------------------
//- bool contains(c T&, c P&) T:{M} P:{b p M} fragment_types
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_map<Type>, bool>::type
contains(const Type& super, const typename Type::element_type& key_value_pair)
{
    typedef typename Type::const_iterator const_iterator;
    const_iterator it_ = icl::find(super, key_value_pair.key);
    return it_ != super.end() && (*it_).second == key_value_pair.data;
}

template<class Type>
typename enable_if<is_interval_map<Type>, bool>::type
contains(const Type& super, const typename Type::segment_type& sub_segment)
{
    typedef typename Type::interval_type  interval_type;
    typedef typename Type::const_iterator const_iterator;

    interval_type sub_interval = sub_segment.first;
    if(icl::is_empty(sub_interval)) 
        return true;

    std::pair<const_iterator, const_iterator> exterior = super.equal_range(sub_interval);
    if(exterior.first == exterior.second)
        return false;

    const_iterator last_overlap = prior(exterior.second);

    if(!(sub_segment.second == exterior.first->second) )
        return false;

    return
          icl::contains(hull(exterior.first->first, last_overlap->first), sub_interval)
      &&  Interval_Map::is_joinable(super, exterior.first, last_overlap);
}

template<class Type, class CoType>
typename enable_if<is_concept_compatible<is_interval_map, Type, CoType>, bool>::type
contains(const Type& super, const CoType& sub)
{
    return Interval_Set::within(sub, super);
}


//------------------------------------------------------------------------------
//- bool contains(c T&, c P&) T:{M} P:{e i S} key_types : total
//------------------------------------------------------------------------------
template<class Type, class CoType>
typename enable_if< mpl::and_< is_interval_map<Type>
                             , is_total<Type> 
                             , is_cross_derivative<Type, CoType> >
            , bool>::type
contains(const Type&, const CoType&)
{
    return true;
}

//------------------------------------------------------------------------------
//- bool contains(c T&, c P&) T:{M} P:{e i S} key_types : partial
//------------------------------------------------------------------------------
template<class Type>
typename enable_if< mpl::and_< is_interval_map<Type>
                             , mpl::not_<is_total<Type> > >
            , bool>::type
contains(const Type& super, const typename Type::domain_type& key)    
{
    return icl::find(super, key) != super.end();
}

template<class Type>
typename enable_if< mpl::and_< is_interval_map<Type>
                             , mpl::not_<is_total<Type> > >
            , bool>::type
contains(const Type& super, const typename Type::interval_type& sub_interval)
{
    typedef typename Type::const_iterator const_iterator;

    if(icl::is_empty(sub_interval)) 
        return true;

    std::pair<const_iterator, const_iterator> exterior = super.equal_range(sub_interval);
    if(exterior.first == exterior.second)
        return false;

    const_iterator last_overlap = prior(exterior.second);

    return
          icl::contains(hull(exterior.first->first, last_overlap->first), sub_interval)
      &&  Interval_Set::is_joinable(super, exterior.first, last_overlap);
}

template<class Type, class KeyT>
typename enable_if< mpl::and_< is_concept_combinable<is_interval_map, is_interval_set, Type, KeyT>
                             , mpl::not_<is_total<Type> > >
            , bool>::type
contains(const Type& super, const KeyT& sub)
{
    return Interval_Set::within(sub, super);
}

//==============================================================================
//= Addition<IntervalMap>
//==============================================================================
//------------------------------------------------------------------------------
//- T& add(T&, c P&) T:{M} P:{b p} fragment_types
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_map<Type>, Type>::type&
add(Type& object, const typename Type::segment_type& operand)
{
    return object.add(operand);
}

template<class Type>
typename enable_if<is_interval_map<Type>, Type>::type&
add(Type& object, const typename Type::element_type& operand)
{
    return icl::add(object, make_segment<Type>(operand));
}

//------------------------------------------------------------------------------
//- T& add(T&, J, c P&) T:{M} P:{p} segment_type
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_map<Type>, typename Type::iterator >::type
add(Type& object, typename Type::iterator      prior_,
            const typename Type::segment_type& operand)
{
    return object.add(prior_, operand);
}

//==============================================================================
//= Insertion<IntervalMap>
//==============================================================================
//------------------------------------------------------------------------------
//- T& insert(T&, c P&) T:{M} P:{b p} fragment_types
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_map<Type>, Type>::type&
insert(Type& object, const typename Type::segment_type& operand)
{
    return object.insert(operand);
}

template<class Type>
inline typename enable_if<is_interval_map<Type>, Type>::type&
insert(Type& object, const typename Type::element_type& operand)
{
    return icl::insert(object, make_segment<Type>(operand));
}

//------------------------------------------------------------------------------
//- T& insert(T&, J, c P&) T:{M} P:{p} with hint
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_map<Type>, typename Type::iterator>::type
insert(Type& object, typename Type::iterator      prior,
               const typename Type::segment_type& operand)
{
    return object.insert(prior, operand);
}


//==============================================================================
//= Erasure<IntervalMap>
//==============================================================================
//------------------------------------------------------------------------------
//- T& erase(T&, c P&) T:{M} P:{e i} key_types
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_map<Type>, Type>::type&
erase(Type& object, const typename Type::interval_type& operand)
{
    return object.erase(operand);
}

template<class Type>
typename enable_if<is_interval_map<Type>, Type>::type&
erase(Type& object, const typename Type::domain_type& operand)
{
    typedef typename Type::interval_type interval_type;
    return icl::erase(object, icl::singleton<interval_type>(operand));
}

//------------------------------------------------------------------------------
//- T& erase(T&, c P&) T:{M} P:{b p} fragment_types
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_map<Type>, Type>::type&
erase(Type& object, const typename Type::segment_type& operand)
{
    return object.erase(operand);
}

template<class Type>
inline typename enable_if<is_interval_map<Type>, Type>::type&
erase(Type& object, const typename Type::element_type& operand)
{
    return icl::erase(object, make_segment<Type>(operand));
}

//==============================================================================
//= Subtraction<IntervalMap>
//==============================================================================
//------------------------------------------------------------------------------
//- T& subtract(T&, c P&) T:{M} P:{b p} fragment_types
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_map<Type>, Type>::type& 
subtract(Type& object, const typename Type::segment_type& operand)
{
    return object.subtract(operand);
}

template<class Type>
typename enable_if<is_interval_map<Type>, Type>::type&
subtract(Type& object, const typename Type::element_type& operand)
{
    return icl::subtract(object, make_segment<Type>(operand));
}

//------------------------------------------------------------------------------
//- T& subtract(T&, c P&) T:{M} P:{e i} key_types
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_map<Type>, Type>::type&
subtract(Type& object, const typename Type::domain_type& operand)
{
    return object.erase(operand);
}

template<class Type>
typename enable_if<is_interval_map<Type>, Type>::type&
subtract(Type& object, const typename Type::interval_type& operand)
{
    return object.erase(operand);
}

//==============================================================================
//= Selective Update<IntervalMap>
//==============================================================================
//------------------------------------------------------------------------------
//- T& set_at(T&, c P&) T:{M} P:{e i}
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_map<Type>, Type>::type&
set_at(Type& object, const typename Type::segment_type& operand)
{
    icl::erase(object, operand.first); 
    return icl::insert(object, operand); 
}

template<class Type>
typename enable_if<is_interval_map<Type>, Type>::type&
set_at(Type& object, const typename Type::element_type& operand)
{
    return icl::set_at(object, make_segment<Type>(operand));
}

//==============================================================================
//= Intersection<IntervalMap>
//==============================================================================
//------------------------------------------------------------------------------
//- T& subtract(T&, c P&) T:{M} P:{b p} fragment_type
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_map<Type>, void>::type
add_intersection(Type& section, const Type& object, 
                 const typename Type::element_type& operand)
{
    //CL typedef typename Type::segment_type segment_type;
    object.add_intersection(section, make_segment<Type>(operand));
}

template<class Type>
typename enable_if<is_interval_map<Type>, void>::type
add_intersection(Type& section, const Type& object, 
                 const typename Type::segment_type& operand)
{
    object.add_intersection(section, operand);
}

//------------------------------------------------------------------------------
//- T& subtract(T&, c P&) T:{M} P:{M'} map fragment_type total
//------------------------------------------------------------------------------
template<class Type, class MapT>
typename enable_if
<
    mpl::and_< is_total<Type>
             , is_concept_compatible<is_interval_map, Type, MapT> >
  , void
>::type
add_intersection(Type& section, const Type& object, const MapT& operand)
{
    section += object;
    section += operand;
}

//------------------------------------------------------------------------------
//- T& subtract(T&, c P&) T:{M} P:{M'} map fragment_type partial
//------------------------------------------------------------------------------
template<class Type, class MapT>
typename enable_if
<
    mpl::and_< mpl::not_<is_total<Type> >
             , is_concept_compatible<is_interval_map, Type, MapT> >
  , void
>::type
add_intersection(Type& section, const Type& object, const MapT& operand)
{
    //CL typedef typename Type::segment_type   segment_type;
    //CL typedef typename Type::interval_type  interval_type;
    typedef typename MapT::const_iterator const_iterator;

    if(operand.empty()) 
        return;
    const_iterator common_lwb, common_upb;
    if(!Set::common_range(common_lwb, common_upb, operand, object))
        return;
    const_iterator it_ = common_lwb;
    while(it_ != common_upb)
        add_intersection(section, object, *it_++);
}

//------------------------------------------------------------------------------
//- T& subtract(T&, c P&) T:{M} P:{e i S} key_type
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_map<Type>, void>::type
add_intersection(Type& section, const Type& object, 
                 const typename Type::domain_type& key_value)
{
    typedef typename Type::interval_type  interval_type;
    typedef typename Type::segment_type   segment_type;
    typedef typename Type::const_iterator const_iterator;

    const_iterator it_ = icl::find(object, key_value);
    if(it_ != object.end())
        add(section, segment_type(interval_type(key_value),(*it_).second));
}

template<class Type>
typename enable_if<is_interval_map<Type>, void>::type
add_intersection(Type& section, const Type& object, 
                 const typename Type::interval_type& inter_val)
{
    typedef typename Type::interval_type  interval_type;
    typedef typename Type::value_type     value_type;
    typedef typename Type::const_iterator const_iterator;
    typedef typename Type::iterator       iterator;

    if(icl::is_empty(inter_val)) 
        return;

    std::pair<const_iterator, const_iterator> exterior 
        = object.equal_range(inter_val);
    if(exterior.first == exterior.second)
        return;

    iterator prior_ = section.end();
    for(const_iterator it_=exterior.first; it_ != exterior.second; it_++) 
    {
        interval_type common_interval = (*it_).first & inter_val; 
        if(!icl::is_empty(common_interval))
            prior_ = add(section, prior_, 
                         value_type(common_interval, (*it_).second) );
    }
}

template<class Type, class KeySetT>
typename enable_if<is_concept_combinable<is_interval_map, is_interval_set, Type, KeySetT>, void>::type
add_intersection(Type& section, const Type& object, const KeySetT& key_set)
{
    typedef typename KeySetT::const_iterator const_iterator;

    if(icl::is_empty(key_set)) 
        return;

    const_iterator common_lwb, common_upb;
    if(!Set::common_range(common_lwb, common_upb, key_set, object))
        return;

    const_iterator it_ = common_lwb;
    while(it_ != common_upb)
        add_intersection(section, object, *it_++);
}

//------------------------------------------------------------------------------
//- intersects<IntervalMaps> fragment_types
//------------------------------------------------------------------------------
template<class Type, class OperandT>
typename enable_if<mpl::and_< is_interval_map<Type>
                            , is_total<Type>
                            , boost::is_same< OperandT
                                            , typename segment_type_of<Type>::type> >, 
                   bool>::type
intersects(const Type&, const OperandT&)
{
    return true;
}

template<class Type, class OperandT>
typename enable_if<mpl::and_< is_interval_map<Type>
                            , mpl::not_<is_total<Type> >
                            , boost::is_same<OperandT, typename segment_type_of<Type>::type> >, 
                   bool>::type
intersects(const Type& object, const OperandT& operand)
{
    Type intersection;
    icl::add_intersection(intersection, object, operand);
    return !icl::is_empty(intersection); 
}

template<class Type, class OperandT>
typename enable_if<mpl::and_< is_interval_map<Type>
                            , boost::is_same<OperandT, typename element_type_of<Type>::type> >, 
                   bool>::type
intersects(const Type& object, const OperandT& operand)
{
    return icl::intersects(object, make_segment<Type>(operand)); 
}

//==============================================================================
//= Symmetric difference<IntervalMap>
//==============================================================================
//------------------------------------------------------------------------------
//- T& flip(T&, c P&) T:{M} P:{b p} fragment_types
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_map<Type>, Type>::type&
flip(Type& object, const typename Type::segment_type& operand)
{
    return object.flip(operand);
}

template<class Type>
inline typename enable_if<is_interval_map<Type>, Type>::type&
flip(Type& object, const typename Type::element_type& operand)
{
    return icl::flip(object, make_segment<Type>(operand));
}

//------------------------------------------------------------------------------
//- T& flip(T&, c P&) T:{M} P:{M'} total absorber 
//------------------------------------------------------------------------------
template<class Type, class OperandT>
typename enable_if< mpl::and_< is_total<Type>
                             , absorbs_identities<Type>
                             , is_concept_compatible<is_interval_map, 
                                                     Type, OperandT >
                             >
                  , Type>::type&
flip(Type& object, const OperandT&)
{
    object.clear();
    return object;
}

//------------------------------------------------------------------------------
//- T& flip(T&, c P&) T:{M} P:{M'} total enricher 
//------------------------------------------------------------------------------
#ifdef BOOST_MSVC 
#pragma warning(push)
#pragma warning(disable:4127) // conditional expression is constant
#endif                        
template<class Type, class OperandT>
typename enable_if< mpl::and_< is_total<Type>
                             , mpl::not_<absorbs_identities<Type> >
                             , is_concept_compatible<is_interval_map, 
                                                     Type, OperandT >
                             >
                  , Type>::type&
flip(Type& object, const OperandT& operand)
{
    typedef typename Type::codomain_type  codomain_type;

    object += operand;
    ICL_FORALL(typename Type, it_, object)
        (*it_).second = identity_element<codomain_type>::value();

    if(mpl::not_<is_interval_splitter<Type> >::value)
        icl::join(object);

    return object;
}
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif


//------------------------------------------------------------------------------
//- T& flip(T&, c P&) T:{M} P:{M'} partial 
//------------------------------------------------------------------------------
template<class Type, class OperandT>
typename enable_if< mpl::and_< mpl::not_<is_total<Type> > 
                             , is_concept_compatible<is_interval_map, 
                                                     Type, OperandT >
                             >
                  , Type>::type&
flip(Type& object, const OperandT& operand)
{
    typedef typename OperandT::const_iterator const_iterator;
    //CL typedef typename Type::codomain_type  codomain_type;

    const_iterator common_lwb, common_upb;

    if(!Set::common_range(common_lwb, common_upb, operand, object))
        return object += operand;

    const_iterator it_ = operand.begin();

    // All elements of operand left of the common range are added
    while(it_ != common_lwb)
        icl::add(object, *it_++);
    // All elements of operand in the common range are symmetrically subtracted
    while(it_ != common_upb)
        icl::flip(object, *it_++);
    // All elements of operand right of the common range are added
    while(it_ != operand.end())
        icl::add(object, *it_++);

    return object;
}

//==============================================================================
//= Set selection
//==============================================================================
template<class Type, class SetT>
typename enable_if<is_concept_combinable<is_interval_set, is_interval_map, 
                                         SetT, Type>, SetT>::type&
domain(SetT& result, const Type& object)
{
    typedef typename SetT::iterator set_iterator;
    result.clear(); 
    set_iterator prior_ = result.end();
    ICL_const_FORALL(typename Type, it_, object) 
        prior_ = icl::insert(result, prior_, (*it_).first); 
    
    return result;
}

template<class Type, class SetT>
typename enable_if<is_concept_combinable<is_interval_set, is_interval_map, 
                                         SetT, Type>, SetT>::type&
between(SetT& in_between, const Type& object)
{
    typedef typename Type::const_iterator const_iterator;
    typedef typename SetT::iterator       set_iterator;
    in_between.clear();
    const_iterator it_ = object.begin(), pred_;
    set_iterator   prior_ = in_between.end();

    if(it_ != object.end())
        pred_ = it_++;

    while(it_ != object.end())
        prior_ = icl::insert(in_between, prior_, 
                             between((*pred_++).first, (*it_++).first));
    
    return in_between;
}

//==============================================================================
//= Manipulation by predicates
//==============================================================================
template<class MapT, class Predicate>
typename enable_if<is_interval_map<MapT>, MapT>::type&
erase_if(const Predicate& pred, MapT& object)
{
    typename MapT::iterator it_ = object.begin();
    while(it_ != object.end())
        if(pred(*it_))
            object.erase(it_++); 
        else ++it_;
    return object;
}

template<class MapT, class Predicate>
inline typename enable_if<is_interval_map<MapT>, MapT>::type&
add_if(const Predicate& pred, MapT& object, const MapT& src)
{
    typename MapT::const_iterator it_ = src.begin();
    while(it_ != src.end())
        if(pred(*it_)) 
            icl::add(object, *it_++); 
    
    return object;
}

template<class MapT, class Predicate>
inline typename enable_if<is_interval_map<MapT>, MapT>::type&
assign_if(const Predicate& pred, MapT& object, const MapT& src)
{
    icl::clear(object);
    return add_if(object, src, pred);
}


//==============================================================================
//= Morphisms
//==============================================================================
template<class Type>
typename enable_if<mpl::and_< is_interval_map<Type>
                            , absorbs_identities<Type> >, Type>::type&
absorb_identities(Type& object)
{
    return object;
}

template<class Type>
typename enable_if<mpl::and_< is_interval_map<Type>
                            , mpl::not_<absorbs_identities<Type> > >, Type>::type&
absorb_identities(Type& object)
{
    typedef typename Type::segment_type segment_type;
    return icl::erase_if(content_is_identity_element<segment_type>(), object);
}

//==============================================================================
//= Streaming
//==============================================================================
template<class CharType, class CharTraits, class Type>
typename enable_if<is_interval_map<Type>, 
                   std::basic_ostream<CharType, CharTraits> >::type& 
operator << (std::basic_ostream<CharType, CharTraits>& stream, const Type& object)
{
    stream << "{";
    ICL_const_FORALL(typename Type, it_, object)
        stream << "(" << (*it_).first << "->" << (*it_).second << ")";

    return stream << "}";
}


}} // namespace boost icl

#endif



/* interval_map.hpp
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
*/