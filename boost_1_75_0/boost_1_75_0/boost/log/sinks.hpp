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
nmN4jBkQjtReg9URbtXZePr5AJbhHjqC+N9v/fTosoymkxLiZWz6EyUaEwM3GalCDq/XbSbFRxCLJIE/NjEcg4lne/RnHMLipzdHLfISD5WrEVbTZWpWxlKcREs/7xuNHQerxmw77XxeUMFx/pxtTw830hbgq+mx72WOAcmcI7ljqiDHv0/74y050qS969Af6lT7oJ/tKD5g9KaiidPv2EDDQtI1rhMwfJUQ0B13s+uAmb+PXC+5nztdg1ZwOT4SRf5J45Cx8NB6eO6XK0P6hDezvz8utyTv1FHZvrEihzCeNxeNqiAJ97lRij4OVXVBE5MEepE+y5btvpNpjF5B6lTJHf7m8z3CmjQRdUy5XBZDpUyHTXuot4XVkweK0y2j/883ZZCZ0RZCgg9zqLeaBaXdPb8sKM3ITbeneZkAFN1Ou7YlvUDgNei4Zz2ixHVR9UeNagYDvP1Dvhtp0WdV0fILn0GUk9/1mR9PCnW+5b+YWRZzM3jc2se17i19LEu5MDpJtygN5BA1dkPEHIxZ2JqwlaVhtbrLnxXUCdHT6t8YI3Dsw0iBpaNeGRUohWZCLJGOkr6nciE73rWy5MUNhrHZ+EbckExZWupxsFqMevEjvx6gUiWyQnfvfGkMe9nCMn9n+zDboc3btWIQNnHEcM0nn9ETadw8vLMxt/jBoFbdgLhwgJ6nn3/PhN+JPmNLeftrm9vh9Th6NYvu
*/