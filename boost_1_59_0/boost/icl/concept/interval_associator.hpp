/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_INTERVAL_ASSOCIATOR_HPP_JOFA_100920
#define BOOST_ICL_CONCEPT_INTERVAL_ASSOCIATOR_HPP_JOFA_100920

#include <boost/range/iterator_range.hpp>
#include <boost/icl/type_traits/domain_type_of.hpp>
#include <boost/icl/type_traits/interval_type_of.hpp>
#include <boost/icl/type_traits/is_combinable.hpp>
#include <boost/icl/detail/set_algo.hpp>
#include <boost/icl/detail/map_algo.hpp>
#include <boost/icl/detail/interval_set_algo.hpp>
#include <boost/icl/detail/interval_map_algo.hpp>
#include <boost/icl/concept/interval.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= Containedness<IntervalSet|IntervalMap>
//==============================================================================
//------------------------------------------------------------------------------
//- bool within(c T&, c P&) T={Set,Map} P={e i b p S M}
//------------------------------------------------------------------------------
template<class SubT, class SuperT>
typename enable_if<is_interval_container<SuperT>, bool>::type 
within(const SubT& sub, const SuperT& super)
{
    return icl::contains(super, sub); 
}

//==============================================================================
//= Equivalences and Orderings<IntervalSet|IntervalMap>
//==============================================================================
template<class Type>
inline typename enable_if<is_interval_container<Type>, bool>::type
operator == (const Type& left, const Type& right)
{
    return Set::lexicographical_equal(left, right);
}

template<class Type>
inline typename enable_if<is_interval_container<Type>, bool>::type
operator < (const Type& left, const Type& right)
{
    typedef typename Type::segment_compare segment_compare;
    return std::lexicographical_compare(
        left.begin(), left.end(), right.begin(), right.end(), 
        segment_compare()
        );
}

/** Returns true, if \c left and \c right contain the same elements. 
    Complexity: linear. */
template<class LeftT, class RightT>
typename enable_if<is_intra_combinable<LeftT, RightT>, bool>::type
is_element_equal(const LeftT& left, const RightT& right)
{
    return Interval_Set::is_element_equal(left, right);
}

/** Returns true, if \c left is lexicographically less than \c right. 
    Intervals are interpreted as sequence of elements.
    Complexity: linear. */
template<class LeftT, class RightT>
typename enable_if<is_intra_combinable<LeftT, RightT>, bool>::type
is_element_less(const LeftT& left, const RightT& right)
{
    return Interval_Set::is_element_less(left, right);
}

/** Returns true, if \c left is lexicographically greater than \c right. 
    Intervals are interpreted as sequence of elements.
    Complexity: linear. */
template<class LeftT, class RightT>
typename enable_if<is_intra_combinable<LeftT, RightT>, bool>::type
is_element_greater(const LeftT& left, const RightT& right)
{
    return Interval_Set::is_element_greater(left, right);
}

//------------------------------------------------------------------------------
template<class LeftT, class RightT>
typename enable_if<is_inter_combinable<LeftT, RightT>, int>::type
inclusion_compare(const LeftT& left, const RightT& right)
{
    return Interval_Set::subset_compare(left, right, 
                                        left.begin(), left.end(),
                                        right.begin(), right.end());
}

//------------------------------------------------------------------------------
template<class LeftT, class RightT>
typename enable_if< is_concept_compatible<is_interval_map, LeftT, RightT>,
                    bool >::type
is_distinct_equal(const LeftT& left, const RightT& right)
{
    return Map::lexicographical_distinct_equal(left, right);
}

//==============================================================================
//= Size<IntervalSet|IntervalMap>
//==============================================================================
template<class Type> 
typename enable_if<is_interval_container<Type>, std::size_t>::type
iterative_size(const Type& object)
{ 
    return object.iterative_size(); 
}

template<class Type>
typename enable_if
< mpl::and_< is_interval_container<Type>
           , is_discrete<typename Type::domain_type> >
, typename Type::size_type
>::type
cardinality(const Type& object)
{
    typedef typename Type::size_type size_type;
    //CL typedef typename Type::interval_type interval_type;

    size_type size = identity_element<size_type>::value();
    ICL_const_FORALL(typename Type, it, object)
        size += icl::cardinality(key_value<Type>(it));
    return size;

}

template<class Type>
typename enable_if
< mpl::and_< is_interval_container<Type>
           , mpl::not_<is_discrete<typename Type::domain_type> > >
, typename Type::size_type
>::type
cardinality(const Type& object)
{
    typedef typename Type::size_type size_type;
    //CL typedef typename Type::interval_type interval_type;

    size_type size = identity_element<size_type>::value();
    size_type interval_size;
    ICL_const_FORALL(typename Type, it, object)
    {
        interval_size = icl::cardinality(key_value<Type>(it));
        if(interval_size == icl::infinity<size_type>::value())
            return interval_size;
        else
            size += interval_size;
    }
    return size;
}

