/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   exception_handler.hpp
 * \author Andrey Semashev
 * \date   12.07.2009
 *
 * This header contains tools for exception handlers support in different parts of the library.
 */

#ifndef BOOST_LOG_UTILITY_EXCEPTION_HANDLER_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_EXCEPTION_HANDLER_HPP_INCLUDED_

#include <new> // std::nothrow_t
#include <boost/mpl/bind.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/utility/functional/nop.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#ifndef BOOST_LOG_MAX_EXCEPTION_TYPES
//! Maximum number of exception types that can be specified for exception handlers
#define BOOST_LOG_MAX_EXCEPTION_TYPES 10
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_exception_types, exception_types, false)

//! Root class for the exception handler class hierarchy
template< typename HandlerT >
class eh_root
{
public:
    //! The exception handler type
    typedef HandlerT handler_type;
    //! The handler result type
    typedef void result_type;

protected:
    //! Exception handler
    handler_type m_Handler;

public:
    //! Initializing constructor
    explicit eh_root(handler_type const& handler) : m_Handler(handler)
    {
    }

    //! Exception launcher
    void operator()() const
    {
        throw;
    }
};

//! A cons-list element of the exception handler class hierarchy
template< typename ExceptionT, typename BaseT >
class eh_cons :
    public BaseT
{
    //! Base type
    typedef BaseT base_type;

public:
    //! The exception handler type
    typedef typename base_type::handler_type handler_type;

public:
    //! Initializing constructor
    explicit eh_cons(handler_type const& handler) : base_type(handler)
    {
    }

    //! Exception launcher
    void operator()() const
    {
        try
        {
            base_type::operator()();
        }
        catch (ExceptionT& e)
        {
            this->m_Handler(e);
        }
    }
};

template< template< typename, typename > class EHT, typename HandlerT >
struct make_self_contained_exception_handler
{
    typedef EHT< typename HandlerT::exception_types, HandlerT > type;
};

} // namespace aux

/*!
 * An exception handler functional object. The handler aggregates a user-defined
 * functional object that will be called when one of the specified exception types
 * is caught.
 */
template< typename SequenceT, typename HandlerT >
class exception_handler :
    public mpl::fold<
        SequenceT,
        aux::eh_root< HandlerT >,
        mpl::bind< mpl::quote2< aux::eh_cons >, mpl::_2, mpl::_1 >
    >::type
{
    //! Base type
    typedef typename mpl::fold<
        SequenceT,
        aux::eh_root< HandlerT >,
        mpl::bind< mpl::quote2< aux::eh_cons >, mpl::_2, mpl::_1 >
    >::type base_type;

public:
#ifndef BOOST_LOG_DOXYGEN_PASS
    typedef typename base_type::handler_type handler_type;
#else
    //! The exception handler type
    typedef HandlerT handler_type;
    //! The handler result type
    typedef void result_type;
#endif

public:
    /*!
     * Initializing constructor. Creates an exception handler with the specified
     * function object that will receive the exception.
     */
    explicit exception_handler(handler_type const& handler) : base_type(handler)
    {
    }

    /*!
     * Exception launcher. Rethrows the current exception in order to detect its type
     * and pass it to the aggregated function object.
     *
     * \note Must be called from within a \c catch statement.
     */
    void operator()() const
    {
        base_type::operator()();
    }
};

/*!
 * A no-throw exception handler functional object. Acts similar to \c exception_handler,
 * but in case if the exception cannot be handled the exception is not propagated
 * from the handler. Instead the user-defined functional object is called with
 * no parameters.
 */
template< typename SequenceT, typename HandlerT >
class nothrow_exception_handler :
    public exception_handler< SequenceT, HandlerT >
{
    //! Base type
    typedef exception_handler< SequenceT, HandlerT > base_type;

public:
#ifndef BOOST_LOG_DOXYGEN_PASS
    typedef typename base_type::handler_type handler_type;
#else
    //! The exception handler type
    typedef HandlerT handler_type;
    //! The handler result type
    typedef void result_type;
#endif

public:
    /*!
     * Initializing constructor. Creates an exception handler with the specified
     * function object that will receive the exception.
     */
    explicit nothrow_exception_handler(handler_type const& handler) : base_type(handler)
    {
    }

    /*!
     * Exception launcher. Rethrows the current exception in order to detect its type
     * and pass it to the aggregated function object. If the type of the exception
     * could not be detected, the user-defined handler is called with no arguments.
     *
     * \note Must be called from within a \c catch statement.
     */
    void operator()() const
    {
        try
        {
            base_type::operator()();
        }
        catch (...)
        {
            this->m_Handler();
        }
    }
};

/*!
 * The function creates an empty exception handler that effectively suppresses any exception
 */
inline nop make_exception_suppressor()
{
    return nop();
}

#ifndef BOOST_LOG_DOXYGEN_PASS

