/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CLOSED_INTERVAL_HPP_JOFA_100324
#define BOOST_ICL_CLOSED_INTERVAL_HPP_JOFA_100324

#include <boost/icl/detail/concept_check.hpp>
#include <boost/icl/concept/interval.hpp>
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