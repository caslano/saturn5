/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_DISCRETE_INTERVAL_HPP_JOFA_100403
#define BOOST_ICL_DISCRETE_INTERVAL_HPP_JOFA_100403

#include <functional> 
#include <boost/static_assert.hpp> 
#include <boost/concept/assert.hpp>
#include <boost/icl/detail/concept_check.hpp>
#include <boost/icl/type_traits/succ_pred.hpp>
#include <boost/icl/concept/interval.hpp>
#include <boost/icl/type_traits/value_size.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>
#include <boost/icl/type_traits/is_continuous.hpp>
#include <boost/icl/type_traits/is_discrete_interval.hpp>
#include <boost/icl/interval_bounds.hpp>

namespace boost{namespace icl
{

template <class DomainT, 
          ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT)>
class discrete_interval
{
public:
    typedef discrete_interval<DomainT,Compare> type;
    typedef DomainT domain_type;
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;
    typedef typename bounded_value<DomainT>::type bounded_domain_type;

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================
    /** Default constructor; yields an empty interval <tt>[0,0)</tt>. */
    discrete_interval()
        : _lwb(identity_element<DomainT>::value()), _upb(identity_element<DomainT>::value())
        , _bounds(interval_bounds::right_open())
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((icl::is_discrete<DomainT>::value));
    }

    //NOTE: Compiler generated copy constructor is used

    /** Constructor for a closed singleton interval <tt>[val,val]</tt> */
    explicit discrete_interval(const DomainT& val)
        : _lwb(val), _upb(val), _bounds(interval_bounds::closed())
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((icl::is_discrete<DomainT>::value));
    }

    /** Interval from <tt>low</tt> to <tt>up</tt> with bounds <tt>bounds</tt> */
    discrete_interval(const DomainT& low, const DomainT& up, 
                      interval_bounds bounds = interval_bounds::right_open(),
                      discrete_interval* = 0)
        : _lwb(low), _upb(up), _bounds(bounds)
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((icl::is_discrete<DomainT>::value));
    }

    domain_type     lower()const { return _lwb; }
    domain_type     upper()const { return _upb; }
    interval_bounds bounds()const{ return _bounds; }

    static discrete_interval open      (const DomainT& lo, const DomainT& up){ return discrete_interval(lo, up, interval_bounds::open());      }
    static discrete_interval right_open(const DomainT& lo, const DomainT& up){ return discrete_interval(lo, up, interval_bounds::right_open());}
    static discrete_interval left_open (const DomainT& lo, const DomainT& up){ return discrete_interval(lo, up, interval_bounds::left_open()); }
    static discrete_interval closed    (const DomainT& lo, const DomainT& up){ return discrete_interval(lo, up, interval_bounds::closed());    }

private:
    domain_type     _lwb;
    domain_type     _upb;
    interval_bounds _bounds;
};

//==============================================================================
//=T discrete_interval -> concept intervals
//==============================================================================
template<class DomainT, ICL_COMPARE Compare>
struct interval_traits< icl::discrete_interval<DomainT, Compare> >
{
    typedef interval_traits type;
    typedef DomainT domain_type;
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;
    typedef icl::discrete_interval<DomainT, Compare> interval_type;

    static interval_type construct(const domain_type& lo, const domain_type& up)
    {
        return interval_type(lo, up);
    }

    static domain_type lower(const interval_type& inter_val){ return inter_val.lower(); }
    static domain_type upper(const interval_type& inter_val){ return inter_val.upper(); }
};

//==============================================================================
//=T discrete_interval -> concept dynamic_interval_traits
//==============================================================================
template<class DomainT, ICL_COMPARE Compare>
struct dynamic_interval_traits<boost::icl::discrete_interval<DomainT,Compare> >
{
    typedef dynamic_interval_traits type;
    typedef boost::icl::discrete_interval<DomainT,Compare> interval_type;
    typedef DomainT domain_type;
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;

    static interval_type construct(const domain_type& lo, const domain_type& up, interval_bounds bounds)
    {
        return interval_type(lo, up, bounds, static_cast<interval_type*>(0) );
    }

    static interval_type construct_bounded(const bounded_value<DomainT>& lo, 
                                           const bounded_value<DomainT>& up)
    {
        return  interval_type
                (
                    lo.value(), up.value(),
                    lo.bound().left() | up.bound().right(),
                    static_cast<interval_type* >(0) 
                );
    }
};

//==============================================================================
//= Type traits
//==============================================================================
template <class DomainT, ICL_COMPARE Compare> 
struct interval_bound_type< discrete_interval<DomainT,Compare> >
{
    typedef interval_bound_type type;
    BOOST_STATIC_CONSTANT(bound_type, value = interval_bounds::dynamic);
};

template <class DomainT, ICL_COMPARE Compare> 
struct is_discrete_interval<discrete_interval<DomainT,Compare> >
{
    typedef is_discrete_interval<discrete_interval<DomainT,Compare> > type;
    BOOST_STATIC_CONSTANT(bool, value = is_discrete<DomainT>::value);
};

template <class DomainT, ICL_COMPARE Compare>
struct type_to_string<icl::discrete_interval<DomainT,Compare> >
{
    static std::string apply()
    { return "dI<"+ type_to_string<DomainT>::apply() +">"; }
};

template<class DomainT> 
struct value_size<icl::discrete_interval<DomainT> >
{
    static std::size_t apply(const icl::discrete_interval<DomainT>&) 
    { return 2; }
};

}} // namespace icl boost

#endif


/* discrete_interval.hpp
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
*/