template<class Type>
inline typename enable_if<is_interval_container<Type>, typename Type::size_type>::type
size(const Type& object)
{
    return icl::cardinality(object);
}

template<class Type>
typename enable_if<is_interval_container<Type>, typename Type::difference_type>::type
length(const Type& object)
{
    typedef typename Type::difference_type difference_type;
    typedef typename Type::const_iterator  const_iterator;
    difference_type length = identity_element<difference_type>::value();
    const_iterator it_ = object.begin();

    while(it_ != object.end())
        length += icl::length(key_value<Type>(it_++));
    return length;
}

template<class Type>
typename enable_if<is_interval_container<Type>, std::size_t>::type
interval_count(const Type& object)
{
    return icl::iterative_size(object);
}


template<class Type>
typename enable_if< is_interval_container<Type> 
                  , typename Type::difference_type >::type
distance(const Type& object)
{
    typedef typename Type::difference_type DiffT;
    typedef typename Type::const_iterator const_iterator;
    const_iterator it_ = object.begin(), pred_;
    DiffT dist = identity_element<DiffT>::value();

    if(it_ != object.end())
        pred_ = it_++;

    while(it_ != object.end())
        dist += icl::distance(key_value<Type>(pred_++), key_value<Type>(it_++));
    
    return dist;
}

//==============================================================================
//= Range<IntervalSet|IntervalMap>
//==============================================================================
template<class Type>
typename enable_if<is_interval_container<Type>, 
                   typename Type::interval_type>::type
hull(const Type& object)
{
    return 
        icl::is_empty(object) 
            ? identity_element<typename Type::interval_type>::value()
            : icl::hull( key_value<Type>(object.begin()), 
                         key_value<Type>(object.rbegin()) );
}

template<class Type>
typename enable_if<is_interval_container<Type>, 
                   typename domain_type_of<Type>::type>::type
lower(const Type& object)
{
    typedef typename domain_type_of<Type>::type DomainT;
    return 
        icl::is_empty(object) 
            ? unit_element<DomainT>::value()
            : icl::lower( key_value<Type>(object.begin()) );
}

template<class Type>
typename enable_if<is_interval_container<Type>, 
                   typename domain_type_of<Type>::type>::type
upper(const Type& object)
{
    typedef typename domain_type_of<Type>::type DomainT;
    return 
        icl::is_empty(object) 
            ? identity_element<DomainT>::value()
            : icl::upper( key_value<Type>(object.rbegin()) );
}

//------------------------------------------------------------------------------
template<class Type>
typename enable_if
< mpl::and_< is_interval_container<Type>
           , is_discrete<typename domain_type_of<Type>::type> > 
, typename domain_type_of<Type>::type>::type
first(const Type& object)
{
    typedef typename domain_type_of<Type>::type DomainT;
    return 
        icl::is_empty(object) 
            ? unit_element<DomainT>::value()
            : icl::first( key_value<Type>(object.begin()) );
}

template<class Type>
typename enable_if
< mpl::and_< is_interval_container<Type>
           , is_discrete<typename domain_type_of<Type>::type> >
, typename domain_type_of<Type>::type>::type
last(const Type& object)
{
    typedef typename domain_type_of<Type>::type DomainT;
    return 
        icl::is_empty(object) 
            ? identity_element<DomainT>::value()
            : icl::last( key_value<Type>(object.rbegin()) );
}


//==============================================================================
//= Addition<IntervalSet|IntervalMap>
//==============================================================================
//------------------------------------------------------------------------------
//- T& op +=(T&, c P&) T:{S}|{M} P:{e i}|{b p}
//------------------------------------------------------------------------------
/* \par \b Requires: \c OperandT is an addable derivative type of \c Type. 
    \b Effects: \c operand is added to \c object.
    \par \b Returns: A reference to \c object.
    \b Complexity:
\code
                  \ OperandT:                    
                   \         element     segment 
Type:
       interval container    O(log n)     O(n)   

             interval_set               amortized
    spearate_interval_set                O(log n) 

n = object.interval_count()
\endcode

For the addition of \b elements or \b segments
complexity is \b logarithmic or \b linear respectively.
For \c interval_sets and \c separate_interval_sets addition of segments
is \b amortized \b logarithmic.
*/
template<class Type, class OperandT>
typename enable_if<is_intra_derivative<Type, OperandT>, Type>::type&
operator += (Type& object, const OperandT& operand)
{ 
    return icl::add(object, operand); 
}


