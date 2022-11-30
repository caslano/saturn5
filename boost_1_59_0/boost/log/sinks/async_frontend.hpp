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

#define BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_1(z, n, data)\
    template< typename T0 >\
    explicit asynchronous_sink(T0 const& arg0, typename boost::log::aux::enable_if_named_parameters< T0, boost::log::aux::sfinae_dummy >::type = boost::log::aux::sfinae_dummy()) :\
        base_type(true),\
        queue_base_type(arg0),\
        m_pBackend(boost::make_shared< sink_backend_type >(arg0)),\
        m_ActiveOperation(idle),\
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
        m_ActiveOperation(idle),\
        m_StopRequested(false),\
        m_FlushRequested(false)\
    {\
        if (arg0[keywords::start_thread | true])\
            start_feeding_thread();\
    }

#define BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_N(z, n, data)\
    template< BOOST_PP_ENUM_PARAMS_Z(z, n, typename T) >\
    explicit asynchronous_sink(BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, T, const& arg)) :\
        base_type(true),\
        queue_base_type((BOOST_PP_ENUM_PARAMS_Z(z, n, arg))),\
        m_pBackend(boost::make_shared< sink_backend_type >(BOOST_PP_ENUM_PARAMS_Z(z, n, arg))),\
        m_ActiveOperation(idle),\
        m_StopRequested(false),\
        m_FlushRequested(false)\
    {\
        if ((BOOST_PP_ENUM_PARAMS_Z(z, n, arg))[keywords::start_thread | true])\
            start_feeding_thread();\
    }\
    template< BOOST_PP_ENUM_PARAMS_Z(z, n, typename T) >\
    explicit asynchronous_sink(shared_ptr< sink_backend_type > const& backend, BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, T, const& arg)) :\
        base_type(true),\
        queue_base_type((BOOST_PP_ENUM_PARAMS_Z(z, n, arg))),\
        m_pBackend(backend),\
        m_ActiveOperation(idle),\
        m_StopRequested(false),\
        m_FlushRequested(false)\
    {\
        if ((BOOST_PP_ENUM_PARAMS_Z(z, n, arg))[keywords::start_thread | true])\
            start_feeding_thread();\
    }

#define BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL(z, n, data)\
    BOOST_PP_IF(BOOST_PP_EQUAL(n, 1), BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_1, BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_N)(z, n, data)

#endif // BOOST_LOG_DOXYGEN_PASS

