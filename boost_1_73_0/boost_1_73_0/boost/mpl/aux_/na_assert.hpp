
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
lcTevRURbKGI4PEporWdIoI1RVxHerMiHlT/36eI9taKCNYUkad3CeK2XcAN77k4PmwP3WuBDFd08wz5+dM82PySx5QntNs+1f3xl93tnvKi/ZRz/1EN/Xh2iPmuQKPFBcRzeFPkejpzL8HrAW2FJv19K1NqQuaLYZQiU1P6/b1vPRsMTo8tLmcTJchi9SBSQhT7VpHHesGQqOSMnpsvLYhKNkazMdULipD53+bio7aEl4acV2RpG1OgZAjxhb5EuUR9P8IR6LgH4rKETBCR2m5XF53o0TcRAsbsHOsSaHJpxDNDS4ITpJdSWW/++Hzy5d3R8P2nwfDjwYejvr7a0LOZKDoVmmdamWlODr+cfj46+XRwSCcJfk7B0vrUxSDBeDqCeJoXibWy6r84PTu0qQQ6vr1HHyo90vPrZPcqofEtcEHExXhMSjH17tn2C53W8Wnvha7T6afPQ9tzvDYkRrjmjYq6dIsmEufk8ux8EQaWmCJ7ZUBuc5YJ6p8o83RWX/UAS5W5xzFV00emGLGERpUJ1bCii9q2DiaU4JpPKiDUqTn0AxwWPUFtT0F7cA3FjnXAOU7o0Wv7tZbt/f3XJbPsZKJJasCmmfWIevmuc8YuTGXebyxD1+bmUqnfSNtp0nIQU5amoeeF3bYb
*/