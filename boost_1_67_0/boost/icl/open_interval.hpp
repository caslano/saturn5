/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_OPEN_INTERVAL_HPP_JOFA_100930
#define BOOST_ICL_OPEN_INTERVAL_HPP_JOFA_100930

#include <functional>
#include <boost/concept/assert.hpp>
#include <boost/icl/detail/concept_check.hpp>
#include <boost/icl/concept/interval.hpp>
#include <boost/icl/type_traits/value_size.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>

namespace boost{namespace icl
{

template <class DomainT, 
          ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT)>
class open_interval
{
public:
    typedef open_interval<DomainT,Compare> type;
    typedef DomainT domain_type;
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================
    /** Default constructor; yields an empty interval <tt>(0,0)</tt>. */
    open_interval() 
        : _lwb(identity_element<DomainT>::value()), _upb(identity_element<DomainT>::value()) 
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
    }

    //NOTE: Compiler generated copy constructor is used

    /** Constructor for an open singleton interval <tt>(val-1,val+1)</tt> */
    explicit open_interval(const DomainT& val)
        : _lwb(pred(val)), _upb(succ(val))
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
    open_interval(const DomainT& low, const DomainT& up) :
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
//=T open_interval -> concept intervals
//==============================================================================
template<class DomainT, ICL_COMPARE Compare>
struct interval_traits< icl::open_interval<DomainT, Compare> >
{
    typedef DomainT domain_type;
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;
    typedef icl::open_interval<DomainT, Compare> interval_type;

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
struct interval_bound_type< open_interval<DomainT,Compare> >
{
    typedef interval_bound_type type;
    BOOST_STATIC_CONSTANT(bound_type, value = interval_bounds::static_open);
};

template <class DomainT, ICL_COMPARE Compare>
struct type_to_string<icl::open_interval<DomainT,Compare> >
{
    static std::string apply()
    { return "(I)<"+ type_to_string<DomainT>::apply() +">"; }
};

template<class DomainT, ICL_COMPARE Compare> 
struct value_size<icl::open_interval<DomainT,Compare> >
{
    static std::size_t apply(const icl::open_interval<DomainT>&) 
    { return 2; }
};

}} // namespace icl boost

#endif


/* open_interval.hpp
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
*/