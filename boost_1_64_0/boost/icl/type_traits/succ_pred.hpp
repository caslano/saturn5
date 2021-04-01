/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2011: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_SUCC_PRED_HPP_JOFA_080913
#define BOOST_ICL_TYPE_TRAITS_SUCC_PRED_HPP_JOFA_080913

#include <boost/icl/type_traits/is_increasing.hpp>

namespace boost{ namespace icl
{
template <class IncrementableT>
inline static IncrementableT succ(IncrementableT x) { return ++x; }

template <class DecrementableT>
inline static DecrementableT pred(DecrementableT x) { return --x; }

namespace detail
{
    template <class DomainT, bool increasing = true>
    struct successor;

    template <class DomainT>
    struct successor<DomainT, true>
    {
        typedef successor type;
        inline static DomainT apply(DomainT value){ return ++value; }
    };

    template <class DomainT>
    struct successor<DomainT, false>
    {
        typedef successor type;
        inline static DomainT apply(DomainT value){ return --value; }
    };

    template <class DomainT, bool increasing = true>
    struct predecessor;

    template <class DomainT>
    struct predecessor<DomainT, true>
    {
        typedef predecessor type;
        inline static DomainT apply(DomainT value){ return --value; }
    };

    template <class DomainT>
    struct predecessor<DomainT, false>
    {
        typedef predecessor type;
        inline static DomainT apply(DomainT value){ return ++value; }
    };
} // namespace detail

//------------------------------------------------------------------------------
template <class DomainT, class Compare>
struct successor
{
    inline static DomainT apply(DomainT value)
    {
        return detail::successor
            <DomainT, is_increasing<DomainT,Compare>::value>::apply(value);
    }
};

template <class DomainT, class Compare>
struct predecessor
{
    inline static DomainT apply(DomainT value)
    {
        return detail::predecessor
            <DomainT, is_increasing<DomainT,Compare>::value>::apply(value);
    }
};

}} // namespace boost icl

#endif



/* succ_pred.hpp
mbmG1uQIvvIw0oogzqI6KNDXxyE41G239GyZNaHjR/GP+rYkaw6HtNx4G0i/FTjY6rrAff2zEYS2OAbQFAB8kZq238z2lX/EgIPRCSHiHFPMEHwMlWpX7kxustgw0//bih1mZvywj6klmfjDotDyZzKY7BoU8u2pO3PQJWdqPHfNDqqJXqq8jI5TvmbXvbcwoaFFgAkxWpVITlodcyyrx9jgnzbEwXLIg5Owk2oI/mJXvub8BV7VW//0wYVRkjRa8ltcAqNvsVTeq6/7lnafZUT0Ww0VN/rEwc+mR3RSGvVk4Kh6iIGdsg0lTJRrGX9Uk0/oRxkm4yOa55LVsbBW2qYZbjEfV6iJzHoDDtdO8PPOVOBSzsMQZrML4zLdCvsiL055Nq6t8ioPhzSkFKmOnOrM/2z53B1Y2QBZp0XwAPQzClvQaNvBqq1z+aMLnvGQ8cAZtpPNEKc2pKKLnLr1WecWVF4z31ptm5zcWqdBfFa9HK/mm3bEIHB/avqNJ9ssTpfVg88Ua1TAvUoAAXOekzkORT5RLm/389RFSYj7jF2Wc4sS3/cM0lGLUg==
*/