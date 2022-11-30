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
    template< BOOST_PP_ENUM_PARAMS_Z(z, n, typename T), typename HandlerT >\
    inline exception_handler<\
        BOOST_PP_CAT(mpl::vector, n)< BOOST_PP_ENUM_PARAMS_Z(z, n, T) >,\
        HandlerT\
    > make_exception_handler(HandlerT const& handler)\
    {\
        typedef exception_handler<\
            BOOST_PP_CAT(mpl::vector, n)< BOOST_PP_ENUM_PARAMS_Z(z, n, T) >,\
            HandlerT\
        > eh_t;\
        return eh_t(handler);\
    }\
    template< BOOST_PP_ENUM_PARAMS_Z(z, n, typename T), typename HandlerT >\
    inline nothrow_exception_handler<\
        BOOST_PP_CAT(mpl::vector, n)< BOOST_PP_ENUM_PARAMS_Z(z, n, T) >,\
        HandlerT\
    > make_exception_handler(HandlerT const& handler, std::nothrow_t const&)\
    {\
        typedef nothrow_exception_handler<\
            BOOST_PP_CAT(mpl::vector, n)< BOOST_PP_ENUM_PARAMS_Z(z, n, T) >,\
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