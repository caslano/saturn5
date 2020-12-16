/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   global_logger_storage.hpp
 * \author Andrey Semashev
 * \date   21.04.2008
 *
 * The header contains implementation of facilities to declare global loggers.
 */

#ifndef BOOST_LOG_SOURCES_GLOBAL_LOGGER_STORAGE_HPP_INCLUDED_
#define BOOST_LOG_SOURCES_GLOBAL_LOGGER_STORAGE_HPP_INCLUDED_

#include <stdexcept>
#include <boost/type_index.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/singleton.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sources {

namespace aux {

//! The base class for logger holders
struct logger_holder_base
{
    //! The source file name where the logger was registered
    const char* const m_RegistrationFile;
    //! The line number where the logger was registered
    const unsigned int m_RegistrationLine;
    //! Stored logger type
    const typeindex::type_index m_LoggerType;

    logger_holder_base(const char* file, unsigned int line, typeindex::type_index logger_type) BOOST_NOEXCEPT :
        m_RegistrationFile(file),
        m_RegistrationLine(line),
        m_LoggerType(logger_type)
    {
    }
};

//! The actual logger holder class
template< typename LoggerT >
struct logger_holder :
    public logger_holder_base
{
    //! The logger instance
    LoggerT m_Logger;

    logger_holder(const char* file, unsigned int line, LoggerT const& logger) :
        logger_holder_base(file, line, typeindex::type_id< LoggerT >()),
        m_Logger(logger)
    {
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    logger_holder(const char* file, unsigned int line, LoggerT&& logger) :
        logger_holder_base(file, line, typeindex::type_id< LoggerT >()),
        m_Logger(static_cast< LoggerT&& >(logger))
    {
    }
#endif
};

//! The class implements a global repository of tagged loggers
struct global_storage
{
    typedef shared_ptr< logger_holder_base >(*initializer_t)();

    //! Finds or creates the logger and returns its holder
    BOOST_LOG_API static shared_ptr< logger_holder_base > get_or_init(typeindex::type_index key, initializer_t initializer);

    //  Non-constructible, non-copyable, non-assignable
    BOOST_DELETED_FUNCTION(global_storage())
    BOOST_DELETED_FUNCTION(global_storage(global_storage const&))
    BOOST_DELETED_FUNCTION(global_storage& operator= (global_storage const&))
};

//! Throws the \c odr_violation exception
BOOST_LOG_API BOOST_LOG_NORETURN void throw_odr_violation(
    typeindex::type_index tag_type,
    typeindex::type_index logger_type,
    logger_holder_base const& registered);

//! The class implements a logger singleton
template< typename TagT >
struct logger_singleton :
    public boost::log::aux::lazy_singleton<
        logger_singleton< TagT >,
        shared_ptr< logger_holder< typename TagT::logger_type > >
    >
{
    //! Base type
    typedef boost::log::aux::lazy_singleton<
        logger_singleton< TagT >,
        shared_ptr< logger_holder< typename TagT::logger_type > >
    > base_type;
    //! Logger type
    typedef typename TagT::logger_type logger_type;

    //! Returns the logger instance
    static logger_type& get()
    {
        return base_type::get()->m_Logger;
    }

    //! Initializes the logger instance (called only once)
    static void init_instance()
    {
        shared_ptr< logger_holder< logger_type > >& instance = base_type::get_instance();
        const typeindex::type_index tag_type_index = typeindex::type_id< TagT >();
        shared_ptr< logger_holder_base > holder = global_storage::get_or_init(tag_type_index, &logger_singleton::construct_logger);
        const typeindex::type_index logger_type_index = typeindex::type_id< logger_type >();
        if (holder->m_LoggerType == logger_type_index)
        {
            // Note: dynamic_cast may fail here if logger_type is not visible (for example, with Clang on Linux, if the original logger
            //       instance was initialized in a different DSO than where it's being queried). logger_holder visibility doesn't
            //       have effect since it is inhibited by the template parameter visibility.
            instance = boost::static_pointer_cast< logger_holder< logger_type > >(holder);
        }
        else
        {
            // In pure C++ this should never happen, since there cannot be two
            // different tag types that have equal type_infos. In real life it can
            // happen if the same-named tag is defined differently in two or more
            // dlls. This check is intended to detect such ODR violations. However, there
            // is no protection against different definitions of the logger type itself.
            boost::log::sources::aux::throw_odr_violation(tag_type_index, logger_type_index, *holder);
        }
    }

private:
    //! Constructs a logger holder
    static shared_ptr< logger_holder_base > construct_logger()
    {
        return boost::make_shared< logger_holder< logger_type > >(
            TagT::registration_file(),
            static_cast< unsigned int >(TagT::registration_line),
            TagT::construct_logger());
    }
};

} // namespace aux

//! The macro forward-declares a global logger with a custom initialization
#define BOOST_LOG_GLOBAL_LOGGER(tag_name, logger)\
    struct tag_name\
    {\
        typedef logger logger_type;\
        enum registration_line_t { registration_line = __LINE__ };\
        static const char* registration_file() { return __FILE__; }\
        static logger_type construct_logger();\
        static inline logger_type& get()\
        {\
            return ::boost::log::sources::aux::logger_singleton< tag_name >::get();\
        }\
    };

//! The macro defines a global logger initialization routine
#define BOOST_LOG_GLOBAL_LOGGER_INIT(tag_name, logger)\
    tag_name::logger_type tag_name::construct_logger()

//! The macro defines a global logger initializer that will default-construct the logger
#define BOOST_LOG_GLOBAL_LOGGER_DEFAULT(tag_name, logger)\
    BOOST_LOG_GLOBAL_LOGGER_INIT(tag_name, logger)\
    {\
        return logger_type();\
    }

//! The macro defines a global logger initializer that will construct the logger with the specified constructor arguments
#define BOOST_LOG_GLOBAL_LOGGER_CTOR_ARGS(tag_name, logger, args)\
    BOOST_LOG_GLOBAL_LOGGER_INIT(tag_name, logger)\
    {\
        return logger_type(BOOST_PP_SEQ_ENUM(args));\
    }

//! The macro declares a global logger with a custom initialization
#define BOOST_LOG_INLINE_GLOBAL_LOGGER_INIT(tag_name, logger)\
    BOOST_LOG_GLOBAL_LOGGER(tag_name, logger)\
    inline BOOST_LOG_GLOBAL_LOGGER_INIT(tag_name, logger)

//! The macro declares a global logger that will be default-constructed
#define BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(tag_name, logger)\
    BOOST_LOG_INLINE_GLOBAL_LOGGER_INIT(tag_name, logger)\
    {\
        return logger_type();\
    }

//! The macro declares a global logger that will be constructed with the specified arguments
#define BOOST_LOG_INLINE_GLOBAL_LOGGER_CTOR_ARGS(tag_name, logger, args)\
    BOOST_LOG_INLINE_GLOBAL_LOGGER_INIT(tag_name, logger)\
    {\
        return logger_type(BOOST_PP_SEQ_ENUM(args));\
    }

} // namespace sources

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SOURCES_GLOBAL_LOGGER_STORAGE_HPP_INCLUDED_

