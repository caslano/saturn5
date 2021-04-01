// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_FORWARD_HPP
#define BOOST_CONVERT_FORWARD_HPP

#include <boost/config.hpp>
#include <boost/version.hpp>
#include <boost/optional.hpp>

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#undef BOOST_CONVERT_CXX11
#else
#define BOOST_CONVERT_CXX11
#endif

// Intel 12.0 and lower have broken SFINAE
#if defined(BOOST_INTEL) && (BOOST_INTEL <= 1200)
#   define BOOST_CONVERT_IS_NOT_SUPPORTED
#endif

// No C++11 support
#if defined(BOOST_GCC_VERSION) && (BOOST_GCC_VERSION <= 40600)
#   define BOOST_CONVERT_IS_NOT_SUPPORTED
#endif

// MSVC-11 and lower have broken SFINAE
#if defined(BOOST_MSVC) && (BOOST_MSVC < 1800)
#   define BOOST_CONVERT_IS_NOT_SUPPORTED
#endif

#if defined(_MSC_VER)

//MSVC++ 7.0  _MSC_VER == 1300
//MSVC++ 7.1  _MSC_VER == 1310 (Visual Studio 2003)
//MSVC++ 8.0  _MSC_VER == 1400 (Visual Studio 2005)
//MSVC++ 9.0  _MSC_VER == 1500 (Visual Studio 2008)
//MSVC++ 10.0 _MSC_VER == 1600 (Visual Studio 2010)
//MSVC++ 11.0 _MSC_VER == 1700 (Visual Studio 2012)
//MSVC++ 12.0 _MSC_VER == 1800 (Visual Studio 2013)
//MSVC++ 14.0 _MSC_VER == 1900 (Visual Studio 2015)
//MSVC++ 15.0 _MSC_VER == 1910 (Visual Studio 2017)

#   pragma warning(disable: 4244)
#   pragma warning(disable: 4224)
#   pragma warning(disable: 4996)
#   pragma warning(disable: 4180) // qualifier applied to function type has no meaning
#   pragma warning(disable: 4100) // unreferenced formal parameter
#   pragma warning(disable: 4146) // unary minus operator applied to unsigned type

#if _MSC_VER < 1900 /* MSVC-14 defines real snprintf()... just about time! */
#   define snprintf _snprintf
#endif

#endif

#endif // BOOST_CONVERT_FORWARD_HPP

/* config.hpp
SrU3vpM3Ns5NgwNkpFlXcamzgFnva0vCxI5LmPk3o5bhPcZnfugdVNLnHENcS/v0bsd2jAIJKBLjMAHxpEF6SO2JAG9gx03Pgli0RGr36rKbRsM1p3L5wzfO2pBHGXAO3gQR6DCMo8qRxomakve9NkzEBqo24NtGG6ILPWuyrIyXD+E9fcmlu0JqCFm3PlqAYJiYRuxMvaT0tQ24O3vE0kpHkKCusDqVfbTezSTSx8SKhuZ0eKiMI5jeJJadnYVRof8sZGroE2Ewfg8f50HcciiEK/9AUtICAJYrfif7C8+wT+H/pnkB7TV3FrHuZAhTaXdFafN+485mUaEtOCu/k6x002oQTq/6sf8hfXploY0y79Grr+EDxvzkb25tap6bAZeOSrNYPqPdaH5iAH5f1lbga7ZTUIFeqxjzcfnt66bUiOi/04AOBZeavuex5drRkqI1HHPZTJYkt3MnFgxYSGx5P9yyFZXzJTWQ8COz2zh9E39amPWce4biaHr/l+8/a7wayNB5OwXY8b/LGRicMhD92ouVUst8A16NdUvLONQju6glknWeqlvedA==
*/