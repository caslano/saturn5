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