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
    bool will_consume(attribute_value_set const& attrs)
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
            m_Version(0),
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
    volatile unsigned int m_Version;

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
        , m_Version(0)
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
        ++m_Version;
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
        ++m_Version;
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
        ++m_Version;
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
        if (!context || context->m_Version != m_Version)
        {
            {
                boost::log::aux::shared_lock_guard< mutex_type > lock(this->frontend_mutex());
                context = new formatting_context(m_Version, m_Locale, m_Formatter);
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