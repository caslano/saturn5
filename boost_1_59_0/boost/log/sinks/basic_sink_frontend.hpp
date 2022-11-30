/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   basic_sink_frontend.hpp
 * \author Andrey Semashev
 * \date   14.07.2009
 *
 * The header contains implementation of a base class for sink frontends.
 */

#ifndef BOOST_LOG_SINKS_BASIC_SINK_FRONTEND_HPP_INCLUDED_
#define BOOST_LOG_SINKS_BASIC_SINK_FRONTEND_HPP_INCLUDED_

#include <boost/mpl/bool.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/code_conversion.hpp>
#include <boost/log/detail/attachable_sstream_buf.hpp>
#include <boost/log/detail/fake_mutex.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/sinks/sink.hpp>
#include <boost/log/sinks/frontend_requirements.hpp>
#include <boost/log/expressions/filter.hpp>
#include <boost/log/expressions/formatter.hpp>
#if !defined(BOOST_LOG_NO_THREADS)
#include <boost/memory_order.hpp>
#include <boost/atomic/atomic.hpp>
#include <boost/thread/exceptions.hpp>
#include <boost/thread/tss.hpp>
#include <boost/log/detail/locks.hpp>
#include <boost/log/detail/light_rw_mutex.hpp>
#endif // !defined(BOOST_LOG_NO_THREADS)
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

