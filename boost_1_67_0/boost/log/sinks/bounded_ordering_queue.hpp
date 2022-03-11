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