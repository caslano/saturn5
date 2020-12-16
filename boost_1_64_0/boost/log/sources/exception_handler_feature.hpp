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
Ir80GWi/TOItZznyu1nf5XaixtOW3vTXi0+O1PdOwORT5aVUNihQtiThfJGzc/oS4xlOlK1+NEyP+g+Ue3pf7GqdaaRiAb6XOq2t9fFmg/ooLAMSTgf4e7G/nnaCDarcVifWcIoIx/6cfrNB/VUYma/jYnc5OQ9z5lGHS5xWQe/2+v02cTeF8hpgniMfi9k59NnRmOMOXRspx6lOJ8Lp4yQTD26NeYWYj0YtdNrK+uI0+lUmdXjAt744nQX4dNatvOGx3jDklmI94cjgdECaqWdMj8hWsa3DI2NjvTH1z6eCArec5Yjz/TLtXeu/HSxm9Wszp4s+RtuvX3869ZvuDMSdS2Yr3y2nO0TcZVI2Xc34vEzM2qobf1hnUZIjCR83xiybGLvJzZo2WfNF4qZ7cBrlXSTUPkR7dD8f0dvGXdpag3c52k3w/YnZjvwm63v2JNQxn6zK+e4+Jd3J3ZeMbNr3xB2ya/Z+RDgN+pFpUw+L3UBaTpSt/+C3cXn/R8Wuj3zL0NJnjN/G2s8zYp9I2FGm/fwuqP0cEH2Uth+/vh9pa+N0Pkn7eU7cdSJdUab9HHa3HxNWX+oiXduP36w/vmIpE3v7eVXcpAanMeS70xppOyp/al9/2jPW7NfLb5A+r+NWmDZSWV1dXFir73S2cx0dxG1/WxvRcDyNvh/GwyRx08ey/6brtGKfGvLavO25v2dcoLxTOurlYciDmHwWr63KryhyGpmXlIm7OFseCSN4DJeFZtNm5oh9G2rSvrat/gPWLxrPa5otr4HrPxJ/0Fn48WYvhVGbAtP8bw3K/9CA/BeYPvk1cTfe6WqXJdZwPI3Kud4s9qc7iVY5YuPfKst6t9gNwc5j2ze2no1ovF0UBJaVplPmItpWdk/SM4OeOnaAOaMZO4PKKq+0ora4uiKftho4f9d6/1WZvA+aOVoX0V/FiOpp9F7/Y/ZyNPIGJ8R+Rt0KotNK5B5aG3+Xy+2TplzVPFg+O1H71UJJzzRCSmBHoZVZr/qmmJ9rxiGnXOQ41N6vD7eeCbhD/Ga569H041fEzmPC/bnoB5s8LBb9HpkZB8p9axsS+2WNyn1/S+x7mPD3iT6sUZnv74p9qj6zxL1+9ze1UZnvx8RNV9WrH5X5fpU+1meSyp1G95bnvt88228eNlvM9Tvj7OXVqTjs7oxr3v3bF568PZuxr2qyuddMfsN0jM8t1/Ys8rt5DcY+M36JuwGsGITbx7/y+r2DPeRzwGTNK4lSWWSV323yLpSpTZ03S8upc5ikHhI1L7v8eaFTltZqPoJl48RNe1se8P/53i0TdB3hkNxRU1FaVuDep9IP+fHL1fWMmTru7jfpXWMePDb5jR+Iu6nEy0zMPmYQViNjhvabF8V+An7DnW7W90sThsjvpFPGWVNUfqcj83jW15HgiRnIQrs3Cn1YRJPyO/6x+zfadlo7YdIWmjdW59va9pd6r+u3uNcV88lPfv9rm/8Yvelvce9tumdm33/9va7/b/e32u+x/XLudd3myE/2O5fCnWEieyF/v+3IuQ75+086N1sKczyypy1/f4z7g2ruhMvYJ3+/hvmjan4dar/+fWOY7F3JvTp3eek76n4v6oC6aYOb4zDLf58U7Opgp31+gKb5p2HOBh8PwtbwZdgF/gweh5nmnif6ufoPQ6Wr/xPq/6+wFfxA/WWjDqq/kZa7Nr+v/p6DyfB5OAy+AEfAAyYcvccIdrKEc1TD+RMMh+/DGHhMw/2zCQd1knDe0nAOazjvaDi/03DeNeHgV8PpbQlnm4ZzI+wJvwbTVd9L9ceh49H7XvT+m6W6L3RCw3nNUxf/W7ALfBvOhO/A2TCSqx3nqXkePAI=
*/