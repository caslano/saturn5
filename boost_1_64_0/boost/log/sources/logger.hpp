/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   logger.hpp
 * \author Andrey Semashev
 * \date   08.03.2007
 *
 * The header contains implementation of a simplistic logger with no features.
 */

#ifndef BOOST_LOG_SOURCES_LOGGER_HPP_INCLUDED_
#define BOOST_LOG_SOURCES_LOGGER_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/features.hpp>
#include <boost/log/sources/threading_models.hpp>
#if !defined(BOOST_LOG_NO_THREADS)
#include <boost/log/detail/light_rw_mutex.hpp>
#endif // !defined(BOOST_LOG_NO_THREADS)
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sources {

#ifdef BOOST_LOG_USE_CHAR

/*!
 * \brief Narrow-char logger. Functionally equivalent to \c basic_logger.
 *
 * See \c basic_logger class template for a more detailed description.
 */
class logger :
    public basic_composite_logger< char, logger, single_thread_model, features< > >
{
    BOOST_LOG_FORWARD_LOGGER_MEMBERS(logger)
};

#if !defined(BOOST_LOG_NO_THREADS)

/*!
 * \brief Narrow-char thread-safe logger. Functionally equivalent to \c basic_logger.
 *
 * See \c basic_logger class template for a more detailed description.
 */
class logger_mt :
    public basic_composite_logger< char, logger_mt, multi_thread_model< boost::log::aux::light_rw_mutex >, features< > >
{
    BOOST_LOG_FORWARD_LOGGER_MEMBERS(logger_mt)
};

#endif // !defined(BOOST_LOG_NO_THREADS)
#endif // BOOST_LOG_USE_CHAR

#ifdef BOOST_LOG_USE_WCHAR_T

/*!
 * \brief Wide-char logger. Functionally equivalent to \c basic_logger.
 *
 * See \c basic_logger class template for a more detailed description.
 */
class wlogger :
    public basic_composite_logger< wchar_t, wlogger, single_thread_model, features< > >
{
    BOOST_LOG_FORWARD_LOGGER_MEMBERS(wlogger)
};

#if !defined(BOOST_LOG_NO_THREADS)

/*!
 * \brief Wide-char thread-safe logger. Functionally equivalent to \c basic_logger.
 *
 * See \c basic_logger class template for a more detailed description.
 */
class wlogger_mt :
    public basic_composite_logger< wchar_t, wlogger_mt, multi_thread_model< boost::log::aux::light_rw_mutex >, features< > >
{
    BOOST_LOG_FORWARD_LOGGER_MEMBERS(wlogger_mt)
};

#endif // !defined(BOOST_LOG_NO_THREADS)
#endif // BOOST_LOG_USE_WCHAR_T

} // namespace sources

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SOURCES_LOGGER_HPP_INCLUDED_

/* logger.hpp
63gwFubCbnAWTFX9QNUPhufA4XAePAvOhxPhAng2XAhnwWWwAJbBIlgOq2EFvARWwhthFbwZVsNdcBX8AVwHP4FfgT0ox/UwHV4C+8FL4QB4GRwMN8JxcDmcDzfBQrgZ1sAtcFfLt8ZPyTpSqGtIzV0/6tOyztLya/m1/Fp+Lb+W35fz/i9ni2UF4Au//3dwvf9v1vluuzo4bfU8Ytp0/3nE/Orq/Avyisvc9xkVkErrN+TxF3z2EJ/2b6LiNrQzloH3EEncQecAJY7AezQj9Dyo1+cWBQuGMt82+SqkSFbVFuetmTF2EvZmzaKGD3znV+PFnNOeKX7e9Uwlh285R235Jtzg+yvWmPtTbxO7Kz2VnghbORi/CXJeUu+3z5P7wK1rIO64qsJlDcSsDbSZGXiv2GfidjzNhXsjdC1jrph97BlLC7rHSUcG/JfO/Z7OYp+AzbgZ2CNJ3pOSPY03nSJnNOc6ImWN4ihrFJFin+tJ8nRy3V9/vjlfOljs/+S8TI28QRzuO3rd31R6WNJR7jnXE2nOT/eU9A90+fHdZ15/d0KWhJ3thJOyRONmTWlFUeUa3zVgaMxZ0yHi9ihrNeHmrPpICb+rK/ya0uUV9eH/UNK0wJPijPT4zwnfKeHUpTHepLG9lMcJyuOg+LnCM8vjvl+4onitXtybqGtTAyWcY85NhHUw4NuRUtcS3jHCe0/CK/VkUr716SwqXU5giZrO+RLWc04qeZvtlJm0/UHM2zuDWP+J1jOMO+ldFyfJ3U3y9wYU6ztQlDmD3aGJdZ3Rvnzrwliie13H9BncBZ7PNd/Ip12j13Yd1FfX6sVuE1ERKqMw03fX08z6vlp1Qf09T21NP6lcRTy2/ohfHYdMv+Z71a6293uxP91pbb+DA/9B4xjtZF1xfTs5LPbx9EevrY/iv3l3t0r5aH4S3GtkpLvhfVmSlsDvrbQKvAumld4vn53rL0O+iSR3eTb9vZHs3NDG5ZN9b2RHI+nJDUgP976E8P2T3FOQnj6aEE0WNsjMZLDuE5AeaWJNpmfpF0iPv80faR30XR+9t6DKpKeG9OSXlcn9ePZ7dmpzG/22j4bjsd49uUbsOoWcfj17H3A/2wBdAuht5H5Ze6LP7gpIf00t11QXarHa72AQ991tedCwPK7+LgHZ+iturf3V5Plb/2TvPOCjKtIA/t7uJrRACpBQQyD0moSINIFQQw9FmkIgFKlJCAlNVFBE7NhA0bOCoIJi74qKioqK5U7vLIf1rHdYD2zcfz++nbzdTCDceV75ZfkN/8x8097U96aKPMFaV9Wt5w7oYz3vVM8lMPVY4nnUOvtTdfuZ5Xs9aWg5Z8l+B0SZ5xd39nuQjrH8Ws9eUP+9z5OjD5Kr9WsKanSwHfc8j9Yx61nRH4m9ifjn2tv0YygP2I28v5e7IcLPIPpM7Ixx2tvbcPXDnDHE/n7pLykfFb8/8UjlIzGsfJj4hbUT22LKnn06rBNt0CiTppSrglm5fQcPGnHi8KPm6W85j1LnhaA/d+98IVAQc+rnhR+nf9H/vtvur5xH+X+aR0kLfcfBWMv61L26PvUVKN+W8Gu4Awd91F2izr90Rm3S79EkXU+cDJvCJjATpsCusCnMgs3gQNgCjoEt4UR4PpwM28AFsCMshhlwHewCb4A94BbYEz4Ds+DzsC/8M+wHP4ED4JdwIPwBngF9xHUQrAuHwCQ4AjaCo2EzeCLsBCfD7nAGHAfnwAmwEObBxXAZXAbPhafqfMsK+Dt4GrwOroKb4ZnwUXgWfAqeDZ+Da+Ar8Hz4e7gQvgGL4B/hTPgWnAXfgcfDP8Ou8D3YDh6E58IY8uU8mADPN/ts9d0WDrA=
*/