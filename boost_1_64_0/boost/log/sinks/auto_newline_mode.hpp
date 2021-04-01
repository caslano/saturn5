/*
 *             Copyright Andrey Semashev 2019.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   sinks/auto_newline_mode.hpp
 * \author Andrey Semashev
 * \date   23.06.2019
 *
 * The header contains definition of auto-newline modes.
 */

#ifndef BOOST_LOG_SINKS_AUTO_NEWLINE_MODE_HPP_INCLUDED_HPP_
#define BOOST_LOG_SINKS_AUTO_NEWLINE_MODE_HPP_INCLUDED_HPP_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

//! The enum lists automatic trailing newline modes
enum auto_newline_mode
{
    disabled_auto_newline,  //!< Do not insert automatic trailing newline characters
    always_insert,          //!< Always insert automatic trailing newline characters
    insert_if_missing       //!< Insert automatic trailing newline characters, if not present already
};

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_AUTO_NEWLINE_MODE_HPP_INCLUDED_HPP_

/* auto_newline_mode.hpp
wjBVX7KYuAbWak6aIEcZKvJgI93GO+XYjyEd2qsJ+zsJx6623Rs9N/UNNCKijXCPU/CqjkboOZHo6NSQkUDYQWFHXM0frKlK/cM34E2U16cHt6GXHURDgYTY7UsQlXHcSu3E39+tSSxTRATodPhcfwYZSxIqtIACl1YwP8Du0m5QhVNYfwRboA/+saSi0vnnj/W6t+Njg9pR4e9kX1XMXTxHlsOYzn3RneLBPlBtUOyjC4sLtyODG2oPCPaHJTa5EKs0nuz9ZsxXge2X8lDO9CcQ9zKQW94GeNSvCNi3N2DqJ4x7zMbYYFs7YQhfN5W/d2LKWxmaQfoQ4cmBDdNImPs6ImItAqQM/4cwwSb1Ac6CSeGLrQwY1lCugF190qVdmqSznEPY14FapdA9ralB/LPIAdhzICOjgfrkht2zGqAPeYwaYHyAA8Mf9605J+w6nyonWRM7YbrVhA6rP6sZfXY7R42hIIO3W/MRxWRYB+JqBPrfYqRZCw6YDP7k85/CZ67pUVcOq9wokZPy68zi9MenQ5D8OHKroDrVnWWOZkJE6esK9kpAu8Zw4g==
*/