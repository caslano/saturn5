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
9KVvUh4lnsZ982GsO0uzp0eP+aINukIHMM3iWF+xgsJaQsflIaIhxr3LtbgOtxTrceraummRItXSWNTzqCWuWm3cr07lMaTvRGUrQdkaUfpjtrKwyXJPv43a9mvMfZ+RayFSqc0etvYWSz3OehQgH2O961G+l5HvAMr3WZtBXyjzfZfyeAV53i/3Lbamc9XQ/iGqcjxNdKc8U4SP6MLxsAqD/FZrdUWuFsTrER6k/MZYg9FKb3sMNK5tkONkA+Xf0LW8hjYZL8v3OuUXrlUR3ppDhz7uE92vlczvC6pfJI6N7Wx1zV/q5ztQ/L2Gdp4iz1ed4n4i/MQhmX99KkM7ZX4Xkd9Iym+tIb9RMr/Pz9OaCq2qqKY58qtK+YWq8iP7EC0ovyOG/kqXa4geprCatv7QVFTDGLto8RKVrDPEGqtPufwStGF+fdjWw75Iu673dmn3QS3P+uL+g0HwaqRdxtcS4g3IOfgVgFfAtDAiybpgCO+v34/4P4IOnXJhLQhYxHvvOR8qQ14te7yrMj7FARGH/fh8EEqDYyIf03mNcaT/G6zLdpT5BxDlQN0QzufYAkGbwI/qyX5lv/MYXoF9gJ00BsXEvNFTXPa18jMDft4u6zeqyONclV0AxGnl14D6Do+aRPGn6tJ7kS79mXW7nvxr7ot7njic+fknyfu+NXXp8/6HdOnFHvwc5vegZHAK5LiHIBfAutowsCvYBBzHuthc/p2sibzPuJB11Yv4d7NW8n7j1WAn1iF35n2r3Xi/anfwNdZpH+V9xp+yrvoL3mcsNLuuuho4GAwB54Ited/vreASMAdcDs4HV+rnBR8AN4MPgW+Bq8FT4GPgD+DjvH/4ad43vBGsCW4C64PPg43AF8DG4ItgUwvv4wV3gingS+AscDe4AtwDbgD3gzvAA+Au8KBeX/Bv4Ifgm+A58Bj4JXhOLw+YhBdQqwf6A/QDU8AAMBUMB9PBSHA0WB88hXStwI/BAeBZMMXDnl8WeB7MA38E54O/gMvBX8GNoIZ8doIe4CE+TxGf5wSf5wzoCZaA3uAV0AesbBWiMlgDDARbgEHgADAMzAKjwZlgLLgGbA5uAePBrWAL8CWwFfgOh38Etge/ATuCwoZxBAaD+nE42BVMBLvr5wN76OcDe4HzwQbgSjBBPy/YElwP6vuonwHPgVvB8+B2cCT4FpgMXgRHgd6eGHf6+cDbwVhwKNgPbIrwwWAzcDgYA6aCceAksDl4DxgPLgP1dlwB1sDxWjAcXA/WBDeBtcBtYAT4JlgHfAeMBM+ADcFizucCWB/Hl/j4S7ABjj287PHwPUP+a0yd/X+0zr54/h+ro/8j3Z/1/X8j9P/69/9rkbhm+ft/FT/jXtTsdvtXgz/hj31nHN//OLGTTaU85Xc74rt+t0sbPhcpbIam+GZHOuW3Nr3zF+Cd/yqF36055gBK6LgHnr0W1bc78nNvn24y8hPv6+ETNMP3dp7RtkwxpR+KZ7BFzjs0ojSxmkVUlrbrRnwAPz4Olsc+hvOmZAqD7adSyjdXKwvPSkE9pb2Z4XSOc+jT+Vjj1Fbam+lK+frhWH5XZ+Uafq/8JKWLxxdpGNUxF3XsQX5NyAbeT1GUhtpqOsKcvjs5j2covk2uUd5Mx11FTeTZGuthqzrbXaJ1xgcj8Q0KeYnXHR9iHgbXGewxLVd/L3TxozHVmr6NqwuNvh36fODOvl2e63eD0hYO4lAdUWf4FTj97nyEpyC3FdKC10xeSsR4onMW2i+wpOycvCzqN/taZCuNd/n97/2hHvcBjL4I1TXAeWmU9nIYXwPcphZK21K5btmYjm3Pyf79hcJ6Y7xXUo13mfYmWV4aH3Jd/Vw=
*/