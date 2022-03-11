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
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
*/