template< typename HandlerT >
inline typename boost::lazy_enable_if_c<
    aux::has_exception_types< HandlerT >::value,
    aux::make_self_contained_exception_handler< exception_handler, HandlerT >
>::type make_exception_handler(HandlerT const& handler)
{
    typedef typename aux::make_self_contained_exception_handler< exception_handler, HandlerT >::type eh_t;
    return eh_t(handler);
}

template< typename HandlerT >
inline typename boost::lazy_enable_if_c<
    aux::has_exception_types< HandlerT >::value,
    aux::make_self_contained_exception_handler< nothrow_exception_handler, HandlerT >
>::type make_exception_handler(HandlerT const& handler, std::nothrow_t const&)
{
    typedef typename aux::make_self_contained_exception_handler< nothrow_exception_handler, HandlerT >::type eh_t;
    return eh_t(handler);
}

#define BOOST_LOG_MAKE_EXCEPTION_HANDLER_INTERNAL(z, n, data)\
    template< BOOST_PP_ENUM_PARAMS(n, typename T), typename HandlerT >\
    inline exception_handler<\
        BOOST_PP_CAT(mpl::vector, n)< BOOST_PP_ENUM_PARAMS(n, T) >,\
        HandlerT\
    > make_exception_handler(HandlerT const& handler)\
    {\
        typedef exception_handler<\
            BOOST_PP_CAT(mpl::vector, n)< BOOST_PP_ENUM_PARAMS(n, T) >,\
            HandlerT\
        > eh_t;\
        return eh_t(handler);\
    }\
    template< BOOST_PP_ENUM_PARAMS(n, typename T), typename HandlerT >\
    inline nothrow_exception_handler<\
        BOOST_PP_CAT(mpl::vector, n)< BOOST_PP_ENUM_PARAMS(n, T) >,\
        HandlerT\
    > make_exception_handler(HandlerT const& handler, std::nothrow_t const&)\
    {\
        typedef nothrow_exception_handler<\
            BOOST_PP_CAT(mpl::vector, n)< BOOST_PP_ENUM_PARAMS(n, T) >,\
            HandlerT\
        > eh_t;\
        return eh_t(handler);\
    }

BOOST_PP_REPEAT_FROM_TO(1, BOOST_LOG_MAX_EXCEPTION_TYPES, BOOST_LOG_MAKE_EXCEPTION_HANDLER_INTERNAL, ~)

#undef BOOST_LOG_MAKE_EXCEPTION_HANDLER_INTERNAL

#else // BOOST_LOG_DOXYGEN_PASS

/*!
 * The function creates an exception handler functional object. The handler will call to the
 * user-specified functional object with an exception as its argument.
 *
 * \param handler User-defined functional object that will receive exceptions.
 * \return A nullary functional object that should be called from within a \c catch statement.
 *
 * \note This form requires the user-defined functional object to have an \c exception_types
 *       nested type. This type should be an MPL sequence of all expected exception types.
 */
template< typename HandlerT >
exception_handler< typename HandlerT::exception_types, HandlerT >
make_exception_handler(HandlerT const& handler);

/*!
 * The function creates an exception handler functional object. The handler will call to the
 * user-specified functional object with an exception as its argument. If the exception type
 * cannot be identified, the handler will call the user-defined functor with no arguments,
 * instead of propagating exception to the caller.
 *
 * \overload
 *
 * \param handler User-defined functional object that will receive exceptions.
 * \return A nullary functional object that should be called from within a \c catch statement.
 *
 * \note This form requires the user-defined functional object to have an \c exception_types
 *       nested type. This type should be an MPL sequence of all expected exception types.
 */
template< typename HandlerT >
nothrow_exception_handler< typename HandlerT::exception_types, HandlerT >
make_exception_handler(HandlerT const& handler, std::nothrow_t const&);

/*!
 * The function creates an exception handler functional object. The handler will call to the
 * user-specified functional object with an exception as its argument. All expected exception
 * types should be specified as first template parameters explicitly, in the order they would
 * be specified in a corresponding <tt>try/catch</tt> statement.
 *
 * \overload
 *
 * \param handler User-defined functional object that will receive exceptions.
 * \return A nullary functional object that should be called from within a \c catch statement.
 */
template< typename... ExceptionsT, typename HandlerT >
exception_handler< MPL_sequence_of_ExceptionsT, HandlerT >
make_exception_handler(HandlerT const& handler);

/*!
 * The function creates an exception handler functional object. The handler will call to the
 * user-specified functional object with an exception as its argument. If the exception type
 * cannot be identified, the handler will call the user-defined functor with no arguments,
 * instead of propagating exception to the caller. All expected exception types should be
 * specified as first template parameters explicitly, in the order they would be specified in
 * a corresponding <tt>try/catch</tt> statement.
 *
 * \overload
 *
 * \param handler User-defined functional object that will receive exceptions.
 * \return A nullary functional object that should be called from within a \c catch statement.
 */
