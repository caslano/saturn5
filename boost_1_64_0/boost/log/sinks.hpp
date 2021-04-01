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
4NUdP0+96zEq3uLTSuuU/lrwM+4RGuooB3AeuzFhMFi/ec9X2CsohCI5tFbg1zldH832PgnvYEJLe3a9oqLNfg285pLAZhtDmFlerZvDK9+MJiyZ23xkPZkqUa8N5KrbXZhDYb5XDoLDl8Uxa3u+tNTRA/Sfck+IUvtl68MNe9RI9YIV2P13emFaD9gGFwjavWqFy1P1LvDoi6rfclW7YJIdezLpJwzHM/Tp/Bw3iLw9s23Et8gFog1d/KAQcNQqmc+Imnotj5ktCPh2HvfAceYIlWfF5Rjcg0qmQMGrB8mGNXxZs5uoMdUSGpsX3cmUZX+WW9zm4P80zAdxj9NXrsFbvk6whLIsDaPhuq/WJi38bNZwUxObzZjks0h8YbEp9tdon3hT6vXVkI8zaT4PjzABT3FYFNvHpBj0VSDMNkDe4NTquI7q5nlq3jdvDxRqTlpLU/mttYTviipFPl+hIJ/9HEqMRjioG9BbQBbppt5wyorS0BQrFM5rcOjOwqhHc6Khz7HbD44yDbXopV9iWcOTkrq+rOt+ZtkxytdLXzBetQ38d6pvkPQ44A==
*/