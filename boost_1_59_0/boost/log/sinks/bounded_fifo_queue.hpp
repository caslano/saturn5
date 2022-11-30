/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   bounded_fifo_queue.hpp
 * \author Andrey Semashev
 * \date   04.01.2012
 *
 * The header contains implementation of bounded FIFO queueing strategy for
 * the asynchronous sink frontend.
 */

#ifndef BOOST_LOG_SINKS_BOUNDED_FIFO_QUEUE_HPP_INCLUDED_
#define BOOST_LOG_SINKS_BOUNDED_FIFO_QUEUE_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_LOG_NO_THREADS)
#error Boost.Log: This header content is only supported in multithreaded environment
#endif

#include <cstddef>
#include <queue>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

/*!
 * \brief Bounded FIFO log record queueing strategy
 *
 * The \c bounded_fifo_queue class is intended to be used with
 * the \c asynchronous_sink frontend as a log record queueing strategy.
 *
 * This strategy describes log record queueing logic.
 * The queue has a limited capacity, upon reaching which the enqueue operation will
 * invoke the overflow handling strategy specified in the \c OverflowStrategyT
 * template parameter to handle the situation. The library provides overflow handling
 * strategies for most common cases: \c drop_on_overflow will silently discard the log record,
 * and \c block_on_overflow will put the enqueueing thread to wait until there is space
 * in the queue.
 *
 * The log record queue imposes no ordering over the queued
 * elements aside from the order in which they are enqueued.
 */
template< std::size_t MaxQueueSizeV, typename OverflowStrategyT >
class bounded_fifo_queue :
    private OverflowStrategyT
{
private:
    typedef OverflowStrategyT overflow_strategy;
    typedef std::queue< record_view > queue_type;
    typedef boost::mutex mutex_type;

private:
    //! Synchronization primitive
    mutex_type m_mutex;
    //! Condition to block the consuming thread on
    condition_variable m_cond;
    //! Log record queue
    queue_type m_queue;
    //! Interruption flag
    bool m_interruption_requested;

protected:
    //! Default constructor
    bounded_fifo_queue() : m_interruption_requested(false)
    {
    }
    //! Initializing constructor
    template< typename ArgsT >
    explicit bounded_fifo_queue(ArgsT const&) : m_interruption_requested(false)
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

        m_queue.push(rec);
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
                m_queue.push(rec);
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
        return try_dequeue(rec);
    }

    //! Attempts to dequeue log record from the queue, does not block if the queue is empty
    bool try_dequeue(record_view& rec)
    {
        lock_guard< mutex_type > lock(m_mutex);
        const std::size_t size = m_queue.size();
        if (size > 0)
        {
            rec.swap(m_queue.front());
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
                rec.swap(m_queue.front());
                m_queue.pop();
                overflow_strategy::on_queue_space_available();
                return true;
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

#endif // BOOST_LOG_SINKS_BOUNDED_FIFO_QUEUE_HPP_INCLUDED_

/* bounded_fifo_queue.hpp
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
*/