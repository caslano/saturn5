/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file
 * \author Andrey Semashev
 * \date   31.10.2009
 *
 * The header contains exception classes declarations.
 */

#ifndef BOOST_LOG_EXCEPTIONS_HPP_INCLUDED_
#define BOOST_LOG_EXCEPTIONS_HPP_INCLUDED_

#include <cstddef>
#include <string>
#include <stdexcept>
#include <boost/type_index.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

// Forward-declaration of an exception base class from Boost.Exception
#if defined(__GNUC__)
#   if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#       pragma GCC visibility push (default)

class exception;

#       pragma GCC visibility pop
#   else

class exception;

#   endif
#else

class BOOST_SYMBOL_VISIBLE exception;

#endif

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! Attaches attribute name exception information
BOOST_LOG_API void attach_attribute_name_info(exception& e, attribute_name const& name);

} // namespace aux

/*!
 * \brief Base class for memory allocation errors
 *
 * Exceptions derived from this class indicate problems with memory allocation.
 */
class BOOST_LOG_API bad_alloc :
    public std::bad_alloc
{
private:
    std::string m_message;

public:
    /*!
     * Initializing constructor. Creates an exception with the specified error message.
     */
    explicit bad_alloc(const char* descr);
    /*!
     * Initializing constructor. Creates an exception with the specified error message.
     */
    explicit bad_alloc(std::string const& descr);
    /*!
     * Destructor
     */
    ~bad_alloc() throw() BOOST_OVERRIDE;

    /*!
     * Error message accessor.
     */
    const char* what() const throw() BOOST_OVERRIDE;

#ifndef BOOST_LOG_DOXYGEN_PASS
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, const char* descr);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, std::string const& descr);
#endif
};

/*!
 * \brief The exception is used to indicate reaching a storage capacity limit
 */
class BOOST_LOG_API capacity_limit_reached :
    public bad_alloc
{
public:
    /*!
     * Initializing constructor. Creates an exception with the specified error message.
     */
    explicit capacity_limit_reached(const char* descr);
    /*!
     * Initializing constructor. Creates an exception with the specified error message.
     */
    explicit capacity_limit_reached(std::string const& descr);
    /*!
     * Destructor
     */
    ~capacity_limit_reached() throw() BOOST_OVERRIDE;

#ifndef BOOST_LOG_DOXYGEN_PASS
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, const char* descr);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, std::string const& descr);
#endif
};

/*!
 * \brief Base class for runtime exceptions from the logging library
 *
 * Exceptions derived from this class indicate a problem that may not directly
 * be caused by the user's code that interacts with the library, such as
 * errors caused by input data.
 */
class BOOST_LOG_API runtime_error :
    public std::runtime_error
{
public:
    /*!
     * Initializing constructor. Creates an exception with the specified error message.
     */
    explicit runtime_error(std::string const& descr);
    /*!
     * Destructor
     */
    ~runtime_error() throw() BOOST_OVERRIDE;
};

/*!
 * \brief Exception class that is used to indicate errors of missing values
 */
class BOOST_LOG_API missing_value :
    public runtime_error
{
public:
    /*!
     * Default constructor. Creates an exception with the default error message.
     */
    missing_value();
    /*!
     * Initializing constructor. Creates an exception with the specified error message.
     */
    explicit missing_value(std::string const& descr);
    /*!
     * Destructor
     */
    ~missing_value() throw() BOOST_OVERRIDE;

#ifndef BOOST_LOG_DOXYGEN_PASS
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, const char* descr);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, std::string const& descr);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, const char* descr, attribute_name const& name);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, std::string const& descr, attribute_name const& name);
#endif
};

/*!
 * \brief Exception class that is used to indicate errors of incorrect type of an object
 */
class BOOST_LOG_API invalid_type :
    public runtime_error
{
public:
    /*!
     * Default constructor. Creates an exception with the default error message.
     */
    invalid_type();
    /*!
     * Initializing constructor. Creates an exception with the specified error message.
     */
    explicit invalid_type(std::string const& descr);
    /*!
     * Destructor
     */
    ~invalid_type() throw() BOOST_OVERRIDE;

#ifndef BOOST_LOG_DOXYGEN_PASS
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, const char* descr);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, std::string const& descr);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, const char* descr, attribute_name const& name);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, std::string const& descr, attribute_name const& name);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, const char* descr, typeindex::type_index const& type);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, std::string const& descr, typeindex::type_index const& type);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, const char* descr, attribute_name const& name, typeindex::type_index const& type);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, std::string const& descr, attribute_name const& name, typeindex::type_index const& type);
#endif
};

/*!
 * \brief Exception class that is used to indicate errors of incorrect value of an object
 */
class BOOST_LOG_API invalid_value :
    public runtime_error
{
public:
    /*!
     * Default constructor. Creates an exception with the default error message.
     */
    invalid_value();
    /*!
     * Initializing constructor. Creates an exception with the specified error message.
     */
    explicit invalid_value(std::string const& descr);
    /*!
     * Destructor
     */
    ~invalid_value() throw() BOOST_OVERRIDE;

#ifndef BOOST_LOG_DOXYGEN_PASS
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, const char* descr);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, std::string const& descr);
#endif
};

/*!
 * \brief Exception class that is used to indicate parsing errors
 */
