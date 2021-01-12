/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   sinks.hpp
 * \author Andrey Semashev
 * \date   13.07.2009
 *
 * This header includes other Boost.Log headers with all sinks.
 */

#ifndef BOOST_LOG_SINKS_HPP_INCLUDED_
#define BOOST_LOG_SINKS_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#include <boost/log/sinks/sink.hpp>

#include <boost/log/sinks/unlocked_frontend.hpp>
#if !defined(BOOST_LOG_NO_THREADS)
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/async_frontend.hpp>
#include <boost/log/sinks/unbounded_fifo_queue.hpp>
#include <boost/log/sinks/unbounded_ordering_queue.hpp>
#include <boost/log/sinks/bounded_fifo_queue.hpp>
#include <boost/log/sinks/bounded_ordering_queue.hpp>
#include <boost/log/sinks/drop_on_overflow.hpp>
#include <boost/log/sinks/block_on_overflow.hpp>
#endif // !defined(BOOST_LOG_NO_THREADS)

#include <boost/log/sinks/syslog_backend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/text_ipc_message_queue_backend.hpp>
#include <boost/log/sinks/text_multifile_backend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#ifdef BOOST_WINDOWS
#include <boost/log/sinks/debug_output_backend.hpp>
#include <boost/log/sinks/event_log_backend.hpp>
#endif // BOOST_WINDOWS

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_LOG_SINKS_HPP_INCLUDED_

/* sinks.hpp
XngvNg48huf7kbNz0rAPbDY+0wvevFnY64ANDpOw0SEJGxx+DnwLEyxXUiETGyCeB/4K+l/g9cH/J2F//FWM/RsyPgaeDDwCWang/RPPv8OcAJk/QDjfw9OEjRTleD4HGSmzIR/mdTD/AXLuAf0t0E2Qm/dqyIZ5Ieh3wy//5pwFz2r4Wwr+l+F+F2SLcNcJP79FfL8JXh/S8CHYx94Dt4Adfp5COB2Iz7fhtwLu3w9Z74P5
*/