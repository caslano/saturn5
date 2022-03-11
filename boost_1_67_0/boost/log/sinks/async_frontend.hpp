/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   async_frontend.hpp
 * \author Andrey Semashev
 * \date   14.07.2009
 *
 * The header contains implementation of asynchronous sink frontend.
 */

#ifndef BOOST_LOG_SINKS_ASYNC_FRONTEND_HPP_INCLUDED_
#define BOOST_LOG_SINKS_ASYNC_FRONTEND_HPP_INCLUDED_

#include <exception> // std::terminate
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_LOG_NO_THREADS)
#error Boost.Log: Asynchronous sink frontend is only supported in multithreaded environment
#endif

#include <boost/bind/bind.hpp>
#include <boost/static_assert.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/atomic.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/log/exceptions.hpp>
#include <boost/log/detail/locking_ptr.hpp>
#include <boost/log/detail/parameter_tools.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/sinks/basic_sink_frontend.hpp>
#include <boost/log/sinks/frontend_requirements.hpp>
#include <boost/log/sinks/unbounded_fifo_queue.hpp>
#include <boost/log/keywords/start_thread.hpp>
#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

#ifndef BOOST_LOG_DOXYGEN_PASS

#define BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_1(n, data)\
    template< typename T0 >\
    explicit asynchronous_sink(T0 const& arg0, typename boost::log::aux::enable_if_named_parameters< T0, boost::log::aux::sfinae_dummy >::type = boost::log::aux::sfinae_dummy()) :\
        base_type(true),\
        queue_base_type(arg0),\
        m_pBackend(boost::make_shared< sink_backend_type >(arg0)),\
        m_StopRequested(false),\
        m_FlushRequested(false)\
    {\
        if (arg0[keywords::start_thread | true])\
            start_feeding_thread();\
    }\
    template< typename T0 >\
    explicit asynchronous_sink(shared_ptr< sink_backend_type > const& backend, T0 const& arg0) :\
        base_type(true),\
        queue_base_type(arg0),\
        m_pBackend(backend),\
        m_StopRequested(false),\
        m_FlushRequested(false)\
    {\
        if (arg0[keywords::start_thread | true])\
            start_feeding_thread();\
    }

#define BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_N(n, data)\
    template< BOOST_PP_ENUM_PARAMS(n, typename T) >\
    explicit asynchronous_sink(BOOST_PP_ENUM_BINARY_PARAMS(n, T, const& arg)) :\
        base_type(true),\
        queue_base_type((BOOST_PP_ENUM_PARAMS(n, arg))),\
        m_pBackend(boost::make_shared< sink_backend_type >(BOOST_PP_ENUM_PARAMS(n, arg))),\
        m_StopRequested(false),\
        m_FlushRequested(false)\
    {\
        if ((BOOST_PP_ENUM_PARAMS(n, arg))[keywords::start_thread | true])\
            start_feeding_thread();\
    }\
    template< BOOST_PP_ENUM_PARAMS(n, typename T) >\
    explicit asynchronous_sink(shared_ptr< sink_backend_type > const& backend, BOOST_PP_ENUM_BINARY_PARAMS(n, T, const& arg)) :\
        base_type(true),\
        queue_base_type((BOOST_PP_ENUM_PARAMS(n, arg))),\
        m_pBackend(backend),\
        m_StopRequested(false),\
        m_FlushRequested(false)\
    {\
        if ((BOOST_PP_ENUM_PARAMS(n, arg))[keywords::start_thread | true])\
            start_feeding_thread();\
    }

#define BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL(z, n, data)\
    BOOST_PP_IF(BOOST_PP_EQUAL(n, 1), BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_1, BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_N)(n, data)

#endif // BOOST_LOG_DOXYGEN_PASS

/*!
 * \brief Asynchronous logging sink frontend
 *
 * The frontend starts a separate thread on construction. All logging records are passed
 * to the backend in this dedicated thread only.
 */
