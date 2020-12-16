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
Be+Gv4T74NUyh/8a+A7cCo/Ba/UcBxkjgAlIimuOwy6ZG3ybhPd22Areoe3L93bQwGC/kcy1bgyjYDysD5vAwNzYRLGfJfadc2O/FP+/grHwa1gffgObwX9I+n0LO8pc5q4ylznNBuwLw2A6DIfDYQQcD2vBTBgJ9dyTKuJTR+ITI/GJlfjUFfs5+nsZdsS+rTcuMEdR7HeCsTBJ7HeGzWAXmAC7wo4wGXaF3RxrCsrF/dbKfZm7aljbEwv7i/tnifsDxP2B4l5e4NsLzBD3opFscW+bpP8NMB7+GjaHt8AWcAdsB2+Co+HNcDzcCSeKnsztk+8bco6Fa27fM+LPH2EMpFrV6bld7PUwpOd9Yu9+sbcPNoC/l/LxAEyED8JOcD/sDv8A9ZzDKsL1iLj/qLj/mNhLD7wHyTtgimuO0Z/E3hti700J11sSrrf18yP9fdjQUN7+Ku4cE3c+Enc+1uFHxH6kIfxtxH5bWAu2c9hLr8JeR0vKqdhLctjLEHu1DfbSxF4vGAl7i71En/RDpd+bYlPVD9KJt2ROP2wEx8OmcAJMgRNhGrwA9oKZ8CyYBYfCbDgSToYz4RSpJ6fCpWKvCE6Hq+BMuB7Ogr+A58Bb4FqpP9fBe8TevTAf3gdnS706B5bCufApWABfhPPgK3A+PAIXwNdhEfwaFsN6RHQlbAVXw0R4gU5f6XNKH9edvl0lfZMlnVKca3nF3hD7vmvOYF9J335Sj58F68EB4s5g2BIOhclwmKT3cNgfjpT0HgHPluvt4VaVc8aYL6bmluW9EmVtQtL5u+945g4hxYhpHlk5tOeSxU0wzyfLqWJO2UmZVxY7kTlOE6s3v2wff5chERnMc0KGIZu5vwBuhauhe97Zbpl7dggOgOXQOQet6STveWirXXPR7oSPI+45aVGZ/nlpSTAdqWp+2mrubUOGDcYMBuaqvZdpnq9WJHPW9iBHHHPXTmZVPX+taTZu2fdgBhKYy7YgW89nY+EF95DAvLY92cFz2xInVz2/rcwxx63RlIp5bjPhemQ74pzzdqQa895yHHPfcjBbjWxD9iFec+E+mloxH649Mk7mxV3mmhu3PadiftwB/n4Pcc6Ts6YRXpgERyF5MmduPdyGlPH3Lp6VA8hHSNNXCSuyAClB9iFHkIgjUVYyko2sQ3YijyMfIbGvYYZkv/bjzEmr+dX8an41v5pfza/mV/Or+f1wvx9n/n/BGv/s/+83/9+et9/IMW9/nK/yvK3Xetov7c4xkDn5S2Sw3DU33jxPeHL1xmec872d456JYbK3j1iaLWFLCQ7bAmzayeM5b7+X0p9m9cbtwebxONwMbX/lUOJgj4esUO7xzcs1x9ySdRL1xJG6yAR0dgfFSU70XZQ/f4UV2nnc2Hedx61sm+cvVjN/PM/VFj+cZ09slUGlvT7iDffAB+yxwOD4Me/FGS85g1XGTl9Runf4SnzGvMIt9zoNOa9V9hF9R5lf7DPEXduVM7v5yZiWjOONnII5NvpTDurKuNlNPBRvIbVb4wayP6HinM27SMGd6DTmPmOw1TpLmri7z5+lHAWfP3tSytGDsnah/pTg63K53i/X06fq6+DzbWrpb04qX/ogo9Gxchz5ok5CJSyO50jm1em8iVT63dn3KML87OcYx7X1OGmcMu9ktXWcFxBP2jVB1oYwXh3vet4kfEFx3SmTGW6Qcd1tyEzCkuGMqyzgqKPL4HJdBiYrvWsI3xD8Enu4lmitdcaV++5zXgutemKnSJldYHUkjqoMNvKXpVziWLexKk+qHB2KP+V52zJO7ywzy+Van2+v8n5TTnDZ2KWvg+ugdTIJY6Z4MAPJ6E59Oy14LsaSguU=
*/