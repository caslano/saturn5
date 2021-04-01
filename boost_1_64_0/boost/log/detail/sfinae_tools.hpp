/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   sfinae_tools.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_SFINAE_TOOLS_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_SFINAE_TOOLS_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! A distinct type that can be used as a fake argument type in constructors filtered by SFINAE
struct sfinae_dummy {};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_SFINAE_TOOLS_HPP_INCLUDED_

/* sfinae_tools.hpp
sFJ6yAUihAz7i+p4bREVc+e5h60Cso3nh7qzIVHhjvsaOjVYsceJSyNFg9InLNLZtNvRnD/3rHr69GyTuWnsanLcYqN1AcorZPT55IJpsIdIokMDVI+TuSD9DQAaipTB1LP9X+z98tKp4AEj8wjZBeNbM0uVvi+YYinEKyMQANrHrd9CcA0yVdwgpT2gli0NIaPveicGv204741s1U5Wzlge9QkH6T5aO+J9i1weZEMLTknMgnAuRBMptAZpJ7gU+df6ytsDRENua6AW8wO05XwYSuKfMteqmdNT03PIJRqxKF8rVE9l3mYrg9QZZXkJFbzLZJ6/2HoI4z4EcBGhlRAQEu5RkM2vHvQMvRScwmiW6Rzif9tdPN1aaJWyWhEXutXl5kH85UbBB8nDg8eraTJ9xYPZWWCDXEMSgFKUr3TGwsvYRyj4kZZDtrWRfOqlnoWDFhRS4ySF13vjchOLNvSUf3td2hcIJzZTytvouMcsqBc7tzKAA32i1ZFiJ7cIpACv+ig2RRtlIuhr5ILNy6HALxKABKhc4PCUScoBFqOliW7OBSRcvGUuAQ==
*/