//! A base class for a logging sink frontend
class BOOST_LOG_NO_VTABLE basic_sink_frontend :
    public sink
{
    //! Base type
    typedef sink base_type;

public:
    //! An exception handler type
    typedef base_type::exception_handler_type exception_handler_type;

#if !defined(BOOST_LOG_NO_THREADS)
protected:
    //! Mutex type
    typedef boost::log::aux::light_rw_mutex mutex_type;

private:
    //! Synchronization mutex
    mutable mutex_type m_Mutex;
#endif

private:
    //! Filter
    filter m_Filter;
    //! Exception handler
    exception_handler_type m_ExceptionHandler;

public:
    /*!
     * \brief Initializing constructor
     *
     * \param cross_thread The flag indicates whether the sink passes log records between different threads
     */
    explicit basic_sink_frontend(bool cross_thread) : sink(cross_thread)
    {
    }

    /*!
     * The method sets sink-specific filter functional object
     */
    template< typename FunT >
    void set_filter(FunT const& filter)
    {
        BOOST_LOG_EXPR_IF_MT(boost::log::aux::exclusive_lock_guard< mutex_type > lock(m_Mutex);)
        m_Filter = filter;
    }
    /*!
     * The method resets the filter
     */
    void reset_filter()
    {
        BOOST_LOG_EXPR_IF_MT(boost::log::aux::exclusive_lock_guard< mutex_type > lock(m_Mutex);)
        m_Filter.reset();
    }

    /*!
     * The method sets an exception handler function
     */
    template< typename FunT >
    void set_exception_handler(FunT const& handler)
    {
        BOOST_LOG_EXPR_IF_MT(boost::log::aux::exclusive_lock_guard< mutex_type > lock(m_Mutex);)
        m_ExceptionHandler = handler;
    }

    /*!
     * The method resets the exception handler function
     */
    void reset_exception_handler()
    {
        BOOST_LOG_EXPR_IF_MT(boost::log::aux::exclusive_lock_guard< mutex_type > lock(m_Mutex);)
        m_ExceptionHandler.clear();
    }

    /*!
     * The method returns \c true if no filter is set or the attribute values pass the filter
     *
     * \param attrs A set of attribute values of a logging record
     */
    bool will_consume(attribute_value_set const& attrs) BOOST_OVERRIDE
    {
        BOOST_LOG_EXPR_IF_MT(boost::log::aux::shared_lock_guard< mutex_type > lock(m_Mutex);)
        try
        {
            return m_Filter(attrs);
        }
#if !defined(BOOST_LOG_NO_THREADS)
        catch (thread_interrupted&)
        {
            throw;
        }
#endif
        catch (...)
        {
            if (m_ExceptionHandler.empty())
                throw;
            m_ExceptionHandler();
            return false;
        }
    }

protected:
#if !defined(BOOST_LOG_NO_THREADS)
    //! Returns reference to the frontend mutex
    mutex_type& frontend_mutex() const { return m_Mutex; }
#endif

    //! Returns reference to the exception handler
    exception_handler_type& exception_handler() { return m_ExceptionHandler; }
    //! Returns reference to the exception handler
    exception_handler_type const& exception_handler() const { return m_ExceptionHandler; }

    //! Feeds log record to the backend
    template< typename BackendMutexT, typename BackendT >
    void feed_record(record_view const& rec, BackendMutexT& backend_mutex, BackendT& backend)
    {
        try
        {
            BOOST_LOG_EXPR_IF_MT(boost::log::aux::exclusive_lock_guard< BackendMutexT > lock(backend_mutex);)
            backend.consume(rec);
        }
#if !defined(BOOST_LOG_NO_THREADS)
        catch (thread_interrupted&)
        {
            throw;
        }
#endif
        catch (...)
        {
            BOOST_LOG_EXPR_IF_MT(boost::log::aux::shared_lock_guard< mutex_type > lock(m_Mutex);)
            if (m_ExceptionHandler.empty())
                throw;
            m_ExceptionHandler();
        }
    }

    //! Attempts to feeds log record to the backend, does not block if \a backend_mutex is locked
    template< typename BackendMutexT, typename BackendT >
    bool try_feed_record(record_view const& rec, BackendMutexT& backend_mutex, BackendT& backend)
    {
#if !defined(BOOST_LOG_NO_THREADS)
        try
        {
            if (!backend_mutex.try_lock())
                return false;
        }
        catch (thread_interrupted&)
        {
            throw;
        }
        catch (...)
        {
            boost::log::aux::shared_lock_guard< mutex_type > frontend_lock(this->frontend_mutex());
            if (this->exception_handler().empty())
                throw;
            this->exception_handler()();
            return false;
        }

        boost::log::aux::exclusive_auto_unlocker< BackendMutexT > unlocker(backend_mutex);
#endif
        // No need to lock anything in the feed_record method
        boost::log::aux::fake_mutex m;
        feed_record(rec, m, backend);
        return true;
    }

    //! Flushes record buffers in the backend, if one supports it
    template< typename BackendMutexT, typename BackendT >
    void flush_backend(BackendMutexT& backend_mutex, BackendT& backend)
    {
        typedef typename BackendT::frontend_requirements frontend_requirements;
        flush_backend_impl(backend_mutex, backend,
            typename has_requirement< frontend_requirements, flushing >::type());
    }

private:
    //! Flushes record buffers in the backend (the actual implementation)
    template< typename BackendMutexT, typename BackendT >
    void flush_backend_impl(BackendMutexT& backend_mutex, BackendT& backend, mpl::true_)
    {
        try
        {
            BOOST_LOG_EXPR_IF_MT(boost::log::aux::exclusive_lock_guard< BackendMutexT > lock(backend_mutex);)
            backend.flush();
        }
#if !defined(BOOST_LOG_NO_THREADS)
        catch (thread_interrupted&)
        {
            throw;
        }
#endif
        catch (...)
        {
            BOOST_LOG_EXPR_IF_MT(boost::log::aux::shared_lock_guard< mutex_type > lock(m_Mutex);)
            if (m_ExceptionHandler.empty())
                throw;
            m_ExceptionHandler();
        }
    }
    //! Flushes record buffers in the backend (stub for backends that don't support flushing)
    template< typename BackendMutexT, typename BackendT >
    void flush_backend_impl(BackendMutexT&, BackendT&, mpl::false_)
    {
    }
};