//------------------------------------------------------------------------------
//- T& op +=(T&, c P&) T:{S}|{M} P:{S'}|{M'}
//------------------------------------------------------------------------------
/** \par \b Requires: \c OperandT is an interval container addable to \c Type. 
    \b Effects: \c operand is added to \c object.
    \par \b Returns: A reference to \c object.
    \b Complexity: loglinear */
template<class Type, class OperandT>
typename enable_if<is_intra_combinable<Type, OperandT>, Type>::type&
operator += (Type& object, const OperandT& operand)
{
    typename Type::iterator prior_ = object.end();
    ICL_const_FORALL(typename OperandT, elem_, operand) 
        prior_ = icl::add(object, prior_, *elem_); 

    return object; 
}


#ifdef BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
//------------------------------------------------------------------------------
//- T op + (T, c P&) T:{S}|{M} P:{e i S}|{b p M}
//------------------------------------------------------------------------------
/** \par \b Requires: \c object and \c operand are addable.
    \b Effects: \c operand is added to \c object.
    \par \b Efficieny: There is one additional copy of 
    \c Type \c object compared to inplace \c operator \c += */
template<class Type, class OperandT>
typename enable_if<is_binary_intra_combinable<Type, OperandT>, Type>::type
operator + (Type object, const OperandT& operand)
{
    return object += operand; 
}

#else //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

template<class Type, class OperandT>
typename enable_if<is_binary_intra_combinable<Type, OperandT>, Type>::type
operator + (const Type& object, const OperandT& operand)
{
    Type temp = object;
    return boost::move(temp += operand); 
}

template<class Type, class OperandT>
typename enable_if<is_binary_intra_combinable<Type, OperandT>, Type>::type
operator + (Type&& object, const OperandT& operand)
{
    return boost::move(object += operand); 
}

#endif //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

#ifdef BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
//------------------------------------------------------------------------------
//- T op + (c P&, T) T:{S}|{M} P:{e i S'}|{b p M'}
//------------------------------------------------------------------------------
/** \par \b Requires: \c object and \c operand are addable.
    \b Effects: \c operand is added to \c object.
    \par \b Efficieny: There is one additional copy of 
    \c Type \c object compared to inplace \c operator \c += */
template<class Type, class OperandT>
typename enable_if<is_binary_intra_combinable<Type, OperandT>, Type>::type
operator + (const OperandT& operand, Type object)
{
    return object += operand; 
}

#else //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

template<class Type, class OperandT>
typename enable_if<is_binary_intra_combinable<Type, OperandT>, Type>::type
operator + (const OperandT& operand, const Type& object)
{
    Type temp = object;
    return boost::move(temp += operand);
}

template<class Type, class OperandT>
typename enable_if<is_binary_intra_combinable<Type, OperandT>, Type>::type
operator + (const OperandT& operand, Type&& object)
{
    return boost::move(object += operand); 
}

#endif //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

#ifdef BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
//------------------------------------------------------------------------------
//- T op + (T, c P&) T:{S}|{M} P:{S}|{M}
//------------------------------------------------------------------------------
/** \par \b Requires: \c object and \c operand are addable.
    \b Effects: \c operand is added to \c object.
    \par \b Efficieny: There is one additional copy of 
    \c Type \c object compared to inplace \c operator \c += */
template<class Type>
typename enable_if<is_interval_container<Type>, Type>::type
operator + (Type object, const Type& operand)
{
    return object += operand; 
}

#else //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

template<class Type>
typename enable_if<is_interval_container<Type>, Type>::type
operator + (const Type& object, const Type& operand)
{
    Type temp = object;
    return boost::move(temp += operand); 
}

template<class Type>
typename enable_if<is_interval_container<Type>, Type>::type
operator + (Type&& object, const Type& operand)
{
    return boost::move(object += operand); 
}

template<class Type>
typename enable_if<is_interval_container<Type>, Type>::type
operator + (const Type& operand, Type&& object)
{
    return boost::move(object += operand); 
}

template<class Type>
typename enable_if<is_interval_container<Type>, Type>::type
operator + (Type&& object, Type&& operand)
{
    return boost::move(object += operand); 
}

#endif //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

//------------------------------------------------------------------------------
//- Addition |=, | 
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//- T& op |=(c P&) T:{S}|{M} P:{e i}|{b p}
//------------------------------------------------------------------------------
/** \par \b Requires: Types \c Type and \c OperandT are addable.
    \par \b Effects: \c operand is added to \c object.
    \par \b Returns: A reference to \c object.
    \b Complexity:
\code
                  \ OperandT:                      interval
                   \         element     segment   container
Type:
       interval container    O(log n)     O(n)     O(m log(n+m))

             interval_set               amortized
    spearate_interval_set                O(log n) 

n = object.interval_count()
m = operand.interval_count()
\endcode

For the addition of \b elements, \b segments and \b interval \b containers
complexity is \b logarithmic, \b linear and \b loglinear respectively.
For \c interval_sets and \c separate_interval_sets addition of segments
is \b amortized \b logarithmic.
*/
template<class Type, class OperandT>
typename enable_if<is_right_intra_combinable<Type, OperandT>, Type>::type&
operator |= (Type& object, const OperandT& operand)
{ 
    return object += operand; 
}

