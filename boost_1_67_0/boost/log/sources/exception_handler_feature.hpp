/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   exception_handler_feature.hpp
 * \author Andrey Semashev
 * \date   17.07.2009
 *
 * The header contains implementation of an exception handler support feature.
 */

#ifndef BOOST_LOG_SOURCES_EXCEPTION_HANDLER_FEATURE_HPP_INCLUDED_
#define BOOST_LOG_SOURCES_EXCEPTION_HANDLER_FEATURE_HPP_INCLUDED_

#include <boost/mpl/if.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/light_function.hpp>
#include <boost/log/detail/locks.hpp>
#include <boost/log/core/record.hpp>
#include <boost/log/sources/threading_models.hpp>
#include <boost/log/utility/strictest_lock.hpp>
#if !defined(BOOST_LOG_NO_THREADS)
#include <boost/thread/exceptions.hpp>
#endif
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sources {

/*!
 * \brief Exception handler feature implementation
 */
template< typename BaseT >
class basic_exception_handler_logger :
    public BaseT
{
    //! Base type
    typedef BaseT base_type;
    typedef basic_exception_handler_logger this_type;
    BOOST_COPYABLE_AND_MOVABLE_ALT(this_type)

public:
    //! Threading model being used
    typedef typename base_type::threading_model threading_model;
    //! Final logger type
    typedef typename base_type::final_type final_type;
    //! Exception handler function type
    typedef boost::log::aux::light_function< void () > exception_handler_type;

#if defined(BOOST_LOG_DOXYGEN_PASS)
    //! Lock requirement for the open_record_unlocked method
    typedef typename strictest_lock<
        typename base_type::open_record_lock,
        no_lock< threading_model >
    >::type open_record_lock;
    //! Lock requirement for the push_record_unlocked method
    typedef typename strictest_lock<
        typename base_type::push_record_lock,
        no_lock< threading_model >
    >::type push_record_lock;
#endif // defined(BOOST_LOG_DOXYGEN_PASS)

    //! Lock requirement for the swap_unlocked method
    typedef typename strictest_lock<
        typename base_type::swap_lock,
#ifndef BOOST_LOG_NO_THREADS
        boost::log::aux::exclusive_lock_guard< threading_model >
#else
        no_lock< threading_model >
#endif // !defined(BOOST_LOG_NO_THREADS)
    >::type swap_lock;

private:
    //! Exception handler
    exception_handler_type m_ExceptionHandler;

public:
    /*!
     * Default constructor. The constructed logger does not have an exception handler.
     */
    basic_exception_handler_logger() : base_type()
    {
    }
    /*!
     * Copy constructor
     */
    basic_exception_handler_logger(basic_exception_handler_logger const& that) :
        base_type(static_cast< base_type const& >(that)),
        m_ExceptionHandler(that.m_ExceptionHandler)
    {
    }
    /*!
     * Move constructor
     */
    basic_exception_handler_logger(BOOST_RV_REF(basic_exception_handler_logger) that) :
        base_type(boost::move(static_cast< base_type& >(that))),
        m_ExceptionHandler(boost::move(that.m_ExceptionHandler))
    {
    }
    /*!
     * Constructor with arguments. Passes arguments to other features.
     */
    template< typename ArgsT >
    explicit basic_exception_handler_logger(ArgsT const& args) :
        base_type(args)
    {
    }

    /*!
     * The method sets exception handler function. The function will be called with no arguments
     * in case if an exception occurs during either \c open_record or \c push_record method
     * execution. Since exception handler is called from a \c catch statement, the exception
     * can be rethrown in order to determine its type.
     *
     * By default no handler is installed, thus any exception is propagated as usual.
     *
     * \sa <tt>utility/exception_handler.hpp</tt>
     * \param handler Exception handling function
     *
     * \note The exception handler can be invoked in several threads concurrently.
     *
     * \note Thread interruptions are not affected by exception handlers.
     */
    template< typename HandlerT >
    void set_exception_handler(HandlerT const& handler)
    {
#ifndef BOOST_LOG_NO_THREADS
        boost::log::aux::exclusive_lock_guard< threading_model > lock(this->get_threading_model());
#endif
        m_ExceptionHandler = handler;
    }

protected:
    /*!
     * Unlocked \c open_record
     */
    template< typename ArgsT >
    record open_record_unlocked(ArgsT const& args)
    {
        try
        {
            return base_type::open_record_unlocked(args);
        }
#ifndef BOOST_LOG_NO_THREADS
        catch (thread_interrupted&)
        {
            throw;
        }
#endif
        catch (...)
        {
            handle_exception();
            return record();
        }
    }

    /*!
     * Unlocked \c push_record
     */
    void push_record_unlocked(BOOST_RV_REF(record) rec)
    {
        try
        {
            base_type::push_record_unlocked(boost::move(rec));
        }
#ifndef BOOST_LOG_NO_THREADS
        catch (thread_interrupted&)
        {
            throw;
        }
#endif
        catch (...)
        {
            handle_exception();
        }
    }

    /*!
     * Unlocked swap
     */
    void swap_unlocked(basic_exception_handler_logger& that)
    {
        base_type::swap_unlocked(static_cast< base_type& >(that));
        m_ExceptionHandler.swap(that.m_ExceptionHandler);
    }

private:
#if !defined(BOOST_LOG_DOXYGEN_PASS)
    //! The function handles the intercepted exception
    void handle_exception()
    {
#ifndef BOOST_LOG_NO_THREADS
        // Here's the trick with the lock type. Since the lock
        // is only needed when an exception is caught, we indicate
        // no locking requirements in the push_record_lock type.
        // However, if other features don't require locking either,
        // we shall acquire a read lock here, when an exception is caught.
        // If other features do require locking, the thread model is
        // already locked by now, and we don't do locking at all.
        typedef typename mpl::if_<
            is_same< no_lock< threading_model >, typename final_type::push_record_lock >,
            boost::log::aux::shared_lock_guard< threading_model >,
            no_lock< threading_model >
        >::type lock_type;
        lock_type lock(base_type::get_threading_model());
#endif // !defined(BOOST_LOG_NO_THREADS)

        if (m_ExceptionHandler.empty())
            throw;
        m_ExceptionHandler();
    }
#endif // !defined(BOOST_LOG_DOXYGEN_PASS)
};

/*!
 * \brief Exception handler support feature
 *
 * The logger with this feature will provide an additional method to
 * install an exception handler functional object. This functional
 * object will be called if during either opening or pushing a record
 * an exception is thrown from the logging core.
 */
struct exception_handler
{
    template< typename BaseT >
    struct apply
    {
        typedef basic_exception_handler_logger< BaseT > type;
    };
};

} // namespace sources

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SOURCES_EXCEPTION_HANDLER_FEATURE_HPP_INCLUDED_

/* exception_handler_feature.hpp
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
*/