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
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
*/