/* global_logger_storage.hpp
3rzx5/LPtVx/oeX6KvTXb7b6626pX4/688J4GAaTYaTWR4TWB3rz/KvS8C63PP96aXuh7iS8/rA3HKjz/yFwEhwGZ8BRsBiOhuXwTLgRjoHa71XWl3xY+v1BnX+9DFPhL3U++QocDH8O5f0GjlF7fz1XabgXWOp5p4Z7u85bv6nzuTthHLwLdoF7YHd4D8yA92q892m8e+F4+ACcDB+EU+HD8Fz4HbgWPga1nlX+kueTpZ6/pfX1sD5nv+2af2Wrv7GWcaRKx/M1MB6u1XnIRbAHvBhmwK/A3nA97K/2w+ClcBS8DGbBDTBb9ZpulcejrVjSPUvbxTwYAee76nef+htlqd9HNL+Pwlj4mI4Xj2s7fQKmwCfhSLgf+tfJnFJdh7Csk10bpuMqlHEVyriq/ncY+Sjs1H8caov6j9Z1hHawLYzTcovXfp+kz8NO2v87w7NgF1gAu8FimAKXwQR4PmwPV6p5NewIa2Ei3KzhHoe7jPwPcxxNX7xr7TJd89cHJsK+2o/7wQzVD4KDtNwGw2yYCSeqfjocDovhCFgC+8My1VfBIXC16teo+52q13ap8hnMdSztMkrT2VbT2Q52hnEwHSZreuPhEJgAh8P2mu4O8DS1Hw+T4CT1p+OVyhyQJ8t49Q+Nn8Yh651eGAPDYByMgJ1UnwJbw+4wGvaGMXAQbAN1vNX9e8oGlRw03t7h1XkulHFFnxv3aju6C6brOoSWH3vhjc8PJnjq2uFkHZdyYFc4BfaEc2G6z6+uK02Do+B0mA1nwnEwF06Ec3R8wp/En+bRPWPd/16qzxHmpPL7m/brf+j85DN9T3N0PBwNe0MvHAbD4NkwHM5Q+5mwlX8dFM5XfSWMgpthNNwCY+BuGAvvUv93wzh4L0yAD8D2cD9Mhc/CNPg87A5fhD3gS7AnPATT4S9gBvwd7A0dD/0ERsL+MBYOhHEwC3aAxK/jmO57wuGWcew+Lae9MBreD7vAfTAFPghTVT9M9WZc1XCTLOPqqxrur2EifN01ru5Xf7mW9HxEu/fAj2F7+HfYUfV9VN9X9TNVv8tb/w2oAV+PdnJQRaiNqN2oF1BHULHfiG75RtQX+EbUjsuiQ/5OVPr10c3+VtQA6icHVYLaiNqF2o96E/UhKu5Wvh2FmoYqQm1A3YJ6GHUIdRQVvos0orJQc1BVqC2o+1DPol5DfYjqcFu0k4mahipCbUDtQj2Beg31IarD7dHOcFQuqgy1EbUb9QTqVdQJVNwd0U4fVA6qCLURdQvqEdRrqBOo2N0t37Zq+bX8Wn4tv5Zfy6/l9+X8vpTv/62orqzwfQDwC37/z/f9u4SejpFHLNJvta3y1r1f1MAPeXGtmqXn8yTi4sIVxdVN3lOHn+CzizbZQtxZzyIbmeENYp9qPevh9lvrBN530x72OMdnn+e0I0U9VObwcvGzxPsdJHL+QeraeqJ5793LXk39fWz3zcYNb3P14RZXs/4iYSTDqySMOd4h7FpNR72JWu2JcMK8Ea47iccaueAd4n6yN+BOJk3P6RLXFk83pL77ebzOEM98J0HTMVDsHvGsd7qQFnPXcbn7fMTXJI/xrnjHmbK7VeId653nLJK4+pGY/qp2q0KuTWTP5iXVqad71KkXU8QuQP9hYp3ZfNwNRTV9Z3RE/POSPqe4oqjpc756jsl9BlxkaKePZm1PzuLW5hc4X+63+98WGc9PCrbe/u74WwcuXhJ56cacpRn/ehnPlm/3fznf7pf1XY+OJTr2LYWZIidizinLenNPmArTYQZEyXpuL9336gtzYT84Dw6AZXAgrIZZcD0cDbfA0+D1cAy8F2bDvXAsfEjlHw6q3MMRmAM/U3mHCA8=
*/