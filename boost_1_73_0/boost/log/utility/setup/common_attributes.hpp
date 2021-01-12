/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   common_attributes.hpp
 * \author Andrey Semashev
 * \date   16.05.2008
 *
 * The header contains implementation of convenience functions for registering commonly used attributes.
 */

#ifndef BOOST_LOG_UTILITY_SETUP_COMMON_ATTRIBUTES_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_SETUP_COMMON_ATTRIBUTES_HPP_INCLUDED_

#include <iostream>
#include <boost/log/detail/config.hpp>
#include <boost/log/core/core.hpp>
#include <boost/log/attributes/clock.hpp>
#include <boost/log/attributes/counter.hpp>
#include <boost/log/attributes/current_process_id.hpp>
#if !defined(BOOST_LOG_NO_THREADS)
#include <boost/log/attributes/current_thread_id.hpp>
#endif
#include <boost/log/detail/default_attribute_names.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief Simple attribute initialization routine
 *
 * The function adds commonly used attributes to the logging system. Specifically, the following
 * attributes are registered globally:
 *
 * \li LineID - logging records counter with value type <tt>unsigned int</tt>
 * \li TimeStamp - local time generator with value type <tt>boost::posix_time::ptime</tt>
 * \li ProcessID - current process identifier with value type
 *     <tt>attributes::current_process_id::value_type</tt>
 * \li ThreadID - in multithreaded builds, current thread identifier with
 *     value type <tt>attributes::current_thread_id::value_type</tt>
 */
inline void add_common_attributes()
{
    shared_ptr< core > pCore = core::get();
    pCore->add_global_attribute(
        aux::default_attribute_names::line_id(),
        attributes::counter< unsigned int >(1));
    pCore->add_global_attribute(
        aux::default_attribute_names::timestamp(),
        attributes::local_clock());
    pCore->add_global_attribute(
        aux::default_attribute_names::process_id(),
        attributes::current_process_id());
#if !defined(BOOST_LOG_NO_THREADS)
    pCore->add_global_attribute(
        aux::default_attribute_names::thread_id(),
        attributes::current_thread_id());
#endif
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_SETUP_COMMON_ATTRIBUTES_HPP_INCLUDED_

/* common_attributes.hpp
HeR77QVUzmzzAe6uy67f2A7sy90JXO8l4Z3hHP4d3RtpJXjyCSkiJ8hJcqqcJqejSTeR30LN+Izdajya73w8kUhaLYFrXbUZ2nJtDezvC+1q/RE9MK4wJsF+GpnDxFS82JpA7d4PypSCM5PtWfZieyUbwCeC9fdyB7qFTOzPQLYnvVHsohcE/NDMWgJL7pX7sOFO/7fKZZka1XJ/petnw5+3aNvg0Lu4D3u1cq72EE5PU/2o
*/