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