/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   block_on_overflow.hpp
 * \author Andrey Semashev
 * \date   04.01.2012
 *
 * The header contains implementation of \c block_on_overflow strategy for handling
 * queue overflows in bounded queues for the asynchronous sink frontend.
 */

#ifndef BOOST_LOG_SINKS_BLOCK_ON_OVERFLOW_HPP_INCLUDED_
#define BOOST_LOG_SINKS_BLOCK_ON_OVERFLOW_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_LOG_NO_THREADS)
#error Boost.Log: This header content is only supported in multithreaded environment
#endif

#include <boost/intrusive/options.hpp>
#include <boost/intrusive/list.hpp>
#include <boost/intrusive/list_hook.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

/*!
 * \brief Blocking strategy for handling log record queue overflows
 *
 * This strategy will cause enqueueing threads to block when the
 * log record queue overflows. The blocked threads will be woken as
 * soon as there appears free space in the queue, in the same order
 * they attempted to enqueue records.
 */
class block_on_overflow
{
#ifndef BOOST_LOG_DOXYGEN_PASS
private:
    typedef intrusive::list_base_hook<
        intrusive::link_mode< intrusive::auto_unlink >
    > thread_context_hook_t;

    struct thread_context :
        public thread_context_hook_t
    {
        condition_variable cond;
        bool result;

        thread_context() : result(true) {}
    };

    typedef intrusive::list<
        thread_context,
        intrusive::base_hook< thread_context_hook_t >,
        intrusive::constant_time_size< false >
    > thread_contexts;

private:
    //! Blocked threads
    thread_contexts m_thread_contexts;

public:
    /*!
     * Default constructor.
     */
    BOOST_DEFAULTED_FUNCTION(block_on_overflow(), {})

    /*!
     * This method is called by the queue when overflow is detected.
     *
     * \param lock An internal lock that protects the queue
     *
     * \retval true Attempt to enqueue the record again.
     * \retval false Discard the record.
     */
    template< typename LockT >
    bool on_overflow(record_view const&, LockT& lock)
    {
        thread_context context;
        m_thread_contexts.push_back(context);
        do
        {
            context.cond.wait(lock);
        }
        while (context.is_linked());

        return context.result;
    }

    /*!
     * This method is called by the queue when there appears a free space.
     * The internal lock protecting the queue is locked when calling this method.
     */
    void on_queue_space_available()
    {
        if (!m_thread_contexts.empty())
        {
            m_thread_contexts.front().cond.notify_one();
            m_thread_contexts.pop_front();
        }
    }

    /*!
     * This method is called by the queue to interrupt any possible waits in \c on_overflow.
     * The internal lock protecting the queue is locked when calling this method.
     */
    void interrupt()
    {
        while (!m_thread_contexts.empty())
        {
            thread_context& context = m_thread_contexts.front();
            context.result = false;
            context.cond.notify_one();
            m_thread_contexts.pop_front();
        }
    }

    //  Copying prohibited
    BOOST_DELETED_FUNCTION(block_on_overflow(block_on_overflow const&))
    BOOST_DELETED_FUNCTION(block_on_overflow& operator= (block_on_overflow const&))
#endif // BOOST_LOG_DOXYGEN_PASS
};

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_BLOCK_ON_OVERFLOW_HPP_INCLUDED_

/* block_on_overflow.hpp
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
*/