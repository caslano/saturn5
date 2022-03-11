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