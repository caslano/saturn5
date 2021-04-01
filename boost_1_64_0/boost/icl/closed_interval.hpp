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
gB1VJYE0msrHhAY7+JumHmfUgUSE32C0ML2V3d5FqfuGiC1uMZgjv0E0oo4zKVusmt+NF/TpE0EFUVN+7GNZ91GKcoHaZq85v3M7oSgQ7227jUNs+DAjiQ4cfKPcSWDe/Vop8tpQnLVrAuOWK25YJ9hpYGPorHDgPgJBhpo2sXD/kNtuVb8/RDeAk/zcYyLqWNpbBkBge3Y4FkILA1GFXKc02WgcJg3z9pWhriID1WnyH+TFrHZeI3gFvpn+rETNPFGLyYH8FZo+gmiUJ9134VQO5Xu869MTmG2IaJRRnyuUbc/IGjF3IbpLry2yhhjnmjFD0ToZtkDdiq1dfvW6V9L0BdKefx/fgzUvl6zAllxK5SEuOYMYBKGF0FchUo0BWNKCRhXFx/sfF5ANZChcme7BOcf2zHNk1dGjIkd8HJwofu5qqQT4S7doJPoVwrv56pUL7NEHROb2EYcce69J3KjmwAx6k/mBMc2ZMR+9c9HhLpgk0fsdLdUYyoV/dcARAMUM3SQPr/LV34Qi7ACE+wsyIaGVhCXtfMsoVXXxG/n5O77cE3CIieRBtg==
*/