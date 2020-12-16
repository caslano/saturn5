// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//

#ifndef BOOST_ASSIGN_STD_SLIST_HPP
#define BOOST_ASSIGN_STD_SLIST_HPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_SLIST

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/move/utility.hpp>
#ifdef BOOST_SLIST_HEADER
# include BOOST_SLIST_HEADER
#else
# include <slist>
#endif

namespace boost
{
namespace assign
{
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< BOOST_STD_EXTENSION_NAMESPACE::slist<V,A> >, V >
    operator+=( BOOST_STD_EXTENSION_NAMESPACE::slist<V,A>& c, V2 v )
    {
        return push_back( c )( v );
    }
#else
    template< class V, class A, class V2 >
    inline list_inserter< assign_detail::call_push_back< BOOST_STD_EXTENSION_NAMESPACE::slist<V,A> >, V >
    operator+=( BOOST_STD_EXTENSION_NAMESPACE::slist<V,A>& c, V2&& v )
    {
        return push_back( c )( boost::forward<V2>(v) );
    }

#endif
}
}

#endif // BOOST_HAS_SLIST

#endif 

/* slist.hpp
DWPVLTpWTWOs2uazwFh1Ol8c58wvNS1w49kjbgjhz5WnuTuQNboG3ak6LunvVB2X5EQZy+ZGGcvmOVXHJROjjG+nRhnfFkUZ35ZGGd/q2jId30qbCaQZNuYNX7++LiOGzuLtKbXXWUzYWDqL8bM6i9c1dSf3aqGzmDhBXbh9Cbsw45fRWRyUAy9uFl2Pr9mRst96fIljr30919y/2U/X4xvUO7KvWXTdt213pOyX7lvC/2Tdtx9kRtd9m70jZb913xInpu5b/GLqvsXvV9F9u715dN23OTtSfpTuW+LF1H2LXyzdt9ZPnjFc7FXN63Tf/pK6bzuPdN0vy570zZ780sYHzK3/wupzpw2LJe8dS555/+XA91eO+n9Z921OpO7bH6njdkNw7krn/nbCZph1mv7XqtP2G5gLv4OjVa5tAnScgJy1H8q3CFgB68FlMBFeARvAFbAh3A0bw69gCkx1x+cwHabDprAJ7AAz4ADYTOUn68FjYAuYD1vBWbA1LIZtVO7LzlnovM1O45U/Fy5qCDvBbNhF5ajtN3WdK9gZ8DNDHSNHd5Xr7qHy233gFNgXzlQ5pVNgf5XbPkzltgeobtrD4cMwR3XTDlbdqkeq3NEI2JNzjYK58BhYCsfA38Dj4Q1wIrxZ5Y6ehifA5+FJ8BM4BX4Pp8IsX8B+LHTtZ6p9mdpXwGlwHSyAr8JCmOgP2I+Crn222hepfRmcCW+FRXANnA2fgsXwBWh1hdpvYrzHRimPeVoeZVrf5mu8Ip++w+t3JzfeCMxk3I3qPj4EnqVy9efCMrgUVsAL4W9U5/F58FJ4rcqFrVG5/HUql/+8yuW/B2+EP8CbTKB+roFt4B9hP3g/PAw+CI+AD8Eh8GE4Wv1PUPtC+KjKgz0Gn1H7FrW38QXs2dC1D4OPw9nwSbgIPgXvUvvrav9e7W39AXsv+AwshM/Bs+B6uEjtV8A/w2vUvgK+BFeq+yq1r4Yvu+dT+z1qv0/tT6t9HdwIn1f7S5rOy2rfCP8KX4V/g2+o/S21v6vhtqr7R+q+C74Kv4Sb4VfwXfgN3AJNXECeNwG+D3vAz+Fx8CM4B+6CS+BuuBzugTfAFfAJ+Af4FFwG18EvbT2VsfmP09m7I+VH6d5l3PmjdOgyzvtROnQZL+2XDt3yOh26tZb1+2+V8/s1ZfwqkN27CvMkZiem1afI+GGKMcswlZhNn9bJ99UddUfdUXfUHXVH3VF31B3/2cevJP8/Z37xT9f/30L1/+eJ/n9NVjX/u2sDemcZOxdWoN++6gVg4lW3tHnXyv0QuXp92COcYPh6Mi+daGreG6AmHdPfxbiune94r6tmndc73/m5risgJzXRF32fhBRvfmlmzy2o+XzeORejr0V9VA6vhwnoZqoMu+fa6b9NM8F47XUdQUy9aRruAAmXG1tvmobrLOHyYuT5WBuuiYSbaEw0nUlemScNr7JHVp5u//Ygj5x7zo2QnYstp15VB8/USB08EeW0Kj56OWWHlVPtdYNm17KcsmtZTtm1LKfs/Syn7P+ycspLiF5OpWHlVDu9hLJfaS3LqbSW5VRay3Iq3c9yKv0vK6d9idHLaefb3nKqvU66nW/Xrpx2vl27ctr5du3Kaefb+1dOO9/+7ygn1TUWY27755vD/qXngPd3Lnx/54Z/6f1hJ8nc/Jqmn3ye9GbRxOUDX7988Zzn3/v55qSjyyjEmquOJXOw/zITdo5F56rrYRZFzF2cqHMXk2E8PAlqPMZ4seMdp/GO13gTPfFS9HyJUeL10Xh9dW6mn8brb8crhNF4Xt1ZuTg1hMNhVzgS9oCjPPGzq4mfo/EHa/wjNf5QT/zSauLnafyxGn+cxh8=
*/