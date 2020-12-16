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
XIs1OmHA1rvIVVW7xBvuU9tUOHOd3TPgZU3P3vWHMrORPrZeshdd7wb/soZVYoh3nOPJJdFErEn7nch07qtHEWTZT3+lcUNSxeVHefu4X4DmNYnq+pmzGSZppGFudZ3ll/z6Ni1XPcOxJz8vMqe+1qr2ld3vyxKL0SXjcjeZvVHYoT7RzWGvZaxqrNxDdcO0cL3J9+aLlG263PHXHs8pgi98LXfnEK0rFd94+vDkegbD+Xyib4+HfzjO3E1z1jS+ZccyITTrnjl6qrMqofpwfGlf6OUD/7a+gq1k7Quj+G0etDg96VwaH049VAkpnXefw4nhMDF9VMG7M37486mD1X5nDvd8I6+hMtYqFnlNRdf90HmBp/rUChQhp+v6v/qZ28q6Mza6kPseslypTHon5kpqI0fPSZd/tW1Iuu/2Q6eT7fEzTr8oWDZKWo13+65VG3+W90khJddi0cHQIS61RcUV8lSKRJPeMsuaNStR/EW1I5yxQkWf97/gP3Wj+CeWIYlsS1fnqXi/tZSsym6uh8/UTKokEuL4f5xeD6G6W+1YyqsbRmI0YfE1LfW6gPS4zYuT3613/VcKGT/633hMfDT1Q39clr94zilLFS4jVvhU3xJK4GpraOquQzH9mpDRg4KSm+GWuXXn1YfYLqPm+OGf8A54v9qs91Oz9898eGrKdn0qIZJ+RJBgPPLlTvHb2em8IKKkCi9CPEOdB8vhZzbGdXGCDlfN62kni5m0CgTd1XB+QSFYwvPLonC9x45kxLgHyZTs/WRz1onLnkqJopQUuom73dwTXbduOmwatldF55xezQngSDsVfI7yZ9eMGbEPly8qGMUIeDJRvsO3dfqKk9xwXUWI0NLuyZP7p7mGMl7fCmLU3rpD+6Tk2WcWw7sBxr2sRwWS5FapA1q0lxXHknGbzbJrPVGrhP7sqroFp9I8ww3P86yZL3Mzw/QObUTW12rwtqsNTs7arAnnLcnc3O7wNrrjUhU0K9+qbmcnNK0qTGr8ze4MNx+N7JX3FVSJG7/CufTYDf+6OnMaiVhe01lspx7LcHwVbK6PtJ99I+50/PJS6z2mnDGirpO/WCn8eJe6hLaVo1vyYj7XnAS/+VV0VPJyZXyhXtkQRyxeH63ifSaXX9HUlo58+XCfy5RhbUFfPThbjCWnLSZL9cmrFMMWG5Vrtz058941MZD+eHzx++MJnPHW1+OLNwcvvFsKYBs7S1Z96V4CtfiXbWtKjrYUdv36RuLUB6Ej8yH5P4k7UmPhM/3/+P8bjz+rVI8d/feE+WEnp7P6PM0/rZsoSlpEX4ULycXtRxZ9RASefLu42qU9ZjBE8qy8h2pls5khXKJIbcdlrL0mYigbj3Mm7ds6WVL+lLAvUb9RD+notGKzt110T5GmNPer04M32vV0T2rk6YiaQnsue7sXsmwtvm3y6Vq4nUF7NoZfqqDKnzBZgfe+0dDusZP9hxH/7VN0jh/JlgU2V+NudGC9C7jd3B8pjLVd6yBTOsKtrs4oeIOtZ/4aqc84zevBD/W2H+TWSNN6V8avjlGG6QWXcSRR8I9yxKxpWJe9xOKT5hUZnzunkVGCl3Cy3yhcL+FC79w1ocBu8urz4Bv2+579lQdtl+MCsf+v//9h/U8OrCX/yrfL5IF9ne+iNkPnZIK2yxc1voyiJVfta7O6idfssX/k/YKqi1tkfegiSg0dsaVVjJAlkIrLDFnZVogRupfTS99ms3XwUHnBu5F4qDzbe82QSrH4O12QAn477Zb5G0N4ItJikvxl62KnqXP8kzz7cpL7JBfs8h7lVOyIc+Nd+ZX+2inBe26LIS05PjeeHvwqKIA3uLP7hg3fsq35j4c=
*/