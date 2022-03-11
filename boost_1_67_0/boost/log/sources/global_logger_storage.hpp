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