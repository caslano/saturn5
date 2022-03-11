/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_RIGHT_OPEN_INTERVAL_HPP_JOFA_100323
#define BOOST_ICL_RIGHT_OPEN_INTERVAL_HPP_JOFA_100323

#include <functional>
#include <boost/concept/assert.hpp>
#include <boost/icl/concept/interval.hpp>
#include <boost/icl/type_traits/succ_pred.hpp>
#include <boost/icl/type_traits/value_size.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>

namespace boost{namespace icl
{

template <class DomainT, 
          ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT)>
class right_open_interval
{
public:
    typedef right_open_interval<DomainT,Compare> type;
    typedef DomainT domain_type;
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================
    /** Default constructor; yields an empty interval <tt>[0,0)</tt>. */
    right_open_interval() 
        : _lwb(identity_element<DomainT>::value()), _upb(identity_element<DomainT>::value()) 
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
    }

    //NOTE: Compiler generated copy constructor is used

    /** Constructor for a singleton interval <tt>[val,val+1)</tt> */
    explicit right_open_interval(const DomainT& val)
        : _lwb(val), _upb(icl::successor<DomainT,domain_compare>::apply(val))
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        // Only for discrete types this ctor creates an interval containing 
        // a single element only.
        BOOST_STATIC_ASSERT((icl::is_discrete<DomainT>::value));
    }

    /** Interval from <tt>low</tt> to <tt>up</tt> with bounds <tt>bounds</tt> */
    right_open_interval(const DomainT& low, const DomainT& up) :
        _lwb(low), _upb(up)
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
    }

    domain_type lower()const{ return _lwb; }
    domain_type upper()const{ return _upb; }

private:
    domain_type _lwb;
    domain_type _upb;
};

//==============================================================================
//=T right_open_interval -> concept intervals
//==============================================================================
template<class DomainT, ICL_COMPARE Compare>
struct interval_traits< icl::right_open_interval<DomainT, Compare> >
{
    typedef DomainT domain_type;
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;
    typedef icl::right_open_interval<DomainT, Compare> interval_type;

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
struct interval_bound_type< right_open_interval<DomainT,Compare> >
{
    typedef interval_bound_type type;
    BOOST_STATIC_CONSTANT(bound_type, value = interval_bounds::static_right_open);
};

template <class DomainT, ICL_COMPARE Compare>
struct type_to_string<icl::right_open_interval<DomainT,Compare> >
{
    static std::string apply()
    { return "[I)<"+ type_to_string<DomainT>::apply() +">"; }
};

template<class DomainT, ICL_COMPARE Compare> 
struct value_size<icl::right_open_interval<DomainT,Compare> >
{
    static std::size_t apply(const icl::right_open_interval<DomainT>&) 
    { return 2; }
};

}} // namespace icl boost

#endif


/* right_open_interval.hpp
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
*/