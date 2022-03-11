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