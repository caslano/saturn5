/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CLOSED_INTERVAL_HPP_JOFA_100324
#define BOOST_ICL_CLOSED_INTERVAL_HPP_JOFA_100324

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
class closed_interval
{
public:
    typedef closed_interval<DomainT,Compare> type;
    typedef DomainT domain_type;
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================
    /** Default constructor; yields an empty interval <tt>[0,0)</tt>. */
    closed_interval()
        : _lwb(unit_element<DomainT>::value()), _upb(identity_element<DomainT>::value())
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((icl::is_discrete<DomainT>::value));
    }

    //NOTE: Compiler generated copy constructor is used

    /** Constructor for a closed singleton interval <tt>[val,val]</tt> */
    explicit closed_interval(const DomainT& val)
        : _lwb(val), _upb(val)
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((!icl::is_continuous<DomainT>::value));
    }

    /** Interval from <tt>low</tt> to <tt>up</tt> with bounds <tt>bounds</tt> */
    closed_interval(const DomainT& low, const DomainT& up) :
        _lwb(low), _upb(up)
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
    }

    DomainT lower()const{ return _lwb; }
    DomainT upper()const{ return _upb; }

    DomainT first()const{ return _lwb; }
    DomainT last() const{ return _upb; }

private:
    DomainT _lwb;
    DomainT _upb;
};


//==============================================================================
//=T closed_interval -> concept intervals
//==============================================================================
template<class DomainT, ICL_COMPARE Compare>
struct interval_traits< icl::closed_interval<DomainT, Compare> >
{
    typedef DomainT domain_type;
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;
    typedef icl::closed_interval<DomainT, Compare> interval_type;

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
struct interval_bound_type< closed_interval<DomainT,Compare> >
{
    typedef interval_bound_type type;
    BOOST_STATIC_CONSTANT(bound_type, value = interval_bounds::static_closed);
};

template <class DomainT, ICL_COMPARE Compare>
struct type_to_string<icl::closed_interval<DomainT,Compare> >
{
    static std::string apply()
    { return "[I]<"+ type_to_string<DomainT>::apply() +">"; }
};

template<class DomainT>
struct value_size<icl::closed_interval<DomainT> >
{
    static std::size_t apply(const icl::closed_interval<DomainT>&)
    { return 2; }
};

}} // namespace icl boost

#endif

/* closed_interval.hpp
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
*/