#ifdef BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
//------------------------------------------------------------------------------
//- T op | (T, c P&) T:{S}|{M} P:{e i S}|{b p M}
//------------------------------------------------------------------------------
/** \par \b Requires: \c object and \c operand are addable.
    \b Effects: \c operand is added to \c object.
    \par \b Efficieny: There is one additional copy of 
    \c Type \c object compared to inplace \c operator \c |= */
template<class Type, class OperandT>
typename enable_if<is_binary_intra_combinable<Type, OperandT>, Type>::type
operator | (Type object, const OperandT& operand)
{
    return object += operand; 
}

#else //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

template<class Type, class OperandT>
typename enable_if<is_binary_intra_combinable<Type, OperandT>, Type>::type
operator | (const Type& object, const OperandT& operand)
{
    Type temp = object;
    return boost::move(temp += operand); 
}

template<class Type, class OperandT>
typename enable_if<is_binary_intra_combinable<Type, OperandT>, Type>::type
operator | (Type&& object, const OperandT& operand)
{
    return boost::move(object += operand); 
}

#endif //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

#ifdef BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
//------------------------------------------------------------------------------
//- T op | (T, c P&) T:{S}|{M} P:{S}|{M}
//------------------------------------------------------------------------------
/** \par \b Requires: \c object and \c operand are addable.
    \b Effects: \c operand is added to \c object.
    \par \b Efficieny: There is one additional copy of 
    \c Type \c object compared to inplace \c operator \c |= */
template<class Type, class OperandT>
typename enable_if<is_binary_intra_combinable<Type, OperandT>, Type>::type
operator | (const OperandT& operand, Type object)
{
    return object += operand; 
}

#else //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

template<class Type, class OperandT>
typename enable_if<is_binary_intra_combinable<Type, OperandT>, Type>::type
operator | (const OperandT& operand, const Type& object)
{
    Type temp = object;
    return boost::move(temp += operand);
}

template<class Type, class OperandT>
typename enable_if<is_binary_intra_combinable<Type, OperandT>, Type>::type
operator | (const OperandT& operand, Type&& object)
{
    return boost::move(object += operand); 
}

#endif //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

#ifdef BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
//------------------------------------------------------------------------------
//- T op | (T, c P&) T:{S}|{M} P:{S}|{M}
//------------------------------------------------------------------------------
/** \par \b Requires: \c object and \c operand are addable.
    \b Effects: \c operand is added to \c object.
    \par \b Efficieny: There is one additional copy of 
    \c Type \c object compared to inplace \c operator \c |= */
template<class Type>
typename enable_if<is_interval_container<Type>, Type>::type
operator | (Type object, const Type& operand)
{
    return object += operand; 
}
#else //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

template<class Type>
typename enable_if<is_interval_container<Type>, Type>::type
operator | (const Type& object, const Type& operand)
{
    Type temp = object;
    return boost::move(temp += operand); 
}

template<class Type>
typename enable_if<is_interval_container<Type>, Type>::type
operator | (Type&& object, const Type& operand)
{
    return boost::move(object += operand); 
}

template<class Type>
typename enable_if<is_interval_container<Type>, Type>::type
operator | (const Type& operand, Type&& object)
{
    return boost::move(object += operand); 
}

template<class Type>
typename enable_if<is_interval_container<Type>, Type>::type
operator | (Type&& object, Type&& operand)
{
    return boost::move(object += operand); 
}

#endif //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES


//==============================================================================
//= Insertion<IntervalSet|IntervalSet>
//==============================================================================
//------------------------------------------------------------------------------
//- T& insert(T&, c P&) T:{S}|{M} P:{S'}|{M'}
//------------------------------------------------------------------------------
template<class Type, class OperandT>
typename enable_if<is_intra_combinable<Type, OperandT>, Type>::type&
insert(Type& object, const OperandT& operand)
{
    typename Type::iterator prior_ = object.end();
    ICL_const_FORALL(typename OperandT, elem_, operand) 
        insert(object, prior_, *elem_); 

    return object; 
}

