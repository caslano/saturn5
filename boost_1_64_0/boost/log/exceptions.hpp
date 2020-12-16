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
xL15hvTcIfG6CdaFN8MO8BbYCd4t+fwb2BPugqPh7XCcmI+Hd8ICuQ74a13gnY9fir9fib9fwyT4D0m3WvJ8/pPrXtDieiIIg5lingUjJB+51v6WiL+zDf7+Rfw9Kv5+KPE9JvH9VOL7scT3E4lvucT3U4nvcZgv1+KvzDfGT4O/HaXcdpJymyTPbWcprykS366wF0yW+HaT+KZIfHvAXLnW8RV/pxj8TRN/e4m/veV56SPPyyCpD/vBnrA/HA3PguPEfDwcCCfLtc5fmeM43eDvaPF3jPg7VvwdJ/5mib8TxN+J4m+G+Jsl/mZKfZyl/UU8/YXib4H4O0/8nS/+LhF/C8Xfc8XfheLvEvF3MZwm19JOMcfSu1++WsrVGhgJz4fSXsgcP+4Z2ourcb8OvF7aqW2wGbwRToU74HS5Xi3Xco62zDdT89sqnaPdTuqJjlJPdIJtYBJsDwdKue8Cu8GucDhMhqPEfAzsAfNgCpwLe8J1MBWuF70NsDe8GPaBV8G+8BbYD94merfDAfBuudb5ucG7frpc0vUKeV5LJNxXyfN6vTyvW+R5vVqe12vgODEfD6+FBXIt34Flvg52EPd34Gcl/Z6Tdu958ecFqV//LPX6S/BMeBgOga/AYfAInAH/BBfDN+Bm+Ba8TOxfDsvgFrk+Drfq+STkuYQrDsGO+t0r4doj4dor7fH9Er6nYFf4e5gGH4Bj4X44Ucwz4ENwPnwEroGPwivh4/Bq0bsGPglvkGvdnmz0rm8ukPy6UPLrIsmvDZJfmyWcGyW/Nkl+XQzHifl4eCmcLNfSPsvcAtw0tM/Lw/3pshLGwVXSHzoPpsD18ryvgenwfDhSrsfBi+BM0ZsF18rztg5eKPflvVLGqOlzGN4rfy71z2VS/1wO42GJ2E/XY7Pq3bvSufFD5T19GIyBOTAezoAJkDDqcJSLO40N4Tgq4fgQxsCPYCw8JuHYbslYJSwS+/WRLWL/EfTC4aMwCj4BW8AnYQI8ANvCP0r7dRB2h8/DwfCQ9LtekPr0NTgFvg7VcyHp/TLMF/NzxXypmHPub0hn89pn+LbcG/U/e0bv6Tqf9z/lbN4f+1xe95m8ew5GWWVIxLNRViIyAMlBipFtyOPIUST2uSirF5KDrEd2IYeQE0jL5wkjUoxsRR5HjiIRh6KsJCQDWY1sRw4g5UjTFygDyCKkBNmDvIGcRFq+yDnBSDZShFyG7ELKkEYvRVmjkAVICbIHOYJ8gzQ9TBiRRch25DDyDZL4MvFCZiKbX/5xzhv+Uc7/W2ivjLFPAPx+5/+1tWLrr7bnv98WxvcJCUMu7rNtkiy+UTqTU2jbabjC2R9jXj67sDp1LEudIxjX2tJze/bLeXkfy/ePY0hWKvXtPJnbM2xUbmC6Cc449oJaurLYuMeU2JX5Vist0ZX9ogNrWzLn2zpNnHPGxJ5zHqVeF7NytvLdPHdM7Dn2+iqYg7ae53m3Mp9vdSXlpyLx9loUbe8CdZJRAaLnmLncnJRquzl22AirYr++JBX+Lsxmqmucc+a0n6gmLq0omCP2m8Lhyv5wKxoNx7oZ0kt0Jb0C83jG2frkGrWHDv9ryo89hLwDY0r1g+ZxI3o/oAjr1HN51d5akqfxznmKOu+479zXQ+eJzEnT+5uptNdze0k77knayVoZ0oN7xFHc1PPZdLxlDxcVZ/rkcibRYLme5FqjtloimCARa4WUoHNI6cteabIHmGxsofLl8lS995cul4eVnXhTuca9U+9r4TXfC7/0vmDOPc2La/Gf0uMnfZpfomstMISdhetBD6MhHqZw45Yui1cq3aI5C5VdWW+KOabmdaILqrdOzxFPPd/1Svue8tM=
*/