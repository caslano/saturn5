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
32ZC8ydb6fTeT8SPl3Zkfd4oQl+eWEZrzhKdK2lg9Xal0OpVoVQpKVBYtdlKw+pOpWt3L9LjvPJ0V7SzIk2GCsVvFWN9pr4uHvtlNYsec47uJ3en6jUbikLWKfbRwIH0pG4cVf6qMYvraaOp137Hnh9agz6Nvca64Drjclqg2PPyK/R2k9bCfGMu01c7L7y1fzazfnSMrZ+0gmbPOi+UPtGLOV5/TkjJ2EsfOHKEt/f3oD/vTBBaR0XTjCY2YeeDfDb93Dlxqf0A/cHEhKmhw+mr/N5s/KHFbKX4qdi2zI9U66RdrPFtR/q6tEsc3XYnO9dmk3h34E4are8hLtDvpxgxXLjsOssOLe8ofB2fQqFfbhLnd6hNM293ZN/Omcxa1msk7h55mDI/fIstP6OjU+NGiG8OX876nnoo3PngdzRnViX2zoxEWj69F/suN55FVpvMOgybyRY9fp62LC5LV5q9JoaVvcJuXyzOpn9QjfXoZhROHClJ04quEIZ/epQCHg1nYXe70Mmvq1CVN0pTdN94tvNRJTY3ZAFFxL5KQ+PmC5V/7ki1tlWiTUf+xEZfXSE8eD+WVgw4KY6bOpCWlSwlvmWpQd2qXRCyR25knVZmCUdml2TLLq8WWP4galWmtTgwsgT7JWilQHMPsxIT+gmNN1Sj9N8tF8dtOcRq17HR8ZOV2ZGSx0Rz0Vy6smsKO/t2Fvshvj/rMnMoLd3+hbC4bDNWdquTek07wB6VqCZsGHuVkt8rLa45+kf2/I0ZLHnIALY1P5nGlt1Pb722jL4vu5TtXzqSNZiVT+aPRgpLsibRiTINxQer97Mj9upkD77ABulDhV1nMkk8kMCKD/qR/XjvPaqa5GT7XKPoi0vbab2ppPBt6DD2h15L6Pq1Wmz/Rx+xBdt+pk8eT6OfKlpozPYsFnB4AXsneA3RMCvLKR4kRIwOY9s/T6Xa3y+n8Pgu4jfNblCjUffFhmuD6P3Qq2xpx3dpVMxxNig+gE16eZj4vWMa7Ws6QlzXPor1bRbM7oT8yCaWDhLzv/2RragmiINy79BPX/3EWuhz2dfL3qCVwQK9MjyP+v0xl9WjBbSkyU0q/tZbQo+UDSyiexXqVLYJzTy/jOKK/J6VubmJSh54kW3ctll417CWfRF3Wniw5iRVeS9C/Lb4VdozrjPb+FI4jX97o9CxqUj6DuMFscIa+HXjxYrhHVi1XhPFsB016PFku1hnzxzKeGc1HfilJssIq/dXhs2DkQsujOLnJu1UlNGgUiqV7AYJDQ0laZGRUW9RomGEiowGDTKiKTMkKsmoJJKSkREhCgkVklDu8/6/wl3POb9zLjdv2ol3409R+eLj9Em8DZ/yTmLw0SN2ea8TOq7OovLqtTRRTpKf09JCmP9QtNRaE5tUTldef0WP20iOhDKoLJtNjESo5/Flju4YiK/3huuHebDIPcx9JEPp2uev9Ed4I/VeOcIbTQ2pfnMvv+tmTOtfBWDaxBF07swaMttgirogJa564jOa3SWgMPIRirRV2Wk+FaE3ynFaexPeSSUALefxbNCe//cnFtpz5zL56C7S2NDE3X9l00vTVPLy304BxktYUL4wvem7wS9FBmB04md4yU8iFnuRLs2aRYo7o3jc3VpY6VViV4kBbuq/ZjHylbSaQMNOedBT5o9Aoxqq+rGWHT+phuyj0bR1hC5VCpVQhb0PcuMWsBtfVyNSu4DvWrYPacsyeX/TGbzx1efWdd+wgVfyzavDoR3WxzvOFNL1/Vd5cPJEiMuKkbvrN2QM5HPv5vM4u/keRXuswqXCK7z9Zx/80p0EfnQCHV+7hq/2CsTJ+j62+qQTSW+p4lnrxag59gU=
*/