//==============================================================================
//= Erasure<IntervalSet|IntervalSet>
//==============================================================================
//------------------------------------------------------------------------------
//- T& erase(T&, c P&) T:{S}|{M} P:{S'}|{S' M'}
//------------------------------------------------------------------------------
template<class Type, class OperandT>
typename enable_if<combines_right_to_interval_container<Type, OperandT>,
                   Type>::type&
erase(Type& object, const OperandT& operand)
{
    typedef typename OperandT::const_iterator const_iterator;

    if(icl::is_empty(operand))
        return object;

    const_iterator common_lwb, common_upb;
    if(!Set::common_range(common_lwb, common_upb, operand, object))
        return object;

    const_iterator it_ = common_lwb;
    while(it_ != common_upb)
        icl::erase(object, *it_++);

    return object; 
}

//==============================================================================
//= Subtraction<IntervalSet|IntervalSet>
//==============================================================================
//------------------------------------------------------------------------------
//- T& op -= (c P&) T:{M} P:{M'} 
//------------------------------------------------------------------------------
/** \par \b Requires: Types \c Type and \c OperandT are subtractable.
    \par \b Effects: \c operand is subtracted from \c object.
    \par \b Returns: A reference to \c object.
    \b Complexity:
\code
                  \ OperandT:                      interval
                   \         element    segment    container
Type:
       interval container    O(log n)     O(n)     O(m log(n+m))

                                       amortized
            interval_sets               O(log n) 

n = object.interval_count()
m = operand.interval_count()
\endcode

For the subtraction of \em elements, \b segments and \b interval \b containers
complexity is \b logarithmic, \b linear and \b loglinear respectively.
For interval sets subtraction of segments
is \b amortized \b logarithmic.
*/
template<class Type, class OperandT>
typename enable_if<is_concept_compatible<is_interval_map, Type, OperandT>, 
                   Type>::type& 
operator -=(Type& object, const OperandT& operand)
{
    ICL_const_FORALL(typename OperandT, elem_, operand) 
        icl::subtract(object, *elem_);

    return object; 
}

//------------------------------------------------------------------------------
//- T& op -= (c P&) T:{S}|{M} P:{e i}|{b p} 
//------------------------------------------------------------------------------
template<class Type, class OperandT>
typename enable_if<is_intra_derivative<Type, OperandT>, Type>::type&
operator -= (Type& object, const OperandT& operand)
{ 
    return icl::subtract(object, operand); 
}

//------------------------------------------------------------------------------
//- T& op -= (c P&) T:{M} P:{e i} 
//------------------------------------------------------------------------------
template<class Type, class OperandT>
typename enable_if<is_cross_derivative<Type, OperandT>, Type>::type&
operator -= (Type& object, const OperandT& operand)
{ 
    return icl::erase(object, operand); 
}

//------------------------------------------------------------------------------
//- T& op -= (c P&) T:{S M} P:{S'}
//------------------------------------------------------------------------------
template<class Type, class IntervalSetT>
typename enable_if<combines_right_to_interval_set<Type, IntervalSetT>,
                   Type>::type&
operator -= (Type& object, const IntervalSetT& operand)
{
    return erase(object, operand);
}

#ifdef BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
//------------------------------------------------------------------------------
//- T op - (T, c P&) T:{S}|{M} P:{e i S'}|{e i b p S' M'} 
//------------------------------------------------------------------------------
template<class Type, class OperandT>
typename enable_if<is_right_inter_combinable<Type, OperandT>, Type>::type
operator - (Type object, const OperandT& operand)
{
    return object -= operand; 
}

#else //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

template<class Type, class OperandT>
typename enable_if<is_right_inter_combinable<Type, OperandT>, Type>::type
operator - (const Type& object, const OperandT& operand)
{
    Type temp = object;
    return boost::move(temp -= operand); 
}

template<class Type, class OperandT>
typename enable_if<is_right_inter_combinable<Type, OperandT>, Type>::type
operator - (Type&& object, const OperandT& operand)
{
    return boost::move(object -= operand); 
}

#endif //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

//==============================================================================
//= Intersection<IntervalSet|IntervalSet>
//==============================================================================
//------------------------------------------------------------------------------
//- void add_intersection(T&, c T&, c P&) T:{S M} P:{S'}
//------------------------------------------------------------------------------
template<class Type, class OperandT>
typename enable_if<mpl::and_<is_interval_set<Type>, 
                             combines_right_to_interval_set<Type, OperandT> >,
                   void>::type
add_intersection(Type& section, const Type& object, const OperandT& operand)
{
    typedef typename OperandT::const_iterator const_iterator;

    if(operand.empty())
        return;

    const_iterator common_lwb, common_upb;
    if(!Set::common_range(common_lwb, common_upb, operand, object))
        return;

    const_iterator it_ = common_lwb;
    while(it_ != common_upb)
        icl::add_intersection(section, object, key_value<OperandT>(it_++));
}

