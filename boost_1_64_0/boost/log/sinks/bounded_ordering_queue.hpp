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
FkSW5SkKTxQh8KlVLn9/nDsS17E3ncfpHsntdZzitle1k/N9k/t2I8W/m48d/eHjeh+V9/oYil9V3hdb24819f0UpPAoLQtP7IfFNNd+l/tbwiheE02uQzCs5QkAv6LwYPmMKraPaWmzsNCX9pvQtXvU91p+U/Rfvye3rSzIHWfbpEV8T95yWl7P6nsy99HfKd5SjAwbRnS0ei/gacX1zG26l8JyRR3EvENpp9SYXran7MOGpDuuL+/Tg+k4tGy9Eh03E1b285d+8eTncu+WY/dTOmcS9MVBcjx2o3Re8vmeRcfB8l3hKqVZorrfU783ofg1+Fiml+MvkY77OD8PuJ2acZk9RFPl74ZeoXPPg77by/la5HtAKYXPFZHS3q3cl4Rx9vuf+3/mupCaBzT43zH5ztkf5G449/38/h8NjJ8zyFwX8r+0LuSU432fv2mSwRAIup/cYN7LMwIMYPuNjfi3+pryeoY4MAVMAEeBqew/Bkzj31pLB+8Bx4LLwAxeLzCOf1vtLnALmAkeBLPBY7ye4gyvpzjH9jZ/ZnubVVDeAtAXnABGgpPARuBkXiexU75v0vsw1S8QsslgV1IDq/O6jSBetxHMdh5D+DcQG3O9Q3mdTBjb/azB9hVrgz3ACLAvWAccDEayHci63C5RvAeqPq+fuZnXU0Sz3cVGvBeqMZc/RuN3I34XTKa8kI8myE3j/pnN/TOH+2Uul3Mz2AJcALbidSS3g4v5twPv5d+6Ww6uY/uS2zndy2xf8jW2L/k625d8i9eXvMP2JN8HV4MXeJ3JRbYrWQKu4b1Ya0EL752ygk9wv60DA8H1YCi4AUwAnwI78h6rzuBGsAe4CRyq2cs3gvdwjQOXgvnsz+Oan2f0zC03rptxuyXw+pyW3M+JYAzbOY0H2/C4bsvt1w68jfesjeV4mWBH3tPWhdu1K9vP7Mb92R1cynvW1oA92E5qT7af2QvczfZX94F9ud37gW/wnrYiPt8mc13Lf/S6liKsZ7kIsS6qJMIXmWtbTGc605nOdKYznelMZzrT/f+6P0X/jy2huTfI/t+xSCH3o+ZqglxziAaJg3yXCP8ixzz+wG5d+id1GTw0aXReejrNUZciXBN6gcr2GU+g+E1U8/iclybnj7f42mU1xFXHaHWeP5Y2pPRzVudzGvfTNrYIcvWo/CCXf0v58mdkZxS4Lf+LFD9YVX7OS5P60eORuvz+su/jsrfksidAvkfc4vJlz06fJLjs0qaBnMP/muLXE96GNt7ge+3lNJbpZw9BriOXqQPkB5wz5p1yZcpHIVzbU5apFcVPQLimalPk56rbSVPpcBBPaR9CuRee48o2WMc2zT4MqrgNFH3loqtIU9ocMOrEirwEuSwL8gMzwJ8S9YlF4284ct5SJ5Y2UdD5O+P8HBc5lIo0TbaX9NfK0qGMWUKofx+zXNtmyfU2i4/pYR2QLkbZhpzWtV/lHm/Pd/Xwd7UE4SV6Q7ZpXso92oXqfpP7tO+l8GGWLajdQUhTi5XyCTTkE8j5KO15sO7rYQofaCmzMZgmf9NyG4XFWxYJm3gM4m2xibJ4eVK3X0Txgi1ZKMEsyBeap9KmwTtUdw+pM0yl40ipH1xMx4O0MNFcc/RnAflN0fZgJlhleyODwqtL/WFX6p901L0V95lzvjdxvnEU7xVDfUbJ9QUvUX36Sj3zKYp7k9Qz76bwGEObpUhd5EYK62wZh2soVKhtIv4YRNcV2/kgoWvsvUi7jcFvg8o4CfyRudVf2kHEZLkj7bXoqW1+qIO0DeJsV5CvH/h5Sz+6NlxsC2ZRHF/na5z8AhXXdHu+puN5unMKxAeih/+K9MuPG+zj0m9GIr8=
*/