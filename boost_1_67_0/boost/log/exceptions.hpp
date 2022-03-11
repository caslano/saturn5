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
    ~bad_alloc() throw();

    /*!
     * Error message accessor.
     */
    const char* what() const throw();

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
    ~capacity_limit_reached() throw();

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
    ~runtime_error() throw();
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
    ~missing_value() throw();

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
    ~invalid_type() throw();

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
    ~invalid_value() throw();

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
    ~parse_error() throw();

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
    ~conversion_error() throw();

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
    ~system_error() throw();

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
    ~logic_error() throw();

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
    ~odr_violation() throw();

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
    ~unexpected_call() throw();

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
    ~setup_error() throw();

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
    ~limitation_error() throw();

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