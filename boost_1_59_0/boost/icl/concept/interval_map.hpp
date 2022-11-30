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
7HhPSO8m1UqhPHJuQl2b7kcekfMNA5+xekFB4rszWOCHeA8z+QIODbxB2Tzja150Mzr7UoLA42HIpA0kdFUbl5NisuEDcbkJtcbWoR98Ym7LDa2ErRmpGPpWuj1oysP5ntVUmsl6mEzYdqd25NIbJE7dqbvKJdV9PVJD/rwLxlcSmsmoMbFcpaFcSeHB833vTBztn12uOaztk2+iXofiP+lItAvOQ9YdZ++TF1e/13i1nDoDeL+0arrKIMUMxJVkjg9aziElIft8e/Uy/uczw7invpLNxzroXXtvw18dyO72CqowUxVCELdM+afpdZGz8gzKd2XDKgjrwvUQB3mzlkXPsutM4Md1JcYsJ0ZDq/JpI7gVuuiGrDOI+0PXNnqbG/TLLEnyCaGmuH+yBuhjOjSbr4we+TzoH7lxTicQ8PmfEBmXG+Iom2adxn51GY5Y/FbNOGNQJp5uaPkcXCkrJ3FqkoGkXY7SZcctMDcr42FYVAxsM8pcxYf8llUogJ9GqBv6mvLbFjQZ6dIO0sC3F04fmhU1hqvKub/YBPqLrLx6DPJW25BcjqcxS21fisY7uGATvH4K1x4Bu620dUE7neKD+0ktrWaS/0K1LHTg8Kyzr9VmJeSiovsKpmcvritvqcq7aGzwmy+N63E/LjVe4Y/7bwW8Fpefn3Vwt/SctiOy+XBF6HW/vMNf3z21jPXYwiyvlvsZcjBAFpUzWloRy+wcfMbOMwsss/6Fwth2xgcw9jjtKKENxQOWwuLt7mfrboeir27RjtvGXba4dtqgfK3kkHUSjhN1Tjdwy7ueuI58ZWhElJqm8YdgWscwZj9Pt23eoB0iMT+km9YWW3UazK0jlyS0IoS74amR1HmYqf0x/NCkx03WlBnxs6wao0vbGzGmi9CymDui5bAdUqAbrWSKJQ+RJzm65NJL2V6Y15UYLa6PdF5IMGzQMI2LXiiB7stby2VVs/mhx6EbGV14yOFWzyYcDR94NA45o8V9orwhrx3vRFYnbNzF73Y3jF1quMCgkyo7u4nzxVRwwFmaekFfuzrtSv3sTj4IizvYX9KXl2UaC6EL/juA05Bvk1r/9Mf/7t/47RkJwvI8+1+hU0WtmbEQW7VkuTDmfaExsdCBHSWEDQlR9M2YP6m4HPlDu6ZXfYZoSKfkJwIPdGqJ1N8GnZbs4WcyzXhueLZttD18MlE8auNLyA1d1oVEIw2cgWdNk+uabpGox4GfqukX6FsYiOn04DLMV/3MfgiLi0OpN4RvN1acoQ3mwgbMLI3TVmwhw8+LDk1H8wmwsG4FPMHWWut/0LLKG2/813xFbPgZ3vLXvn2mJCpRSzc9jeKJb/nGi0I8SnDfZngdDfHQ9F+U1RLDQHSv1iAjwXH1c1t0mQTYknMqcA3HMORxJfS3KSWSsFKeAFMw52v3/+VJRhroYiUU6FvdGltP0l275+kq+iEPj+hYzXa4H/4Ddwdg7r9ulS8MemRas2GxGDeFHyBJ3VhYXQmfysMVcgS5TlPMm3n+J5PldicxxpWDC/lCduSs80qamZhJ90n+o2TQuLhOBP0Rq+lNaaQkMeOziVmy/MfUFNUWiGuMHuIojZcGxrRudu0I+id0tDCL7rOrek/MpA8zaaBIJc8uxLyCPNmNWKU5DY6n+HyOjtzIc7a8ai0Q20CFV2v80umS7eoxzjhNM26lb/sOLPCcT8gbcoJBN5qkPqrpcR/NwKaB9cwCDZUnY4OMeMnbb3dByusHyAmQY1N2WwAL2uIs8vkfcFS2ImO4Oa/DO7RPUJn5Mu0lzYWjd2AWmI28tpZYC2xagC68gdCeTRaDDxJBI+1VTXmYZKx8J7TeSQZdFh1HIbVvZXWzBneQ+pQRRByJvdi6JmN4j88huPSrEyF/7PRTWl0rrpcmOitkc9ZkX22Uqu+2GWvLFRiE4+ZzE+4wAprySxMtS8u/kfILgJogM1nejY65cPvO+NRGILsWSDelg+fWK077jmnHWZUmv2nr5i3h3WwL6p5RjIrOUYn6xoWSxFhjrisVLdG7iNE29qQNd1m1cWHNYVZw05RjabFBgO8OVjeo69UYCSYLI8iPhG6AhYkjM68dFK67SneoDqcqlLUo1xeUZGb6o0sja97P+JtUuDv9AU7wY5md9QXy70lXo6yHtu6RILznMga3ey8U3Y4BmTbKYXz1sUxG3LZFKmgS4N4BdkToERCvJRgbiskmXNh0fFSJyiqGpKitQrNF8hm3O+gA2kEhJqLCfegJJSs40xinfFoB8fPGfuXykqvYYoWjdvteyB5ZdP33orNMwhwNneeKBG1Y+a/t8x1Ji1NOfYqXUIA+E4SkjPIpZa0Cnr4cQN6GBPyqaHDnf2c8bflYr65yYQ+fFV4udzXDz6XBgSYs1u5wpXaLqF2A/bAeCBBq93GZkn26czp7jq7Vp+NnFAFAC853KLlWYopuTCYMVyM0ecHBHt20bVX2PKWDd4BIKX6uRH4SlTNMzVdgOOvV0JetAKvIm5t1vlyBN0h8XbLwasrwDHrZzWqX9ngnuSmoBGpFtTInB6I2dnIHoC1KH/TTjnj6DlhOwblAphmxGWeDgOieCTI/QgK4QPzmeMwGj2HFnj4SNrv5bApkr1FZ0I+S/pgewAUkTYaZUOGKk9D0iaFdCr3+qQSuvjhUEQkeAS4p1KVBK8ZzJBBU/vSyw0L9h7CB2s3gxYObVxUtcQl1xxZvwF7j28pt2lFKfLi+w3uEl/Nyz4R11V+XfwxGLEF4GMB0PPrfElwPzBoKY4k73uSgeE2PaFvIIq5+IvINbowHG8XGjXX76wBo/eJoi0EduOZ0eZOsfU8FuXiWHcbuCAeZ4ZjzkeLR51gEC+tYkihpx02yeACHQZSD2cC452yfAZPp7LlJ6vIih/4WQBXqgy8g68dZJmyrmSaWi4btcYAor4mYYc4yyWDIjLK9/VlMMGgFqJWaayC2l2q2rgsJzrABZgRWFfl4MhcTXswaY2zRhnHwG34YhWY+vY15wR+H8LXx5fdwWMlZuGPp/IeZZqKQe8aupMO47tzF8PEl3oBce4MlDicgBeA41jjHNXicod//TNVDPTaMV8KlwSdlGGgzdZaP2cx27PTzBmc5Ln9at0N6j/JJO6zZrnAutw7vxCSDug3qJll7UK1uxBwS78UvU9uX2EBL0NW3VB05xuARFzL+AdaCrqxQoXK9tih/gaEqfTgPdu3ILoHnMtWOdenylArcTpp71e2X5kpa4keH/4gzl1vwlRXahF+3Qrum6oQeTwSIY1G/7mftVuCMundK50y7zsVqiwzcG6i4qU1bcpUcrQUcEkpHqo0vT2lwV9oJgFYbmpzhn2wTm4wUcQRNOPu9AUMxJnbhDd1AO4HrRzAvWvKFNTdSJfnN2IaiMuFKdfFOP0rEEFfIEhSYJR7f7ZoefzQAg+Dyb6zBVp4ZZuHl56f/Y5f7h8n95uPraR/3RX0wKjkdSOUoIXyFBUt5dWkTqpTVDURMAC7gapjnYK90qmZRYs9rGOwcVzKZCk+hzvv7kaCfKWCXPWyQXqthGDEKgiRSHKSz98MDQoyWHDZeO0vHug+Y7IVq91TtLvN5m0Nvend5H7Ve0pxiUYAIpHKPCh9gfVGTCjie7AzA4E2pNUHqWWCc2GP8zeJTnDSLtntW8Av4VlrChBKwXA0jfEALmXcVi1H0r81cfDnE2k4fbLizd15geumnjU4Vje7L1GbQqDWUI9Lk7DCJS9dBv+/dt8No6LN8L5P3D0N2cLDtYODNXzBqGG9Iv20x78Io/QLIP0BQf46xFSw23dgIm2A9+dF2e52/XpB6dou8dsN0YQWcSw261+4DAWnBPd8tKPyG36A4u8HLxv+K7BLRRYh/qm1Ub1NKFxTVCKUp0lEq6H3GLTIet0yQ2h73e6zCeZK7QpzuOS4DkQYPqSgRoKtNqEaZEkRS5ek0q9Ro0am/HVWwOqrmfPJUA8U9jUzYS43d/mtVM8WKvt4waldQWsmZG/nT0Yg8Wj2fNyzVkO0FdMB5yRHqUN4NY/hTKj83MakVWrjBMGOQrxjTrn1HMjEAuiEu0XsXV3FbWJ+rodki1QVPfhwEuCR9QM916R2sDCcOS63JY7Cwf4FEKo20FZDy6kyNRir9ZJd6sfv6ZLdyurt0tjPXEndtauRLvf4l+oA9XeSS/88T5YB6Td2lGaz41LfJoK+TefFM7q0Vk2e4jON69dqzZDGyoR2F+dO7pd8fJOTgyL6XSy9+a+dr0D8A6MYaUH6IVu/TX6/Z+VXcZfEsyLHAvyT0kZnhe9bjBPxbc+pQ5m7WIERoakoqeM9ZuE+v/9o64o20Rb69rplfrYDn78ox6kRy2JsPK/M4pU0qQPEIzFor8AgJnu0EXb0H6MQLN6A3cPVb3ANCL12jAFenqmaQ3ZYQJenMqIipFLYpXrKiDXa6g85MhuNMDoEwaZbxzFk6cldyx3slo9fpSeUS6PVYzCeG4qTaFnMkid1wrtHBEC1u7gbJu9pWQ+6U4aglZJWF4V8regA/9kyuWe2BkdRBBiBY6rT17LAv9r89P/4ZmN2M8mid65o52BxhNw05J5/s1vdmEetvrtmJ1641M7DeU8dHTIU8QL6HnIGNFOp6qWljeVeKiQZkIWltT065LobfwypgpT0e0s6gMw9nuzTLvZo1fgervZqFfsqlXo2QkLx3SnotOnotKnrHSWm0CWm0qWnL45MrY5Of99IxYHSDQurAcGYgTMVAbVR7ngJfyzUNfX3uEW2+Eizgrx9ktPtrVEK7zNwfX280qGOz5eS9kpexqcwCPnbUAc/fGu0LXlSCPqPLHyoEPUQpr7YlGLi6Cq57acsCkVF4JW0AnkGge/Qts6FZu4K4ObNk7usHQHPeiAxG0G9ku2H9mlT24omhS5v500B2je7+FANl6yVt4xhQaQrKQK1NOEEr14od+ldx0+rZXSF6phUbKnPYFS5Vs5HT/2AD1I6EKpue5/IBu6mS8b1W6nP2E6XEZlHNMYYBG0b1sePSIviiZF4BVnvTpR1nUoU88KseQ0quQKNnzP46Rf/4xirW+hPW2UYZO99Xhs+by92XoELhhfTzJidVG7pUE7BD1C/N0diIyCdfGYaVBjlrtAagrTSUHUt5sS2BKoukOtX+6J3gfnc+NctGOsWp6wteJ5RXXqH50u8SqkMyIjMT4r0pNUHejm22PaPaHIDyCU6ry+XN3YYAACz/069wU+FRSs2gP9Nff5sTbpsmCEq0HAzeoiYZ678mloeQ6SJQ072OAtDye9XnuTTjGOSB8TmFDs+52bP3Cm+90rLAQ2rGGlsevqE3uHJ7qrKmcteTFB63Z8TAHOGaaro1rIOhfyRf2qRtLB6tn46lgxOYGUICcp1NeKz/dE/PycIj7aM7DKFC9esI78G5VkpJufQKKnG9GAI59P7EU/uj4OMeH/cHAagTdw4qJj0wdGrwU5EoZMkqzgXWcvx11vLUW/LgrKML3rHX/daERNp38aPdsQzdNSh9c3H5qLsW6b7HeGMkZNsE6DN6MVV8mWYDITPm0CD93GXhLEmhcrsjmkiBefLyjW5B4fnjigyn2GrrgZt+SUSjyS+xwB32rqy5hqFG5TCYq1IqrsXZMFAp04P1QhuwikSdlF18O3KhKFZmN1Kn8ioz6ReAL6XKO2YsjRsRdAiPFQ+KksQHHSMh7BJKcmKK8wbmC1ev0ium20vRA2Z8r5U8nZBNuiB10KVwxCo81jsIgHwJzNI/s+LURsMWmqrPBKAv/92Bf8XCNIFyAA6Z7Oe6VbZuMyfyUdcHLuNWdu1rIbw90heosN2pWGE0F3/y5aGdndrgF9P0+HAQMeBXRq2TPDoU9jmFQRtwS3p6yXQYZze+aAoVlDdim5K25iTN2zhxpJ3C03QhAdljiT0GzgnYfceEpDDjkALve9UWC38+UqtnhpWLv5AveoDkFTICnJKBbgkNIyoF458bEsWDZ3OWFesz1wezTkaPrgEFc6ekXl0gJKe48OHypxnu3zp7T/SY5k/PxkroS3OLVkVlqDmrwwcfHmDbJGKoInq0GUuVPa804+6CxVkTkJImyyd5AU9yS5DaU5WRBAaoFBtWOQWcrVQi4NawyrmDs2cyZLwS3LCLJ29slB6PqI7kvuD2nClaTiDUxL71Ec98c6Xn/KDVJ2F62kTX7T+G7vjwhoQTzQlIPzUjzyrk0mQn3i9aH9j1NQk1e0YtOHfqADq2gSCAscbJN6Ck49lHtbHEBenhda33lZ4gp+/4Bypa7ysBo2uLOuJI3ttYHiR2iBMoGxqUVLZFYbhbNvkMR+grnws2Uun6gBXH5iDuCKd5Z+TMFdkd4wLwv8U7UEeU7wqOz2FdbRq01V2qD3nhA32ukhw7rjV49USsa6guz7UK2eDqOzAVZdhB4O1N6pvTM0HUfAXKxHSN8u48/tTUN/5AAsJoHojIalsTLcIzUPBYfNR2uoelKPmDFJ7CVRx7INnVmTNmF+ewtJE1PQ7D0/3yUw/dE04R9GPY7P+26v+GXVMJDioBvXDWhk/L5+e7jPGXTFUund+7NXbjlXUme4911o38AFMT6pDjC/73eMSVD7Q78mpKXRHmJjCahD8BUVs+idWByndERHfEOAZR0B+ZuphPFBCYt5fSanVSSviI+CGE7HqlODuRBdsFW7dFW/3xls0/SWyyUngsqbif/gZ4cn3BPO6HjGKEXf1gxl8n2dyJpsKJf1q3v3df7HroNZzMj2e6T3K99F54mkCFWyl1wxxxxBDbMHtI/c7xtXWLfVgNg0eL7q2wnoeCW8kGtVX1pllsyLqB+AVb6NWZ05bL8BTlddMp8qor4KpTBFK/xFLYmxQX9mUZcgh2LXW54SS0arwBJ8cGvitqwrfGusj3xSx2xpvl1DZHXakzSdI0VrMTXt7I+4LQvg3aj68Gh5vOFrAGnkz2Mo5Y05EkVsUplBfzL5CsS3lNt9yB/1DkFVR0CFkPHbwjI/W+dKAKAMrzODeBOUGp1gHnRzFA4rca8rO9qexhAXyArB3M68Mnbq4wsXaDTRfcc/qlqutRN6z7ks8Js4KnNmmpTArcrtr6m1c2f3j6C8ykUNxs6kj2TNGBuNLKXwLN5ehkcoBxM4ACxqzV18Mpv/Pi8czKB5Xb56JPDqknJ/QCNiCujJBWJj2K98U7gW/OcunYtbtSiL8nD/qE32+yRxO3KFyVzwm1Wd2IjSi6Le9QVdNJvQEf4IPZP3LiKSGaoFW0nFTPLVjepKctzlcuRQZ54V/IG/58LYxAbn2fMCcPNtrpRNLCwrQKdZq/Vo7hc4bU+DAH8CknSnONT79Y/fB8UWSSaMiHtHTBse5Ixbn6svCPh0KbDdX1TN2XgYc32rFgRQkkPBQ30D0hPvoAx0j7BBM9JvmY+bo5ARd/q+B7oDi5lvt5Z3c2t2986VPfXzyDVekH7JeqBd3FP1MyZGp5S30c1aQ7EAvbinuBWAV/s+QNmz82wP05n7b3MndeNPNekwgDBbXPWc5eSxzu1EpdQ01de4i7i3kyouddjDEBJ/QT2frLXahhmTE7AHvQxOKND/zvc+fVvl4DCs4NB+4l9tWe3jUGg450Iec065R5Pwyvc95i
*/