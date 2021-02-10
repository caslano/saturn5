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
LjpgrdIoBM8XIANrPLfsZKo4XERj0RbtOg8tys8aUW5W0d1dVFKK2wMRWff9gUPxq+vBTe/s/PveS+SuPRGHRsuG/lTFXWP5vfB/lSVvSCFyrknpX5glbwAhtzTULSrHXTV4vRNR6YWTs3ALouWW1puL6iYhYVQa2sdqM0dBzc33UtrvONlwFv6aQUR6/DXysNWqPYzTxoc4Q+RuEDSsWIcDfrpEhGc5YiY4QPCxXyix9K91M8TkXvW5uJOuRqhOi9RiF6Yd106uHFXOil0he4haLDzsX91MdTvvim0mdtcEjSoBvZxQBYnjUjKo4FqrAsI9zDYoIS2VuaPEgWd4DrMGTubIwMULjYLjZ/nRz3uOf+Um9q7AaEoZCH8FxnpShk59KPrVxqhGEYh9DXBVOKP8kbgPuERTGd3lhZzE7zst5OZz8CKum8IwJccs8MtT4dD5FGlsrYk2Q5hryopET599t/GGEpbcFPCg9ztZxJMHiFMgF6jMWU46807dy1xGMfhuBwzgf4wxfgkJHdhcsgOi9fnR8Vc///eB+OWAv512xdv0F1iM1ZGuoxLBBsb7MknkbZgkFEDMwgrf/qDyYVrtEXIUU9RiiaaDJ/6RE/xYH4xEiHkiH3j5kFbh+yd23R8csqXZvSrQjORD
*/