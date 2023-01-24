
#ifndef BOOST_MPL_AUX_NA_ASSERT_HPP_INCLUDED
#define BOOST_MPL_AUX_NA_ASSERT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if !BOOST_WORKAROUND(_MSC_FULL_VER, <= 140050601)    \
    && !BOOST_WORKAROUND(__EDG_VERSION__, <= 243)
#   include <boost/mpl/assert.hpp>
#   define BOOST_MPL_AUX_ASSERT_NOT_NA(x) \
    BOOST_MPL_ASSERT_NOT((boost::mpl::is_na<type>)) \
/**/
#else
#   include <boost/static_assert.hpp>
#   define BOOST_MPL_AUX_ASSERT_NOT_NA(x) \
    BOOST_STATIC_ASSERT(!boost::mpl::is_na<x>::value) \
/**/
#endif

#endif // BOOST_MPL_AUX_NA_ASSERT_HPP_INCLUDED

/* na_assert.hpp
5C5i/yTtLGPi4LIwXIoVKFAo8uGluBd3L1Dc3XVw18GhlGLFobj7h+tgg7u7uwxugw4wq9n9s8kmu8lJbs7Nyc19b8798eT8eNuw+7oz+rTliDK/KEsnyckjEe1s1zKaCXo1N5FnV14NBZzsra17NTb1uC/lvsUJmOg/VFJeRYCFbRNKm/wu2r3qO7o6bzCJixezsLAa4R8jIprkJg9mwJ80D1g52KkWxQ3uXoGhCK9B4mPqzUbdKus+lE38PnaHWRLm+KJMCCMeZuinjB4ZR2tTKU9fqzUWp8pLAA5KcFWiSuRj9WOAP0DebqnR2oKojo2Obide6/h1c0Odmq1V6CX++A+lg80YU9+N5tUAmo+v/WW4LGtgrZHPW7zvHt6/7exdAxpa6xnkwxjLmMwJTpfVk6FBAX5laCuM4bH9xF44oIA//Z6NC1uRIYFVGqHLZQt3gzyanNj6evku6aYR8ibJ+MCXmsp6FqdpHqNYVZ9KBkGHuN02mirKqyVP7SF/iXkMEMqcDjewv+nQh9Pk0PGh1h6O7wPM1MpzKDo176LTagD5U2095V9pIWjZtka3GVXn4QchPvq9K3Ajpx8R5ZXfqL4JZnoyznLYQ3UPKBkjPGq2fI31e81JeEbMkur5pkE9N5vsTMdYTa9NU/6RO2Llq2G+iHEgi0FVG642tVxZ0t3o7ixh7iLC9XTFpWPxpw5ioDPlRAuOWz2C
*/