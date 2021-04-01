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
4f1BZoNv85YdeeAIp3RxUb4a6F7nxcrEdFHn4m6grCcnEFFLdlrfyjYkREbTy2NYbPwso54VMsup9GAOcLpPs1kLSwvU+ZJYeK+ETyUhSYIP3peAF8jrPh5nuEvAtsRDn6+N4+/cwjBEIRb7Lb3ve/zaiGq3YZC+fVJTO6/CTWz/hR9SxCkvHReh6EkarH+SLevkP0tNQPnBpY4OysmnosheVH2/Qkrng05fHfHBCOC5OqX9TNORIm6saENVsGGpE++2wrqTPDG6XJhDmQUcr5mgogYkcMM57sFF0/znrV+Oc5Ex/PLhmKQ4Gbie99hLxbTxFh9bcerFyGm6ZF/nb21MD4z3pYOyHNuweFL7ztFBHtszJCzlGfb7XvLNzvL+2jvvRxYU6lZ2JDRoBkGBs1n6gZFYjNU0Wer9jaw5veBU2gy6DwTT9+0Yz9LY8rzyWwvqcePsGqQLMOCfqQ9bjyFUlME46aJVZDCvz1cH22zZG6P7Y3AGSiNLjFCDC86mCOIu701gsogNBm7XUpk8qgn0BCoCetW5fVcSTpS04RpDhPf9qWfI1+8dJQ==
*/