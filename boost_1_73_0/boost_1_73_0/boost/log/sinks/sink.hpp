/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   sink.hpp
 * \author Andrey Semashev
 * \date   22.04.2007
 *
 * The header contains an interface declaration for all sinks. This interface is used by the
 * logging core to feed log records to sinks.
 */

#ifndef BOOST_LOG_SINKS_SINK_HPP_INCLUDED_
#define BOOST_LOG_SINKS_SINK_HPP_INCLUDED_

#include <string>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/light_function.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

//! A base class for a logging sink frontend
class BOOST_LOG_NO_VTABLE sink
{
public:
    //! An exception handler type
    typedef boost::log::aux::light_function< void () > exception_handler_type;

private:
    //! The flag indicates that the sink passes log records across thread boundaries
    const bool m_cross_thread;

public:
    /*!
     * Default constructor
     */
    explicit sink(bool cross_thread) : m_cross_thread(cross_thread)
    {
    }

    /*!
     * Virtual destructor
     */
    virtual ~sink() {}

    /*!
     * The method returns \c true if no filter is set or the attribute values pass the filter
     *
     * \param attributes A set of attribute values of a logging record
     */
    virtual bool will_consume(attribute_value_set const& attributes) = 0;

    /*!
     * The method puts logging record to the sink
     *
     * \param rec Logging record to consume
     */
    virtual void consume(record_view const& rec) = 0;

    /*!
     * The method attempts to put logging record to the sink. The method may be used by the
     * core in order to determine the most efficient order of sinks to feed records to in
     * case of heavy contention. Sink implementations may implement try/backoff logic in
     * order to improve overall logging throughput.
     *
     * \param rec Logging record to consume
     * \return \c true, if the record was consumed, \c false, if not.
     */
    virtual bool try_consume(record_view const& rec)
    {
        consume(rec);
        return true;
    }

    /*!
     * The method performs flushing of any internal buffers that may hold log records. The method
     * may take considerable time to complete and may block both the calling thread and threads
     * attempting to put new records into the sink while this call is in progress.
     */
    virtual void flush() = 0;

    /*!
     * The method indicates that the sink passes log records between different threads. This information is
     * needed by the logging core to detach log records from all thread-specific resources before passing it
     * to the sink.
     */
    bool is_cross_thread() const BOOST_NOEXCEPT { return m_cross_thread; }

    BOOST_DELETED_FUNCTION(sink(sink const&))
    BOOST_DELETED_FUNCTION(sink& operator= (sink const&))
};

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_SINK_HPP_INCLUDED_

/* sink.hpp
DpdIlVeJUlPgDIaD9RCYAjCSmEj/fbsBzEGJth42tMUD6Pv6esaDf+7VgQE8+4rcX4Qv/HQcn7T6L4/tduoougf/D7mu8fM5JWNoWO6jPjzPcg89xxIFLe/oexQ9p+iabKO3MXFeR/QVT5CNOA9UsdZimVnoHfTh9Y8//hv2YP/V/qshHDIpeA4zy+WC6+UQ3iXu5OeM3d2NDP8wBG6B5aMgap4JA0al9pZpDvg9FzGXhifADCTcxFos8IeQYDMOqcg5HJx/upqe/TKE20zEGQlZqxJMpso8gYzdcNA85uLGyyiYtqBSZEfhiTAWBZZWKDlC3Rws1ytDMkg9y40CdsNEzhaoiFnIrC3Mm/E4LnWO1o8TFZtxXLk/yuyq9uQKjVixNajCglVQGj4EohzCSiUipU8MCB4W5SIXJhs21qAqmYyVBsPznGQhn+DGm81hFsIzJDIo0GJh6cMoaUjVbaZWG4QYR5KSllqiIowDEiUKwzyEUiZcO2LneaUixNQF+KupaexNQEk0BrqTGUxnXVgwI8wQPk/nv55fzuHz5OJicja/gvNjmJxdkbDfpmeHmHqByjTwu0Jzg8o1iFWRC54Enf/ca9z5Tsg4LxMOXatUHhluy2KUdTutC3QnZob704SnQnI4Opt8PDmK
*/