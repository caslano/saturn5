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
#include <boost/static_assert.hpp>
#include <boost/concept/assert.hpp>
#include <boost/icl/detail/concept_check.hpp>
#include <boost/icl/concept/interval.hpp>
#include <boost/icl/type_traits/succ_pred.hpp>
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