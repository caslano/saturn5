/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONTINUOUS_INTERVAL_HPP_JOFA_100327
#define BOOST_ICL_CONTINUOUS_INTERVAL_HPP_JOFA_100327

#include <functional> 
#include <boost/static_assert.hpp> 
#include <boost/concept/assert.hpp>
#include <boost/icl/detail/concept_check.hpp>
#include <boost/icl/concept/interval.hpp>
#include <boost/icl/concept/container.hpp>
#include <boost/icl/type_traits/value_size.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>
#include <boost/icl/type_traits/is_continuous.hpp>
#include <boost/icl/type_traits/is_continuous_interval.hpp>
#include <boost/icl/interval_bounds.hpp>

namespace boost{namespace icl
{

template <class DomainT, 
          ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT)>
class continuous_interval
{
public:
    typedef continuous_interval<DomainT,Compare> type;
    typedef DomainT domain_type;
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;
    typedef typename bounded_value<DomainT>::type bounded_domain_type;

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================
    /** Default constructor; yields an empty interval <tt>[0,0)</tt>. */
    continuous_interval()
        : _lwb(identity_element<DomainT>::value()), _upb(identity_element<DomainT>::value())
        , _bounds(interval_bounds::right_open())
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((icl::is_continuous<DomainT>::value)); 
    }

    //NOTE: Compiler generated copy constructor is used

    /** Constructor for a closed singleton interval <tt>[val,val]</tt> */
    explicit continuous_interval(const DomainT& val)
        : _lwb(val), _upb(val), _bounds(interval_bounds::closed())
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((icl::is_continuous<DomainT>::value));
    }

    /** Interval from <tt>low</tt> to <tt>up</tt> with bounds <tt>bounds</tt> */
    continuous_interval(const DomainT& low, const DomainT& up, 
                      interval_bounds bounds = interval_bounds::right_open(),
                      continuous_interval* = 0)
        : _lwb(low), _upb(up), _bounds(bounds)
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_STATIC_ASSERT((icl::is_continuous<DomainT>::value));
    }

    domain_type     lower()const { return _lwb; }
    domain_type     upper()const { return _upb; }
    interval_bounds bounds()const{ return _bounds; }

    static continuous_interval open     (const DomainT& lo, const DomainT& up){ return continuous_interval(lo, up, interval_bounds::open());      }
    static continuous_interval right_open(const DomainT& lo, const DomainT& up){ return continuous_interval(lo, up, interval_bounds::right_open());}
    static continuous_interval left_open (const DomainT& lo, const DomainT& up){ return continuous_interval(lo, up, interval_bounds::left_open()); }
    static continuous_interval closed   (const DomainT& lo, const DomainT& up){ return continuous_interval(lo, up, interval_bounds::closed());    }

private:
    domain_type     _lwb;
    domain_type     _upb;
    interval_bounds _bounds;
};


//==============================================================================
//=T continuous_interval -> concept interval
//==============================================================================
template<class DomainT, ICL_COMPARE Compare>
struct interval_traits< icl::continuous_interval<DomainT, Compare> >
{
    typedef interval_traits type;
    typedef DomainT domain_type;
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;
    typedef icl::continuous_interval<DomainT, Compare> interval_type;

    static interval_type construct(const domain_type& lo, const domain_type& up)
    {
        return interval_type(lo, up);
    }

    static domain_type lower(const interval_type& inter_val){ return inter_val.lower(); }
    static domain_type upper(const interval_type& inter_val){ return inter_val.upper(); }
};


//==============================================================================
//=T continuous_interval -> concept dynamic_interval
//==============================================================================
template<class DomainT, ICL_COMPARE Compare>
struct dynamic_interval_traits<boost::icl::continuous_interval<DomainT,Compare> >
{
    typedef dynamic_interval_traits type;
    typedef boost::icl::continuous_interval<DomainT,Compare> interval_type;
    typedef DomainT domain_type;
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;

    static interval_type construct(const domain_type lo, const domain_type up, interval_bounds bounds)
    {
        return icl::continuous_interval<DomainT,Compare>(lo, up, bounds,
            static_cast<icl::continuous_interval<DomainT,Compare>* >(0) );
    }

    static interval_type construct_bounded(const bounded_value<DomainT>& lo, 
                                           const bounded_value<DomainT>& up)
    {
        return  icl::continuous_interval<DomainT,Compare>
                (
                    lo.value(), up.value(),
                    lo.bound().left() | up.bound().right(),
                    static_cast<icl::continuous_interval<DomainT,Compare>* >(0) 
                );
    }
};

//==============================================================================
//= Type traits
//==============================================================================
template <class DomainT, ICL_COMPARE Compare> 
struct interval_bound_type< continuous_interval<DomainT,Compare> >
{
    typedef interval_bound_type type;
    BOOST_STATIC_CONSTANT(bound_type, value = interval_bounds::dynamic);
};

template <class DomainT, ICL_COMPARE Compare> 
struct is_continuous_interval<continuous_interval<DomainT,Compare> >
{
    typedef is_continuous_interval<continuous_interval<DomainT,Compare> > type;
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template <class DomainT, ICL_COMPARE Compare>
struct type_to_string<icl::continuous_interval<DomainT,Compare> >
{
    static std::string apply()
    { return "cI<"+ type_to_string<DomainT>::apply() +">"; }
};

template<class DomainT> 
struct value_size<icl::continuous_interval<DomainT> >
{
    static std::size_t apply(const icl::continuous_interval<DomainT>&) 
    { return 2; }
};

}} // namespace icl boost

#endif


/* continuous_interval.hpp
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
*/