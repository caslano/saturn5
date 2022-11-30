/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_INTERVAL_SET_HPP_JOFA_100920
#define BOOST_ICL_CONCEPT_INTERVAL_SET_HPP_JOFA_100920

#include <boost/icl/type_traits/is_combinable.hpp>
#include <boost/icl/type_traits/interval_type_of.hpp>
#include <boost/icl/detail/set_algo.hpp>
#include <boost/icl/detail/interval_set_algo.hpp>
#include <boost/icl/concept/interval.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= Containedness<IntervalSet>
//==============================================================================
//------------------------------------------------------------------------------
//- bool contains(c T&, c P&) T:{S} P:{e i S} fragment_types
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_set<Type>, bool>::type
contains(const Type& super, const typename Type::element_type& element)
{
    return !(icl::find(super, element) == super.end());
}

template<class Type>
typename enable_if<is_interval_set<Type>, bool>::type
contains(const Type& super, const typename Type::segment_type& inter_val)
{ 
    typedef typename Type::const_iterator const_iterator;
    if(icl::is_empty(inter_val)) 
        return true;

    std::pair<const_iterator, const_iterator> exterior 
        = super.equal_range(inter_val);
    if(exterior.first == exterior.second)
        return false;

    const_iterator last_overlap = cyclic_prior(super, exterior.second);

    return 
        icl::contains(hull(*(exterior.first), *last_overlap), inter_val)
    &&  Interval_Set::is_joinable(super, exterior.first, last_overlap);
}

template<class Type, class OperandT>
typename enable_if<has_same_concept<is_interval_set, Type, OperandT>, 
                   bool>::type 
contains(const Type& super, const OperandT& sub)
{
    return Interval_Set::contains(super, sub);
}

//==============================================================================
//= Addition<IntervalSet>
//==============================================================================
//------------------------------------------------------------------------------
//- T& add(T&, c P&) T:{S} P:{e i} fragment_types
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_set<Type>, Type>::type&
add(Type& object, const typename Type::segment_type& operand)
{
    return object.add(operand);
}

template<class Type>
inline typename enable_if<is_interval_set<Type>, Type>::type&
add(Type& object, const typename Type::element_type& operand)
{
    typedef typename Type::segment_type segment_type;
    return icl::add(object, icl::singleton<segment_type>(operand));
}

//------------------------------------------------------------------------------
//- T& add(T&, J, c P&) T:{S} P:{i} interval_type
//------------------------------------------------------------------------------
template<class Type>
inline typename enable_if<is_interval_set<Type>, typename Type::iterator>::type
add(Type& object, typename Type::iterator      prior, 
            const typename Type::segment_type& operand)
{
    return object.add(prior, operand);
}

//==============================================================================
//= Insertion<IntervalSet>
//==============================================================================
//------------------------------------------------------------------------------
//- T& insert(T&, c P&) T:{S} P:{e i} fragment_types
//------------------------------------------------------------------------------
template<class Type>
inline typename enable_if<is_interval_set<Type>, Type>::type&
insert(Type& object, const typename Type::segment_type& operand)
{
    return icl::add(object, operand);
}

template<class Type>
inline typename enable_if<is_interval_set<Type>, Type>::type&
insert(Type& object, const typename Type::element_type& operand)
{
    return icl::add(object, operand);
}

//------------------------------------------------------------------------------
//- T& insert(T&, J, c P&) T:{S} P:{i} with hint
//------------------------------------------------------------------------------
template<class Type>
inline typename enable_if<is_interval_set<Type>, typename Type::iterator>::type
insert(Type& object, typename Type::iterator      prior,
               const typename Type::segment_type& operand)
{
    return icl::add(object, prior, operand);
}

//==============================================================================
//= Subtraction<IntervalSet>
//==============================================================================
//------------------------------------------------------------------------------
//- T& subtract(T&, c P&) T:{S} P:{e i} fragment_type
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_set<Type>, Type>::type&
subtract(Type& object, const typename Type::segment_type& operand)
{
    return object.subtract(operand);
}

template<class Type>
inline typename enable_if<is_interval_set<Type>, Type>::type&
subtract(Type& object, const typename Type::element_type& operand)
{
    typedef typename Type::segment_type segment_type;
    return icl::subtract(object, icl::singleton<segment_type>(operand));
}

//==============================================================================
//= Erasure<IntervalSet>
//==============================================================================
//------------------------------------------------------------------------------
//- T& erase(T&, c P&) T:{S} P:{e i} fragment_types
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_set<Type>, Type>::type&
erase(Type& object, const typename Type::segment_type& minuend)
{
    return icl::subtract(object, minuend);
}

template<class Type>
typename enable_if<is_interval_set<Type>, Type>::type&
erase(Type& object, const typename Type::element_type& minuend)
{
    return icl::subtract(object, minuend);
}

