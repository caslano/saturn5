//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_CSTDLIB_HPP_INCLUDED
#define BOOST_NOWIDE_CSTDLIB_HPP_INCLUDED

#include <boost/nowide/config.hpp>
#if !defined(BOOST_WINDOWS)
#include <cstdlib>
#endif

namespace boost {
namespace nowide {
#if !defined(BOOST_WINDOWS) && !defined(BOOST_NOWIDE_DOXYGEN)
    using std::getenv;
    using std::system;
#else
    ///
    /// \brief UTF-8 aware getenv. Returns 0 if the variable is not set.
    ///
    /// This function is not thread safe or reenterable as defined by the standard library
    ///
    BOOST_NOWIDE_DECL char* getenv(const char* key);

    ///
    /// Same as std::system but cmd is UTF-8.
    ///
    BOOST_NOWIDE_DECL int system(const char* cmd);

#endif
    ///
    /// \brief Set environment variable \a key to \a value
    ///
    /// if overwrite is not 0, that the old value is always overwritten, otherwise,
    /// if the variable exists it remains unchanged
    ///
    /// \a key and \a value are UTF-8 on Windows
    /// \return zero on success, else nonzero
    ///
    BOOST_NOWIDE_DECL int setenv(const char* key, const char* value, int overwrite);

    ///
    /// \brief Remove environment variable \a key
    ///
    /// \a key is UTF-8 on Windows
    /// \return zero on success, else nonzero
    ///
    BOOST_NOWIDE_DECL int unsetenv(const char* key);

    ///
    /// \brief Adds or changes an environment variable, \a string must be in format KEY=VALUE
    ///
    /// \a string MAY become part of the environment, hence changes to the value MAY change
    /// the environment. For portability it is hence recommended NOT to change it.
    /// \a string is UTF-8 on Windows
    /// \return zero on success, else nonzero
    ///
    BOOST_NOWIDE_DECL int putenv(char* string);

} // namespace nowide
} // namespace boost

#endif

/* cstdlib.hpp
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
*/