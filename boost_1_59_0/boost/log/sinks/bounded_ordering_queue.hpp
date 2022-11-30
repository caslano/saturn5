/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   bounded_ordering_queue.hpp
 * \author Andrey Semashev
 * \date   06.01.2012
 *
 * The header contains implementation of bounded ordering queueing strategy for
 * the asynchronous sink frontend.
 */

#ifndef BOOST_LOG_SINKS_BOUNDED_ORDERING_QUEUE_HPP_INCLUDED_
#define BOOST_LOG_SINKS_BOUNDED_ORDERING_QUEUE_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_LOG_NO_THREADS)
#error Boost.Log: This header content is only supported in multithreaded environment
#endif

#include <cstddef>
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
 * \brief Bounded ordering log record queueing strategy
 *
 * The \c bounded_ordering_queue class is intended to be used with
 * the \c asynchronous_sink frontend as a log record queueing strategy.
 *
 * This strategy provides the following properties to the record queueing mechanism:
 *
 * \li The queue has limited capacity specified by the \c MaxQueueSizeV template parameter.
 * \li Upon reaching the size limit, the queue invokes the overflow handling strategy
 *     specified in the \c OverflowStrategyT template parameter to handle the situation.
 *     The library provides overflow handling strategies for most common cases:
 *     \c drop_on_overflow will silently discard the log record, and \c block_on_overflow
 *     will put the enqueueing thread to wait until there is space in the queue.
 * \li The queue has a fixed latency window. This means that each log record put
 *     into the queue will normally not be dequeued for a certain period of time.
 * \li The queue performs stable record ordering within the latency window.
 *     The ordering predicate can be specified in the \c OrderT template parameter.
 */
template< typename OrderT, std::size_t MaxQueueSizeV, typename OverflowStrategyT >
class bounded_ordering_queue :
    private OverflowStrategyT
{
private:
    typedef OverflowStrategyT overflow_strategy;
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
    //! Synchronization primitive
    mutex_type m_mutex;
    //! Condition to block the consuming thread on
    condition_variable m_cond;
    //! Log record queue
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
    explicit bounded_ordering_queue(ArgsT const& args) :
        m_ordering_window(args[keywords::ordering_window || &bounded_ordering_queue::get_default_ordering_window].total_milliseconds()),
        m_queue(args[keywords::order]),
        m_interruption_requested(false)
    {
    }

    //! Enqueues log record to the queue
    void enqueue(record_view const& rec)
    {
        unique_lock< mutex_type > lock(m_mutex);
        std::size_t size = m_queue.size();
        for (; size >= MaxQueueSizeV; size = m_queue.size())
        {
            if (!overflow_strategy::on_overflow(rec, lock))
                return;
        }

        m_queue.push(enqueued_record(rec));
        if (size == 0)
            m_cond.notify_one();
    }

    //! Attempts to enqueue log record to the queue
    bool try_enqueue(record_view const& rec)
    {
        unique_lock< mutex_type > lock(m_mutex, try_to_lock);
        if (lock.owns_lock())
        {
            const std::size_t size = m_queue.size();

            // Do not invoke the bounding strategy in case of overflow as it may block
            if (size < MaxQueueSizeV)
            {
                m_queue.push(enqueued_record(rec));
                if (size == 0)
                    m_cond.notify_one();
                return true;
            }
        }

        return false;
    }

    //! Attempts to dequeue a log record ready for processing from the queue, does not block if the queue is empty
    bool try_dequeue_ready(record_view& rec)
    {
        lock_guard< mutex_type > lock(m_mutex);
        const std::size_t size = m_queue.size();
        if (size > 0)
        {
            const boost::log::aux::timestamp now = boost::log::aux::get_timestamp();
            enqueued_record const& elem = m_queue.top();
            if (static_cast< uint64_t >((now - elem.m_timestamp).milliseconds()) >= m_ordering_window)
            {
                // We got a new element
                rec = elem.m_record;
                m_queue.pop();
                overflow_strategy::on_queue_space_available();
                return true;
            }
        }

        return false;
    }

    //! Attempts to dequeue log record from the queue, does not block if the queue is empty
    bool try_dequeue(record_view& rec)
    {
        lock_guard< mutex_type > lock(m_mutex);
        const std::size_t size = m_queue.size();
        if (size > 0)
        {
            enqueued_record const& elem = m_queue.top();
            rec = elem.m_record;
            m_queue.pop();
            overflow_strategy::on_queue_space_available();
            return true;
        }

        return false;
    }

    //! Dequeues log record from the queue, blocks if the queue is empty
    bool dequeue_ready(record_view& rec)
    {
        unique_lock< mutex_type > lock(m_mutex);

        while (!m_interruption_requested)
        {
            const std::size_t size = m_queue.size();
            if (size > 0)
            {
                const boost::log::aux::timestamp now = boost::log::aux::get_timestamp();
                enqueued_record const& elem = m_queue.top();
                const uint64_t difference = (now - elem.m_timestamp).milliseconds();
                if (difference >= m_ordering_window)
                {
                    rec = elem.m_record;
                    m_queue.pop();
                    overflow_strategy::on_queue_space_available();
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
        overflow_strategy::interrupt();
        m_cond.notify_one();
    }
};

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_BOUNDED_ORDERING_QUEUE_HPP_INCLUDED_

/* bounded_ordering_queue.hpp
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
*/