//! A base class for a logging sink frontend with formatting support
template< typename CharT >
class BOOST_LOG_NO_VTABLE basic_formatting_sink_frontend :
    public basic_sink_frontend
{
    typedef basic_sink_frontend base_type;

public:
    //! Character type
    typedef CharT char_type;
    //! Formatted string type
    typedef std::basic_string< char_type > string_type;

    //! Formatter function object type
    typedef basic_formatter< char_type > formatter_type;
    //! Output stream type
    typedef typename formatter_type::stream_type stream_type;

#if !defined(BOOST_LOG_NO_THREADS)
protected:
    //! Mutex type
    typedef typename base_type::mutex_type mutex_type;
#endif

private:
    struct formatting_context
    {
        class cleanup_guard
        {
        private:
            formatting_context& m_context;

        public:
            explicit cleanup_guard(formatting_context& ctx) BOOST_NOEXCEPT : m_context(ctx)
            {
            }

            ~cleanup_guard()
            {
                m_context.m_FormattedRecord.clear();
                m_context.m_FormattingStream.rdbuf()->max_size(m_context.m_FormattedRecord.max_size());
                m_context.m_FormattingStream.rdbuf()->storage_overflow(false);
                m_context.m_FormattingStream.clear();
            }

            BOOST_DELETED_FUNCTION(cleanup_guard(cleanup_guard const&))
            BOOST_DELETED_FUNCTION(cleanup_guard& operator=(cleanup_guard const&))
        };

#if !defined(BOOST_LOG_NO_THREADS)
        //! Object version
        const unsigned int m_Version;
#endif
        //! Formatted log record storage
        string_type m_FormattedRecord;
        //! Formatting stream
        stream_type m_FormattingStream;
        //! Formatter functor
        formatter_type m_Formatter;

        formatting_context() :
#if !defined(BOOST_LOG_NO_THREADS)
            m_Version(0u),
#endif
            m_FormattingStream(m_FormattedRecord)
        {
            m_FormattingStream.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        }
#if !defined(BOOST_LOG_NO_THREADS)
        formatting_context(unsigned int version, std::locale const& loc, formatter_type const& formatter) :
            m_Version(version),
            m_FormattingStream(m_FormattedRecord),
            m_Formatter(formatter)
        {
            m_FormattingStream.exceptions(std::ios_base::badbit | std::ios_base::failbit);
            m_FormattingStream.imbue(loc);
        }
#endif
    };

private:
#if !defined(BOOST_LOG_NO_THREADS)

    //! State version
    boost::atomic< unsigned int > m_Version;

    //! Formatter functor
    formatter_type m_Formatter;
    //! Locale to perform formatting
    std::locale m_Locale;

    //! Formatting state
    thread_specific_ptr< formatting_context > m_pContext;

#else

    //! Formatting state
    formatting_context m_Context;

#endif // !defined(BOOST_LOG_NO_THREADS)

public:
    /*!
     * \brief Initializing constructor
     *
     * \param cross_thread The flag indicates whether the sink passes log records between different threads
     */
    explicit basic_formatting_sink_frontend(bool cross_thread) :
        basic_sink_frontend(cross_thread)
#if !defined(BOOST_LOG_NO_THREADS)
        , m_Version(0u)
#endif
    {
    }

    /*!
     * The method sets sink-specific formatter function object
     */
    template< typename FunT >
    void set_formatter(FunT const& formatter)
    {
#if !defined(BOOST_LOG_NO_THREADS)
        boost::log::aux::exclusive_lock_guard< mutex_type > lock(this->frontend_mutex());
        m_Formatter = formatter;
        m_Version.opaque_add(1u, boost::memory_order_relaxed);
#else
        m_Context.m_Formatter = formatter;
#endif
    }
    /*!
     * The method resets the formatter
     */
    void reset_formatter()
    {
#if !defined(BOOST_LOG_NO_THREADS)
        boost::log::aux::exclusive_lock_guard< mutex_type > lock(this->frontend_mutex());
        m_Formatter.reset();
        m_Version.opaque_add(1u, boost::memory_order_relaxed);
#else
        m_Context.m_Formatter.reset();
#endif
    }

    /*!
     * The method returns the current locale used for formatting
     */
    std::locale getloc() const
    {
#if !defined(BOOST_LOG_NO_THREADS)
        boost::log::aux::exclusive_lock_guard< mutex_type > lock(this->frontend_mutex());
        return m_Locale;
#else
        return m_Context.m_FormattingStream.getloc();
#endif
    }
    /*!
     * The method sets the locale used for formatting
     */
    void imbue(std::locale const& loc)
    {
#if !defined(BOOST_LOG_NO_THREADS)
        boost::log::aux::exclusive_lock_guard< mutex_type > lock(this->frontend_mutex());
        m_Locale = loc;
        m_Version.opaque_add(1u, boost::memory_order_relaxed);
#else
        m_Context.m_FormattingStream.imbue(loc);
#endif
    }

protected:
    //! Returns reference to the formatter
    formatter_type& formatter()
    {
#if !defined(BOOST_LOG_NO_THREADS)
        return m_Formatter;
#else
        return m_Context.m_Formatter;
#endif
    }

    //! Feeds log record to the backend
    template< typename BackendMutexT, typename BackendT >
    void feed_record(record_view const& rec, BackendMutexT& backend_mutex, BackendT& backend)
    {
        formatting_context* context;

#if !defined(BOOST_LOG_NO_THREADS)
        context = m_pContext.get();
        if (!context || context->m_Version != m_Version.load(boost::memory_order_relaxed))
        {
            {
                boost::log::aux::shared_lock_guard< mutex_type > lock(this->frontend_mutex());
                context = new formatting_context(m_Version.load(boost::memory_order_relaxed), m_Locale, m_Formatter);
            }
            m_pContext.reset(context);
        }
#else
        context = &m_Context;
#endif

        typename formatting_context::cleanup_guard cleanup(*context);

        try
        {
            // Perform the formatting
            context->m_Formatter(rec, context->m_FormattingStream);
            context->m_FormattingStream.flush();

            // Feed the record
            BOOST_LOG_EXPR_IF_MT(boost::log::aux::exclusive_lock_guard< BackendMutexT > lock(backend_mutex);)
            backend.consume(rec, context->m_FormattedRecord);
        }
#if !defined(BOOST_LOG_NO_THREADS)
        catch (thread_interrupted&)
        {
            throw;
        }
#endif
        catch (...)
        {
            BOOST_LOG_EXPR_IF_MT(boost::log::aux::shared_lock_guard< mutex_type > lock(this->frontend_mutex());)
            if (this->exception_handler().empty())
                throw;
            this->exception_handler()();
        }
    }

    //! Attempts to feeds log record to the backend, does not block if \a backend_mutex is locked
    template< typename BackendMutexT, typename BackendT >
    bool try_feed_record(record_view const& rec, BackendMutexT& backend_mutex, BackendT& backend)
    {
#if !defined(BOOST_LOG_NO_THREADS)
        try
        {
            if (!backend_mutex.try_lock())
                return false;
        }
        catch (thread_interrupted&)
        {
            throw;
        }
        catch (...)
        {
            boost::log::aux::shared_lock_guard< mutex_type > frontend_lock(this->frontend_mutex());
            if (this->exception_handler().empty())
                throw;
            this->exception_handler()();
            return false;
        }

        boost::log::aux::exclusive_auto_unlocker< BackendMutexT > unlocker(backend_mutex);
#endif
        // No need to lock anything in the feed_record method
        boost::log::aux::fake_mutex m;
        feed_record(rec, m, backend);
        return true;
    }
};

namespace aux {

    template<
        typename BackendT,
        bool RequiresFormattingV = has_requirement<
            typename BackendT::frontend_requirements,
            formatted_records
        >::value
    >
    struct make_sink_frontend_base
    {
        typedef basic_sink_frontend type;
    };
    template< typename BackendT >
    struct make_sink_frontend_base< BackendT, true >
    {
        typedef basic_formatting_sink_frontend< typename BackendT::char_type > type;
    };

} // namespace aux

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_BASIC_SINK_FRONTEND_HPP_INCLUDED_

/* basic_sink_frontend.hpp
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
*/