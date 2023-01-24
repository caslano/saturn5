/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    noexcept.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_DETAIL_NOEXCEPT_HPP
#define BOOST_HOF_GUARD_DETAIL_NOEXCEPT_HPP

#include <boost/hof/config.hpp>

#if BOOST_HOF_HAS_NOEXCEPT_DEDUCTION
#define BOOST_HOF_NOEXCEPT(...) noexcept(__VA_ARGS__)
#else
#define BOOST_HOF_NOEXCEPT(...)
#endif

#endif

/* noexcept.hpp
PA+e2VO8oJV415NVN9gZouXkCCH1k8Dc48L+w2N+lo3Ri2WWy4D1bWO46qof6UbRUYeAhoP6h4v7RRc0mrA/Rd6sakncBqS+ywZ5DXurxs11YyY6X+tY3fbm2G+QtqvkOwo/Dejzf2OoruOqDTpYb9uLWKdEX+u2OStiTrAl8KVeFcBb/Uk24yWuNWi/7MSBx8ilqdozqbko6pOAKfWkpaEL1bKsqeuN+iDdNBIzW6tyG7Pylye0rsQSZQxtpZkZfhKwx+tfMZ33vJg1l8wHjhRAQwDe2CWyM3aYY7DBXinz0t+Kex+syONQVXZrwFrqiSq6q90X8a/eaw4mr31Vvm61hLyOA/2yrQccjaduwdBHMbZWnL+RQ/7OLlnbDCf5zr6yl6//vuDaWjnVDWVUQQuOpz+LdSL7DnfJwjM/uUGSuzBQuBzAixbCTA1I4Np0v8unY6f0yYx4AHlLalurPVuKHF2NDTLAORwucirpp5071jNfwiclkzPdZ903ExegtuhxEToVPGA8+BCj7S3z1mnU3EBg2MujYxymNY3ogUGD9kavh19q93n9Ma6S0WklAXDHXcgNrZ8pBOxGSKlRTjuJjbhK8A2qW/AWMV3QRX/b+v3jMUh98ZuQ+ZD09JG0aY9ff7rSMSsXG3f5+pzEr0gvZz54eGVDzrkf5yAoP2iRD/ztd0qx6LXR5ElYnaz0zGBt4EYei6Hkkqko
*/