template< typename SinkBackendT, typename QueueingStrategyT = unbounded_fifo_queue >
class asynchronous_sink :
    public aux::make_sink_frontend_base< SinkBackendT >::type,
    public QueueingStrategyT
{
    typedef typename aux::make_sink_frontend_base< SinkBackendT >::type base_type;
    typedef QueueingStrategyT queue_base_type;

private:
    //! Backend synchronization mutex type
    typedef boost::recursive_mutex backend_mutex_type;
    //! Frontend synchronization mutex type
    typedef typename base_type::mutex_type frontend_mutex_type;

    //! A scope guard that implements thread ID management
    class scoped_thread_id
    {
    private:
        frontend_mutex_type& m_Mutex;
        condition_variable_any& m_Cond;
        thread::id& m_ThreadID;
        boost::atomic< bool >& m_StopRequested;

    public:
        //! Initializing constructor
        scoped_thread_id(frontend_mutex_type& mut, condition_variable_any& cond, thread::id& tid, boost::atomic< bool >& sr)
            : m_Mutex(mut), m_Cond(cond), m_ThreadID(tid), m_StopRequested(sr)
        {
            lock_guard< frontend_mutex_type > lock(m_Mutex);
            if (m_ThreadID != thread::id())
                BOOST_LOG_THROW_DESCR(unexpected_call, "Asynchronous sink frontend already runs a record feeding thread");
            m_ThreadID = this_thread::get_id();
        }
        //! Initializing constructor
        scoped_thread_id(unique_lock< frontend_mutex_type >& l, condition_variable_any& cond, thread::id& tid, boost::atomic< bool >& sr)
            : m_Mutex(*l.mutex()), m_Cond(cond), m_ThreadID(tid), m_StopRequested(sr)
        {
            unique_lock< frontend_mutex_type > lock(move(l));
            if (m_ThreadID != thread::id())
                BOOST_LOG_THROW_DESCR(unexpected_call, "Asynchronous sink frontend already runs a record feeding thread");
            m_ThreadID = this_thread::get_id();
        }
        //! Destructor
        ~scoped_thread_id()
        {
            try
            {
                lock_guard< frontend_mutex_type > lock(m_Mutex);
                m_StopRequested.store(false, boost::memory_order_release);
                m_ThreadID = thread::id();
                m_Cond.notify_all();
            }
            catch (...)
            {
            }
        }

        BOOST_DELETED_FUNCTION(scoped_thread_id(scoped_thread_id const&))
        BOOST_DELETED_FUNCTION(scoped_thread_id& operator= (scoped_thread_id const&))
    };

    //! A scope guard that resets a flag on destructor
    class scoped_flag
    {
    private:
        frontend_mutex_type& m_Mutex;
        condition_variable_any& m_Cond;
        boost::atomic< bool >& m_Flag;

    public:
        explicit scoped_flag(frontend_mutex_type& mut, condition_variable_any& cond, boost::atomic< bool >& f) :
            m_Mutex(mut), m_Cond(cond), m_Flag(f)
        {
        }
        ~scoped_flag()
        {
            try
            {
                lock_guard< frontend_mutex_type > lock(m_Mutex);
                m_Flag.store(false, boost::memory_order_release);
                m_Cond.notify_all();
            }
            catch (...)
            {
            }
        }

        BOOST_DELETED_FUNCTION(scoped_flag(scoped_flag const&))
        BOOST_DELETED_FUNCTION(scoped_flag& operator= (scoped_flag const&))
    };

public:
    //! Sink implementation type
    typedef SinkBackendT sink_backend_type;
    //! \cond
    BOOST_STATIC_ASSERT_MSG((has_requirement< typename sink_backend_type::frontend_requirements, synchronized_feeding >::value), "Asynchronous sink frontend is incompatible with the specified backend: thread synchronization requirements are not met");
    //! \endcond

#ifndef BOOST_LOG_DOXYGEN_PASS

    //! A pointer type that locks the backend until it's destroyed
    typedef boost::log::aux::locking_ptr< sink_backend_type, backend_mutex_type > locked_backend_ptr;

#else // BOOST_LOG_DOXYGEN_PASS

    //! A pointer type that locks the backend until it's destroyed
    typedef implementation_defined locked_backend_ptr;

#endif // BOOST_LOG_DOXYGEN_PASS

private:
    //! Synchronization mutex
    backend_mutex_type m_BackendMutex;
    //! Pointer to the backend
    const shared_ptr< sink_backend_type > m_pBackend;

    //! Dedicated record feeding thread
    thread m_DedicatedFeedingThread;
    //! Feeding thread ID
    thread::id m_FeedingThreadID;
    //! Condition variable to implement blocking operations
    condition_variable_any m_BlockCond;

    //! The flag indicates that the feeding loop has to be stopped
    boost::atomic< bool > m_StopRequested;
    //! The flag indicates that queue flush has been requested
    boost::atomic< bool > m_FlushRequested;

public:
    /*!
     * Default constructor. Constructs the sink backend instance.
     * Requires the backend to be default-constructible.
     *
     * \param start_thread If \c true, the frontend creates a thread to feed
     *                     log records to the backend. Otherwise no thread is
     *                     started and it is assumed that the user will call
     *                     either \c run or \c feed_records himself.
     */
    asynchronous_sink(bool start_thread = true) :
        base_type(true),
        m_pBackend(boost::make_shared< sink_backend_type >()),
        m_StopRequested(false),
        m_FlushRequested(false)
    {
        if (start_thread)
            start_feeding_thread();
    }
    /*!
     * Constructor attaches user-constructed backend instance
     *
     * \param backend Pointer to the backend instance.
     * \param start_thread If \c true, the frontend creates a thread to feed
     *                     log records to the backend. Otherwise no thread is
     *                     started and it is assumed that the user will call
     *                     either \c run or \c feed_records himself.
     *
     * \pre \a backend is not \c NULL.
     */
    explicit asynchronous_sink(shared_ptr< sink_backend_type > const& backend, bool start_thread = true) :
        base_type(true),
        m_pBackend(backend),
        m_StopRequested(false),
        m_FlushRequested(false)
    {
        if (start_thread)
            start_feeding_thread();
    }

    /*!
     * Constructor that passes arbitrary named parameters to the interprocess sink backend constructor.
     * Refer to the backend documentation for the list of supported parameters.
     *
     * The frontend uses the following named parameters:
     *
     *   \li start_thread - If \c true, the frontend creates a thread to feed
     *                      log records to the backend. Otherwise no thread is
     *                      started and it is assumed that the user will call
     *                      either \c run or \c feed_records himself.
     */
#ifndef BOOST_LOG_DOXYGEN_PASS
    BOOST_LOG_PARAMETRIZED_CONSTRUCTORS_GEN(BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL, ~)
#else
    template< typename... Args >
    explicit asynchronous_sink(Args&&... args);
#endif

    /*!
     * Destructor. Implicitly stops the dedicated feeding thread, if one is running.
     */
    ~asynchronous_sink() BOOST_NOEXCEPT
    {
        try
        {
            boost::this_thread::disable_interruption no_interrupts;
            stop();
        }
        catch (...)
        {
            std::terminate();
        }
    }

    /*!
     * Locking accessor to the attached backend
     */
    locked_backend_ptr locked_backend()
    {
        return locked_backend_ptr(m_pBackend, m_BackendMutex);
    }

    /*!
     * Enqueues the log record to the backend
     */
    void consume(record_view const& rec)
    {
        if (BOOST_UNLIKELY(m_FlushRequested.load(boost::memory_order_acquire)))
        {
            unique_lock< frontend_mutex_type > lock(base_type::frontend_mutex());
            // Wait until flush is done
            while (m_FlushRequested.load(boost::memory_order_acquire))
                m_BlockCond.wait(lock);
        }
        queue_base_type::enqueue(rec);
    }

    /*!
     * The method attempts to pass logging record to the backend
     */
    bool try_consume(record_view const& rec)
    {
        if (!m_FlushRequested.load(boost::memory_order_acquire))
        {
            return queue_base_type::try_enqueue(rec);
        }
        else
            return false;
    }

    /*!
     * The method starts record feeding loop and effectively blocks until either of this happens:
     *
     * \li the thread is interrupted due to either standard thread interruption or a call to \c stop
     * \li an exception is thrown while processing a log record in the backend, and the exception is
     *     not terminated by the exception handler, if one is installed
     *
     * \pre The sink frontend must be constructed without spawning a dedicated thread
     */
    void run()
    {
        // First check that no other thread is running
        scoped_thread_id guard(base_type::frontend_mutex(), m_BlockCond, m_FeedingThreadID, m_StopRequested);

        // Now start the feeding loop
        while (true)
        {
            do_feed_records();
            if (!m_StopRequested.load(boost::memory_order_acquire))
            {
                // Block until new record is available
                record_view rec;
                if (queue_base_type::dequeue_ready(rec))
                    base_type::feed_record(rec, m_BackendMutex, *m_pBackend);
            }
            else
                break;
        }
    }

    /*!
     * The method softly interrupts record feeding loop. This method must be called when the \c run
     * method execution has to be interrupted. Unlike regular thread interruption, calling
     * \c stop will not interrupt the record processing in the middle. Instead, the sink frontend
     * will attempt to finish its business with the record in progress and return afterwards.
     * This method can be called either if the sink was created with a dedicated thread,
     * or if the feeding loop was initiated by user.
     *
     * \note Returning from this method does not guarantee that there are no records left buffered
     *       in the sink frontend. It is possible that log records keep coming during and after this
     *       method is called. At some point of execution of this method log records stop being processed,
     *       and all records that come after this point are put into the queue. These records will be
     *       processed upon further calls to \c run or \c feed_records.
     */
    void stop()
    {
        unique_lock< frontend_mutex_type > lock(base_type::frontend_mutex());
        if (m_FeedingThreadID != thread::id() || m_DedicatedFeedingThread.joinable())
        {
            try
            {
                m_StopRequested.store(true, boost::memory_order_release);
                queue_base_type::interrupt_dequeue();
                while (m_StopRequested.load(boost::memory_order_acquire))
                    m_BlockCond.wait(lock);
            }
            catch (...)
            {
                m_StopRequested.store(false, boost::memory_order_release);
                throw;
            }

            lock.unlock();
            m_DedicatedFeedingThread.join();
        }
    }

    /*!
     * The method feeds log records that may have been buffered to the backend and returns
     *
     * \pre The sink frontend must be constructed without spawning a dedicated thread
     */
    void feed_records()
    {
        // First check that no other thread is running
        scoped_thread_id guard(base_type::frontend_mutex(), m_BlockCond, m_FeedingThreadID, m_StopRequested);

        // Now start the feeding loop
        do_feed_records();
    }

    /*!
     * The method feeds all log records that may have been buffered to the backend and returns.
     * Unlike \c feed_records, in case of ordering queueing the method also feeds records
     * that were enqueued during the ordering window, attempting to empty the queue completely.
     */
    void flush()
    {
        unique_lock< frontend_mutex_type > lock(base_type::frontend_mutex());
        if (m_FeedingThreadID != thread::id() || m_DedicatedFeedingThread.joinable())
        {
            // There is already a thread feeding records, let it do the job
            m_FlushRequested.store(true, boost::memory_order_release);
            queue_base_type::interrupt_dequeue();
            while (!m_StopRequested.load(boost::memory_order_acquire) && m_FlushRequested.load(boost::memory_order_acquire))
                m_BlockCond.wait(lock);

            // The condition may have been signalled when the feeding thread was finishing.
            // In that case records may not have been flushed, and we do the flush ourselves.
            if (m_FeedingThreadID != thread::id())
                return;
        }

        m_FlushRequested.store(true, boost::memory_order_release);

        // Flush records ourselves. The guard releases the lock.
        scoped_thread_id guard(lock, m_BlockCond, m_FeedingThreadID, m_StopRequested);

        do_feed_records();
    }

private:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! The method spawns record feeding thread
    void start_feeding_thread()
    {
        boost::thread(boost::bind(&asynchronous_sink::run, this)).swap(m_DedicatedFeedingThread);
    }

    //! The record feeding loop
    void do_feed_records()
    {
        while (!m_StopRequested.load(boost::memory_order_acquire))
        {
            record_view rec;
            bool dequeued = false;
            if (BOOST_LIKELY(!m_FlushRequested.load(boost::memory_order_acquire)))
                dequeued = queue_base_type::try_dequeue_ready(rec);
            else
                dequeued = queue_base_type::try_dequeue(rec);

            if (dequeued)
                base_type::feed_record(rec, m_BackendMutex, *m_pBackend);
            else
                break;
        }

        if (BOOST_UNLIKELY(m_FlushRequested.load(boost::memory_order_acquire)))
        {
            scoped_flag guard(base_type::frontend_mutex(), m_BlockCond, m_FlushRequested);
            base_type::flush_backend(m_BackendMutex, *m_pBackend);
        }
    }
#endif // BOOST_LOG_DOXYGEN_PASS
};

#undef BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_1
#undef BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_N
#undef BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_ASYNC_FRONTEND_HPP_INCLUDED_

/* async_frontend.hpp
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
*/