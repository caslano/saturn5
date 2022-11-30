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
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
*/