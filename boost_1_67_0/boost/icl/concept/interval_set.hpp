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