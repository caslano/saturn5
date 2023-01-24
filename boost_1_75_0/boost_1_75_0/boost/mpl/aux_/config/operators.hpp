
#ifndef BOOST_MPL_AUX_CONFIG_OPERATORS_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_OPERATORS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if !defined(BOOST_MPL_CFG_USE_OPERATORS_OVERLOADING) \
    && ( BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
        || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        || BOOST_WORKAROUND(__EDG_VERSION__, <= 245) \
        || BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, <= 0x0295) \
        || BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(600)) \
        || BOOST_WORKAROUND(__NVCC__, BOOST_TESTED_AT(1)) \
        )

#   define BOOST_MPL_CFG_USE_OPERATORS_OVERLOADING

#endif

#endif // BOOST_MPL_AUX_CONFIG_OPERATORS_HPP_INCLUDED

/* operators.hpp
ztc8lI2ooPkt0NCG1ool91MX5nW9cb62cnw3NNTOt7a25fzsl6psYGCDWD4rgxo+Pr6lxWFZCbeO9jICLKNIXVy6cfp0zVHpUklpyMBKWWnOesvCFqr0n+kRVmAheUpLn/v6ws5hMlKYsOAt3/gayZd0V87r6qxsLC5urK9bf767v1vEx3u4f8gl+dThshum52xTWTmtsMezskjfZElDmahOXYmBVNW3HwnVIjZL/mtAuT9368KJ7M+ON/UlVqqQjRXOWaeUur+zi1uwil9wQlPH2tbp4nJxHRgLTYtN8Nq+u1u5aVjvHegPFC9y1KiQH/wNBalSd06P8Vd0RCFWgSoDjjYSzD4wRFWVDifFrf33dwRvAPrf8SiFSWKEh5+Oj6efm2WYR3HByDivpY0G8pAUHubEm8hfEvjacHef8aJYejtw9BLTtdTe7ltRcbC2BlczbDFvyViE084gLWHaIKZLi6EZArh95g7o/jEzEfdXxdiMu/frny3RSdEOF8k2IMDKwUHGo5maUZ3YVQKHlBUBdZdMOCvoCYOXL6MpOHg8V7jzF5v9YBhkUYNJHcCu5fDhYXtZ29y9qbZAfAWhoJ0KUMLdEjj7Gcb303TOVBUzHg5dsVbOFx3SqWlRPfrDlGtY3ABjmjydAYU6paPSsx107KB/RQKcRXnPh4ffi5h9VVeLJXMz10ZW9gsRUQ2qXZP8koaWpSoj8Ed0
*/