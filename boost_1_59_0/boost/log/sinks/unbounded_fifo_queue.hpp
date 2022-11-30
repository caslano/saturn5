/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   unbounded_fifo_queue.hpp
 * \author Andrey Semashev
 * \date   24.07.2011
 *
 * The header contains implementation of unbounded FIFO queueing strategy for
 * the asynchronous sink frontend.
 */

#ifndef BOOST_LOG_SINKS_UNBOUNDED_FIFO_QUEUE_HPP_INCLUDED_
#define BOOST_LOG_SINKS_UNBOUNDED_FIFO_QUEUE_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_LOG_NO_THREADS)
#error Boost.Log: This header content is only supported in multithreaded environment
#endif

#include <boost/memory_order.hpp>
#include <boost/atomic/atomic.hpp>
#include <boost/log/detail/event.hpp>
#include <boost/log/detail/threadsafe_queue.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

/*!
 * \brief Unbounded FIFO log record queueing strategy
 *
 * The \c unbounded_fifo_queue class is intended to be used with
 * the \c asynchronous_sink frontend as a log record queueing strategy.
 *
 * This strategy implements the simplest logic of log record buffering between
 * threads: the queue has no limits and imposes no ordering over the queued
 * elements aside from the order in which they are enqueued.
 * Because of this the queue provides decent performance and scalability,
 * however if sink backends can't consume log records fast enough the queue
 * may grow uncontrollably. When this is an issue, it is recommended to
 * use one of the bounded strategies.
 */
class unbounded_fifo_queue
{
private:
    typedef boost::log::aux::threadsafe_queue< record_view > queue_type;

private:
    //! Thread-safe queue
    queue_type m_queue;
    //! Event object to block on
    boost::log::aux::event m_event;
    //! Interruption flag
    boost::atomic< bool > m_interruption_requested;

protected:
    //! Default constructor
    unbounded_fifo_queue() : m_interruption_requested(false)
    {
    }
    //! Initializing constructor
    template< typename ArgsT >
    explicit unbounded_fifo_queue(ArgsT const&) : m_interruption_requested(false)
    {
    }

    //! Enqueues log record to the queue
    void enqueue(record_view const& rec)
    {
        m_queue.push(rec);
        m_event.set_signalled();
    }

    //! Attempts to enqueue log record to the queue
    bool try_enqueue(record_view const& rec)
    {
        // Assume the call never blocks
        enqueue(rec);
        return true;
    }

    //! Attempts to dequeue a log record ready for processing from the queue, does not block if the queue is empty
    bool try_dequeue_ready(record_view& rec)
    {
        return m_queue.try_pop(rec);
    }

    //! Attempts to dequeue log record from the queue, does not block if the queue is empty
    bool try_dequeue(record_view& rec)
    {
        return m_queue.try_pop(rec);
    }

    //! Dequeues log record from the queue, blocks if the queue is empty
    bool dequeue_ready(record_view& rec)
    {
        // Try the fast way first
        if (m_queue.try_pop(rec))
            return true;

        // Ok, we probably have to wait for new records
        while (true)
        {
            m_event.wait();
            if (m_interruption_requested.exchange(false, boost::memory_order_acquire))
                return false;
            if (m_queue.try_pop(rec))
                return true;
        }
    }

    //! Wakes a thread possibly blocked in the \c dequeue method
    void interrupt_dequeue()
    {
        m_interruption_requested.store(true, boost::memory_order_release);
        m_event.set_signalled();
    }
};

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_UNBOUNDED_FIFO_QUEUE_HPP_INCLUDED_

/* unbounded_fifo_queue.hpp
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
*/