//------------------------------------------------------------------------------
//- T& op &=(T&, c P&) T:{S}|{M} P:{e i S'}|{e i b p S' M'}
//------------------------------------------------------------------------------
template<class Type, class OperandT>
typename enable_if<is_right_inter_combinable<Type, OperandT>, Type>::type&
operator &= (Type& object, const OperandT& operand)
{
    Type intersection;
    add_intersection(intersection, object, operand);
    object.swap(intersection);
    return object;
}

#ifdef BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
//------------------------------------------------------------------------------
//- T op & (T, c P&) T:{S}|{M} P:{e i S'}|{e i b p S' M'} S<S' M<M' <:coarser
//------------------------------------------------------------------------------
template<class Type, class OperandT>
typename enable_if<is_binary_inter_combinable<Type, OperandT>, Type>::type
operator & (Type object, const OperandT& operand)
{
    return object &= operand; 
}

#else //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

template<class Type, class OperandT>
typename enable_if<is_binary_inter_combinable<Type, OperandT>, Type>::type
operator & (const Type& object, const OperandT& operand)
{
    Type temp = object;
    return boost::move(temp &= operand); 
}

template<class Type, class OperandT>
typename enable_if<is_binary_inter_combinable<Type, OperandT>, Type>::type
operator & (Type&& object, const OperandT& operand)
{
    return boost::move(object &= operand); 
}

#endif //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

#ifdef BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
//------------------------------------------------------------------------------
//- T op & (c P&, T) T:{S}|{M} P:{e i S'}|{e i b p S' M'} S<S' M<M' <:coarser
//------------------------------------------------------------------------------
template<class Type, class OperandT>
typename enable_if<is_binary_inter_combinable<Type, OperandT>, Type>::type
operator & (const OperandT& operand, Type object)
{
    return object &= operand; 
}

#else //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

template<class Type, class OperandT>
typename enable_if<is_binary_inter_combinable<Type, OperandT>, Type>::type
operator & (const OperandT& operand, const Type& object)
{
    Type temp = object;
    return boost::move(temp &= operand);
}

template<class Type, class OperandT>
typename enable_if<is_binary_inter_combinable<Type, OperandT>, Type>::type
operator & (const OperandT& operand, Type&& object)
{
    return boost::move(object &= operand); 
}

#endif //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

#ifdef BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
//------------------------------------------------------------------------------
//- T op & (T, c T&) T:{S M}
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_container<Type>, Type>::type
operator & (Type object, const Type& operand)
{
    return object &= operand; 
}

#else //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

template<class Type>
typename enable_if<is_interval_container<Type>, Type>::type
operator & (const Type& object, const Type& operand)
{
    Type temp = object;
    return boost::move(temp &= operand); 
}

template<class Type>
typename enable_if<is_interval_container<Type>, Type>::type
operator & (Type&& object, const Type& operand)
{
    return boost::move(object &= operand); 
}

template<class Type>
typename enable_if<is_interval_container<Type>, Type>::type
operator & (const Type& operand, Type&& object)
{
    return boost::move(object &= operand); 
}

template<class Type>
typename enable_if<is_interval_container<Type>, Type>::type
operator & (Type&& object, Type&& operand)
{
    return boost::move(object &= operand); 
}

#endif //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

//------------------------------------------------------------------------------
//- intersects<IntervalSet|IntervalMap>
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//- bool intersects(c T&, c P&) T:{S}|{M} P:{e i}
//------------------------------------------------------------------------------
template<class Type, class CoType>
typename enable_if<mpl::and_< is_interval_container<Type>
                            , boost::is_same<CoType, typename domain_type_of<Type>::type> >, 
                   bool>::type
intersects(const Type& left, const CoType& right)
{
    return icl::contains(left, right); 
}

template<class Type, class CoType>
typename enable_if<mpl::and_< is_interval_container<Type>
                            , boost::is_same<CoType, typename interval_type_of<Type>::type> >, 
                   bool>::type
intersects(const Type& left, const CoType& right)
{
    return icl::find(left, right) != left.end();
}


template<class LeftT, class RightT>
typename enable_if< mpl::and_< is_intra_combinable<LeftT, RightT> 
                             , mpl::or_<is_total<LeftT>, is_total<RightT> > >
                  , bool>::type
intersects(const LeftT&, const RightT&)
{
    return true;
}

template<class LeftT, class RightT>
typename enable_if< mpl::and_< is_intra_combinable<LeftT, RightT> 
                             , mpl::not_<mpl::or_< is_total<LeftT>
                                                 , is_total<RightT> > > >
                  , bool>::type
