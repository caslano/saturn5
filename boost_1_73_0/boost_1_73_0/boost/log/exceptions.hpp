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
6FDCVCY5iLbewkX/eosHSgT4GpUo4la2oK1uOtcxqUgVkgQ74jbjbIh9idT6QAJtUCMsPOCQ3gqw7Dg2c56E6QNWVOEJeeISTyyYzWP2zQp+yBOo+scOgOyqDjswegi6qH7DL/zL3OQeOeD0XOAYpALuWtOplwIC0zRL98o8jCR3BSUGzCUrMA/GWYcjyVW/nEEYsMf2lyyjMK+Htjz1c9FutTW/dncVENwHAE2mPjaCcwe9fdt2QzvcV66Kn49+0Q/F778Lp6XV9gNBWGghIdgYqbMpvGKFJxAsJl47toolmDv4IYRZnMHdTFHeQeapngMr0SjvQeJTTpHR42wOBnLvf+ZZJf2ZcI2QJx57wRjYzzidOxtVOsT40EAdf7laCuo4wgi1oDptsOLNj7rinrYZqwxYj5Sap/xgrEXXCoWLP011DH+4t7uUcVYL+mp8RbO/lpv1MM4RHbNsxGB3F8Ubvu3uNsdnWtQQgWeGVF4w59PveJEFrrgi9vT3CSB62nZ/GvVbijbqYZ1Lyio5ugaxcH3LwIHDTcBEtBwsXaC6sxgccnrbxUQ6pEQhLEnDqYfda2Pe2cnYNm59zAoNTmpVi2K4sDRdITjLc8SeCskCy0R0EE113zsCiRGTEMNU90AN2k0uPYc0XBd8
*/