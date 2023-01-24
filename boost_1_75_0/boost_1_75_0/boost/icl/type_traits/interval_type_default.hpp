/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_INTERVAL_TYPE_DEFAULT_HPP_JOFA_100403
#define BOOST_ICL_TYPE_TRAITS_INTERVAL_TYPE_DEFAULT_HPP_JOFA_100403

#include <boost/mpl/if.hpp>
#include <boost/icl/detail/design_config.hpp>
#include <boost/icl/continuous_interval.hpp>
#include <boost/icl/discrete_interval.hpp>
#include <boost/icl/right_open_interval.hpp>
#include <boost/icl/left_open_interval.hpp>
#include <boost/icl/closed_interval.hpp>
#include <boost/icl/open_interval.hpp>
#include <boost/icl/type_traits/is_continuous.hpp>
#include <boost/icl/type_traits/is_discrete.hpp>

namespace boost{ namespace icl
{

    template <class DomainT, ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT)> 
    struct interval_type_default
    {
#ifdef BOOST_ICL_USE_STATIC_BOUNDED_INTERVALS
        typedef
            typename mpl::if_< is_discrete<DomainT>
#  ifdef BOOST_ICL_DISCRETE_STATIC_INTERVAL_DEFAULT 
                             , BOOST_ICL_DISCRETE_STATIC_INTERVAL_DEFAULT<DomainT,Compare>
#  else
                             , right_open_interval<DomainT,Compare>
#  endif

#  ifdef BOOST_ICL_CONTINUOUS_STATIC_INTERVAL_DEFAULT 
                             , BOOST_ICL_CONTINUOUS_STATIC_INTERVAL_DEFAULT<DomainT,Compare> 
#  else
                             , right_open_interval<DomainT,Compare>
#  endif
                             >::type type;
#else
        typedef
            typename mpl::if_< is_discrete<DomainT>
                             ,   discrete_interval<DomainT,Compare>
                             , continuous_interval<DomainT,Compare> >::type type;
#endif
    };

}} // namespace boost icl

#endif



/* interval_type_default.hpp
EVMqupriecI1PAXaerzL0aQINJrVBAygly3AGsDvLxWf1fQi6qvODT32zM4YS/8q7u3Zeza+5YJX0T3bTBy4J6CgGW146Dp3LAbsgcY7aFziTA/Ng1ZPzOmwkacad/1sbsPc45zVakoDivt+6mvQp48eNW0xUHHnz+YL8O770uT5U2dRcR/F9ib01Tt/6bZhwl1AczzQmc893SenMKS04zQ2dzrN1xeuW1jfoLJnjp8H/Ee7OL5mMcdnXgD8Bzq+meODuFPH8bcMjl+MskUXYT36Lg9eht+pLfCr8k+QQlA7APcRlWFvpbP68RhbGVTcRXDwQpS9aaZpDKm4m+iIB3Pez/CsnpYSdxMddKO+h99n3uaA+4nKXdjL9NsU2UWR9Rbu5Rhsh05a8Kx7CEbcX3SI2hV/qTBvScEdRtvPxbfNLo3hDqm4e+LkhdBHy7ndIdmUumOFOz9QvyOd4x91D8WIMxqEdz+Nt/34QH2P14etlsCVXQT/+Zmb5xKfE3s76H1JbfD7y19FTIeMd6ApfnMDfPZPj4rnDoF3XYi41T1VGl7bk4E7lgbg4zjfqxrKvcGdS5nzUfdTHmll+TxjfgPuMNnegLpv7XYPwQi+OfS73vxxbTeMJB/F7boA5fx1O+Gl59sZRVVxh9Mu8g2Fk28/tSnsDxN7FukI/RE9y6Kq7iU8xRdCx7ady+Pn/J9AdPkSXygUXLFkhmPW
*/