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
sDT7Jc7IwcAEDBJylLqPRr5LnX9reGXAI541sKBp1nvS4TPHuo/aom+0PH2fU3EkbBirBXOMEQA+mr/N9RJNVCbdDZVHVxwP1vdz3Y+sxlJKCQ16LJlgqUGKim7qhgg90DzMXzTcr0qWu3hD/Yw5vSBMWfIUsXZdyVTU5q+aTl/NbbqAp8xhv3QLmvtG9njQ/djm97w/6zLXHuZuDH6TQc7vurs9oIenV9jTHrjwySaBMGJo
*/