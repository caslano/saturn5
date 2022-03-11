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