intersects(const LeftT& left, const RightT& right)
{
    typedef typename RightT::const_iterator const_iterator;
    LeftT intersection;

    const_iterator right_common_lower_, right_common_upper_;
    if(!Set::common_range(right_common_lower_, right_common_upper_, right, left))
        return false;

    const_iterator it_ = right_common_lower_;
    while(it_ != right_common_upper_)
    {
        icl::add_intersection(intersection, left, *it_++);
        if(!icl::is_empty(intersection))
            return true;
    }
    return false; 
}

template<class LeftT, class RightT>
typename enable_if<is_cross_combinable<LeftT, RightT>, bool>::type
intersects(const LeftT& left, const RightT& right)
{
    typedef typename RightT::const_iterator const_iterator;
    LeftT intersection;

    if(icl::is_empty(left) || icl::is_empty(right))
        return false;

    const_iterator right_common_lower_, right_common_upper_;
    if(!Set::common_range(right_common_lower_, right_common_upper_, right, left))
        return false;

    typename RightT::const_iterator it_ = right_common_lower_;
    while(it_ != right_common_upper_)
    {
        icl::add_intersection(intersection, left, key_value<RightT>(it_++));
        if(!icl::is_empty(intersection))
            return true;
    }

    return false; 
}

/** \b Returns true, if \c left and \c right have no common elements.
    Intervals are interpreted as sequence of elements.
    \b Complexity: loglinear, if \c left and \c right are interval containers. */
template<class LeftT, class RightT>
typename enable_if<is_inter_combinable<LeftT, RightT>, bool>::type
disjoint(const LeftT& left, const RightT& right)
{
    return !intersects(left, right);
}

/** \b Returns true, if \c left and \c right have no common elements.
    Intervals are interpreted as sequence of elements.
    \b Complexity: logarithmic, if \c AssociateT is an element type \c Type::element_type. 
    linear, if \c AssociateT is a segment type \c Type::segment_type. */
template<class Type, class AssociateT>
typename enable_if<is_inter_derivative<Type, AssociateT>, bool>::type
disjoint(const Type& left, const AssociateT& right)
{
    return !intersects(left,right);
}


//==============================================================================
//= Symmetric difference<IntervalSet|IntervalSet>
//==============================================================================
//------------------------------------------------------------------------------
//- Symmetric difference ^=, ^
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//- T& op ^=(T&, c P&) T:{S}|{M} P:{S'}|{M'}
//------------------------------------------------------------------------------
template<class Type, class OperandT>
typename enable_if<is_intra_combinable<Type, OperandT>, Type>::type&
operator ^= (Type& object, const OperandT& operand)
{ 
    return icl::flip(object, operand); 
}

//------------------------------------------------------------------------------
//- T& op ^=(T&, c P&) T:{S}|{M} P:{e i}|{b p}
//------------------------------------------------------------------------------
template<class Type, class OperandT>
typename enable_if<is_intra_derivative<Type, OperandT>, Type>::type&
operator ^= (Type& object, const OperandT& operand)
{ 
    return icl::flip(object, operand); 
}

#ifdef BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
//------------------------------------------------------------------------------
//- T op ^ (T, c P&) T:{S}|{M} P:{e i S'}|{b p M'} S<S' M<M' <:coarser
//------------------------------------------------------------------------------
template<class Type, class OperandT>
typename enable_if<is_binary_intra_combinable<Type, OperandT>, Type>::type
operator ^ (Type object, const OperandT& operand)
{
    return object ^= operand; 
}

#else //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

template<class Type, class OperandT>
typename enable_if<is_binary_intra_combinable<Type, OperandT>, Type>::type
operator ^ (const Type& object, const OperandT& operand)
{
    Type temp = object;
    return boost::move(temp ^= operand); 
}

template<class Type, class OperandT>
typename enable_if<is_binary_intra_combinable<Type, OperandT>, Type>::type
operator ^ (Type&& object, const OperandT& operand)
{
    return boost::move(object ^= operand); 
}

#endif //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

#ifdef BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
//------------------------------------------------------------------------------
//- T op ^ (c P&, T) T:{S}|{M} P:{e i S'}|{b p M'} S<S' M<M' <:coarser
//------------------------------------------------------------------------------
template<class Type, class OperandT>
typename enable_if<is_binary_intra_combinable<Type, OperandT>, Type>::type
operator ^ (const OperandT& operand, Type object)
{
    return object ^= operand; 
}

#else //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

template<class Type, class OperandT>
typename enable_if<is_binary_intra_combinable<Type, OperandT>, Type>::type
operator ^ (const OperandT& operand, const Type& object)
{
    Type temp = object;
    return boost::move(temp ^= operand);
}

template<class Type, class OperandT>
typename enable_if<is_binary_intra_combinable<Type, OperandT>, Type>::type
operator ^ (const OperandT& operand, Type&& object)
{
    return boost::move(object ^= operand); 
}