/*!
 * \brief Asynchronous logging sink frontend
 *
 * The frontend starts a separate thread on construction. All logging records are passed
 * to the backend in this dedicated thread.
 *
 * The user can prevent spawning the internal thread by specifying \c start_thread parameter
 * with the value of \c false on construction. In this case log records will be buffered
 * in the internal queue until the user calls \c run, \c feed_records or \c flush in his own
 * thread. Log record queueing strategy is specified in the \c QueueingStrategyT template
 * parameter.
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

    //! Operation bit mask
    enum operation
    {
        idle = 0u,
        feeding_records = 1u,
        flushing = 3u
    };

    //! Function object to run the log record feeding thread
    class run_func
    {
    public:
        typedef void result_type;

    private:
        asynchronous_sink* m_self;

    public:
        explicit run_func(asynchronous_sink* self) BOOST_NOEXCEPT : m_self(self)
        {
        }

        result_type operator()() const
        {
            m_self->run();
        }
    };

    //! A scope guard that implements active operation management
    class scoped_feeding_opereation
    {
    private:
        asynchronous_sink& m_self;

    public:
        //! Initializing constructor
        explicit scoped_feeding_opereation(asynchronous_sink& self) : m_self(self)
        {
        }
        //! Destructor
        ~scoped_feeding_opereation()
        {
            m_self.complete_feeding_operation();
        }

        BOOST_DELETED_FUNCTION(scoped_feeding_opereation(scoped_feeding_opereation const&))
        BOOST_DELETED_FUNCTION(scoped_feeding_opereation& operator= (scoped_feeding_opereation const&))
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
                m_Flag.store(false, boost::memory_order_relaxed);
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
    //! Condition variable to implement blocking operations
    condition_variable_any m_BlockCond;

    //! Currently active operation
    operation m_ActiveOperation;
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
     *                     \c run, \c feed_records or \c flush himself.
     */
    explicit asynchronous_sink(bool start_thread = true) :
        base_type(true),
        m_pBackend(boost::make_shared< sink_backend_type >()),
        m_ActiveOperation(idle),
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
     *                     \c run, \c feed_records or \c flush himself.
     *
     * \pre \a backend is not \c NULL.
     */
    explicit asynchronous_sink(shared_ptr< sink_backend_type > const& backend, bool start_thread = true) :
        base_type(true),
        m_pBackend(backend),
        m_ActiveOperation(idle),
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
     *                      \c run, \c feed_records or \c flush himself.
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
    ~asynchronous_sink() BOOST_NOEXCEPT BOOST_OVERRIDE
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
    void consume(record_view const& rec) BOOST_OVERRIDE
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
    bool try_consume(record_view const& rec) BOOST_OVERRIDE
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
        {
            unique_lock< frontend_mutex_type > lock(base_type::frontend_mutex());
            if (start_feeding_operation(lock, feeding_records))
                return;
        }

        scoped_feeding_opereation guard(*this);

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
     * The method softly interrupts record feeding loop. This method must be called when \c run,
     * \c feed_records or \c flush method execution has to be interrupted. Unlike regular thread
     * interruption, calling \c stop will not interrupt the record processing in the middle.
     * Instead, the sink frontend will attempt to finish its business with the record in progress
     * and return afterwards. This method can be called either if the sink was created with
     * an internal dedicated thread, or if the feeding loop was initiated by user.
     *
     * If no record feeding operation is in progress, calling \c stop marks the sink frontend
     * so that the next feeding operation stops immediately.
     *
     * \note Returning from this method does not guarantee that there are no records left buffered
     *       in the sink frontend. It is possible that log records keep coming during and after this
     *       method is called. At some point of execution of this method log records stop being processed,
     *       and all records that come after this point are put into the queue. These records will be
     *       processed upon further calls to \c run or \c feed_records.
     *
     * \note If the record feeding loop is being run in a user's thread (i.e. \c start_thread was specified
     *       as \c false on frontend construction), this method does not guarantee that upon return the thread
     *       has returned from the record feeding loop or that it won't enter it in the future. The method
     *       only ensures that the record feeding thread will eventually return from the feeding loop. It is
     *       user's responsibility to synchronize with the user's record feeding thread.
     */
    void stop()
    {
        boost::thread feeding_thread;
        {
            lock_guard< frontend_mutex_type > lock(base_type::frontend_mutex());

            m_StopRequested.store(true, boost::memory_order_release);
            queue_base_type::interrupt_dequeue();

            m_DedicatedFeedingThread.swap(feeding_thread);
        }

        if (feeding_thread.joinable())
            feeding_thread.join();
    }

    /*!
     * The method feeds log records that may have been buffered to the backend and returns
     *
     * \pre The sink frontend must be constructed without spawning a dedicated thread
     */
    void feed_records()
    {
        // First check that no other thread is running
        {
            unique_lock< frontend_mutex_type > lock(base_type::frontend_mutex());
            if (start_feeding_operation(lock, feeding_records))
                return;
        }

        scoped_feeding_opereation guard(*this);

        // Now start the feeding loop
        do_feed_records();
    }

    /*!
     * The method feeds all log records that may have been buffered to the backend and returns.
     * Unlike \c feed_records, in case of ordering queueing the method also feeds records
     * that were enqueued during the ordering window, attempting to drain the queue completely.
     */
    void flush() BOOST_OVERRIDE
    {
        {
            unique_lock< frontend_mutex_type > lock(base_type::frontend_mutex());
            if (static_cast< unsigned int >(m_ActiveOperation & feeding_records) != 0u)
            {
                // There is already a thread feeding records, let it do the job
                m_FlushRequested.store(true, boost::memory_order_release);
                queue_base_type::interrupt_dequeue();
                while (!m_StopRequested.load(boost::memory_order_acquire) && m_FlushRequested.load(boost::memory_order_acquire))
                    m_BlockCond.wait(lock);

                // The condition may have been signalled when the feeding operation was finishing.
                // In that case records may not have been flushed, and we do the flush ourselves.
                if (m_ActiveOperation != idle)
                    return;
            }

            m_ActiveOperation = flushing;
            m_FlushRequested.store(true, boost::memory_order_relaxed);
        }

        scoped_feeding_opereation guard(*this);

        do_feed_records();
    }

private:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! The method spawns record feeding thread
    void start_feeding_thread()
    {
        boost::thread(run_func(this)).swap(m_DedicatedFeedingThread);
    }

    //! Starts record feeding operation. The method blocks or throws if another feeding operation is in progress.
    bool start_feeding_operation(unique_lock< frontend_mutex_type >& lock, operation op)
    {
        while (m_ActiveOperation != idle)
        {
            if (BOOST_UNLIKELY(op == feeding_records && m_ActiveOperation == feeding_records))
                BOOST_LOG_THROW_DESCR(unexpected_call, "Asynchronous sink frontend already runs a record feeding thread");

            if (BOOST_UNLIKELY(m_StopRequested.load(boost::memory_order_relaxed)))
            {
                m_StopRequested.store(false, boost::memory_order_relaxed);
                return true;
            }

            m_BlockCond.wait(lock);
        }

        m_ActiveOperation = op;

        return false;
    }

    //! Completes record feeding operation
    void complete_feeding_operation() BOOST_NOEXCEPT
    {
        try
        {
            lock_guard< frontend_mutex_type > lock(base_type::frontend_mutex());
            m_ActiveOperation = idle;
            m_StopRequested.store(false, boost::memory_order_relaxed);
            m_BlockCond.notify_all();
        }
        catch (...)
        {
        }
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