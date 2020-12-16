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
ungdZqwgxhOKuEP3Wymj58lZiS9uGZfXid/hXv+dILvETVv3d+urHNc+ykaxP+Jc7KRyPinRnJveIvHV5+kqcZfuCqeCcOrL+CGJN9acm39c9Cfc9xlVucvtBgnvFdZubzX3gZSLWQ9zzva7phzxY9IUZe5vukTcD/S47lAx6fmz2LU37Wn/Wr3/Q+PaI/bvMQ8/w4T/tisPr5GHb4mbv7vOr6424SeIXayZC6aI/gp2Ds82cwZHzBJc7UC+T23mHtslvrm8b6WxNp3samOF+dWMjv4x41NxN8X0hSOi72jOzU71xUO87SkbV/1IgXf2xyVu/kGLJzfORu4B6qx5oddJuYaZuntA3H7myne5PS6thwlidqYr/bXD3POx98S+SsPwt9vnKL0qtx9zrj8BHhY3g9z2Q8Ve6+8PYn+G2364uz2Gr5OyVb0/zjhzp9XdqXKHlfDH8KCourE33T2XasbYq2bWsdc9H8KB/Kr0OVmJ+ozc55q9cZ63cq9JwKPSPU5ax1P8Bz8nzd52tdh1c+Js91Nb/RaYvrpa7Do5sfZ9Vvzaxl/r3Ae3J3/uzhP7EttZdPxa3w1MP1kg9std7wVyrZl5Ni8X+3naBuqfvVczl/prYujPX998+sELv/j95sHP5g4Bz+Yv9/z5OtmffWpP5AV//uj9e77Rbd7gr2w48sd//flz+z5y8/dVm7v/+592Lv1fff7c9R17WZ9Yqnupx1FrzTqYrNeJXaxItshPvoPugethW3gp7Akvg73gFtgbboSnwyvgTLgZngOvhAvhVTAPXg0LxZ+etzVrVnQwjb81aprGf9Spi/89GAWPQZGngV0gYUj8f4ED4Qk4FtJMTfhVGn62Jfy3NPy3YQQ8DDvAd2A3+DvYF74LR8EjcAz8vYafg9qv4S/S8N3fef25hv9L2BW+oeG+BmfC38CFan4cHjPrILLGI+F10fpy9Lv7MfATDedTmAYv1Pr4DH0mdNCPB16YA8Og1C0sh/FwBzwL3gHHwEfhOPgknATfhzkQv85UGAfPhslwOuwMZ8K+cDYcA+fDaXAlXAyrYSWshVfDC+A2uA7eBEm3nv/Ud2NdKwg+/7nVlw54A2wDt8F4eCPsCr8G0+Bt2h5vh/3hbpgNvwmnwDvhDPiQttN74AJ4L1wM79P2uReWwH1wJXwQrlZ/a9T8UjXfpObHYa7/HRHO0ny0Qk1AOXp/gBfuhe3g/XAwfACOg/v0/NbLMBf+TNsF/UnfR+QdTcIdhLoIA34iZxALZ8PO8ByYAufADJUn6A/v0PaxEE6B52k7XAxnw3xYAAtgESyEl8FilXcogdtVvwuWwofg+fA7cAV8BpbDP8Aq+BlcCWmLEn8krIHRcBWMg1+Bg+FGOApugufCalgMr4GXqPkmeDW8Cm6B16j99fA6eC/cCu+H18PH4FfhE/AG+BLcBl+BN8JP4XbooVx3wAHwG3AEvBWOhbfDqfAOqOOmzknIo2Xc7Kr1PEjrebDWS6bWy3DYC46AKGeUji9ZcBI8E+bDSfB8OBlWwhz4Qos8yCmRB4l7NHSZkPTro5stF9J6Z7TTB5WDKkFtRu1BHUSdQHW9uUVmpOXX8mv5/dv2/4tOlfx/a5f8/326z12oe6wFqJvTefZVuNc4+E5X4LqGkc8eLe4WOgn8Oxh1pn2fh/BC2xto6K7AspZhc1du9ozmit0ZuPcyH29lW9/Av3V9w7aeYdz2YO/4Yafu3pAPE0lHp26R4bGRXdk9jmjFX51aOeY+vMykwL3jDxKbllNo7vqE3uOr+nLb2gRuRsdfLenn/SgrcH+6A5FJm9W6H496fwjz2uC6z1u5qrRwhbv+zR7Yo+L2NKk=
*/