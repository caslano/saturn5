/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2015
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_DETAIL_MINIMAL_LESS_EQUAL_HEADER_HPP
#define BOOST_INTRUSIVE_DETAIL_MINIMAL_LESS_EQUAL_HEADER_HPP
#
#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif
#
#//Try to avoid including <functional>, as it's quite big in C++11
#if defined(BOOST_GNU_STDLIB)
#  include <bits/stl_function.h>
#else
#  include <functional>    //Fallback
#endif
#
#endif //BOOST_INTRUSIVE_DETAIL_MINIMAL_LESS_EQUAL_HEADER_HPP

/* minimal_less_equal_header.hpp
VsOyIPk6BVqathCsLg+9/bGebSK3XeGZpv0SKnfHpTxitqVIm0nRiWPNZLhfNqDHLDmcm+kTbTqulEFsx2elL6/54WjMvZSKpWTwLjkVsa2by8sDBP+8+aG23bIt5pQVmJCzz9/QuD702rhuIxXH4eDwu/Zll3zkse5hdTL+RfVXihx6uxKLaXGoG1+OmlyVK7d1g9mx5XymnYHF/V/C8N/C5QZMPAWDMSw6TdQ09py/fg4smjo9UjK8vb3fNAlHmfMsE/tGaXDi7pCUt+pTQHk9PLillWOwXstCz0KPmyQ36PVkOHyBzIir/MxoEaP6NtupvYYe4DOx+udVuLmmVMwqQlo/6fMs7pgnKR0OXStluYVZTsz0d3zs07INCGn0DppX56XHwRmGl9+bl/OxwZe0K4bhkEcqPUoxvB+l3Dz7SayYL5U9wIIDYTEuJSGq0numvsl3dHqMHdzPa8dr1hZbfUMuqu/uXuWl2+RTxatVZtm5szJGJxK7topflFA3RMIVLbxhGigyiYt7g7gJKBJKqpMGVuJut01bXxxkxa1CiRrq3vxqcBFF9+Odlmx9088plXqHNfC0hcjUiqXDeNBNRb+js4NUHEa8HXz5qRNZQJ6GKoR0bqyyOG0rUHUGacXm0udS6BHxVbwTB/Cl/ZnmkeCRW6a4tjevz1ht4In+VeyVwPpyawfnFfWV+FWgE1uC6U8UKyw17R0A
*/