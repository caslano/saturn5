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
#include <boost/concept/assert.hpp>
#include <boost/icl/detail/concept_check.hpp>
#include <boost/icl/concept/interval.hpp>
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
JOYCnLS7FhSm5xgJCu8wk8FhJnKmGFdNUSnJRCM/GDcXmru0VGC6qIhmgg1aULUwHSsoyOVZYSZZrB7UFk18mrmzcLcXkUTlV6ukqKTAAjTTjVsi/+RhxgquqRZmEualme7VvLlCIYekLJWqWlLScE18HnIUqvLDCvNrBZUunHGSCh/D4BzSVcN/NJXZNNMjSGWQKXExjUMEKCyf5xfD1Qi1Op1mfqYKV3hDhG66unwGQOVrpGtqvF2NID/yCGIgHUiljqpgrJ1eTd0AFgznF4sgHQkD6aRdiW3QSFdqlo8ApBp4Nclw+aT66DK4MN2raPJg0h2pWky6sZdLy8GG6z84yVgjucBbJ39OW5fCZM3yr5L6SJjLYKVGcgHT0PTycvFyUZKWKgYvVZJ4RiESqpeG/uK+TmdvV6aPV7ZPKdunlO1TStqnGGXJcY8iV+8/jGB3S1wk5LTfwL8YVyjBKEzA6U3p4kVxI7mRECEX9e6r0iprhCXJaftAS7sRKBVyjNN8n8TuZ0FcnymdB0xWhHlV5bN0jvhFgLg18KY1g5Y7vpR6sUUS1xYQ001ITb9aJQAXMb9qFndRNOfpYvAyUbDJ3PiquMoqxWgB6feRip+JMUYEMKKzoBeeAfEcaJIlyMLCBFmSnyBzUQiygoIUmRGk4FkwRSYIKbIkeYqsUjUkRUp5E0WKUUFBafXxUB7QrqWVmlo1bwJWX1pC
*/