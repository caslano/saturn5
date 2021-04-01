/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/permissions.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * The header contains the \c permissions keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_PERMISSIONS_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_PERMISSIONS_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass interprocess queue permissions to the queue constructor
BOOST_PARAMETER_KEYWORD(tag, permissions)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_PERMISSIONS_HPP_INCLUDED_

/* permissions.hpp
3MaoehLBmkrb0/HU1HqVjzxUrQAMCe7qV9pTbgOzyWV+BZuVVFv2QxZvpJP5oIXXhaRiYxceJfrrApQ5S9GG+5TJLpVN08z19WEzoSw0MzJcPIWZC+iVsOWBkRvABY9Ft+Egiv1K5d1X1Ha76NVLuHGHd36xqdcaElt23CcidEKSWTLl484nkSB1fRnF4P4M4yKSRMGgao1/A85ma0mDLqqe75IWYnIsztLkfUAwmXE4I7umGvSNDw7CZof8lMUNjCWQS9TzEPkQ+6YfgYRQrRtAkBY0UcG11Xwpf94hyTC5dsmGIXG+35Hv9oUe9zPx7HG3ibNH0VtkoWWQrQcYh7GbwZB6oZwxuip8eizTHGPYQAr+AtM+NE/hpgp1dh0US3LqzqjXbk41GYT/f8sk+Sxh++R82S2J/D1If9aPq3O2fdvb3rfkle9ypTR4jeCbhxDC9tvgVO8Q7CUNnQ/ePo/uok3/QuV8SfT6zyKh1mgQKXTueXJSLvymylEFb29p66MtRvBg1BXagP4GsUJXXKFg/LOrBvEfRfzgZMDWvyJyMjT/qIIlO94RuA==
*/