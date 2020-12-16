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
l4H/ISUCAPD/5YsAIAwBgAgBAPh3Av8voxAApCAA6I4A4CICgG8IAB4iAAD/G+DvCv6W4G8I/ie7IAAA/6Pgb9UBAQD4V3NGAAD+NWwRAIB/Dvg/BP+X4N9qOAIA8FeCf03wHwX+bd0RAIB/I/AXg39v8F8K/tHg7w3+14YiAAB/B/B/1B8BAPjngn8M+BP/4P8a/Nng/xP8t+5EAAD+qZMRAID/ARkCAPDvCv5h4B8/GgEA+BcfRwAA/uteIwAA/0DwDwf/duA/Gvw5zxEAGCIAAP/h4B8F/j52CADAfw34dwf/5eDfuRoCgE4IAJohAAB/T/D/BP77wH8n+N8KQAAA/mbgXw7+H8D/0ggEAOBvAv7mRxEAgD/XAwEA+AeBfwPwPxaHAOAnAgDw9y1CAAD+/cDfGvzlhxAAgP8I8I8E/9tBCABiEQB4IwAA/3Hg3+UkAgDwLwR/C/C/C/79wb8W+JeA/33wd1MgALBAAAD+oSYIAMDfthABAPgfAf/LgQgAjiEA6IgAAPxng//j9wgAwP/ZRAQAYgQAtxAAgP9k8L+6CAEA+K8FfxH49wD/j+D/AvwFHxEABCMAAH8j8N9ThgCgKwKAvggAwL9xTwQAcgQA4H8C/EvzEQCUIgAAfxvw7wb++8F/oikCgPsIAIYgAAD/AvBPAv8Q8DcA/8+NEQAcQQCQigAA/HuC/+4GCADA/zD4NwH/PPB/AP5f2yAAAP+64C8E/5s1EAC0QwDgiADABwGAJQIA8H8O/ufBPy4KAQD43zNAAAD++eA/HvxrCxAAXEcAAP4B4J8C/v7gPx/8HcHfFPy3gH8s+O8F//pRqz92jxH4Dzu6okHDOf1beZ1JW+/9jrPYZn389w0zDR51i/vuwv6cnrFxesbZcXZh+p9+Xn8Sef1M6+M5QR4tpy5PKAjtvfVucqM9dvPqvOA8OPS7n77S+Wi9srARy+d2mXzi2+W0Z9ypBrMXzbB8OSj94K1e0bMdRx24crmZIt5BeD80qOjUlNTxR5RZ2VM+pvnFz78zcHernZEPDjTYOK4saQP71A6v80Otut7jj3Rt+GRAu+5zOcNjEu5nJm7N3ZS2t/HSEb9ntTH6Fp8SIrX+xZk6VnR31q6vg6NbXJavf6jfTdZzqs2j1uvjkmrYv9xmcKTAecHg42NWGnW4/H6svcu2lQdb7Ek10O87sv7rNo0vTJixI3t12fsaH/IfCiPOfbwluHqgWnWbBPeLE36vOrY4xsl9adyHZW4PJlRTvvy8ouOrUbXWvR3QufqSgf27m4n3f5vQzM+3+p05m6r53emy/2l4weTY6dX6HRsouVLdsNwyaoDtj3nWc5/vv3Y2sPP4zLybyfsDSreMmzi+hmcf62clb4qyg42H5D83DRhyqmnuVxbSqDE5NUNet3HbIK3bNELWW/SjvM6vHp6jTZte3eTbqqNj+8SbpsbNVvVNuRjbZ6GXU3vbrcnGJqbPes68NOfNjrzpCxtFHj+Us4x9myfsltm7fsN6jY33zHz4pPXSQ4H3m/s0adCoXq3aNetsPDnx/e41Ox2L1ja1GG39rmdYDeXmvXfmv/k1YPjyJS31vuz7JOt73DspyH3Yjz4ZDoETb59ocSbl5+ud/HePC0/fdr1uNpof0Ln5XHN23RO5Q227jv7qu/dSXbdvm9LzHU52c85r8sFl2+1X0WNqFz86nCmqv73N/N3Std9DZtVtnvg8+Nikn2sadipbeqPt0B5vp7VrfjIidOzhi543fy87Pal9rSvzLoz4tMr+7qCVLafsurXi4MZOjxd7ta09Iytq4VluakKXYbFHzCd/Li28Ma3/l45OnzYfHXkgp9+SITOLhWs=
*/