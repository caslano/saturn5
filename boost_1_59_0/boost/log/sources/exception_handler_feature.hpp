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
#include <boost/type_traits/is_nothrow_move_constructible.hpp>
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
        boost::log::aux::multiple_unique_lock2< threading_model, threading_model >
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
    basic_exception_handler_logger(BOOST_RV_REF(basic_exception_handler_logger) that) BOOST_NOEXCEPT_IF(boost::is_nothrow_move_constructible< base_type >::value && boost::is_nothrow_move_constructible< exception_handler_type >::value) :
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