class BOOST_LOG_API parse_error :
    public runtime_error
{
public:
    /*!
     * Default constructor. Creates an exception with the default error message.
     */
    parse_error();
    /*!
     * Initializing constructor. Creates an exception with the specified error message.
     */
    explicit parse_error(std::string const& descr);
    /*!
     * Destructor
     */
    ~parse_error() throw() BOOST_OVERRIDE;

#ifndef BOOST_LOG_DOXYGEN_PASS
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, const char* descr);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, std::string const& descr);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, const char* descr, std::size_t content_line);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, std::string const& descr, std::size_t content_line);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, const char* descr, attribute_name const& name);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, std::string const& descr, attribute_name const& name);
#endif
};

/*!
 * \brief Exception class that is used to indicate conversion errors
 */
class BOOST_LOG_API conversion_error :
    public runtime_error
{
public:
    /*!
     * Default constructor. Creates an exception with the default error message.
     */
    conversion_error();
    /*!
     * Initializing constructor. Creates an exception with the specified error message.
     */
    explicit conversion_error(std::string const& descr);
    /*!
     * Destructor
     */
    ~conversion_error() throw() BOOST_OVERRIDE;

#ifndef BOOST_LOG_DOXYGEN_PASS
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, const char* descr);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, std::string const& descr);
#endif
};

/*!
 * \brief Exception class that is used to indicate underlying OS API errors
 */
class BOOST_LOG_API system_error :
    public boost::system::system_error
{
public:
    /*!
     * Initializing constructor. Creates an exception with the specified error message.
     */
    system_error(boost::system::error_code code, std::string const& descr);
    /*!
     * Destructor
     */
    ~system_error() throw() BOOST_OVERRIDE;

#ifndef BOOST_LOG_DOXYGEN_PASS
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, const char* descr, int system_error_code);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, std::string const& descr, int system_error_code);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, const char* descr, boost::system::error_code code);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, std::string const& descr, boost::system::error_code code);
#endif
};

/*!
 * \brief Base class for logic exceptions from the logging library
 *
 * Exceptions derived from this class usually indicate errors on the user's side, such as
 * incorrect library usage.
 */
class BOOST_LOG_API logic_error :
    public std::logic_error
{
public:
    /*!
     * Initializing constructor. Creates an exception with the specified error message.
     */
    explicit logic_error(std::string const& descr);
    /*!
     * Destructor
     */
    ~logic_error() throw() BOOST_OVERRIDE;

#ifndef BOOST_LOG_DOXYGEN_PASS
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, const char* descr);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, std::string const& descr);
#endif
};

/*!
 * \brief Exception class that is used to indicate ODR violation
 */
class BOOST_LOG_API odr_violation :
    public logic_error
{
public:
    /*!
     * Default constructor. Creates an exception with the default error message.
     */
    odr_violation();
    /*!
     * Initializing constructor. Creates an exception with the specified error message.
     */
    explicit odr_violation(std::string const& descr);
    /*!
     * Destructor
     */
    ~odr_violation() throw() BOOST_OVERRIDE;

#ifndef BOOST_LOG_DOXYGEN_PASS
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, const char* descr);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, std::string const& descr);
#endif
};

/*!
 * \brief Exception class that is used to indicate invalid call sequence
 */
class BOOST_LOG_API unexpected_call :
    public logic_error
{
public:
    /*!
     * Default constructor. Creates an exception with the default error message.
     */
    unexpected_call();
    /*!
     * Initializing constructor. Creates an exception with the specified error message.
     */
    explicit unexpected_call(std::string const& descr);
    /*!
     * Destructor
     */
    ~unexpected_call() throw() BOOST_OVERRIDE;

#ifndef BOOST_LOG_DOXYGEN_PASS
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, const char* descr);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, std::string const& descr);
#endif
};

/*!
 * \brief Exception class that is used to indicate invalid library setup
 */
class BOOST_LOG_API setup_error :
    public logic_error
{
public:
    /*!
     * Default constructor. Creates an exception with the default error message.
     */
    setup_error();
    /*!
     * Initializing constructor. Creates an exception with the specified error message.
     */
    explicit setup_error(std::string const& descr);
    /*!
     * Destructor
     */
    ~setup_error() throw() BOOST_OVERRIDE;

#ifndef BOOST_LOG_DOXYGEN_PASS
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, const char* descr);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, std::string const& descr);
#endif
};

/*!
 * \brief Exception class that is used to indicate library limitation
 */
class BOOST_LOG_API limitation_error :
    public logic_error
{
public:
    /*!
     * Default constructor. Creates an exception with the default error message.
     */
    limitation_error();
    /*!
     * Initializing constructor. Creates an exception with the specified error message.
     */
    explicit limitation_error(std::string const& descr);
    /*!
     * Destructor
     */
    ~limitation_error() throw() BOOST_OVERRIDE;

#ifndef BOOST_LOG_DOXYGEN_PASS
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, const char* descr);
    static BOOST_LOG_NORETURN void throw_(const char* file, std::size_t line, std::string const& descr);
#endif
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#ifndef BOOST_LOG_DOXYGEN_PASS

#define BOOST_LOG_THROW(ex)\
    ex::throw_(__FILE__, static_cast< std::size_t >(__LINE__))

#define BOOST_LOG_THROW_DESCR(ex, descr)\
    ex::throw_(__FILE__, static_cast< std::size_t >(__LINE__), descr)

#define BOOST_LOG_THROW_DESCR_PARAMS(ex, descr, params)\
    ex::throw_(__FILE__, static_cast< std::size_t >(__LINE__), descr, BOOST_PP_SEQ_ENUM(params))

#endif // BOOST_LOG_DOXYGEN_PASS

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXCEPTIONS_HPP_INCLUDED_

/* exceptions.hpp
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
*/