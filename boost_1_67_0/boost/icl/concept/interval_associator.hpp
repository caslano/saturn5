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