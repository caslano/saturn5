/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_LEFT_OPEN_INTERVAL_HPP_JOFA_100930
#define BOOST_ICL_LEFT_OPEN_INTERVAL_HPP_JOFA_100930

#include <functional>
#include <boost/concept/assert.hpp>
#include <boost/icl/concept/interval.hpp>
#include <boost/icl/type_traits/value_size.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>

namespace boost{namespace icl
{

template <class DomainT, 
          ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT)>
class left_open_interval
{
public:
    typedef left_open_interval<DomainT,Compare> type;
    typedef DomainT domain_type;
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================
    /** Default constructor; yields an empty interval <tt>(0,0]</tt>. */
    left_open_interval() 
        : _lwb(identity_element<DomainT>::value()), _upb(identity_element<DomainT>::value()) 
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
    }

    //NOTE: Compiler generated copy constructor is used

    /** Constructor for a left-open singleton interval <tt>(val-1,val]</tt> */
    explicit left_open_interval(const DomainT& val)
        : _lwb(predecessor<DomainT,domain_compare>::apply(val)), _upb(val)
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        // Only for discrete types this ctor creates an interval containing 
        // a single element only.
        BOOST_STATIC_ASSERT((icl::is_discrete<DomainT>::value));
        BOOST_ASSERT((numeric_minimum<DomainT, domain_compare, is_numeric<DomainT>::value >
                                     ::is_less_than(val) )); 
    }

    /** Interval from <tt>low</tt> to <tt>up</tt> with bounds <tt>bounds</tt> */
    left_open_interval(const DomainT& low, const DomainT& up) :
        _lwb(low), _upb(up)
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
    }

    DomainT lower()const{ return _lwb; }
    DomainT upper()const{ return _upb; }

private:
    DomainT _lwb;
    DomainT _upb;
};

//==============================================================================
//=T left_open_interval -> concept intervals
//==============================================================================
template<class DomainT, ICL_COMPARE Compare>
struct interval_traits< icl::left_open_interval<DomainT, Compare> >
{
    typedef DomainT domain_type;
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;
    typedef icl::left_open_interval<DomainT, Compare> interval_type;

    static interval_type construct(const domain_type& lo, const domain_type& up)
    {
        return interval_type(lo, up);
    }

    static domain_type lower(const interval_type& inter_val){ return inter_val.lower(); }
    static domain_type upper(const interval_type& inter_val){ return inter_val.upper(); }
};


//==============================================================================
//= Type traits
//==============================================================================
template <class DomainT, ICL_COMPARE Compare> 
struct interval_bound_type< left_open_interval<DomainT,Compare> >
{
    typedef interval_bound_type type;
    BOOST_STATIC_CONSTANT(bound_type, value = interval_bounds::static_left_open);
};

template <class DomainT, ICL_COMPARE Compare>
struct type_to_string<icl::left_open_interval<DomainT,Compare> >
{
    static std::string apply()
    { return "(I]<"+ type_to_string<DomainT>::apply() +">"; }
};

template<class DomainT, ICL_COMPARE Compare> 
struct value_size<icl::left_open_interval<DomainT,Compare> >
{
    static std::size_t apply(const icl::left_open_interval<DomainT>&) 
    { return 2; }
};

}} // namespace icl boost

#endif


/* left_open_interval.hpp
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
*/