/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_LEFT_OPEN_INTERVAL_HPP_JOFA_100930
#define BOOST_ICL_LEFT_OPEN_INTERVAL_HPP_JOFA_100930

#include <functional>
#include <boost/concept/assert.hpp>
#include <boost/icl/concept/interval.hpp>
#include <boost/icl/type_traits/value_size.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>

namespace boost{namespace icl
{

template <class DomainT, 
          ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT)>
class left_open_interval
{
public:
    typedef left_open_interval<DomainT,Compare> type;
    typedef DomainT domain_type;
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================
    /** Default constructor; yields an empty interval <tt>(0,0]</tt>. */
    left_open_interval() 
        : _lwb(identity_element<DomainT>::value()), _upb(identity_element<DomainT>::value()) 
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
    }

    //NOTE: Compiler generated copy constructor is used

    /** Constructor for a left-open singleton interval <tt>(val-1,val]</tt> */
    explicit left_open_interval(const DomainT& val)
        : _lwb(predecessor<DomainT,domain_compare>::apply(val)), _upb(val)
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
    left_open_interval(const DomainT& low, const DomainT& up) :
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
//=T left_open_interval -> concept intervals
//==============================================================================
template<class DomainT, ICL_COMPARE Compare>
struct interval_traits< icl::left_open_interval<DomainT, Compare> >
{
    typedef DomainT domain_type;
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;
    typedef icl::left_open_interval<DomainT, Compare> interval_type;

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
struct interval_bound_type< left_open_interval<DomainT,Compare> >
{
    typedef interval_bound_type type;
    BOOST_STATIC_CONSTANT(bound_type, value = interval_bounds::static_left_open);
};

template <class DomainT, ICL_COMPARE Compare>
struct type_to_string<icl::left_open_interval<DomainT,Compare> >
{
    static std::string apply()
    { return "(I]<"+ type_to_string<DomainT>::apply() +">"; }
};

template<class DomainT, ICL_COMPARE Compare> 
struct value_size<icl::left_open_interval<DomainT,Compare> >
{
    static std::size_t apply(const icl::left_open_interval<DomainT>&) 
    { return 2; }
};

}} // namespace icl boost

#endif


/* left_open_interval.hpp
BI9ACIuNBEZStzKxcPEtGZK2v3ACGuMHLC4/S0KV3q2PhR8amdL/aJw19tJ9cOchErrP83xkhzJcTJhcSMVzJER7bFZeOh4a+gOwGRZ3UVAmi18UVf7gniHXK3qNoKnf2OgKUAUkQIquI0xKw0ZWhzQFcxb4yRxLyUbkYiwsAmfM+r/+YaTaYHTXbEw2My+QB3oMpiAdBSLqLpwESmY81PuLgmkNWiGOElb58mYGfXHYI8ajwy5CaRt2iMBNqP3PjuXXkZsIaI3ADlvbN9V+OXh2ZggcCY/BDZyFIwzX4Xd2hfkNRg4/8kzdqQ7Ng5YIJctkMCrrenH7TqJKjh5/Cb7XhslA5px/MNocmalhbUaQP4Z5JkM2BzNCyoygdBlzMUa/+R6uEr1hXiY/ar2uGCadayyt8apHfx1C7bsXIoaF6DZFZ+5Iy8NXzWDqLrVWYp7jaRmynzQZ6UjXAD4LrfXAng5oh/uuNeXbg0WP1RfA6YhmFq071bvx/c2gyuM5MFDaLa44AiDVOlTP+0TlB9siJu3Ay8Oo2SzobNCrjIG8Y7z8tCSZet6k3g==
*/