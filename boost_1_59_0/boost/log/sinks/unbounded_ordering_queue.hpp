/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   unbounded_ordering_queue.hpp
 * \author Andrey Semashev
 * \date   24.07.2011
 *
 * The header contains implementation of unbounded ordering record queueing strategy for
 * the asynchronous sink frontend.
 */

#ifndef BOOST_LOG_SINKS_UNBOUNDED_ORDERING_QUEUE_HPP_INCLUDED_
#define BOOST_LOG_SINKS_UNBOUNDED_ORDERING_QUEUE_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_LOG_NO_THREADS)
#error Boost.Log: This header content is only supported in multithreaded environment
#endif

#include <queue>
#include <vector>
#include <boost/cstdint.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/thread_time.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/detail/timestamp.hpp>
#include <boost/log/detail/enqueued_record.hpp>
#include <boost/log/keywords/order.hpp>
#include <boost/log/keywords/ordering_window.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

/*!
 * \brief Unbounded ordering log record queueing strategy
 *
 * The \c unbounded_ordering_queue class is intended to be used with
 * the \c asynchronous_sink frontend as a log record queueing strategy.
 *
 * This strategy provides the following properties to the record queueing mechanism:
 *
 * \li The queue has no size limits.
 * \li The queue has a fixed latency window. This means that each log record put
 *     into the queue will normally not be dequeued for a certain period of time.
 * \li The queue performs stable record ordering within the latency window.
 *     The ordering predicate can be specified in the \c OrderT template parameter.
 *
 * Since this queue has no size limits, it may grow uncontrollably if sink backends
 * dequeue log records not fast enough. When this is an issue, it is recommended to
 * use one of the bounded strategies.
 */
template< typename OrderT >
class unbounded_ordering_queue
{
private:
    typedef boost::mutex mutex_type;
    typedef sinks::aux::enqueued_record enqueued_record;

    typedef std::priority_queue<
        enqueued_record,
        std::vector< enqueued_record >,
        enqueued_record::order< OrderT >
    > queue_type;

private:
    //! Ordering window duration, in milliseconds
    const uint64_t m_ordering_window;
    //! Synchronization mutex
    mutex_type m_mutex;
    //! Condition for blocking
    condition_variable m_cond;
    //! Thread-safe queue
    queue_type m_queue;
    //! Interruption flag
    bool m_interruption_requested;

public:
    /*!
     * Returns ordering window size specified during initialization
     */
    posix_time::time_duration get_ordering_window() const
    {
        return posix_time::milliseconds(m_ordering_window);
    }

    /*!
     * Returns default ordering window size.
     * The default window size is specific to the operating system thread scheduling mechanism.
     */
    static posix_time::time_duration get_default_ordering_window()
    {
        // The main idea behind this parameter is that the ordering window should be large enough
        // to allow the frontend to order records from different threads on an attribute
        // that contains system time. Thus this value should be:
        // * No less than the minimum time resolution quant that Boost.DateTime provides on the current OS.
        //   For instance, on Windows it defaults to around 15-16 ms.
        // * No less than thread switching quant on the current OS. For now 30 ms is large enough window size to
        //   switch threads on any known OS. It can be tuned for other platforms as needed.
        return posix_time::milliseconds(30);
    }

protected:
    //! Initializing constructor
    template< typename ArgsT >
    explicit unbounded_ordering_queue(ArgsT const& args) :
        m_ordering_window(args[keywords::ordering_window || &unbounded_ordering_queue::get_default_ordering_window].total_milliseconds()),
        m_queue(args[keywords::order]),
        m_interruption_requested(false)
    {
    }

    //! Enqueues log record to the queue
    void enqueue(record_view const& rec)
    {
        lock_guard< mutex_type > lock(m_mutex);
        enqueue_unlocked(rec);
    }

    //! Attempts to enqueue log record to the queue
    bool try_enqueue(record_view const& rec)
    {
        unique_lock< mutex_type > lock(m_mutex, try_to_lock);
        if (lock.owns_lock())
        {
            enqueue_unlocked(rec);
            return true;
        }
        else
            return false;
    }

    //! Attempts to dequeue a log record ready for processing from the queue, does not block if no log records are ready to be processed
    bool try_dequeue_ready(record_view& rec)
    {
        lock_guard< mutex_type > lock(m_mutex);
        if (!m_queue.empty())
        {
            const boost::log::aux::timestamp now = boost::log::aux::get_timestamp();
            enqueued_record const& elem = m_queue.top();
            if (static_cast< uint64_t >((now - elem.m_timestamp).milliseconds()) >= m_ordering_window)
            {
                // We got a new element
                rec = elem.m_record;
                m_queue.pop();
                return true;
            }
        }

        return false;
    }

    //! Attempts to dequeue log record from the queue, does not block.
    bool try_dequeue(record_view& rec)
    {
        lock_guard< mutex_type > lock(m_mutex);
        if (!m_queue.empty())
        {
            enqueued_record const& elem = m_queue.top();
            rec = elem.m_record;
            m_queue.pop();
            return true;
        }

        return false;
    }

    //! Dequeues log record from the queue, blocks if no log records are ready to be processed
    bool dequeue_ready(record_view& rec)
    {
        unique_lock< mutex_type > lock(m_mutex);
        while (!m_interruption_requested)
        {
            if (!m_queue.empty())
            {
                const boost::log::aux::timestamp now = boost::log::aux::get_timestamp();
                enqueued_record const& elem = m_queue.top();
                const uint64_t difference = (now - elem.m_timestamp).milliseconds();
                if (difference >= m_ordering_window)
                {
                    // We got a new element
                    rec = elem.m_record;
                    m_queue.pop();
                    return true;
                }
                else
                {
                    // Wait until the element becomes ready to be processed
                    m_cond.timed_wait(lock, posix_time::milliseconds(m_ordering_window - difference));
                }
            }
            else
            {
                // Wait for an element to come
                m_cond.wait(lock);
            }
        }
        m_interruption_requested = false;

        return false;
    }

    //! Wakes a thread possibly blocked in the \c dequeue method
    void interrupt_dequeue()
    {
        lock_guard< mutex_type > lock(m_mutex);
        m_interruption_requested = true;
        m_cond.notify_one();
    }

private:
    //! Enqueues a log record
    void enqueue_unlocked(record_view const& rec)
    {
        const bool was_empty = m_queue.empty();
        m_queue.push(enqueued_record(rec));
        if (was_empty)
            m_cond.notify_one();
    }
};

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_UNBOUNDED_ORDERING_QUEUE_HPP_INCLUDED_

/* unbounded_ordering_queue.hpp
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
*/