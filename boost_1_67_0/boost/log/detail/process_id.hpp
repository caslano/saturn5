/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   process_id.hpp
 * \author Andrey Semashev
 * \date   12.09.2009
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_PROCESS_ID_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_PROCESS_ID_HPP_INCLUDED_

#include <iosfwd>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/id.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! The process id descriptor
struct process
{
    typedef unsigned long native_type;
    typedef boost::log::aux::id< process > id;
};

namespace this_process {

//! The function returns current process identifier
BOOST_LOG_API process::id get_id();

} // namespace this_process

template< typename CharT, typename TraitsT >
BOOST_LOG_API std::basic_ostream< CharT, TraitsT >&
operator<< (std::basic_ostream< CharT, TraitsT >& strm, process::id const& pid);

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_PROCESS_ID_HPP_INCLUDED_

/* process_id.hpp
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
*/