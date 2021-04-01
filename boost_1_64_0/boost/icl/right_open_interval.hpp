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
#include <boost/concept/assert.hpp>
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
OpzrWoG4TrlUkjkDvZN2N/5/8MGH2TIMyhP7HLMD4CtQASYT+uwWUJoiZJGp9Twmtkfyw94II4cSizF7OPPLLtxl4NLxAJduRoby4gtNq0tGWP3Z2jcCOw+ZuoSgrXcQtLsQb2KL2WWVL9TbMlDDFI1vFtDIl+LMr7ICOSzXjWlczlyYcjZAziNZjNlP5DexR0tv/0HTJztr6sG6OR7hGdAWZSKQ4yd1gEB0+v0IJdHyNrt49XeIvak1KFxcdUfHSMtHYluMRwWDZ7CT1gwOK1wNQD/OVW3VFT38zUN3gHY4GCUeNNOjNmeki39ioEBA3Z6KDd8AjeXYnOrnhvlceJl9ePUoStM/CrnF4j/nROiCEZtT5WWNFUTWDN5DgzByvEXiAgNHrvEeTVH656QO2rJzkc1anJ/q4mZaeWybTjalmwjvmaL8vk4WhgehOtWXI6DmUgx/uPKxhM9ukjG/Lu66BQ+nmt13xi0UHX2uiUCI4JgJXKUg3E3v9A3Cy58ZJS88nJAbCZRr+fgHulXiStV2xSsDir4aMcSnHQ5iukueW33WwcRuL3MTPQ==
*/