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
tsIBvDiBhDQBHXxgP2/AYSWghxPsrwXIugcSUgO8NoHE+sD6vwRJ8wP+u0E+FwCbJWBTIsD2O5DefbD/CSBeACxgBRjDB6zdQbAAk6yAmY9gj0PAbz1Ydg2kLg9R4gfyfgj2sQMLBAKqMkGG62CL64DuNsDhRcDKG5AkFth9ng1CDrClCBhOAezXAcIrPCDEAFvfAQUfALnNEDmTEBsPACFcgJb3YBNbwBYJ4NIcEJIGiDaD+HgKuGu5AYELKKoBXOUCqsIgaowBF+WAfgrA5DZESgNgYEABQhbs2ws4EQabGwHKrgGKEgCLB4D0H2AhfcB8EuDnGKJBD2LkBWBRHLBzEzBzCiJECDCxBdhlAaTVQkQaWkN4g33jIDaHAGlMgGw5wLA64KcDMOQFWBcFmwYAcj6D/Ysg7jzBwq4QN9oQy7iACRpA3HPAKBnE3SWIAnqIU1qIyX1A0y3ALyNgghSsvQTR0Qjo+BUgZRaQng3RPgVxHA5I+QrxPAxx6A7YfQ3omIEokwLkqfpYZGRFxPSI6S66V796WHSTV3ijo8lfdSlX40ST1mHg6wHHHDEdz72J1lDtsqM38xXo/+v/6//rX16DUod8Z0+yMnnfr9q4R7JJ8koy0Q8oo3SpuVMmSl2ZvRylg81Vja9DY6ROfXF+0pc8lWVm32/aRkZnsdD6+GSQ2UHsHuftPp+WTjeWky9qxq4DUm2y2sG8k9TPPUN5Gvtzhqe6sqkUbS+F2NWY8hJpMk8LNF2wIdcsuvJYm7lPeiCnU2rcglc0MJ/3RBlN9NfxvJBMSBp9k3S9Rs7lVr7wdtVG/c+1tz+qj6xt7jkwuBPo9d3z8L+4sxqj2VLGLHT7cYMPr92NHPPXasRKFv08fnNNMcyCNZlkYkvnZx9XGl46uSHVKn8kmcRfcrFv95d3/X5olbwrH3rJ8yLbrmYwR40w7c03KeZQEVV7wpHm2eeOOfqqvHQ3tak00ts1Z5Tqjq0UysKLq8t/pUvyVr49yMwwnuj8ULiGTjyOqPWUsMR8xa7mBWOvR1eqslzuTP7Io7JmlHEfGvzOFUtJs2vE4fja0k+tKJY4RmQFt6ojsvttIJHeyAUO0ushNvEfc0qD+y/E9msXmciGjfzC2UCGPaMivivwASVPBbIlff3loXhDU5ab8B3N4gx5c/8IAUn/XkrXvA85ty+idZz5R8dhagTFkq27xgK4kiJ+ne1mVsN63S5dTimDvb+gfDfkf1pk1+Dg7XmytnCSjAWhvtixa8ExRNsZ0l/ype9c5k/cpsfFEdMpijL0vd6HAjTFLwigyffmzY/zdOq5hTucpQdK1ZwF3uTvnNWLLW7WtGEnPcs90nWz2P99utzdb4d7W+1BxQnjWjSsM4NFko3Pe788W+bBVmbMeMHW2FmhNbmcnNE49Ir/pxnbkqELE1yyiZzyTSVWRA9GibrUi3ZtHhXRS8KvT/LVi3rkBi5sSut5lBx6DuAm4tHEzq5Kzwu0VQ7eYz7Vc8aky85b5INtuU3zo8P71l2fTv1iQnRycMyMeMp8+/K1Uc4BvSc91yraiF47H9KoJwv1HKpa90ZUNZxhmL5+3N5MvHom/4yO6AteORxJjfJQ04vuolNu3Rw60dIr6VHDL2ifeA5ceNrtjEVw8rRj867+21Gp8U9urudWB5flrjkJ0JZndLP+qlGT1vu73PnN8nOs/UcVzk+0hF88K+XwHFQ27lR/4hyjPU/2OncT55Tu159x3i0LU2ONFzVHXb9aL5R1wi5EoOzR9smer8GCPTeZbU9R+6m20Umf2Rph7yszz2n5s/e/qi0POXIWBuU3MpTeV2QZ3Dobku+mLMaTLD0ls7DWR1g=
*/