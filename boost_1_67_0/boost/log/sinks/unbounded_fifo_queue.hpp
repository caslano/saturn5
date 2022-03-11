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