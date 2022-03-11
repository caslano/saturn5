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