//==============================================================================
//= Intersection
//==============================================================================
//------------------------------------------------------------------------------
//- void add_intersection(T&, c T&, c P&) T:{S} P:{e i} fragment_types
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_set<Type>, void>::type
add_intersection(Type& section, const Type& object, 
                 const typename Type::element_type& operand)
{
    typedef typename Type::const_iterator const_iterator;
    const_iterator found = icl::find(object, operand);
    if(found != object.end())
        icl::add(section, operand);
}


template<class Type>
typename enable_if<is_interval_set<Type>, void>::type
add_intersection(Type& section, const Type& object, 
                 const typename Type::segment_type& segment)
{
    typedef typename Type::const_iterator const_iterator;
    typedef typename Type::iterator       iterator;
    typedef typename Type::interval_type  interval_type;

    if(icl::is_empty(segment)) 
        return;

    std::pair<const_iterator, const_iterator> exterior 
        = object.equal_range(segment);
    if(exterior.first == exterior.second)
        return;

    iterator prior_ = section.end();
    for(const_iterator it_=exterior.first; it_ != exterior.second; it_++) 
    {
        interval_type common_interval = key_value<Type>(it_) & segment;
        if(!icl::is_empty(common_interval))
            prior_ = section.insert(prior_, common_interval);
    }
}

//==============================================================================
//= Symmetric difference<IntervalSet>
//==============================================================================
//------------------------------------------------------------------------------
//- T& flip(T&, c P&) T:{S} P:{e i S'} fragment_types
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_set<Type>, Type>::type&
flip(Type& object, const typename Type::element_type& operand)
{
    if(icl::contains(object, operand))
        return object -= operand;
    else
        return object += operand;
}

template<class Type>
typename enable_if<is_interval_set<Type>, Type>::type&
flip(Type& object, const typename Type::segment_type& segment)
{
    typedef typename Type::const_iterator const_iterator;
    typedef typename Type::interval_type  interval_type;
    // That which is common shall be subtracted
    // That which is not shall be added
    // So x has to be 'complementary added' or flipped
    interval_type span = segment;
    std::pair<const_iterator, const_iterator> exterior 
        = object.equal_range(span);

    const_iterator fst_ = exterior.first;
    const_iterator end_ = exterior.second;

    interval_type covered, left_over;
    const_iterator it_ = fst_;
    while(it_ != end_) 
    {
        covered = *it_++; 
        //[a      ...  : span
        //     [b ...  : covered
        //[a  b)       : left_over
        left_over = right_subtract(span, covered);
        icl::subtract(object, span & covered); //That which is common shall be subtracted
        icl::add(object, left_over);           //That which is not shall be added

        //...      d) : span
        //... c)      : covered
        //     [c  d) : span'
        span = left_subtract(span, covered);
    }

    //If span is not empty here, it_ is not in the set so it_ shall be added
    icl::add(object, span);
    return object;
}


template<class Type, class OperandT>
typename enable_if<is_concept_compatible<is_interval_set, Type, OperandT>, Type>::type&
flip(Type& object, const OperandT& operand)
{
    typedef typename OperandT::const_iterator const_iterator;

    if(operand.empty())
        return object;

    const_iterator common_lwb, common_upb;

    if(!Set::common_range(common_lwb, common_upb, operand, object))
        return object += operand;

    const_iterator it_ = operand.begin();

    // All elements of operand left of the common range are added
    while(it_ != common_lwb)
        icl::add(object, *it_++);
    // All elements of operand in the common range are symmertrically subtracted
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
template<class Type>
typename enable_if<is_interval_set<Type>, Type>::type&
domain(Type& dom, const Type& object)
{
    typedef typename Type::const_iterator const_iterator;
    typedef typename Type::iterator       iterator;
    dom.clear();
    const_iterator it_    = object.begin();
    iterator       prior_ = dom.end();

    while(it_ != object.end())
        prior_ = icl::insert(dom, prior_, *it_++);

    return dom;
}

template<class Type>
typename enable_if<is_interval_set<Type>, Type>::type&
between(Type& in_between, const Type& object)
{
    typedef typename Type::const_iterator const_iterator;
    typedef typename Type::iterator       iterator;
    in_between.clear();
    const_iterator it_ = object.begin(), pred_;
    iterator prior_ = in_between.end();

    if(it_ != object.end())
        pred_ = it_++;

    while(it_ != object.end())
        prior_ = icl::insert(in_between, prior_, 
                             icl::between(*pred_++, *it_++));

    return in_between;
}


//==============================================================================
//= Streaming
//==============================================================================
template<class CharType, class CharTraits, class Type>
typename enable_if<is_interval_set<Type>, 
                   std::basic_ostream<CharType, CharTraits> >::type& 
operator << (std::basic_ostream<CharType, CharTraits>& stream, const Type& object)
{
    stream << "{";
    ICL_const_FORALL(typename Type, it_, object)
        stream << (*it_);

    return stream << "}";
}


}} // namespace boost icl

#endif



/* interval_set.hpp
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
*/