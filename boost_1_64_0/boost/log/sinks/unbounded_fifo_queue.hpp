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
26ho/G24yF8PVMLQggp/PfyxvZSnkTG7U9w96Yzh31LUTpStTggvWC7YyFBvFLs1ThI+F1ETK/Gh5+DU39PObU4nE56am7qKrGsbpSTSyPT9UexXOz1oXbOcCKvMhUmThuGIDLbK44tdqePlv46kZ4LKYmmdFhOXuQPgMXG7B5etkDTlPRV1GX56UG+tfPHE1am9qHtQ+1C+uvT2DF12gXKXutO6dMtQki89Oy9l4JZLOHX76M39/kBz99GninzDC7tnvf7UpVs/vmHsmWO3xt2Z2rhchV1eoTF5iObLJTRXPuNUfU/ALq/QfHmOUymXsMM/Nup4vUfb6RZtqO1o3mGwI+wAE2EaTILpMBn2g53hUNgNjoApcBTsDmfBHroP3hPOh+lwGcyAZbAXXAl7w7WwDzwOHY/2ZR3H9tTFIX3A0fVPHzNhFBwCU+BQTec82AMOhxPhSDgNjoL5MAsWq7vlug5aBc+AF8Cz4IUwG67X9c/L4AR4BZwLr1P/22AO3K7rn3vhNPggnA4fgzPgfnX/NMyFL8JZ8ACcDV/XcN9Wd7tb1hv/o9cbS26KZrO5ZU2x5dfya/m1/Fp+X/z35bz/V1bU+hYATsH7f3hPx5zbekH3suV7lqhClJcJ2dYa/3vn9Jkz5uSNn7Mgr7Cy6gJ597qsY9137HBq5MRvFPdLnO72904Nz+Pyv6y6srz+3PdOsZ/H22W4dU1A/WO2CJEAuffMqOB3t9ZKJ+i7db54O5p08/5mzCQtAefZtng1AJQHNRb1EhPguNoG5bKsurjYlS9fRdWfTewo7s+wlYmG5WGevkjsDibWq1vimv52ZEC+JN6g72GG1TnO1jyM0TxUNcxDaUVprebB3IFo8rBK3J9mywNhBdbLoR5Ghfy9R0m/xulOf6x6WKTpX4hyaJv7G6a/oniNY9Kv9zKatnlI3E90Wss9IXwnn4S+hoqgH4R1ixkc09f30dRYWx7kO6r+Mw47Q6gTd/qfiKyz+DqeY+BNMJz0Z65qkP4aEmxrQ7K2s1bcj7edpdGw9HvA6pe+bM6rvCf2YdY+5fZ7UUC96zlasS/3WNZs8Gu9C9Pc1TFW7Dd72pHK+nsdZ5c6rnZVIm46eUTPX4+tRo9tdL17cw7zR+J2CukOY7QbbMK4RPyMdoLCkDj5piy/Wl+BSP6P6rd6YwaSf/ON6frvmh+XOFqL28O4neEsErsl8eaeRsabunbxun5L9170Q1CFnevcFUGfeWaSsZe/hyaFcu6M+xlXm/sYrf07wX0no9a1rj0Ff09b8ksZYFZXBphJvsi/fmM78I6G3TpwbkaFoTahfp7B+LHG1l65xKZwRTHBSlkfwh3n9yWRidpuZ4m/1c6Z/FtsfS5o2NqOwmSN2BesY+6mmiz2F/EuH+GU29sxYdj7gKXd4jb0+17VbfC4Yu7TmiP21c4ocpLveM29Mjtw+414+nsKfR+1Dse3xNcRc1TTa8f+uqdcqSspV1P3lBNmUk5a9wHtocl7OYv09XcWKgqVi/p0CPKqpp59z0OZcSyvLC+uvgB7s76rZWCrS/wH3/drrS91Fzze2e8SsteX6f8fiP0UW/0Zv677eM3Y1mqtz25U4PhVUT/mfih+c/ReqcD+H9nT159Dr0NZE9Zys34j29LHbfV3ln7f+EA7R34zvMiMw6lw4mjkE9c2Un9yVNNVh0Fj9YwL5M4aGXlt9Uq4Wo7Gv9krOV/8Zpj62CZu59jqnXCs9W6eVUfFvoNJV5XoJ1MHeo+zCaO752ZnpqudmLDdZ6br7nrTdL4v9stY0+xmziz/Rcy2u/eZzJ3CHeBqsX/X49t32EQbOwrTPY+bOWvtWr2/FNMEPas=
*/