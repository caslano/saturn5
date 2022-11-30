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