#endif //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

#ifdef BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
//------------------------------------------------------------------------------
//- T op ^ (T, c T&) T:{S M}
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_container<Type>, Type>::type
operator ^ (typename Type::overloadable_type object, const Type& operand)
{
    return object ^= operand; 
}

#else //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

template<class Type>
typename enable_if<is_interval_container<Type>, Type>::type
operator ^ (const Type& object, const Type& operand)
{
    Type temp = object;
    return boost::move(temp ^= operand); 
}

template<class Type>
typename enable_if<is_interval_container<Type>, Type>::type
operator ^ (Type&& object, const Type& operand)
{
    return boost::move(object ^= operand); 
}

template<class Type>
typename enable_if<is_interval_container<Type>, Type>::type
operator ^ (const Type& operand, Type&& object)
{
    return boost::move(object ^= operand); 
}

template<class Type>
typename enable_if<is_interval_container<Type>, Type>::type
operator ^ (Type&& object, Type&& operand)
{
    return boost::move(object ^= operand); 
}

#endif //BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

//==========================================================================
//= Element Iteration <IntervalSet|IntervalMap>
//==========================================================================
//--------------------------------------------------------------------------
//- Forward
//--------------------------------------------------------------------------
template<class Type>
typename enable_if
<mpl::and_< is_interval_container<Type> 
          , mpl::not_<is_continuous_interval<typename Type::interval_type> > >,
typename Type::element_iterator>::type
elements_begin(Type& object)
{
    return typename Type::element_iterator(object.begin());
}

template<class Type>
typename enable_if
<mpl::and_< is_interval_container<Type> 
          , mpl::not_<is_continuous_interval<typename Type::interval_type> > >,
typename Type::element_iterator>::type
elements_end(Type& object)
{ 
    return typename Type::element_iterator(object.end()); 
}

template<class Type>
typename enable_if
<mpl::and_< is_interval_container<Type> 
          , mpl::not_<is_continuous_interval<typename Type::interval_type> > >,
typename Type::element_const_iterator>::type
elements_begin(const Type& object)
{ 
    return typename Type::element_const_iterator(object.begin());
}

template<class Type>
typename enable_if
<mpl::and_< is_interval_container<Type> 
          , mpl::not_<is_continuous_interval<typename Type::interval_type> > >,
typename Type::element_const_iterator>::type
elements_end(const Type& object)
{ 
    return typename Type::element_const_iterator(object.end());
}

template<class Type>
typename enable_if
<mpl::and_< is_interval_container<Type>
          , mpl::not_<is_continuous_interval<typename Type::interval_type> > >,
iterator_range<typename Type::element_iterator> >::type
elements(Type& object)
{
    return
    make_iterator_range( typename Type::element_iterator(object.begin())
                       , typename Type::element_iterator(object.end())  );
}

template<class Type>
typename enable_if
<mpl::and_< is_interval_container<Type>
          , mpl::not_<is_continuous_interval<typename Type::interval_type> > >,
iterator_range<typename Type::element_const_iterator> >::type
elements(Type const& object)
{
    return
    make_iterator_range( typename Type::element_const_iterator(object.begin())
                       , typename Type::element_const_iterator(object.end())  );
}

//--------------------------------------------------------------------------
//- Reverse
//--------------------------------------------------------------------------
template<class Type>
typename enable_if
<mpl::and_< is_interval_container<Type> 
          , mpl::not_<is_continuous_interval<typename Type::interval_type> > >,
typename Type::element_reverse_iterator>::type
elements_rbegin(Type& object)
{
    return typename Type::element_reverse_iterator(object.rbegin());
}

template<class Type>
typename enable_if
<mpl::and_< is_interval_container<Type> 
          , mpl::not_<is_continuous_interval<typename Type::interval_type> > >,
typename Type::element_reverse_iterator>::type
elements_rend(Type& object)
{ 
    return typename Type::element_reverse_iterator(object.rend());
}

template<class Type>
typename enable_if
<mpl::and_< is_interval_container<Type> 
          , mpl::not_<is_continuous_interval<typename Type::interval_type> > >,
typename Type::element_const_reverse_iterator>::type
elements_rbegin(const Type& object)
{ 
    return typename Type::element_const_reverse_iterator(object.rbegin());
}

template<class Type>
typename enable_if
<mpl::and_< is_interval_container<Type> 
          , mpl::not_<is_continuous_interval<typename Type::interval_type> > >,
typename Type::element_const_reverse_iterator>::type
elements_rend(const Type& object)
{ 
    return typename Type::element_const_reverse_iterator(object.rend());
}

}} // namespace boost icl

#endif



/* interval_associator.hpp
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
*/