template< typename... ExceptionsT, typename HandlerT >
nothrow_exception_handler< MPL_sequence_of_ExceptionsT, HandlerT >
make_exception_handler(HandlerT const& handler, std::nothrow_t const&);

#endif // BOOST_LOG_DOXYGEN_PASS

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_EXCEPTION_HANDLER_HPP_INCLUDED_

/* exception_handler.hpp
ntgTe2JP7Ik9sefn+fwkv/8LJ/7qSPz+D/2G7+i6/791Tf6R9WvWguEH8PgWrH0dDN+5TcAR92wWhrSOOdf/V7kv2rY/Wv0IuNyWTHa7LRK3KeYcSaOvQ/qB1j30xi9zdoV7Cl1+tRe3yWaf+YSvRG/utnhC3CcFeuHbfELYQ7iWMygmnAwTDumfWDq1xH0OWvyuYe62XC9uOgRbsat8JinfgLKcWRG/7XcF6N0Dkh8tbedXjNvMw/c0Ti2ZXFA6YeK4Mvf56cZfhuw9r3q+vC75km7OTvYXee+4o4w/k6ZyEMXk216RTzNxSvgbetKTIfc+8oj8hmD/wABJx7R4OS9DYRSb/BkmbuLMudC+kl+fB2oFriT+mKGbJ3a+chqxgvonvVdyA96fIXZ7BG3ndG6SsFuqnlukRZ/kmLsZJR7sXXDdzfi6+Nc4UJOzsd84DSVvPyUc13cYikpd92tvkDLoHqzrJASbBZNM2CXiT1tzhv4jsXd7XEunKC4U92X4uVXMnnblLXWnYIrJl5vEj8N3LLUS/bGm7HZKek6TvFgRymrR/yZ4OK6lkr7M8F3aEt76uPHBL53lcYnmHGu25G2COR+9Wuy9EZfhqjsFY0pGTxk7wWmgYT8l9etbpyf1+re43e0km7tdnxHZ5nhXPEjY4TO8t0t4M8xZ4XUS3qq4nsEpAVuctuNnudhZGXe4DlEOxZSdnvn8o+RN30AqpVqf+jHOWYlbZKbuZIpfy/HrBrH7z4CJn97RGc73+WL/KHXPHi/RNzH5vlTiUmJtM6/h/5Mi3/ZDXH8o1xx3m2sm4Z8RrOje2O/g7ve6if141VPbRR+UNraW8DqJflgwqHXb3MtaMMWkYY/UjYtNGMhNnDJgU0ljA9UfzrNkY/8iU17tRPYRMUjDBmamvL53UuWc2x/d4Zi01IMtxJ6eoTbhxLvsT8pxp/0hkdc9LKfcJ7v8O1fkXaz+NZOxoCwXyH0Y4fNIg8XOKXr3qp5dE7M0tRcQe+IXqckUewGxV6zhpfGfK6+LmCM17TT3a42z9l39Rd/amcVcduNQWGlyLwVK7p0Q/bf6TRXr99j1WyxjG4jijGmEErdvNmXuFxXielR5iI3Ef/k713UPeH4l9+1RH+337elYrucS1Ywx2vsNdR1rMyPurTDjYtT7Kz7V+0vrar/s/u65fR6/+ueAqjtv/itZD/jdqjlDWvYZ83StXWd982pOwdLqnyeq7nfY7esH0c5DVf9ckv0cWfXXIap7Lsm+jlL9c2r2c2TRz20ddHji9L1I31+nw/NRX5Lm8J6uWvAu2BUugoPh3XA4fCh0hgU+iH56SA9nwifhTfAp+BBcDh9V+0/AZ3Rv7wr4OlwJd8Ln4ftwFfwcroZ/U3d/hy/qHt+XYC34MqwP18LWcB3Mg6/A0+DrcAJ8E86EG+HtcBO8G26GK+BWuBb+Eb4Cd8ItcBf8CO6BX+le4JpB6hbMgO/COvA92Abug53hBzAPfgxPgvthD/gJ7A0PwAHwC3gmPAgnwm/h1fDv8G74PXwABnTPbxx8G8bDvTAB7odJsBZlmQKPhqmwCawNc2Ed2BPWhb1hJjwHZsNfwiZwNGwBZ8AOcBbMhbNhRzgHdoI3wZPg3XAALIdnwS1wINwG8+F+lR+Al8BE6tel8Cg4A3aB18FBcC4cDG+GE+A8WAZvhZfC2+BseCf8LVwAH4B3wcfg3fBxeA98Fi6Gr8B74VvwIbgFPgD/BB+EH6j54p/ZHsAfa/8fa4rsAfzv7/+r7t6/hbG1zNgTe2JP7Ik9sSf2xJ7YE3tiT+yJPbHn/+KJR4370df/J4SW//+jtf/Q3v89zMcve8xxmOGY0CE=
*/