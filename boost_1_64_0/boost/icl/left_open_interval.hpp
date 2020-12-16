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
BXpeev56K/QC9cL0EvXS9HL1DuhV69Xo1el16N3Q69Lr0RvUG9VDC7ACmoAj4AocBe6CFYJQQbggWpAoSBdsFWQJ8gWFgqOCEkGtoF7QIegU9AkeCgYFwwKkPl2fqc/TF+p76vvoB+iH6kfoR+rH66frb9ffqZ+rX6BfpV+t36Dfot+t36c/oP9Ef1yfbsA3MDUwNxAbOBp4GHga+BiEG0QaRBtsMMg0yDXIMygyOGJQbFBj0GJw32DAYNhgzGDCgGBIMVQx5BoKDS0NbQ0lhr6GfobhhkmGaYZbDfcaHjAsNSw3rDRsNmw17DLsNewzfGg4ZDhpiDdiGrGMREYuRguMFhkFGoUaxRptNyowKjQqNio3qjBqMGo0ajfqMUIao43xxmRjNWOWMc/YyNjc2NrY1tjR2NfY3zjaONk41TjDeK9xrnGBcZHxEeMy40rjOuN64xbjduP7xgPGWCFBSBLShHyhQCgRugk9hIuEXkJfYbQwUZgiTBOmC48IS4Tlwnphq7BN2CXsFt4XDgpHhGNCpAnZhGsiMLE2EZn4mPiZ+JuEmcSaJJukmGSYZJvkmBSZFJtUmdSaNJo0m7SZdJr0mNwzGTIZN5kwQZsSTNVMOaZ8UyNTW1MXUzdTD9MVpoGmYaaRpvGmqabZpnmmB0yLTctM600bTTtMu0wHTUdNJ00JZgwzFTOmmcDM0szPbIVZsFmEWbRZolmS2QazTLM8swNmR81KzcrNKs2azJrNWs3azB6aDZoNm42Z4c155gbmQnNLc4m5u7m/eYB5mHmEebx5snmqebp5oXmReal5lXmdebN5u/mA+RPzCXOkBcWCbqFmoWFhbeFm4WPhaxFsEW4RaZFmsdMi2yLXosDiiMVxi2qLJot2i16LJxaTFgRLFUumpZGluaXIUmLpZRlqGW0Za5lkucEyxTLNMtMyyzLPMt+y0LLSssay1rLessOy2/K+5ZAl1gpvRbPiWplaWVpZW4msFll5Wnlb+VkFWkVYRVrttMqyKrU6blVlVW3VYtVm1Wf10GrUCmmNtsZba1g7WrtZL7D2tF5hHWidaJ1qnWldZF1sXWLdZN1h3WP9xHrYetQaa0Oy4diY21jaSGzcbTxsvG18bQJsQm2ibWJtUmyybPJsjtpU2jTYNNm02nTYdNp02/Ta9NlM2iBtmbZcW56twFZoK7aV2C6y9beNsE22TbFNt91pm22bY5tvW2h71Pa4bblttW2tbYttt+092wHbIdtxW7Qd3Y5hx7Lj2xnYmdp52HnZ+dsF24XZRdol2221O2JXbFdp12LXYddrd89uwG7YbsIOLaKJNEQcEVdkJLIVuYm8RX6iAFGsaIMoTbRdlC86IDoiOioqFVWKqkT1omZRm6hT1CvqE42IJkVIe7I9zV7FnmUvsLe0d7H3tPe297cPtY+wj7XPsN9un2t/1L7Cvta+0b7Nvtu+x/6J/ag9WkwWq4k1xCwxR2wkNhdbix3FLuJocbw4UZws3iDOEGeLc8UF4hLxcXGFuFpcJ24St4qHxVgHggPFgebAdOA6CByEDuYOEgdfh2CHUIckhzSHrQ6FDlUONQ61DvUODQ5NDp0OXQ69DvcdhhwmHUiOZEdrR5Gj2FHi6OcY4BjqGOaY7JjiuNMx27HUsdaxxbHdsdvxoeOA4xPHCUcNJ44Tz8nAydTJ0cnFyc1phVOgU5hTpNNWp2ynIqdipzKnSqcapy6nHqcBp1GnMSeChCShSRgSjsRcYikRSRwlfpJQSYQkSbJBsldSIqmU1EhqJc2S+5IhybBkTIJ1xjurObOcuc4CZ6Gzi7O3s4+zv3Ogc7xzinO6c4bzduds51znAucK5wbnZuc=
*/